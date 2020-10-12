#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void member_area(user_t *u) {
	int choice;
	char name[80];
	do {
		printf("\n\n0. Sign Out\n1. Find Book\n2. Edit Profile\n3. Change Password\n4. Book Availability\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: // Find book
         			printf("Enter book name: ");
		    		scanf("%s", name);
			    	book_find_by_name(name);
                    break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		}
	}while (choice != 0);	
}
