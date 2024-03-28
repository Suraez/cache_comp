run:
	rm ./main && clang++ main.cpp -o main && ./main
nclean:
	clang++ main.cpp -o main && ./main