OBJECTS = udpchat.o  
CPPFLAGS = -g -Wall 
chat: $(OBJECTS)
	gcc $(CPPFLAGS) -o chat $(OBJECTS)

%.o: %.c
	gcc -c $<

	
