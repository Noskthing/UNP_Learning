#include "unp.h"

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	SIG	SIGUSR1

static void
diec(int error, const char *msg)
{

	fprintf(stderr, "%s: %s\n", msg, strerror(error));
	err_sys("diec error");
}

static void
die(const char *msg)
{

	diec(errno, msg);
}

static int
do_sendmsg(int fd, const char *sockpath)
{
	struct sockaddr_storage sockaddr;
	struct sockaddr_un *addr;
	struct msghdr msg;
	struct cmsghdr *cmsghdr;
	struct iovec iov[1];
	ssize_t nbytes;
	char buf[CMSG_SPACE(sizeof(struct cmsgcred))], c;

	addr = (struct sockaddr_un *)&sockaddr;
	addr->sun_family = AF_LOCAL;
	strlcpy(addr->sun_path, sockpath, sizeof(addr->sun_path));
	addr->sun_len = SUN_LEN(addr);

	c = '*';
	iov[0].iov_base = &c;
	iov[0].iov_len = sizeof(c);
	memset(buf, 0x0b, sizeof(buf));
	cmsghdr = (struct cmsghdr *)buf;
	cmsghdr->cmsg_len = CMSG_LEN(sizeof(struct cmsgcred));
	cmsghdr->cmsg_level = SOL_SOCKET;
	cmsghdr->cmsg_type = SCM_CREDS;
#if 0
	msg.msg_name = addr;
	msg.msg_namelen = addr->sun_len;
#else
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
#endif
	msg.msg_iov = iov;
	msg.msg_iovlen = sizeof(iov) / sizeof(iov[0]);
	msg.msg_control = cmsghdr;
	msg.msg_controllen = CMSG_SPACE(sizeof(struct cmsgcred));
	msg.msg_flags = 0;

	nbytes = sendmsg(fd, &msg, 0);
	if (nbytes == -1)
		return (1);

	return (0);
}

static int
server_main(pid_t ppid, const char *sockpath)
{
	struct sockaddr_storage storage;
	struct sockaddr_un *addr;
	int error, s, sock;

	sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock == -1)
		die("socket(2)");
	addr = (struct sockaddr_un *)&storage;
	addr->sun_family = AF_LOCAL;
	strlcpy(addr->sun_path, sockpath, sizeof(addr->sun_path));
	addr->sun_len = SUN_LEN(addr);
	if (bind(sock, (struct sockaddr *)addr, addr->sun_len) == -1)
		die("bind(2)");
	if (listen(sock, 0) == -1)
		goto fail;
	if (kill(ppid, SIG) == -1)
		goto fail;
	if ((s = accept(sock, NULL, 0)) == -1)
		goto fail;

	if (do_sendmsg(s, sockpath) != 0)
		goto fail;

	if (close(s) == -1)
		goto fail;
	if (close(sock) == -1)
		goto fail;
	if (unlink(sockpath) == -1)
		goto fail;

	return (0);

fail:
	error = errno;
	unlink(sockpath);
	diec(error, "");

	/* NOTREACHED */
	return (1);
}

static int
do_recvmsg(int fd)
{
	struct msghdr msg;
	struct cmsghdr *cmsghdr;
	struct cmsgcred *cmsgcred;
	struct iovec iov[1];
	ssize_t nbytes;
	int i;
	char buf[CMSG_SPACE(sizeof(struct cmsgcred))], c;

	iov[0].iov_base = &c;
	iov[0].iov_len = sizeof(c);
	memset(buf, 0x0d, sizeof(buf));
	cmsghdr = (struct cmsghdr *)buf;
	cmsghdr->cmsg_len = CMSG_LEN(sizeof(struct cmsgcred));
	cmsghdr->cmsg_level = SOL_SOCKET;
	cmsghdr->cmsg_type = SCM_CREDS;
#if 0
	msg.msg_name = &sockaddr;
	msg.msg_namelen = sizeof(sockaddr);
#else
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
#endif
	msg.msg_iov = iov;
	msg.msg_iovlen = sizeof(iov) / sizeof(iov[0]);
	msg.msg_control = cmsghdr;
	msg.msg_controllen = CMSG_SPACE(sizeof(struct cmsgcred));
	msg.msg_flags = 0;

	nbytes = recvmsg(fd, &msg, 0);
	if (nbytes == -1)
		return (1);

	printf("nbytes=%ld\n", nbytes);
	printf("c=%d\n", msg.msg_controllen);
	cmsgcred = (struct cmsgcred *)CMSG_DATA(buf);
	printf("cmcred_pid=%d\n", cmsgcred->cmcred_pid);
	printf("cmcred_uid=%d\n", cmsgcred->cmcred_uid);
	printf("cmcred_euid=%d\n", cmsgcred->cmcred_euid);
	printf("cmcred_gid=%d\n", cmsgcred->cmcred_gid);
	printf("cmcred_ngroups=%d\n", cmsgcred->cmcred_ngroups);
	for (i = 0; i < cmsgcred->cmcred_ngroups; i++)
		printf("cmcred_groups[%d]=%d\n", i, cmsgcred->cmcred_groups[i]);

	return (0);
}


