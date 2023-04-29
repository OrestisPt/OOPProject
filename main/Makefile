# paths
INCLUDE = ../include

# compiler
CC = g++

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CXXFLAGS =  -g -I$(INCLUDE) 
LDFLAGS = -lm

# Αρχεία .o
OBJS = main.o 
# Το εκτελέσιμο πρόγραμμα
EXEC = program

$(EXEC): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) 

valgrind: $(EXEC)
	valgrind ./$(EXEC) 