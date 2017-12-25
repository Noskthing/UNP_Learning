# Unix_Socket_Case

### 当前版本目录结构
.
├── Makefile
├── Makefile.defines
├── README.md
├── advio
│   ├── Makefile
│   ├── dgclitimeopt.c
│   ├── dgclitimeoselect.c
│   ├── dgclitimeosig.c
│   └── udpcli.c
├── inetd
│   ├── Makefile
│   ├── daytimetcpsrvdaemon.c
│   └── daytimetcpsrvinetd.c
├── lib
│   ├── Makefile
│   ├── connect_timeo.c
│   ├── daemon_inetd.c
│   ├── daemon_init.c
│   ├── dg_cli.c
│   ├── dg_echo.c
│   ├── error.c
│   ├── readable_timeo.c
│   ├── readline.c
│   ├── signal.c
│   ├── sock_ntop.c
│   ├── sock_ntop_host.c
│   ├── str_cli.c
│   ├── str_echo.c
│   ├── tcp_connect.c
│   ├── tcp_listen.c
│   ├── udp_client.c
│   ├── udp_connect.c
│   ├── udp_server.c
│   ├── unp.h
│   ├── wraplib.c
│   ├── wrapsock.c
│   ├── wrapstdio.c
│   ├── wrapunix.c
│   └── writen.c
├── names
│   ├── Makefile
│   ├── daytimetcpcli.c
│   ├── daytimetcpcligetsrv.c
│   ├── daytimetcpserv.c
│   ├── daytimeudpclicon.c
│   ├── daytimeudpcliuncon.c
│   ├── daytimeudpserv.c
│   ├── daytimeudpservreuse.c
│   ├── hostadr.c
│   ├── hostent.c
│   └── udp_server_reuseaddr.c
├── select
│   ├── Makefile
│   ├── strcliselect.c
│   ├── tcpcliselect.c
│   ├── tcpservpoll.c
│   └── tcpservselect.c
├── tcpcliserv
│   ├── Makefile
│   ├── sigchldwaitpid.c
│   ├── str_echo08.c
│   ├── tcpcli01.c
│   ├── tcpserv01.c
│   └── tcpservfork.c
└── udpcliserv
├── Makefile
├── dgcliaddr.c
├── dgcliconnect.c
├── dgcliloop.c
├── dgecholoop.c
├── sigchldwaitpid.c
├── udpcli01.c
├── udpcliaddr.c
├── udpcliipaddr.c
├── udpserv01.c
└── udpservselect.c
