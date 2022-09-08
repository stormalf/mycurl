CC = gcc

OBJECT = mycurl.c 
OBJECT_OUT = mycurl

CFLAGS = -Wall -lrt 
LDFLAGS = -lcurl

INCLUDES = -I/usr/local/include -L/usr/local/lib 

all: clean mycurl

clean:
	rm -f $(OBJECT_OUT)
	
mycurl: 
		$(CC) $(INCLUDES) $(CFLAGS) $(OBJECT) -o $(OBJECT_OUT) $(LDFLAGS)

