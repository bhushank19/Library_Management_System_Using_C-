#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "date.h"

void date_tester() {
	date_t d1 = {1, 1, 2000}, d2 = {31, 12, 2000};
	date_t d = {1, 1, 2000};
	date_t r = date_add(d, 366);
	date_print(&r);
	int diff = date_cmp(d1, d2);
	printf("date diff: %d\n", diff);
}


int main() {
	printf("Hello Library!\n");
    date_tester();
	return 0;
}
