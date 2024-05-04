# ? Support more different compilers? 
# ! Support more compilers [only GCC, currently - learn others]; 
gccwin32: include/*.h src/*.c
	if not exist build/ mkdir build
	gcc -Wall -c -o build/base.o -Iinclude src/base.c
	gcc -Wall -c -o build/optimized.o -Iinclude src/optimized.c
	gcc -Wall -c -o build/recursive_int.o -Iinclude src/recursive_int.c	
	gcc -Wall -c -o build/print.o -Iinclude src/print.c	
	gcc -Wall -c -o build/string.o -Iinclude src/string.c
	ar rcs build/$(NAME).a build/base.o build/optimized.o build/recursive_int.o build/print.o

gcc: include/*.h src/*.c
	if [ ! -d "build" ]; then 
		mkdir "build"
	fi

	gcc -Wall -c -o build/base.o -Iinclude src/base.c
	gcc -Wall -c -o build/optimized.o -Iinclude src/optimized.c
	gcc -Wall -c -o build/recursive_int.o -Iinclude src/recursive_int.c	
	gcc -Wall -c -o build/print.o -Iinclude src/print.c	
	gcc -Wall -c -o build/string.o -Iinclude src/string.c
	ar rcs build/$(NAME).a build/base.o build/optimized.o build/recursive_int.o build/print.o