#include <stdio.h>
#include <sqlite3.h>

void print_greeting();
sqlite3* connect_to_database(char *filename);

void
print_greeting()
{
	printf("AirWay\n");
}

sqlite3*
connect_to_database(char *filename)
{
	sqlite3 *db;

	int rc = sqlite3_open(filename, &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return NULL;
	} 

	return db;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "No database to connect to.\n");
		return 1;
	}
	sqlite3 *db = connect_to_database(argv[1]);
	if (!db) {
		return 2;
	}
	print_greeting();
	return 0;
}
