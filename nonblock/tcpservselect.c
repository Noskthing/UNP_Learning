#include "unp.h"

#define NOTDEF 1
int main(int argc, char ** argv)
{
	int					i, maxi, maxfd, listenfd, connfd, sockfd;
	int					nready, client[FD_SETSIZE];
	ssize_t				n;
	fd_set				rset, allset;
	char				line[MAXLINE];
	char*				ipstr;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	/* initialize */
	maxfd = listenfd;
	maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for ( ; ; )
	{
		rset = allset;
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset))	/* new client connection */
		{
			printf("listening socket readable\n");
			sleep(5);	/* simulate server is busy */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef NOTDEF
			ipstr = Malloc(INET_ADDRSTRLEN);
			Inet_ntop(AF_INET, &cliaddr.sin_addr, ipstr, INET_ADDRSTRLEN);
			printf("new client: %s, port %d\n", ipstr,
					ntohs(cliaddr.sin_port));
#endif
			for ( i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i] == -1)
				{
					client[i] = connfd;		/* save descriptor */
					break;
				}
			}

			if ( i == FD_SETSIZE)
				err_quit("too many clients");

			FD_SET(connfd, &allset);

			if (connfd > maxfd)
				maxfd = connfd;
			if (i > maxi)
				maxi = i;

			if (--nready == 0)
				continue;
		}

		for ( i = 0; i <= maxi; i++)
		{
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset))
			{
				if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
				{
					/* connection clised by client */
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
				Writen(sockfd, line, n);

				/* 
				 * 上面的nearby == 0调用continue是在Event Runloop里
				 * 这里的nearby调用break是跳出enum clients 
				 */
				if (--nready <= 0)
					break;
			}
		}
	}
}
