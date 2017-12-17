#include "unp.h"

int tcp_connect(const char *host, const char *serv)
{
	int			sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_connect error for %s, %s : %s",
				host, serv, gai_strerror(n));
	ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		Close(sockfd);
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("tcp_connect error for %s, %s", host, serv);

	freeaddrinfo(ressave);

	return(sockfd);
}

/* 和tcp_listen一样，该函数只在成功时返回，否则终止进程。如过需要提供错误码那么要引入新的参数。 这意味着包裹函数是没有意义的，这里添加只是为了统一性 */
int Tcp_connect(const char *host, const char *serv)
{
	return(tcp_connect(host, serv));
}
