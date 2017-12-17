#include "unp.h"

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int				listenfd, n;
	const int		on = 1;
	struct addrinfo hints, *res, *ressave;

	/* hints 可以为NULL ，也可以指定返回res的各项类型 */
	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;	/* 典型的服务器进程只指定service而不是hostname. 同时设定AI_PASSIVE使得返回套接字地址包含INADDR_ANY和IN6ADDR_ANY_INIT */
	hints.ai_family = AF_UNSPEC;	/* 返回适用于主机名和服务名且适合任意协议族的地址 */
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_listen error for %s, %s: %s",
				host, serv, gai_strerror(n));
	ressave = res;

	do
	{
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		if (listenfd < 0)
			continue;	/* error, try next one */

		Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;		/* success */

		Close(listenfd);
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("tcp_listen error for %s, %s", host, serv);

	Listen(listenfd, LISTENQ);

	if (addrlenp)
		*addrlenp = res->ai_addrlen;

	freeaddrinfo(ressave);	/* struct addrinfo *ai 应指向第一个addrinfo */

	return(listenfd);
}


int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	return(tcp_listen(host, serv, addrlenp));
}
