CC = gcc
CFLAGS = -g -DRPC_SVC_FG

all: client server

client: client.o date_clnt.o
        $(CC) -o client client.o date_clnt.o -lnsl

server: server.o date_svc.o
        $(CC) -o server server.o date_svc.o -lnsl

date_svc.o: date.h
        $(CC) $(CFLAGS) -c date_svc.c

date_clnt.o: date.h
        $(CC) $(CFLAGS) -c date_clnt.c

server.o: server.c date.h
        $(CC) $(CFLAGS) -c server.c

client.o: client.c date.h
        $(CC) $(CFLAGS) -c client.c

# date.x produces date.h, date_clnt.c and  date_svc.c
# make sure we generate these if they're missing or our interface changes

date_clnt.c:	date.x
        rpcgen -C date.x

date_svc.c:	date.x
        rpcgen -C date.x

date.h: date.x
        rpcgen -C date.x

clean:
        rm -f client client.o server server.o date_clnt.* date_svc.* date.h 
