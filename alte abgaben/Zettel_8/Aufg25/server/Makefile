OBJECTS = bank_server.o  
CPPFLAGS = -g -Wall 
server: $(OBJECTS)
	gcc $(CPPFLAGS) -o server $(OBJECTS)

%.o: %.c
	gcc -c $<

	
