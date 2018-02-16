all:server client
server:server.c
	gcc server.c process.c -o server -std=c99
client:client.c
	gcc client.c -o client -std=c99
clean:
	rm server client
