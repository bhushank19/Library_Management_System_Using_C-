#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void librarian_area(user_t *u) {
	int choice;
	char name[80];
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
			case 4: // Add book
			        add_book();
				    break;
			case 5: // Find book
         			printf("Enter book name: ");
		    		scanf("%s", name);
			    	book_find_by_name(name);
                    break;
			case 6: // Edit Book
			        book_edit_by_id();
				    break;
			case 7: // Check Availability
			        bookcopy_checkavail_details();
				    break;
			case 8: // Add Copy
			        bookcopy_add();
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

void add_book() {
	FILE *fp;
	// input book details
	book_t b;
	book_accept(&b);
	b.id = get_next_book_id();
	// add book into the books file
	// open books file.
	fp = fopen(BOOK_DB, "ab");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// append book to the file.
	fwrite(&b, sizeof(book_t), 1, fp);
	printf("book added in file.\n");
	// close books file.
	fclose(fp);
}

void book_edit_by_id() {
	int id, found = 0;
	FILE *fp;
	book_t b;
	// input book id from user.
	printf("enter book id: ");
	scanf("%d", &id);
	// open books file
	fp = fopen(BOOK_DB, "rb+");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// read books one by one and check if book with given id is found.
	while(fread(&b, sizeof(book_t), 1, fp) > 0) {
		if(id == b.id) {
			found = 1;
			break;
		}
	}
	// if found
	if(found) {
		// input new book details from user
		long size = sizeof(book_t);
		book_t nb;
		book_accept(&nb);
		nb.id = b.id;
		// take file position one record behind.
		fseek(fp, -size, SEEK_CUR);
		// overwrite book details into the file
		fwrite(&nb, size, 1, fp);
		printf("book updated.\n");
	}
	else // if not found
		// show message to user that book not found.
		printf("Book not found.\n");
	// close books file
	fclose(fp);
}

void bookcopy_add() {
	FILE *fp;
	// input book copy details
	bookcopy_t b;
	bookcopy_accept(&b);
	b.id = get_next_bookcopy_id();
	// add book copy into the books file
	// open book copies file.
	fp = fopen(BOOKCOPY_DB, "ab");
	if(fp == NULL) {
		perror("cannot open book copies file");
		exit(1);
	}
	// append book copy to the file.
	fwrite(&b, sizeof(bookcopy_t), 1, fp);
	printf("book copy added in file.\n");
	// close books copies file.
	fclose(fp);
}

void bookcopy_checkavail_details() {
	int book_id;
	FILE *fp;
	bookcopy_t bc;
	int count = 0;
	// input book id
	printf("enter the book id: ");
	scanf("%d", &book_id);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb");
	if(fp == NULL) {
		perror("cannot open bookcopies file.");
		return;
	}

	// read bookcopy records one by one
	while(fread(&bc, sizeof(bookcopy_t), 1, fp) > 0) {
		// if book id is matching and status is available, print copy details
		if(bc.bookid == book_id && strcmp(bc.status, STATUS_AVAIL)==0) {
			bookcopy_display(&bc);
			count++;
		}
	}
	// close book copies file
	fclose(fp);
	// if no copy is available, print the message. 
	if(count == 0)
		printf("no copies availables.\n");
}
