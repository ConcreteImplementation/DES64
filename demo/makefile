VPATH = ../
objects = des64_global_definitions.o des64_keyschedule.o des64.o


demo.out : libdes64.a des64.h
	gcc demo.c -L./ -ldes64 -o demo.out 
	valgrind ./demo.out


libdes64.a: $(objects)
	ar crs libdes64.a $(objects)
	rm *.o
	

des64_global_definitions.o : des64_global_definitions.h
des64_keyschedule.o : des64_keyschedule.h des64_keyschedule.internal.h
des64.o : des64.h des64.internal.h
