#Για χρηση απο τα windows με το mingw32 και mingw.threads

CC = g++
INCLUDE = C:\MinGW\bin

CXXFLAGS = -I$(INCLUDE) -D _WIN32_WINNT=0x0A00
OBJS = main.o
EXEC = main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o main

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

