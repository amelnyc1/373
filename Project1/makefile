CPP = g++
CPPFLAGS = -Wall -g -std=c++11

melnyczuk_p1: Driver.o NFA.o
	$(CPP) $(CPPFLAGS) Driver.o NFA.o -o melnyczuk_p1

Driver.o: Driver.cpp
	$(CPP) $(CPPFLAGS) -c Driver.cpp

NFA.o: NFA.cpp NFA.h
	$(CPP) $(CPPFLAGS) -c NFA.cpp

clean:
	rm -f melnyczuk_p1 *.o
