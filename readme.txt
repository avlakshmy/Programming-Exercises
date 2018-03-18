CS2710: Programming and Data Structures Lab

Assignment 8:Disjoint-set-union-and-find 

NAME: A V Lakshmy

ROLL NO.: CS16B101

The files included as part of this exercise are:
driver.c
disjoint_set.h
disjoint_set.c
Makefile

The program simulates the disjoint-set-union-and-find operation.

Details of compilation: At the terminal, use the command...
	gcc driver.c disjoint_set.c
...followed by 
	./a.out

Alternatively, one can use the Makefile that is also part of this folder...
	make
...this does the compilation, and to execute the program...
	./go

Once the program starts running, the user is asked to enter the number of elements, on which the operations are to be performed. 

Then, the user is prompted to enter the values of the elements one by one. The user should give the values accordingly.

These elements are made into separate nodes, whose leader points to themselves.

The keys of these nodes are now printed on the screen.

After that, the user is asked to enter the number of unite + findSet operations to be performed on these elements.

Once that is done, the program enters a for-loop which should be run m number of times (where m = number of operations).

At each iteration of the loop, the user is given two choices- unite (1) or findSet (2).

The user must enter either 1 or 2. If the user enters something else, the program displays an appropriate message, and goes on to the next iteration of the loop.

After the operation is done, the program prints the nodes along with their parents. 

In case of union operation, the user is asked to specify the keys of the nodes whose sets are to be united. 

Again, if the keys supplied are not valid, an apt error message is displayed and the loop goes to the next iteration.

Similarly, if the user chooses the findSet operation, the program asks the user to specify the key of the node whose set-leader is to be found.

In the process of findSet, path compression is also done, wherever possible.

Once the number of iterations exceeds m, the control comes out of the loop. The final status of the nodes and their parents is printed on the terminal.

All-in-all, I have tried to make the program as user-friendly as possible. 
