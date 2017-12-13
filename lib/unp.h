#ifndef __unp_h
#define __unp_h

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

#define SA struct sockaddr 
#define LISTENQ 1024

#define SERV_PORT 9877

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

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		struct sockaddr *sa, socklen_t *salenptr);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout);
void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr * sa, socklen_t salen);
int Socket(int family, int type, int protocol);
void Shutdown(int fd, int how);

void Close(int fd);
pid_t Fork(void);
ssize_t Read(int fd, void *ptr, size_t nbytes);
void Write(int fd, void *ptr, size_t nbytes);

void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);

#endif
