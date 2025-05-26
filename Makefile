CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = school_management
SOURCES = main.c student.c lecturer.c course.c schedule.c tuition.c department.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	del $(TARGET).exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
