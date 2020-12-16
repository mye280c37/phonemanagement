#ifndef PHONEBOOKMANAGEMENT_CLUSTERING_H
#define PHONEBOOKMANAGEMENT_CLUSTERING_H

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_ITERATION 50
#define MAX_FLOAT 99999.0
#define RANGE 100
#define CTD_NUM 4

typedef enum {ctd, data} tagfield;
typedef struct centroid_* ctd_ptr;
typedef struct centroid_{
    int frequency;
    int period;
	tagfield tag;
	ctd_ptr next;
	union{
		node_pointer info[2];
		int total;
	}u;
} centroid;

int is_change;
ctd_ptr CENTROID[CTD_NUM];

void L2Distance(ctd_ptr, int*);
void move(ctd_ptr, int);
int str_to_int(char*, int);
int get_period(char*);
void initialize_centroid();
void cluster();
void update_centroid();
void update_cluster();
void clean();

#endif
