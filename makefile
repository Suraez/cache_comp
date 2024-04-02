run:
	rm ./main && clang++ main.cpp -o main && ./main
nclean:
	clang++ main.cpp -o main && ./main

run_sim:
	clang++ sim.cpp -o sim && ./sim