#include "unp.h"
#include <syslog.h>
#include <syslog.h>
#include <syslog.h>

extern int daemon_proc;		/* defined in error.c */

void daemon_inetd(const char *pname, int facility)
{
	daemon_proc = 1;		/*4our err_xxx() functions */
	openlog(pname, LOG_PID, facility);
}
