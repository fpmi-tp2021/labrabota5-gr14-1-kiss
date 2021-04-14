SQLITE=sqlite3
DB=flights.db
SQLDIR=sql
SQL_SCRIPTS=$(wildcard $(SQLDIR)/*)
CC=gcc
LIBS=-l sqlite3 `pkg-config --libs chafa`
SOURCE=./src/farbfeld.c ./src/farbfeld-print.c ./src/airway.c
INCDIR=./include
PROGRAM=airway
BIN=bin

all: doc/report.pdf $(DB) $(BIN)/$(PROGRAM)

$(DB): $(SQL_SCRIPTS) plane.ff
	-for script in $(SQL_SCRIPTS); \
	do \
	$(SQLITE) <$$script $(DB) ; \
	done

$(BIN)/$(PROGRAM): $(SOURCE)
	-mkdir $(BIN)
	@echo `pkg-config --cflags chafa`
	$(CC) -I $(INCDIR) `pkg-config --cflags chafa` $^ -o $@ $(LIBS)

run: $(BIN)/$(PROGRAM) $(DB)
	./$(BIN)/$(PROGRAM) $(DB)

doc/report.pdf:
	cd doc && make

plane.ff:
	jpg2ff <plane.jpg >$@

clean:
	-rm $(DB)
	-rm plane.ff
	-rm $(BIN)/$(PROGRAM)
	-rmdir $(BIN)
	-cd doc && make clean

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

install: $(BIN)
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 $(BIN)/$(PROGRAM) $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM)

.PHONY: clean run
