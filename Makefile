CC=gcc
BINARY=./lightdm-gtk-backgroundmatcher
SOURCES=./source/lightdm-backgroundmatch.c ./source/strtools.c
INCLUDES=./include

all:
	$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES)

run:
	$(BINARY)

install:
	install -m 644 $(BINARY) /etc/bin/
