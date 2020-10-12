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

// bookcopy functions
void bookcopy_accept(bookcopy_t *c) {
	printf("id: ");
	scanf("%d", &c->id);
	printf("name: ");
	scanf("%d", &c->bookid);
	printf("author: ");
	scanf("%d", &c->rack);
	strcpy(c->status, STATUS_AVAIL);
}

void bookcopy_display(bookcopy_t *c) {
	printf("%d, %d, %d, %s\n", c->id, c->bookid, c->rack, c->status);
}

// issuerecord functions
void issuerecord_accept(issuerecord_t *r) {
	printf("id: ");
	scanf("%d", &r->id);
	printf("copy id: ");
	scanf("%d", &r->copyid);
	printf("member id: ");
	scanf("%d", &r->memberid);
	printf("issue ");
	date_accept(&r->issue_date);
	r->return_duedate = date_add(r->issue_date, BOOK_RETURN_DAYS);
	memset(&r->return_date, 0, sizeof(date_t));
	r->fine_amount = 0.0;
}

void issuerecord_display(issuerecord_t *r) {
	printf("issue record: %d, copy: %d, member: %d, find: %.2lf\n", r->id, r->copyid, r->memberid, r->fine_amount);
	printf("issue ");
	date_print(&r->issue_date);
	printf("return due ");
	date_print(&r->return_duedate);
	printf("return ");
	date_print(&r->return_date);
}

// payment functions
void payment_accept(payment_t *p) {
	printf("id: ");
	scanf("%d", &p->id);
	printf("member id: ");
	scanf("%d", &p->memberid);
	printf("type (fees/fine): ");
	scanf("%s", p->type);
	printf("amount: ");
	scanf("%d", &p->amount);
	p->tx_time = date_current();
	if(strcmp(p->type, PAY_TYPE_FEES) == 0)
		p->next_pay_duedate = date_add(p->tx_time, MEMBERSHIP_MONTH_DAYS);
	else
		memset(&p->next_pay_duedate, 0, sizeof(date_t));
}

void payment_display(payment_t *p) {
	printf("payment: %d, member: %d, %s, amount: %.2lf\n", p->id, p->memberid, p->type, p->amount);
	printf("payment ");
	date_print(&p->tx_time);
	printf("payment due");
	date_print(&p->next_pay_duedate);
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