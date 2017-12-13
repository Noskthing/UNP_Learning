/*
 * Socket wrapper functions.
 */

#include "unp.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;

again:
	if ( (n = accept(fd, sa, salenptr)) < 0)
	{
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			err_sys("accept error");
	}
	return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if( bind(fd, sa, salen) < 0)
	{
		err_sys("bind error");
	}
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if ( connect(fd, sa, salen) < 0)
        err_sys("connect error");
}

void Listen(int fd, int backlog)
{
    char	*ptr;
    
    /*4can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);
    
    if (listen(fd, backlog) < 0)
        err_sys("listen error");
}

int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
	int		n;

	if( (n = poll(fdarray, nfds, timeout)) < 0)
		err_sys("poll error");

	return(n);
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		struct sockaddr *sa, socklen_t *salenptr)
{
	ssize_t		n;

	if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
		err_sys("recvfrom error");
	return(n);
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
	int		n;

	if( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
		err_sys("select error");

	return(n);
}

/*
 原函数sendto()是返回一个ssize_t类型的结果告知发送的字节数
 这里的包裹函数去掉了返回结果，只关心发送是成功还是失败
 调用sendto()之后比对返回结果和预期进行判断
 */
void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr * sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
		err_sys("sendto error");
}

int Socket(int family, int type, int protocol)
{
    int		n;
    
    if ( (n = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return(n);
}

void Shutdown(int fd, int how)
{
	if (shutdown(fd, how) < 0)
		err_sys("shutdown error");
}
