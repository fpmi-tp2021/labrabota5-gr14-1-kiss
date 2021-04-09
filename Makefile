SQLITE=sqlite3
DB=flights.db
SQLDIR=sql
SQL_SCRIPTS=$(wildcard $(SQLDIR)/*)
CC=gcc
LIBS=-l sqlite3
SOURCE=./src/query-sqlite.c
BIN=bin

all: $(DB) $(BIN)/query-sqlite

$(DB): $(SQL_SCRIPTS)
	-for script in $(SQL_SCRIPTS); \
	do \
	$(SQLITE) <$$script $(DB) ; \
	done

$(BIN)/query-sqlite:  $(SOURCE)
	-mkdir $(BIN)
	$(CC) $< -o $@ $(LIBS)

clean:
	-rm $(DB)
	-rm $(BIN)/query-sqlite
	-rmdir $(BIN)

.PHONY: clean
