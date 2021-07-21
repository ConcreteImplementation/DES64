VPATH = ../:binary_utility/
objects = des64_global_definitions.o des64_keyschedule.o des64.o binary_utility.o


des64_tests.out : $(objects) 
	gcc des64_tests.c $(objects) -o des64_tests.out -lcmocka -D TESTING
	rm *.o
	valgrind ./des64_tests.out
	rm des64_tests.out


des64_global_definitions.o : des64_global_definitions.h
des64_keyschedule.o : des64_keyschedule.h des64_keyschedule.internal.h
	gcc -c ../des64_keyschedule.c -D TESTING
des64.o : des64.h des64.internal.h
	gcc -c ../des64.c -D TESTING

binary_utility.o : binary_utility.h