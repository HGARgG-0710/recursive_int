# ? Support more different compilers? 
# ! Support more operating systems! [this is batch file - windows only...]; 
gccwin32: include/*.h src/*.c
	if not exist build/ mkdir build
	gcc -Wall -c -o build/base.o -Iinclude src/base.c
	gcc -Wall -c -o build/optimized.o -Iinclude src/optimized.c
	gcc -Wall -c -o build/recursive_int.o -Iinclude src/recursive_int.c	
	gcc -Wall -c -o build/print.o -Iinclude src/print.c
	ar rcs build/$(NAME).a build/base.o build/optimized.o build/recursive_int.o build/print.o