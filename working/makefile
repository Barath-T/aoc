CC = clang++ 
FILE=main

compile: $(FILE).cpp
	$(CC) -g -o out/main $(FILE).cpp
run: $(FILE).cpp
	$(CC) -o out/main $(FILE).cpp
	./out/main < ./in/input.txt
runo: $(FILE).cpp
	$(CC) -o out/main $(FILE).cpp
	./out/main < ./in/input.txt > ./out/output.txt
debug: $(FILE).cpp
	$(CC) -g -o out/main $(FILE).cpp
	gdb ./out/main
clean:
	rm out/main out/output.txt
