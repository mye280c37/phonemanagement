#ifndef PHONEBOOKMANAGEMENT_MAIN_H
#define PHONEBOOKMANAGEMENT_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IS_FULL(ptr) (!(ptr))

#define BACK 0
#define DISPLAY 1
#define SEARCH 2
#define GARBAGE 3
#define EXIT 4
#define RECOVER 5
#define DELETE 6


#define MAX_ITERATION 50
#define MAX_FLOAT 99999.0
#define RANGE 100

typedef struct node_* node_pointer;
typedef struct node_ {
    char name[20];
    char number[30];
    char email[40];
    char latestdate[20];
    int frequency;
    node_pointer next;
} node;

clock_t start_t, end_t, total_t;

int key;

node_pointer head;
node_pointer del_head;

void menu();
void option();
void execute();
node_pointer new_node();
void read(FILE*);
void write(node_pointer);

// DISPLAY
void display();

// SORTING
void alphabetical_sort();

// SEARCH
void search();
// find data using KMP
void does_exist();

// DELETED
// delete data that user select
void delete_node();
/* About MENU 3, linked list about deleted data by clustering or user
   user can recover data in this option */
void garbage();
void delete_data();

// RECOVER
void recover();
#endif