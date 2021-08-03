mymake2 : mymake2.o traversal.o
	gcc -Wall -o mymake2 mymake2.o traversal.o

mymake2.o : mymake2.c traversal.h
	gcc -Wall -c mymake2.c

traversal.o : traversal.c traversal.h
	gcc -Wall -c traversal.c
