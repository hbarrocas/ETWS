
etws-mac: etws.o menuclass.o repleti.o-mac
	gcc -o etws etws.o menuclass.o repleti.o -lreadline -L/opt/homebrew/Cellar/readline/8.2.1/lib

etws-linux: etws.o menuclass.o repleti.o
	gcc -o etws etws.o menuclass.o repleti.o -lreadline

etws.o:
	gcc -c etws.c

menuclass.o:
	gcc -c menuclass.c

repleti.o-mac:
	gcc -c repleti.c -I/opt/homebrew/Cellar/readline/8.2.1/include

repleti.o:
	gcc -c repleti.c

clean:
	rm -f *.o *~
	rm -f etws 
