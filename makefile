notDefault:
	@echo "No arguments runs the first recipe no matter what you call it."

compile: client host

client: client.o networking.o messaging.o
	@gcc -o client client.o networking.o messaging.o

host: host.o networking.o messaging.o
	@gcc -o host host.o networking.o messaging.o

client.o: client.c networking.h messaging.h
	@gcc -c client.c

host.o: host.c networking.h messaging.h
	@gcc -c host.c

networking.o: networking.c networking.h
	@gcc -c networking.c

messaging.o: messaging.c messaging.h
	@gcc -c messaging.c

clean:
	@rm -f *.o
	@rm -f host
	@rm -f client
	@rm -f *~