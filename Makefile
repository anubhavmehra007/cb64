SHELL := /bin/bash
CC := gcc
CFLAGS := -Wall
TESTFLAGS := -lcriterion
OUTPUT := ./bin
EXECUTABLE := base_64_anubhav
SRC := ./src/
TESTS := ./tests/
MAIN := ./main.c
BINARY := $(OUTPUT)/$(EXECUTABLE)

SRCFILES := $(wildcard $(SRC)*.c)
TESTFILES := $(wildcard $(TESTS)*.c)

all: cleanbin create_bin $(SRCFILES) $(MAIN) test
	@echo "Making...";
	@$(CC) $(CFLAGS) -o $(OUTPUT)/$(EXECUTABLE) $(SRCFILES) $(MAIN)

create_bin: $(OUTPUT)
	@echo "Generating bin directory...";
	@mkdir -p $(OUTPUT)

test: cleantest $(SRCFILES) $(TESTFILES)
		@echo "Testing..."
		@for testf in $(TESTFILES) ; do \
		$(CC) $(CFLAGS) $(TESTFLAGS) -o $(basename $$testf).out $(SRCFILES) $$testf ; \
		echo "Testing $(basename $$testf)" ; \
		$(basename $$testf).out ; \
		done




run : all $(BINARY)
	@echo "Running...";
	@$(BINARY)

install : $(BINARY) 
	@echo "Installing...";
	@mv $(BINARY) /usr/local/bin/


cleantest:
	@echo "Cleaning Test Directory...";
	@-rm -f $(TESTS)*.out

cleanbin:
	@echo "Cleaning Bin Directory...";
	@-rm -f $(OUTPUT)/*

clean: cleantest cleanbin

