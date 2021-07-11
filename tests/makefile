des64_tests.out : des64.o binary_utility.o
	gcc  des64_tests.c des64.o binary_utility.o -o des64_tests.out -lcmocka
	rm *.o
	valgrind ./des64_tests.out


des64.o : ../des64.c ../des64_tables.h
	gcc -c ../des64.c

binary_utility.o : ../binary_utility/binary_utility.c ../binary_utility/binary_utility.h
	gcc -c ../binary_utility/binary_utility.c