CFLAGS = -Wall

TARGET = subnt
BINPATH = /usr/local/bin/

default:
	gcc -o $(TARGET) $(TARGET).c

install:
	gcc -o $(TARGET) $(TARGET).c
	cp $(TARGET) $(BINPATH)

uninstall:
	rm $(BINPATH)$(TARGET)

clean:
	rm $(TARGET)
