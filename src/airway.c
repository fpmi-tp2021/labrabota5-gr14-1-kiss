#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "queries.h"

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
	printf("%c\t%s\n", Q_IMAGE, QUERY_IMAGE);
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

	for(i = 0; i<argc; i++) {
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
	sqlite3_stmt *pStmt;
	char query[250];
	int done = 0, rc = 0, bytes = 0;
	void *farbfeld_image;
	while (!done) {
		char qn = ask_query();
		switch (qn) {
		case 'q':
			done = 1;
			break;
		case Q_IMAGE:
			strcpy(query, QUERY_IMAGE);
			rc = sqlite3_prepare_v2(db, query, -1, &pStmt, 0);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "Failed to prepare statement\n");
			}
			rc = sqlite3_step(pStmt);
			if (rc == SQLITE_ROW) {
				bytes = sqlite3_column_bytes(pStmt, 0);
				printf("read %d bytes\n", bytes);
			}
			farbfeld_image = sqlite3_column_blob(pStmt, 0);
			if (strncmp(farbfeld_image, "farbfeld", 8) == 0) {
				printf("read farbfeld data\n");
			}
			printf("\n");
			continue;
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
