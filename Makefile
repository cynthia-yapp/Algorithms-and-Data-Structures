all: map1 map2
map2: map2.o list.o tree.o
	gcc -o map2 map2.o list.o tree.o
map1: map1.o list.o tree.o
	gcc -o map1 map1.o list.o tree.o

list.o :list.c list.h
	gcc -c -Wall list.c
map1.o: map1.c map1.h
	gcc -c -Wall map1.c
map2.o: map2.c map2.h
	gcc -c -Wall map2.c
tree.o: tree.c tree.h
	gcc -c -Wall tree.c
	