#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
	int			maxdp1, stdineof;
	fd_set		rset;
	char		buf[MAXLINE];
	int			n;

	stdineof = 0;
	FD_ZERO(&rset);
	for( ; ; )
	{
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxdp1 = fileno(fp) > sockfd ? fileno(fp) + 1 : sockfd + 1;
		Select(maxdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset))/* socket is readable */
		{
			if( (n = Read(sockfd, buf, MAXLINE)) == 0)
			{
				if (stdineof == 1)
					return;
				else
					err_quit("str_cli: server terminated prematurely");
			}

			Write(fileno(stdout), buf, n);	/* 字节流套接字才会出现write()返回值比预期小的情况,然而我们并不能确定这里fileno()获得的是一个字节流套接字 */
		}

		if (FD_ISSET(fileno(fp), &rset))/*input is readable */
		{
			if( (n = Read(fileno(fp), buf, MAXLINE)) == 0)
			{
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR); /* send FIN */
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			Writen(sockfd, buf, n);
		}
	}
}
