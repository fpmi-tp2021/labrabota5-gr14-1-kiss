SQLITE=sqlite3
DB=flights.db
SQLDIR=sql
SQL_SCRIPTS=$(wildcard $(SQLDIR)/*)
CC=gcc
LIBS=-l sqlite3
SOURCE=./src/airway.c
PROGRAM=airway
BIN=bin

all: doc/report.pdf $(DB) $(BIN)/$(PROGRAM)

$(DB): $(SQL_SCRIPTS)
	-for script in $(SQL_SCRIPTS); \
	do \
	$(SQLITE) <$$script $(DB) ; \
	done

$(BIN)/$(PROGRAM):  $(SOURCE)
	-mkdir $(BIN)
	$(CC) $< -o $@ $(LIBS)

run: $(BIN)/$(PROGRAM) $(DB)
	./$(BIN)/$(PROGRAM) $(DB)

doc/report.pdf:
	cd doc && make

clean:
	-rm $(DB)
	-rm $(BIN)/$(PROGRAM)
	-rmdir $(BIN)
	-cd doc && make clean

.PHONY: clean run
