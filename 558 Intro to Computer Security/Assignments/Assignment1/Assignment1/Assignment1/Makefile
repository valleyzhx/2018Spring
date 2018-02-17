all:server client
server:server.c
	gcc server.c process.c -o telnetserv -std=c99
client:client.c
	gcc client.c -o telnetcli -std=c99
clean:
	rm telnetserv telnetcli
