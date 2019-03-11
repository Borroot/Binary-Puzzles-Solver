make: binarysolver

binarysolver: BinarySolver.cpp
	g++ -o BinarySolver BinarySolver.cpp

clean: 
	rm BinarySolver
