HPATH=../include
OBJ=sort.o
static:$(OBJ)
	ar rcs libalgorithms.a sort.o

dynamic:$(OBJ)
	gcc -shared -fPIC -o libalgorithms.so sort.o

clean:
	rm -f  *.a
