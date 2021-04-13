#include <stdio.h>

void print_greeting();

void
print_greeting()
{
	printf("AirWay\n");
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "No database to connect to.\n");
		return 1;
	}
	print_greeting();
	return 0;
}
