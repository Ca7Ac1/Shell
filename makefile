all: main.o shell.o parser.o format.o command.o
	gcc -o main main.o shell.o parser.o format.o command.o

main.o: main.c shell.h
	gcc -c main.c

shell.o: shell.c shell.h command.h parser.h
	gcc -c shell.c

parser.o: parser.c parser.h format.h command.h
	gcc -c parser.c

format.o: format.c format.h
	gcc -c format.c

command.o: command.c command.h
	gcc -c command.c

clean:
	rm *.o

run:
	./main