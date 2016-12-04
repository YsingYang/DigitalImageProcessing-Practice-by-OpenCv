CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

equalized:equalized.o
	g++ equalized.o $(CFLAGE)  $(LIBS) -o equlized
equalized.o:Equalized.cpp
	g++ -g -Wall -c Equalized.cpp -o equalized.o

clean:
	rm *.o equalized
