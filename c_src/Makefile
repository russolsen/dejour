CC = i586-mingw32msvc-gcc

regular_objects := args.o  classpath.o main.o

all: install

release: install
	rm -f ../bin/cljw.exe ../bin/clj.exe
	cp cljw.exe clj.exe ../bin
        
install: cljw.exe clj.exe
     
paths_no_console.o: main.c
	$(CC) -c -DNO_CONSOLE -mwindows -o paths_no_console.o paths.c

paths_with_console.o: main.c
	$(CC) -c -o paths_with_console.o paths.c

clj.exe : $(regular_objects) paths_with_console.o
	$(CC) -o clj.exe paths_with_console.o $(regular_objects)

cljw.exe : $(regular_objects) paths_no_console.o
	$(CC) -DNO_CONSOLE -mwindows -o cljw.exe paths_no_console.o $(regular_objects)

clean: 
	rm -f *.o clj.exe cljw.exe