static int
client_main(pid_t pid, const char *sockpath)
{
	struct sockaddr_storage sockaddr;
	struct sockaddr_un *addr;
	sigset_t set;
	int sig, sock, status;

	if (sigemptyset(&set) == -1)
		die("sigemptyset(3)");
	if (sigaddset(&set, SIG) == -1)
		die("sigaddset(3)");
	if (sigwait(&set, &sig) != 0)
		die("sigwait(2)");
	if (sig != SIG)
		return (2);
	sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock == -1)
		die("socket(2)");
	addr = (struct sockaddr_un *)&sockaddr;
	addr->sun_family = AF_LOCAL;
	strlcpy(addr->sun_path, sockpath, sizeof(addr->sun_path));
	addr->sun_len = SUN_LEN(addr);
	if (connect(sock, (struct sockaddr *)addr, addr->sun_len) == -1)
		die("connect(2)");
	if (do_recvmsg(sock) == -1)
		return (3);
	if (close(sock) == -1)
		die("close(2)");
	if (wait4(pid, &status, 0, NULL) == -1)
		die("wait4(2)");
	if (!WIFEXITED(status))
		return (4);
	if (WEXITSTATUS(status) != 0)
		return (32 + WEXITSTATUS(status));

	return (0);
}

int
main1(int argc, const char *argv[])
{
	sigset_t set;
	pid_t pid, ppid;
	char sockpath[MAXPATHLEN];

	if (sigfillset(&set) == -1)
		die("sigfillset(3)");
	if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
		die("sigprocmask(2)");

	ppid = getpid();
	snprintf(sockpath, sizeof(sockpath), "%d.sock", ppid);

	pid = fork();
	switch (pid) {
	case -1:
		die("fork(2)");
	case 0:
		return (server_main(ppid, sockpath));
	default:
		break;
	}

	return (client_main(pid, sockpath));
}

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_un	servaddr;

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	struct msghdr msg;
	struct cmsghdr *cmsghdr;
	struct iovec iov[1];
	ssize_t nbytes;
	char buf[CMSG_SPACE(sizeof(struct cmsgcred))], c;

	c = '*';
	iov[0].iov_base = &c;
	iov[0].iov_len = sizeof(c);
	memset(buf, 0x0b, sizeof(buf));
	cmsghdr = (struct cmsghdr *)buf;
	cmsghdr->cmsg_len = CMSG_LEN(sizeof(struct cmsgcred));
	cmsghdr->cmsg_level = SOL_SOCKET;
	cmsghdr->cmsg_type = SCM_CREDS;
#if 0
	msg.msg_name = addr;
	msg.msg_namelen = addr->sun_len;
#else
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
#endif
	msg.msg_iov = iov;
	msg.msg_iovlen = sizeof(iov) / sizeof(iov[0]);
	msg.msg_control = cmsghdr;
	msg.msg_controllen = CMSG_SPACE(sizeof(struct cmsgcred));
	msg.msg_flags = 0;

	

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	if ( (nbytes = sendmsg(sockfd, &msg, 0)) == -1)
		fprintf(stderr, "sendmsg error: %s\n", strerror(errno));

	str_cli(stdin, sockfd);

	exit(0);
}
