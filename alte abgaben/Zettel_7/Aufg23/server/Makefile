OBJECTS = chat_server.o  
CPPFLAGS = -g -Wall 
Serv: $(OBJECTS)
	gcc $(CPPFLAGS) -o server $(OBJECTS)

%.o: %.c
	gcc -c $<

	
