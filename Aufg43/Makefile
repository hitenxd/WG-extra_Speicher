OBJECTS = mat.o  
CPPFLAGS = -g -Wall -pthread
mat: $(OBJECTS)
	gcc $(CPPFLAGS) -o mat $(OBJECTS)

%.o: %.c
	gcc -c $<

	
