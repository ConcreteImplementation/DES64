demo.out : des_defines.o keyschedule.o des64.o padding.o
	gcc main.c des64.o keyschedule.o des_defines.o padding.o -o demo.out 
	rm *.o
	valgrind ./demo.out 
	rm demo.out 


des_defines.o : ../des64_global_defines.c ../des64_global_defines.h
	gcc -c ../des64_global_defines.c -o des_defines.o

keyschedule.o : ../des64_keyschedule.c ../des64_keyschedule.internal.h ../des64_keyschedule.tables.h
	gcc -c ../des64_keyschedule.c -o keyschedule.o

des64.o : ../des64.c ../des64.tables.h
	gcc -c ../des64.c




padding.o : padding.c padding.h
	gcc -c padding.c
