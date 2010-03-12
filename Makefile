OBJ=compat-5.1.o htmltidy.o tdoc.o tnode.o support.o tconst.o
CFLAGS=-I/usr/include/lua50 -I/usr/include/tidy -Wall

all: luahtmltidy.so

clean:
	rm *.o
	rm *.so

luahtmltidy.so: $(OBJ)
	$(CC) -rdynamic -shared -ltidy -llua50 -llualib50 -W1,-soname,luahtmltidy.so.1 -o luahtmltidy.so $(OBJ)


