#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
#define IS_FULL(ptr) (!(ptr))
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef struct node* node_pointer;
typedef struct node {
	char name[20];
	char number[30];
	char email[40];
	char latestdate[20];
	int frequency;
	node_pointer next;
}node;

int key;
node_pointer head, del_head;

void menu();
void display();
node_pointer read(FILE* fp);
void write(node_pointer node);
void recover(node_pointer head, node_pointer del_head);
void garbage();

node_pointer new_node();

int main(void) {
	FILE* fp;
	fp = fopen("input_project.txt", "r");
	node_pointer a;
	a = read(fp);
	write(a);
}

node_pointer read(FILE* fp) {
	char tname[20]="";
	char tnumber[30]="";
	char temail[40]="";
	char tlatestdate[20]="";
	int tfrequency=0;

	node_pointer temp, head, last;
	

	fscanf(fp, "%s %s %s %s %d", tname, tnumber, temail, tlatestdate, &tfrequency);
	temp = new_node();
	

	strcpy(temp->name, tname);
	strcpy(temp->number, tnumber);
	strcpy(temp->email, temail);
	strcpy(temp->latestdate, tlatestdate);
	temp->frequency = tfrequency;
	
	//printf("%s %s %s %s %d", temp->name, temp->number, temp->email, temp->latestdate, temp->frequency);

	head = temp;

	last = temp;

	while (fscanf(fp, "%s %s %s %s %d", tname, tnumber, temail, tlatestdate, &tfrequency) != EOF) {
		temp = new_node();
		
		strcpy(temp->name, tname);
		strcpy(temp->number, tnumber);
		strcpy(temp->email, temail);
		strcpy(temp->latestdate, tlatestdate);
		temp->frequency = tfrequency;
		//printf("%s %s %s %s %d", temp->name, temp->number, temp->email, temp->latestdate,temp->frequency);
		
		last->next = temp;
		last = temp;

	}
	
	return head;

}

void write(node_pointer node) {
	node_pointer temp = node;
	int i = 0;
	
	while (temp!=NULL) {
		
		fprintf(stderr,"%d ", i);
		printf("%s ", temp->name);
		printf("%s ", temp->number);
		printf("%s ", temp->email);
		printf("%s ", temp->latestdate);
		printf("%d ", temp->frequency);
		printf("\n");
		temp = temp->next;
		i++;
	}
	return;
}

void garbage() {
	write(del_head);

	
	//option(); 2번->recover(head, del_head);


	
}

void recover(node_pointer head, node_pointer del_head) {
	int i = 0;
	int n;
	printf("지울 연락처의 number를 입력하시오\n");
	scanf("%d", &n);

	node_pointer temp;
	temp = del_head;
	for (i = 0; i < n-1; i++) {
		temp = temp->next;
	}
	node_pointer temp1;
	temp1 = del_head;
	for (int j = 0; j < n - 2; j++) {
		temp1 = temp1->next;
	}
	temp1->next = temp->next;
	node_pointer temp2;

	temp2 = head;
	while (temp2->next != NULL) {
		temp2 = temp2->next;
	}

	temp2->next = temp;
	temp->next = NULL;

	//option(); 2번->display();

}

node_pointer new_node( ) {
	node_pointer temp;
	temp= (node_pointer)malloc(sizeof(node));
	if (IS_FULL(temp)) {
		printf("Error!");
		exit(-1);
	}
	temp->next = NULL;
	return temp;
}
