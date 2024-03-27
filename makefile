build: n-queen-problem.o script.o
	g++ n-queen-problem.o script.o -o n-queen-problem

run:
	make clean
	make build
	./n-queen-problem

debug: script.o
	g++ -g n-queen-problem.cpp script.o

n-queen-problem.o: n-queen-problem.cpp
	g++ -c n-queen-problem.cpp

script.o: script.cpp
	g++ -c script.cpp

clean:
	del *.o
	del n-queen-problem.exe

cleanLin:
	rm -rf *.o
	rm -rf n-queen-problem