ALL:
	clang -lm -O3 -o integrators *.cpp

debug:
	clang -lm -O0 -g -o integrators-debug *.cpp
