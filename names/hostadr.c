#include "unp.h"

int main(int argc, char **argv)
{
	char			 *ptr, **pptr;
	char			 str[INET_ADDRSTRLEN];
	struct in_addr	 addr;
	struct hostent	 *hptr;

	while(-- argc > 0)
	{
		ptr = *++argv;

		bzero(&addr, sizeof(addr));
		Inet_pton(AF_INET, ptr, &addr);

		if ( (hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET)) == NULL)
		{
			err_msg("gethostname error for host: %s : %s",
					ptr, hstrerror(h_errno));
			continue;
		}
		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr ++)
			printf("\talias: %s\n", *pptr);

		switch (hptr->h_addrtype)
		{
			case AF_INET:
				pptr = hptr->h_addr_list;
				for ( ; *pptr != NULL; pptr++)
					printf("\taddress: %s\n",
							Inet_ntop(AF_INET, *pptr, str, sizeof(str)));
				break;
			default:
				err_quit("unknown address type");
				break;
		}
		
	}
	exit(0);
}
