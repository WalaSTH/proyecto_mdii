CC = clang

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CTEST = -Wall -Wextra -Werror -pedantic -std=c99 -g

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

gdb:
	$(CC) $(CTEST) -o $(TARGET) $(TARGET).c

clean: 
	  $(RM) $(TARGET)