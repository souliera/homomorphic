all:
	g++ -o a.out main.cpp -Wall -Wextra -g

clean:
	find . -type f -iname *.o -delete

mrproper:
	find . -type f -iname *.out -delete
