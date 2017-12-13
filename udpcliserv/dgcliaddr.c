#include "unp.h"

/*
 单接口主机没有问题
 多宿的服务器主机可能会因为没有绑定接口，导致请求接口和外出接口不一致
 消息会被误判
 */
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int			n;
	char		sendline[MAXLINE], recvline[MAXLINE];
	socklen_t	len;
	struct sockaddr *preply_addr;

	preply_addr = Malloc(servlen);

	while (Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		len = servlen;
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
		if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0)
		{
			printf("reply from %s (ignored)\n",
					Sock_ntop(preply_addr, len));
			continue;
		}

		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
}
