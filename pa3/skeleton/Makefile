
todo_out: todo.o main.o given.o
	g++ -o todo_out todo.o main.o given.o
	rm *.o

todo.o: todo.cpp
	g++ -c todo.cpp

main.o: main.cpp
	g++ -c main.cpp

given.o: given.cpp
	g++ -c given.cpp
