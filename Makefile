CC = gcc

CFLAGS = -Wall -Wextra -O3 -std=c99
CTEST = -Wall -Wextra -O3 -std=c99 -g

TARGET = main
COMPILED = $(TARGET:.c:.o)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

run:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
	./$(TARGET)

gdb:
	$(CC) $(CTEST) -fsanitize=address,undefined -o $(TARGET) -DNDEBUG $(TARGET).c

clean: 
	  $(RM) $(TARGET) $(COMPILED)