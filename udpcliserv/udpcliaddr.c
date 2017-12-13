#include "unp.h"

int main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in servaddr;

	if (argc < 2)
		err_sys("usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	/*
	 作为值-结果的参数，返回时系统会设置sin_len.
	 这个版本我们需要比对应答的服务器地址
	 如果不手动设置会默认为0
	 影响memcpy()的结果
	*/
	servaddr.sin_len = sizeof(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

	exit(0);
}
