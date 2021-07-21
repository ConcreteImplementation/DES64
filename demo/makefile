demo.out : des64_global_definitions.o keyschedule.o des.o
	gcc demo.c des.o keyschedule.o des64_global_definitions.o -o demo.out 
	rm *.o
	valgrind ./demo.out 
	rm demo.out 


des64_global_definitions.o : ../des64_global_definitions.c ../des64_global_definitions.h
	gcc -c ../des64_global_definitions.c -o des64_global_definitions.o

keyschedule.o : ../des64_keyschedule.c ../des64_keyschedule.h ../des64_keyschedule.internal.h
	gcc -c ../des64_keyschedule.c -o keyschedule.o

des.o : ../des64.c ../des64.h ../des64.internal.h
	gcc -c ../des64.c -o des.o
