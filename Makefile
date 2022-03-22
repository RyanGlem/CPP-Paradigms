lab2:
	echo "Running lab 2"
	cd calc/src && g++ main.cpp -o main && ./main
	$(RM) main