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
	char name[10];
	char number[20];
	char email[30];
	char latestdate[10];
	int frequency;
	node_pointer next;
};

node_pointer readphonebook(FILE* fp);
void writephbook(node_pointer node);
void recover_deletednode(int n, node_pointer head, node_pointer garbage);
node_pointer new_node();

int main(void) {
	FILE* fp;
	fp=fopen("input_project.txt", "r");
	node_pointer a;
	a = readphonebook(fp);
	writephbook(a);
}

node_pointer readphonebook(FILE* fp) {
	char name[10];
	char number[20];
	char email[30];
	char latestdate[10];
	int frequency;

	node_pointer temp, head, last;
	temp = new_node();
	
	fscanf(fp, "%s %s %s %s %d", name, number, email,latestdate, &frequency);
	strcpy(name, temp->name);
	strcpy(number, temp->number);
	strcpy(email, temp->email);
	strcpy(latestdate, temp->latestdate);
	temp->frequency = frequency;
	head = temp;

	last = head;

	while(1){
		if (fscanf(fp, "%s %s %s %s %d", name, number, email, latestdate, &frequency) == -1)
			break;
		//nullÀÌ¸é??//
		else {
			temp = new_node();
			strcpy(name,temp->name);
			strcpy(number,temp->number);
			strcpy(email,temp->email);
			strcpy(latestdate, temp->latestdate);
			temp->frequency = frequency;
			last->next = temp;
			last = temp;
			
		}
		
	}
	return head;
	
}

void writephbook(node_pointer node) {
	node_pointer temp=node;
	int i = 0;
	while (temp != NULL) {
		printf("%d ", i);
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

void recover_deletednode(int n, node_pointer head,node_pointer garbage) {
	int i = 0;
	node_pointer temp;
	temp = garbage;
	for (i = 0; i < n;i++) {
		temp = temp->next;
	}
	node_pointer temp2;
	temp2 = head;
	while (temp2->next!= NULL) {
		temp2 = temp2->next;
	}
	temp->next = temp2->next;
	temp2->next = temp;
	
}

node_pointer new_node() {
	node_pointer node;
	node = (node_pointer)malloc(sizeof(node));
	if (IS_FULL(node)) {
		printf("Error!");
		exit(-1);
	}
	return node;
}
