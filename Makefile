CC=gcc
BINARY=./lightdm-gtk-backgroundmatch
SOURCES=./source/lightdm-backgroundmatch.c ./source/strtools.c
INCLUDES=./include

all:
	$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES)
	sh user.sh

run:
	$(BINARY)
