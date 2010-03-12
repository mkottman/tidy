OBJ=htmltidy.o tdoc.o tnode.o support.o tconst.o
CFLAGS=-fPIC -I/usr/include/lua5.1 -I/usr/include/tidy -Wall

all: tidy.so

install: tidy.so
	cp tidy.so /usr/lib/lua/5.1

clean:
	rm *.o
	rm *.so

tidy.so: $(OBJ)
	$(CC) -fPIC -rdynamic -shared -ltidy -llua5.1 -o tidy.so $(OBJ)


