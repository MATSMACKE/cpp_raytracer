all:
	clang++ -o out/ray main.cpp -std=c++20 -O3 && ./out/ray > out/image.ppm