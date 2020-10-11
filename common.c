#include <stdio.h>
#include <string.h>
#include "library.h"


// user functions
void user_accept(user_t *u) {
	printf("id: ");
	scanf("%d", &u->id);
	printf("name: ");
	scanf("%s", u->name);
	printf("email: ");
	scanf("%s", u->email);
	printf("phone: ");
	scanf("%s", u->phone);
	printf("password: ");
	scanf("%s", u->password);
	strcpy(u->role, ROLE_MEMBER);
}

void user_display(user_t *u) {
	printf("%d, %s, %s, %s, %s\n", u->id, u->name, u->email, u->phone, u->role);
}

// book functions
void book_accept(book_t *b) {
	printf("id: ");
	scanf("%d", &b->id);
	printf("name: ");
	scanf("%s", b->name);
	printf("author: ");
	scanf("%s", b->author);
	printf("subject: ");
	scanf("%s", b->subject);
	printf("price: ");
	scanf("%lf", &b->price);
	printf("isbn: ");
	scanf("%s", b->isbn);
}

void book_display(book_t *b) {
	printf("%d, %s, %s, %s, %.2lf, %s\n", b->id, b->name, b->author, b->subject, b->price, b->isbn);
}


void user_add(user_t *u) {
	// open the file for appending the data
	FILE *fp;
	fp = fopen(USER_DB, "ab");
	if(fp == NULL) {
		perror("failed to open users file");
		return;
	}
	
	// write user data into the file
	fwrite(u, sizeof(user_t), 1, fp);
	printf("user added into file.\n");
	
	// close the file
	fclose(fp);
}

int user_find_by_email(user_t *u, char email[]) {
	FILE *fp;
	int found = 0;
	// open the file for reading the data
	fp = fopen(USER_DB, "rb");
	if(fp == NULL) {
		perror("failed to open users file");
		return found;
	}
	// read all users one by one
	while(fread(u, sizeof(user_t), 1, fp) > 0) {
		// if user email is matching, found 1
		if(strcmp(u->email, email) == 0) {
			found = 1;
			break;
		}
	}
	// close file
	fclose(fp);
	// return
	return found;
}