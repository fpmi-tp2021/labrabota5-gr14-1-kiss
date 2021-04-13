#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define QUERY1 "SELECT * FROM FLIGHTS"

void print_greeting();
sqlite3* connect_to_database(char *filename);
char ask_query();
static int callback(void *data, int argc, char **argv, char **azColName);

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

char
ask_query()
{
	printf("q\tquit\n");
	printf("0\tquery1\n");
	printf("1\tquery2\n");
	printf("2\tquery3\n");
	printf("\n");
	printf("\033[32m");
	system ("/bin/stty raw");
	char c = getchar();
	system ("/bin/stty cooked");
	printf("\033[0m\n");
	return c;
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
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
	char query[250];
	int done = 0;
	while (!done) {
		char qn = ask_query();
		switch (qn) {
		case 'q':
			done = 1;
			break;
		case '0':
			strcpy(query, QUERY1);
			break;
		case '1': /* FALLTHROUGH */
		case '2': /* FALLTHROUGH */
			strcpy(query, "\0");
			break;
		default:
			printf("\033[33mᐱ unknown query\033[0m\n", qn);
		}
		if (done) break;
		int rc = sqlite3_exec(db, query, callback, NULL, NULL);
		char *zErrMsg;
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}
	sqlite3_close(db);
	return 0;
}
