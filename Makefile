#Για χρηση απο τα windows με το mingw32 
# Συνιστάται χρήση σε Visual Studio 2022
CC = g++

OBJS = main.o 
EXEC = main.exe

$(EXEC): $(OBJS)
	$(CC) -o main $(OBJS)

run: $(EXEC)
	./$(EXEC)

clean:
	del $(OBJS) $(EXEC)

