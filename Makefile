all:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11 -Wall -Wextra -g -fsanitize=undefined,address
	
