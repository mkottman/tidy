OBJ=htmltidy.o tdoc.o tnode.o support.o tconst.o
CFLAGS=-fPIC -I/usr/include/lua5.1 -I/usr/include/tidy -Wall

all: luahtmltidy.so

clean:
	rm *.o
	rm *.so

luahtmltidy.so: $(OBJ)
	$(CC) -fPIC -rdynamic -shared -ltidy -llua5.1 -o luahtmltidy.so $(OBJ)


