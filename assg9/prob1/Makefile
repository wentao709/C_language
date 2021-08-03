mymake : mymake.o traversal.o
	gcc -Wall -o mymake mymake.o traversal.o

mymake.o : mymake.c traversal.h
	gcc -Wall -c mymake.c

traversal.o : traversal.c traversal.h
	gcc -Wall -c traversal.c	
