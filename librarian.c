#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void librarian_area(user_t *u) {
	int choice;
	do {
		printf("\n\n0. Sign Out\n1. Add member\n2. Edit Profile\n3. Change Password\n4. Add Book\n5. Find Book\n6. Edit Book\n7. Check Availability\n8. Add Copy\n9. Change Rack\n10. Issue Copy\n11. Return Copy\n12. Take Payment\n13. Payment History\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: // Add member
				    add_member();
				    break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
		}
	}while (choice != 0);		
}

void add_member() {
	// input member details
	user_t u;
	user_accept(&u);
	// add librarian into the users file
	user_add(&u);
}
