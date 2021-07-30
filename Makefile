CC = gcc
CFLAGS = -Wall
TARGET = subnt
BINPATH = /usr/local/bin/$(TARGET)

default:
	$(CC) -o $(TARGET) *.c
clean:
	rm $(TARGET)
install:
	cp $(TARGET) $(BINPATH)
uninstall:
	rm $(BINPATH)
