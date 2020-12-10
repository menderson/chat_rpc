all: client server

hw.h: hw.x
	rpcgen hw.x
	
hw_svc.c hw_clnt.c hw_client.c: hw.h

hw_xdr.o: hw_xdr.c
	gcc -o hw_xdr.o -c hw_xdr.c

client: hw_client.o hw_clnt.o hw_xdr.o
	gcc -o client hw_client.o hw_clnt.o hw_xdr.o -lnsl

server: hw_server.o hw_svc.o
	gcc -o server hw_server.o hw_svc.o hw_xdr.o -lnsl

.PHONY: clean

clean:
	-rm *.o
	-rm client*
	-rm server*
	-rm *.serv; rm *.client
	-rm hw.h
	-rm hw_clnt.c
	-rm hw_svc.c

