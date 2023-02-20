output: main.o MyList.o flightticket.o flighthashtable.o 
	g++ main.o MyList.o flightticket.o flighthashtable.o -o output
main.o: main.cpp MyList.h flightticket.h flighthashtable.h
	g++ -c main.cpp
MyList.o: MyList.h MyList.cpp
	g++ -c MyList.cpp
flightticket.o: flightticket.h flightticket.cpp 
	g++ -c flightticket.cpp
flighthashtable.o: flighthashtable.h flighthashtable.cpp
	g++ -c flighthashtable.cpp
clean:
	rm *.o output