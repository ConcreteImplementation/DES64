des64_tests.out : des64_global_definitions.o keyschedule.o des.o binary_utility.o 
	gcc des64_tests.c des.o keyschedule.o des64_global_definitions.o binary_utility.o -o des64_tests.out -lcmocka  -D TESTING
	rm *.o
	valgrind ./des64_tests.out
	rm des64_tests.out


des64_global_definitions.o : ../des64_global_definitions.c ../des64_global_definitions.h
	gcc -c ../des64_global_definitions.c -o des64_global_definitions.o

keyschedule.o : ../des64_keyschedule.c ../des64_keyschedule.h ../des64_keyschedule.internal.h
	gcc -c ../des64_keyschedule.c -o keyschedule.o -D TESTING

des.o : ../des64.c ../des64.h ../des64.internal.h
	gcc -c ../des64.c -o des.o -D TESTING




binary_utility.o : binary_utility/binary_utility.c binary_utility/binary_utility.h
	gcc -c binary_utility/binary_utility.c
