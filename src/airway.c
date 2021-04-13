#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define QUERY_ALL_FLIGHTS "SELECT * FROM Flights"
#define Q_ALL_FLIGHTS	'F'
#define QUERY_ALL_HELICOPTERS "SELECT * FROM Helicopters"
#define Q_ALL_HELICOPTERS	'H'
#define QUERY_ALL_PILOTS "SELECT * FROM Pilots"
#define Q_ALL_PILOTS	'P'
#define QUERY_1 "SELECT Helicopters.brand, sum(Flights.hours) FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Helicopters.last_overhaul < Flights.date;"
#define Q_1 'o'
#define QUERY_2 "SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), Flights.id, Flights.date FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number;"
#define Q_2 'f'

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
	printf("%c\t%s\n", Q_ALL_HELICOPTERS, QUERY_ALL_HELICOPTERS);
	printf("%c\t%s\n", Q_ALL_PILOTS, QUERY_ALL_PILOTS);
	printf("%c\t%s\n", Q_ALL_FLIGHTS, QUERY_ALL_FLIGHTS);
	printf("%c\t%s\n", Q_1, QUERY_1);
	printf("%c\t%s\n", Q_2, QUERY_2);
	printf("\n");
	printf("\033[32m");
	system("/bin/stty raw");
	char c = getchar();
	system("/bin/stty cooked");
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
		case Q_ALL_HELICOPTERS:
			strcpy(query, QUERY_ALL_HELICOPTERS);
			break;
		case Q_ALL_PILOTS:
			strcpy(query, QUERY_ALL_PILOTS);
			break;
		case Q_ALL_FLIGHTS:
			strcpy(query, QUERY_ALL_FLIGHTS);
			break;
		case Q_1:
			strcpy(query, QUERY_1);
			break;
		case Q_2:
			strcpy(query, QUERY_2);
			break;
		default:
			printf("\033[33mᐱ unknown query\033[0m\n", qn);
			continue;
		}
		if (done) break;
		printf("\n");
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
