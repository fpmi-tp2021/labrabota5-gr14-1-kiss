SQLITE=sqlite3
DB=flights.db
SQLDIR=sql
SQL_SCRIPTS=$(wildcard $(SQLDIR)/*)

$(DB): $(SQL_SCRIPTS)
	-for script in $(SQL_SCRIPTS); \
	do \
	$(SQLITE) <$$script $(DB) ; \
	done

clean:
	-rm $(DB)

.PHONY: clean
