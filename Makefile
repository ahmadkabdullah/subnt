CFLAGS = -Wall

TARGET = subnt
BINPATH = /usr/local/bin/

default:
	gcc -o $(TARGET) *.c

install:
	gcc -o $(TARGET) *.c
	cp $(TARGET) $(BINPATH)

uninstall:
	rm $(BINPATH)$(TARGET)

clean:
	rm $(TARGET)
