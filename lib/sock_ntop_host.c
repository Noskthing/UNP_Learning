#include "unp.h"

#include <net/if_dl.h>

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family)
	{
		case AF_INET:
		{
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;

			if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
				return(NULL);
			return(str);
		}
		case AF_INET6:
		{
			struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

			if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
				return(NULL);
			return(str);
		}
		case AF_UNIX:
		{
			struct sockaddr_un *unp = (struct sockaddr_un *)sa;

			/* OK to have no pathname bound to the socket: happens on
			 * every connect() unless client bind() first */
			if (unp->sun_path[0] == 0)
				strcpy(str, "(no pathname bound)");
			else
				snprintf(str, sizeof(str), "%s", unp->sun_path);
			return(str);
		}
		/* remove AF_LINK case */
		default:
			snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d,\
					len %d", sa->sa_family, salen);
			return(str);
	}
	return(NULL);
}

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	char *ptr;

	if( (ptr = sock_ntop_host(sa, salen)) == NULL)
		err_sys("sock_ntop_host error");
	return(ptr);
}
