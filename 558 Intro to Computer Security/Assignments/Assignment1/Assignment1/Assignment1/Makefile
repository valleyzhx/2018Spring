all:server client
server:server.c
	gcc server.c process.c -o server
client:client.c
	gcc client.c -o client
runserver:
	./server
runclient:
	./client
clean:
	rm server client
