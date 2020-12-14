#include "clustering.h"

void L2Distance(ctd_ptr target_node, int *new_ctd){
    float min_dist = MAX_FLOAT;
    int x_freq = target_node->frequency;
    int	y_per = target_node->period;

    for(int i=0; i<4; i++){
        int delta_x = x_freq - CENTROID[i]->frequency;
        int delta_y = y_per - CENTROID[i]->period;
        float dist_i = (float)delta_x*delta_x + delta_y*delta_y;
        dist_i = (float)sqrt(dist_i);
        if(min_dist > dist_i){
            min_dist = dist_i;
            *new_ctd = i;
        }
    }
}

void initialize_centroid(){
    int i;

    srand(time(NULL));

    for(i=0; i<4; i++){
        CENTROID[i] = (ctd_ptr)malloc(sizeof(centroid));
        CENTROID[i]->frequency = rand()%RANGE;
        CENTROID[i]->period = rand()%RANGE;
        CENTROID[i]->next = NULL;
        CENTROID[i]->tag = ctd;
        CENTROID[i]->u.total = 0;
    }

    for(i=0; i<3; i++){
        CENTROID[i]->next = CENTROID[i+1];
    }
}


void update_centroid(){
    for(int i=0; i<4; i++){
        int total = CENTROID[i]->u.total;
        if(total != 0){
            int freq, per;
            freq = per = 0;
            ctd_ptr tmp = CENTROID[i]->next;
            while(tmp->tag != ctd){
                freq += tmp->frequency;
                per += tmp->period;
                tmp=tmp->next;
                if(tmp == NULL)
                    break;
            }
            if(CENTROID[i]->frequency != freq/total || CENTROID[i]->period != per/total) {
                is_change=1;
                CENTROID[i]->frequency = freq/total;
                CENTROID[i]->period = per/total;
            }
        }
        else{
            srand(time(NULL));
            CENTROID[i]->frequency = rand()%RANGE;
            CENTROID[i]->period = rand()%RANGE;
        }
    }
}


void initialize_cluster(){
    ctd_ptr ctd_tmp;
    node_pointer node_tmp = head, preNode = NULL;
    int new_ctd;

    while(node_tmp != NULL){
        ctd_tmp = (ctd_ptr)malloc(sizeof(centroid));
        ctd_tmp->tag = data;
        ctd_tmp->u.info[0] = preNode;
        ctd_tmp->u.info[1] = node_tmp;
        ctd_tmp->frequency = node_tmp->frequency;
        ctd_tmp->period = get_period(node_tmp->latestdate);
        ctd_tmp->next = NULL;
        L2Distance(ctd_tmp, &new_ctd);
        move(ctd_tmp, new_ctd);
        CENTROID[new_ctd]->u.total++;
        preNode = node_tmp;
        node_tmp = node_tmp->next;
    }
}

void update_cluster() {
    ctd_ptr tmp = CENTROID[0], preNode;
    int new_ctd, cur_ctd = -1;

    while (1) {
        if (tmp->tag == ctd){
            cur_ctd++;
            preNode = tmp;
            tmp = tmp->next;
        }
        else if (tmp->tag == data) {
            L2Distance(tmp, &new_ctd);
            if (cur_ctd != new_ctd) {
                is_change =1;
                preNode->next = tmp->next;
                CENTROID[cur_ctd]->u.total--;
                CENTROID[new_ctd]->u.total++;
                move(tmp, new_ctd);
                tmp = preNode->next;
            }
            else{
                preNode = tmp;
                tmp = tmp->next;
            }
        }

        if(tmp == NULL)
            break;
    }
}

void move(ctd_ptr tmp, int new_ctd){
    ctd_ptr postNode = CENTROID[new_ctd]->next;
    CENTROID[new_ctd]->next = tmp;
    tmp->next = postNode;
}

int str_to_int(char* str, int flag)
{
    int num = 0;

    switch (flag) {
        case 0:
            for(int i=0; i<4; i++){
                num *= 10;
                num += str[i]-'0';
            }
            break;
        case 1:
            for(int i=4; i<6; i++){
                num *= 10;
                num += str[i]-'0';
            }
            break;
        case 2:
            for(int i=6; i<8; i++){
                num *= 10;
                num += str[i]-'0';
            }
            break;
    }

    return num;
}


int get_period(char* latestdate){
    int per = 0;
    int target_year, target_month, target_day;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    target_year = str_to_int(latestdate, 0);
    target_month = str_to_int(latestdate, 1);
    target_day = str_to_int(latestdate, 2);

    per = (tm.tm_mday-target_day) + ((1+tm.tm_mon)-target_month)*31 + ((1900+tm.tm_year)-target_year)*365;

    return per;
}

void cluster()
{
    is_change = 0;
    initialize_centroid();
    initialize_cluster();

    for (int iteration = 1; iteration<MAX_ITERATION; iteration++){
        is_change = 0;
        update_centroid();
        update_cluster();
        if(!is_change)
            break;
    }
    // print all cluster
    //get_cluster();
    int MAX_Gradient = CENTROID[0]->frequency?CENTROID[0]->period/CENTROID[0]->frequency:MAX_INT;
    int del_cluster = 0;
    for(int c = 1; c<4; c++){
        int gradient = CENTROID[c]->frequency?CENTROID[c]->period/CENTROID[c]->frequency:MAX_INT;
        if(MAX_Gradient<gradient){
            MAX_Gradient = gradient;
            del_cluster = c;
        }
    }
    ctd_ptr tmp = CENTROID[del_cluster]->next;
    del_head = tmp->u.info[1];
    tmp->u.info[0]->next = tmp->u.info[1]->next;
    tmp->u.info[1]->next = NULL;
    tmp = tmp->next;
    node_pointer preNode = del_head;
    while(1){
        if(tmp == NULL || tmp->tag == ctd){
            preNode->next = NULL;
            break;
        }
        // delete node form origin list
        if(tmp->u.info[0] != NULL){
            tmp->u.info[0]->next = tmp->u.info[1]->next;
        }
        else{
            head = tmp->u.info[1]->next;
        }
        // add node to del_list
        preNode->next = tmp->u.info[1];
        tmp->u.info[1]->next = NULL;
        // move centroid
        tmp = tmp->next;
        // move del_list
        preNode = preNode->next;
    }
    clean();
}

void get_cluster(){
    int cnt;
    int ctd_index = 1;
    for(ctd_ptr tmp = CENTROID[0]; tmp != NULL; tmp=tmp->next){
        if (tmp->tag == ctd){
            cnt = 0;
            printf("\n\n<CLUSTER 0%d>\n", ctd_index++);
            printf("x: %d, y: %d, total: %d(tag: %d)\n\n", tmp->frequency, tmp->period, tmp->u.total, tmp->tag);
        }
        else{
            printf("%d| %d, %d\n", cnt++, tmp->frequency, tmp->period);
        }
    }
}

void clean()
{
    ctd_ptr tmp = CENTROID[0], postNode;

    while(tmp->next != NULL){
        postNode = tmp->next;
        free(tmp);
        tmp=postNode;
    }

    free(tmp);
}