# ? Support more different compilers? 
gcc: include/*.h src/*.c
	mkdir build	
	gcc -Wall -c -o build/base.o -Iinclude src/base.c
	gcc -Wall -c -o build/optimized.o -Iinclude src/optimized.c
	gcc -Wall -c -o build/recursive_int.o -Iinclude src/recursive_int.c	
	gcc -Wall -c -o build/print.o -Iinclude src/print.c
	ar rcs build/$(NAME) build/base.o build/optimized.o build/recursive_int.o build/print.o