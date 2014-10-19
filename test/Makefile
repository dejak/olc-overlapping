.PHONY: all
all:
	@make -C ..
# we cheat and delete the main.o file so we can link tests easily
	@rm ../bin/main.o
	@make -C unit
	@make -C functional
	@make -C integration

