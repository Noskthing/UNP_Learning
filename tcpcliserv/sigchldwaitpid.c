#include "unp.h"

/*
 使用waitpid而不是wait的原因在于：如果多个信号同时送达，使用wait可能会丢失
 部分信号。
 原因在于，当处理第一个到来的信号时，可能会有多个信号同时抵达。
 我们只会执行一次wait()函数，在Unix中，这期间到来的信号不会排队。
 为什么使用waitpid()没有这个问题呢，触发信号函数的时候我们会使用一个循环检查出当时所有已经僵死的子进程。
 也就是说处理第一个信号时，如果同时来了多个信号僵死了多个程序，会在循环里全部kill掉。
 为什么wait()不可以循环遍历呢，因为wait()是会阻塞的。当处理完所有僵死的程序以后waitpid()会返回负值退出循环，而wait()则拥塞了。
 */

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		/*
		 信号处理函数中使用标准I/O函数是不妥的。这里只是为了标识一下进程终止
		 */
		printf("child %d terminated\n", pid);
	return;
}
