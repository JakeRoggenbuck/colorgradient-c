CC=gcc
TARGET=colorgradient

all:
	$(CC) src/main.c -o $(TARGET)

clean:
	rm $(TARGET)
