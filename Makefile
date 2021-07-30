CFLAGS = -Wall

TARGET = subnt
BINPATH = /usr/local/bin/subnt

default:
	gcc -o $(TARGET) *.c

install:
	gcc -o $(TARGET) *.c
	cp $(TARGET) $(BINPATH)

uninstall:
	rm $(BINPATH)

clean:
	rm $(TARGET)
