SSLCLI = sslcli/
LIB = lib/
INCLUDE = include/
SSLSERV = sslserv/
GENPASS = gen-pass/
OPENSSL = -I$(INCLUDE) -I$(GENPASS) -L$(LIB) -lcrypto -lssl
objects = gen-pass.o sslcli.o sslserv.o
CFLAGS = -std=c99
ifeq ($(shell uname), SunOS)
	CFLAGS = -lsocket -lnsl -std=c99
endif
all: $(objects)

sslcli.o:
	gcc $(SSLCLI)client.c -o sslcli.o $(OPENSSL) $(CFLAGS)
sslserv.o:
	gcc $(SSLSERV)server.c $(GENPASS)gen-pass.c -o sslserv.o $(OPENSSL) $(CFLAGS)
gen-pass.o:
	gcc $(GENPASS)gen-pass.c $(GENPASS)main.c -o gen-pass.o $(OPENSSL) $(CFLAGS)

clean:
	rm *.o
