all:server client
server:server.c
ifeq ($(shell uname), SunOS)
	gcc server.c process.c -lsocket -lnsl -o telnetserv -std=c99
else	
	gcc server.c process.c -o telnetserv -std=c99
endif
client:client.c
ifeq ($(shell uname), SunOS)
	gcc client.c -o telnetcli -lsocket -lnsl -std=c99
else
	gcc client.c -o telnetcli -std=c99
endif
clean:
	rm telnetserv telnetcli
