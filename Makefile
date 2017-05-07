ARCH = $(shell uname -m)

CXXFLAGS = -std=c++11 -pipe -Wall -Wextra -fno-builtin -flto -fno-rtti
DFLAGS =
OFLAGS = -O3
LFLAGS = -pthread -L. -L/usr/local/lib/

ifeq ($(ARCH),x86_64)
	CXXFLAGS += -m64
endif

CXXFLAGS += $(OFLAGS) $(DFLAGS) -I.

OBJS = main.o minimizer.o minimize.o nucleotide.o nucleotides.o fastq_parser.o fasta_parser.o format_parser.o
PROGS = olc-overlapping

all: $(OBJS) $(PROGS)

olc-overlapping: $(OBJS)
	@$(CXX) -o bin/bioinf $(addprefix bin/, $(OBJS)) $(CXXFLAGS) $(LFLAGS)
	@strip bin/bioinf

.PHONY: clean
clean:
	@rm -f $(addprefix bin/, $(OBJS)) $(addprefix bin/, $(PROGS))
	@echo "Binary and object files cleaned."

.PHONY: test
test:
	@make -C test

$(OBJS): %.o: src/%.cpp
	@$(CXX) -o bin/$@ $(CXXFLAGS) -c $<
	@echo "[$(CXX)] $@"

