des64_tests.out : des_defines.o keyschedule.o des64.o binary_utility.o 
	gcc des64_tests.c des64.o keyschedule.o des_defines.o binary_utility.o -o des64_tests.out -lcmocka  -D TESTING -D DES64_NUMBER_OF_ROUNDS=1
	rm *.o
	valgrind ./des64_tests.out
	rm des64_tests.out


des_defines.o : ../des64_global_defines.c ../des64_global_defines.h
	gcc -c ../des64_global_defines.c -o des_defines.o

keyschedule.o : ../des64_keyschedule.c ../des64_keyschedule.internal.h ../des64_keyschedule.tables.h
	gcc -c ../des64_keyschedule.c -o keyschedule.o -D TESTING -D DES64_NUMBER_OF_ROUNDS=1

des64.o : ../des64.c ../des64.tables.h
	gcc -c ../des64.c




binary_utility.o : ../binary_utility/binary_utility.c ../binary_utility/binary_utility.h
	gcc -c ../binary_utility/binary_utility.c
