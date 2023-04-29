#Για χρηση απο τα windows με το mingw32 και mingw.threads

CC = g++
INCLUDE = C:\MinGW\bin

CXXFLAGS = -D _WIN32_WINNT=0x0A00 -I$(INCLUDE)
OBJS = main.o 
EXEC = main.exe

$(EXEC): $(OBJS)
	$(CC) -o main $(OBJS)

run: $(EXEC)
	./$(EXEC)

clean:
	del $(OBJS) $(EXEC)

