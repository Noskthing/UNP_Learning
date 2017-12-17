#include "unp.h"

/* 因为UDP没有TIME_WAIT这个概念，所以reuse是一个没有必要的操作 */
int udp_server_reuseaddr(const char *host, const char *serv, socklen_t *addrlenp)
{
	int				sockfd, n;
	const int		on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_server error for %s, %s : %s",
				host, serv, gai_strerror(n));
	ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;

		Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;	/* success */

		Close(sockfd);
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_sever error for %s, %s",
				host, serv);

	if (addrlenp)
		*addrlenp = res->ai_addrlen;

	freeaddrinfo(ressave);

	return(sockfd);
}

int Udp_server_reuseaddr(const char *host, const char *serv, socklen_t *addrlenp)
{
	return(udp_server_reuseaddr(host, serv, addrlenp));
}
