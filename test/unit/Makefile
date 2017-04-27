all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

# compile each .cpp file into .out file, run it and delete it after
.PHONY: %.o
%.o: %.cpp Makefile
	@$(CXX) -c -I.. -I../../src -flto -std=c++11 $< -o $@

.PHONY: %.out
%.out: %.o
	@rm -f $@
	@$(CXX) -flto -std=c++11 ../../bin/*.o $< -o $@
	@./$@
	@rm $@ $<

