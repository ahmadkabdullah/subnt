CFLAGS = -Wall

TARGET = subnt
BINPATH = /usr/local/bin/$(TARGET)

default:
	gcc -o $(TARGET) *.c

clean:
	rm $(TARGET)

install:
	cp $(TARGET) $(BINPATH)

uninstall:
	rm $(BINPATH)

