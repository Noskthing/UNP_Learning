#include "unp.h"

static void recvfrom_int(int);
static int  count;

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	socklen_t	len;
	char		mesg[MAXLINE];

	Signal(SIGINT, recvfrom_int);

	for( ; ; )
	{
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		printf("get a udp datagram!\n");
		count ++;
	}
}

static void recvfrom_int(int signo)
{
	printf("\nreceive %d %s\n", count, count == 1?"datagram":"datagrams");
	exit(0);
}
