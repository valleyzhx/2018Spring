SSLCLI = sslcli/
LIB = lib/
INCLUDE = include/
SSLSERV = sslserv/
GENPASS = gen-pass/
ifeq ($(shell uname),SunOS)
	INCLUDE = /usr/local/ssl/include/
	LIB = /usr/local/ssl/lib
else
endif
OPENSSL = -I$(INCLUDE) -I$(GENPASS) -L$(LIB) -lcrypto -lssl
objects = gen-pass.o sslcli.o sslserv.o

all: $(objects)

sslcli.o:
	gcc $(SSLCLI)client.c -o sslcli.o $(OPENSSL)
sslserv.o:
	gcc $(SSLSERV)server.c $(GENPASS)gen-pass.c -o sslserv.o $(OPENSSL)
gen-pass.o:
	gcc $(GENPASS)gen-pass.c $(GENPASS)main.c -o gen-pass.o $(OPENSSL)

clean:
	rm *.o
