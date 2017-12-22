#include "unp.h"

static void connect_alarm(int);

/* 多线程中正确使用信号是非常困难的，建议在单线程中使用  */
int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
	Sigfunc		*sigfunc;
	int			n;

	sigfunc = Signal(SIGALRM, connect_alarm);	/* save previous sigfunc */
	if (alarm(nsec) != 0)
		err_msg("connect_timeo: alarm was already set");

	if ( (n = connect(sockfd, saptr, salen)) < 0)
	{
		close(sockfd);
		if (errno == EINTR)
			errno = ETIMEDOUT;
	}

	alarm(0);	/* turn off alarm */
	Signal(SIGALRM, sigfunc);		/* restore previous signal handler */

	return(n);
}

static void connect_alarm(int signo)
{
	return;		/* just interrupt the connect() */
}

void Connect_timeo(int sockfd, const SA *sa, socklen_t salen, int nsec)
{
	if (connect_timeo(sockfd, sa, salen, nsec))
		err_sys("connect_timeo error");
}
