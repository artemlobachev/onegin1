all: program

program:
	g++ main.cpp TextSorting.cpp FileWorks.cpp FileWorks.h TextSorting.h   

END:
	g++ main.cpp TextSorting.cpp FileWorks.cpp FileWorks.h TextSorting.h -D END

TextSorting.o: TextSorting.cpp
	g++ -c TextSorting.cpp

FileWorks.o: FileWorks.cpp
	g++ -c FileWorks.cpp

main.o: main.cpp
	g++ -c main.cpp

