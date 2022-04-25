lab2:
	echo "Running lab 2"
	cd calc/src && g++ main.cpp -o main && ./main
	$(RM) main

lab3:
	echo "Running lab 3"
	cd bc_courses/src && g++ main.cpp data_stats.cpp data_format.cpp io.cpp -o main && ./main
	$(RM) main