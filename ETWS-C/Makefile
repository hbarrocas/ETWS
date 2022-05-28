
all: etws

etws: etws.o menuclass.o repleti.o
	gcc -o etws etws.o menuclass.o repleti.o -lreadline

hellomain.o:
	gcc -c hellomain.c

menuclass.o:
	gcc -c menuclass.c

repleti.o:
	gcc -c repleti.c

clean:
	rm -f *.o *~
	rm -f hellomain
