#ifndef __unp_h
#define __unp_h

#include "../config.h"
#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>
#include <stdarg.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <sys/poll.h>

#include<signal.h>

#include <netdb.h>

#include <sys/un.h>

#include <fcntl.h>

#include <sys/uio.h>

#define SA struct sockaddr 
#define LISTENQ 1024

#ifndef AF_LOCAL
#define AF_LOCAL	AF_UNIX
#endif

#define SERV_PORT 9877

#define UNIXSTR_PATH	"/tmp/unix.str"	/* UNIX domain stream */
#define UNIXDG_PATH		"/tmp/unix.dg"	/* UNIX domain datagram */
/* Miscellaneous constants */
#define MAXLINE 4096 /* max text line length */
#define BUFFSIZE 8192 /* buffer size for reads and writes */ 

typedef void Sigfunc(int);		/* For signal handlers */

/*
 POSIX requires that an #include of <poll.h> definE INFTIM, but many systems still DefinE it in <sys/stropts.h>. 
 We don't want to include all the STREAMS stuff if it' not needed, so we just DefinE INFTIM here.
 This is the statndard value, but there's no guarantee it is -1
 */ 
#ifndef INFTIM 
#define INFTIM		(-1) /* infinite poll timeout */
/* $.Ic INFTIM$$ */
#ifdef HAVE_POLL_H 
#define INFTIM_UNPH		/* tell unpxti.h we defined it */ 
#endif
#endif

struct cmsgcred {
	pid_t	cmcred_pid;		/* PID of sending process */
	uid_t	cmcred_uid;		/* real UID of sending process */
	uid_t	cmcred_euid;		/* effective UID of sending process */
	gid_t	cmcred_gid;		/* real GID of sending process */
	short	cmcred_ngroups;		/* number or groups */
	gid_t	cmcred_groups[16];	/* groups */
};

#define min(a,b)	((a) < (b))? (a) : (b)
#define max(a,b)	((a) > (b))? (a) : (b)
Sigfunc *Signal(int signo, Sigfunc *func);

ssize_t	Readline(int fd, void *ptr, size_t maxlen);
void Writen(int fd, void *ptr, size_t nbytes);

void str_cli(FILE *fp, int sockfunp_testunp_testd);
void str_echo(int sockfd);

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen);
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

char *Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);

char *Sock_ntop(const struct sockaddr *sa, socklen_t salen);
char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getpeername(int, SA *, socklen_t *);
void Listen(int fd, int backlog);
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		struct sockaddr *sa, socklen_t *salenptr);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout);
void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr * sa, socklen_t salen);
int Socket(int family, int type, int protocol);
void Shutdown(int fd, int how);
void Socketpair(int family, int type, int protocol, int *fd);

void Close(int fd);
pid_t Fork(void);
void *Malloc(size_t size);
ssize_t Read(int fd, void *ptr, size_t nbytes);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Write(int fd, void *ptr, size_t nbytes);

int Tcp_connect(const char *host, const char *serv);
int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);
int Udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp);
int Udp_connect(const char *host, const char *serv);
int Udp_server(const char *host, const char *serv, socklen_t *addrlenp);

int daemon_init(const char *pname, int facility);
void daemon_inetd(const char *pname, int facility);

void Connect_timeo(int sockfd, const SA *sa, socklen_t salen, int nsec);
int Readable_timeo(int fd, int sec);

ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
ssize_t Write_fd(int fd, void *ptr, size_t nbytes, int sendfd);

/* 在unp提供的源码里，声明了所有原函数和与其对应的包裹函数
 * 通常情况下我们会使用包裹函数来处理错误
 * 但部分情况下我们需要自己处理错误
 * 这个时候我们需要使用原函数
 * 之前的源码只提供了包裹函数
 * 后续版本会更新上所有原函数
*/
	/* prototyptes for our own library functions */
ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd);


void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_ret(const char *fmt, ...);

#endif
