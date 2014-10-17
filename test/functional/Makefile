all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

# compile each .cpp file into .out file, run it and delete it after
%.out: %.cpp Makefile
	@g++ $< -o $@ -I.. -std=c++0x
	@./$@
	@rm $@

