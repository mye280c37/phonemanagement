#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATION 50
#define MAX_FLOAT 99999.0
#define RANGE 100

int is_change;

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

ctd_ptr CENTROID[4];

void L2Distance(ctd_ptr, int*);
void move(ctd_ptr, int);
int str_to_int(char*, int);
int get_period(char*);
void initialize_centroid();
void cluster();
void update_centroid();
void update_cluster();
void clean();
//
void get_cluster();

