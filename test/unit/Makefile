all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

# compile each .cpp file into .out file, run it and delete it after
.PHONY: %.o
%.o: %.cpp Makefile
	@g++ -c -I.. -I../../src -std=c++0x $< -o $@

.PHONY: %.out
%.out: %.o
	@rm -f $@
	@g++ -std=c++0x ../../bin/*.o $< -o $@
	@./$@
	@rm $@ $<

