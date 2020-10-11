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

void tester() {
	user_t u;
	book_t b;
	user_accept(&u);
	user_display(&u);
	book_accept(&b);
	book_display(&b);
}

void sign_in() {
	// find the user in the users file.
	// check input password is correct.
	// if correct, call user_area() based on its role.
}

void sign_up() {
	// input user details from the user.
    user_t u;
	user_accept(&u);
    // write user details into the users file.
    user_add(&u);
}

int main() {
   // date_tester();
   //tester();
   int choice;
	do {
		printf("\n\n0. Exit\n1. Sign In\n2. Sign Up\nEnter choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: // Sign In
			sign_in();
			break;
		case 2:	// Sign Up
			sign_up();	
			break;
		}
	}while(choice != 0);
	return 0;
}
