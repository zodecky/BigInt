# make file
all:
	gcc exemplo.c bigint.c -o main -Wall; ./main
clean:
	rm -rf main
clang:
	clang exemplo.c bigint.c -o main -Wall; ./main