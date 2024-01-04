notDefault:
	@echo "No arguments runs the first recipe no matter what you call it."

compile: client host

client: client.o networking.o
	@gcc -o client client.o networking.o

host: host.o networking.o
	@gcc -o host host.o networking.o

client.o: client.c networking.h
	@gcc -c client.c

host.o: host.c networking.h
	@gcc -c host.c

networking.o: networking.c networking.h
	@gcc -c networking.c

clean:
	@rm -f *.o
	@rm -f host
	@rm -f client
	@rm -f *~

