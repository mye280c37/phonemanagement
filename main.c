#include "main.h"
#include "clustering.h"

int main() {
    FILE *fp;
    fp = fopen("input_project.txt", "r");
    read(fp);
    fclose(fp);
    cluster();
    menu();

    return 0;
}

void menu(){
    int t = 0;

    printf("1. view all\n");
    printf("2. search\n");
    printf("3. garbage\n");
    printf("4. exit\n");

    printf("\nchoose option: ");
    scanf("%d", &key);

    while(t < 3 && (key <1 || key >4)){
        printf("this is WRONG key. please enter right key from 1 to 4\n");
        printf("\nchoose option: ");
        scanf("%d", &key);
        t++;
    }

    if (t >= 3){
        printf("ext program\n");
        exit(1);
    }

    execute();
}

void option(){
    printf("===========option===========\n");
    printf("0. go back\n");
    switch (key) {
        case DISPLAY:
            printf("6. delete\n");
            break;
        case SEARCH:
            printf("2. continue searching\n");
            break;
        case GARBAGE:
            printf("5. recover \n");
            break;
        case RECOVER:
            printf("1. view all\n");
            break;
        case DELETE:
            printf("3. garbage\n");
            break;
        case EXIT:
            exit_program();
    }
    printf("4. exit\n");
    printf("============================\n");
    printf("\nchoose option: ");

    scanf("%d", &key);
    printf("\n");

    execute();
}

void execute(){
    switch (key) {
        case BACK:
            menu();
            break;
        case DISPLAY:
            display();
            break;
        case SEARCH:
            search();
            break;
        case GARBAGE:
            garbage();
            break;
        case EXIT:
            exit_program();
        case RECOVER:
            recover();
            break;
        case DELETE:
            delete_data();
            break;
    }
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

void read(FILE* fp){
    char tname[20]="";
    char tnumber[30]="";
    char temail[40]="";
    char tlatestdate[20]="";
    int tfrequency=0;

    node_pointer temp, last;


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

}

void write(node_pointer node) {
    node_pointer temp = node;
    int i = 0;

    while (temp!=NULL) {

        printf("%d| ", i);
        printf("%s ", temp->name);
        printf("%s ", temp->number);
        printf("%s ", temp->email);
        printf("%s ", temp->latestdate);
        printf("%d ", temp->frequency);
        printf("\n");
        temp = temp->next;
        i++;
    }
}

void display()
{
    alphabetical_sort();
    printf("\n[all]\n");
    write(head);
    printf("\n");
    option();
}

void search()
{
    searchOperation();
    printf("\n");
    option();
}

void garbage()
{
    printf("\n[deleted]\n");
    write(del_head);
    printf("\n");
    option();
}

void delete_data()
{
    int target, i=0;
    node_pointer tmp = head, preNode = NULL;
    printf("\ndelete_data\n\n");
    write(head);
    printf("\n----------------------------------------------------\n");
    printf("Enter a data number that you want to delete: ");
    scanf("%d", &target);
    while(tmp != NULL){
        if(target == i)
            break;
        preNode = tmp;
        tmp = tmp->next;
        i++;
    }
    // delete from origin list
    if(preNode != NULL){
        preNode->next = tmp->next;
    }
    else{
        head = tmp->next;
    }
    // add to deleted list
    node_pointer del_tmp = del_head;
    while(del_tmp->next != NULL){
        del_tmp = del_tmp->next;
    }
    del_tmp->next = tmp;
    tmp->next = NULL;
    printf("\n");
    option();
}

void recover()
{
    write(del_head);
    int i;
    int n = 0;
    node_pointer temp4=del_head;
    int c = 1;
    while (temp4 != NULL) {
        temp4 = temp4->next;
        c++;
    }

    printf("\n---------------------recover--------------------------\n");
    printf("Enter a data number that you want to recover: ");
    scanf("%d", &n);
    if (n > c) {
        printf("invalid number.\n");
        printf("\n----------------------------------------------------\n");
        printf("Enter a data number that you want to delete: ");
        scanf("%d", &n);
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int target_year, target_month, target_day;
    target_year = tm.tm_year + 1900;
    target_month = tm.tm_mon + 1;
    target_day = tm.tm_mday;
    char str0[30];
    char str1[20];
    char str2[20];
    sprintf(str0, "%d", target_year);
    sprintf(str1, "%d", target_month);
    sprintf(str2, "%d", target_day);
    strcat(str0, str1);
    strcat(str0, str2);

    node_pointer temp1;
    temp1 = NULL;

    node_pointer temp;
    temp = del_head;
    for (i = 0; i < n; i++) {
        temp1 = temp;
        temp = temp->next;
    }

    if (temp1 != NULL) {
        temp1->next = temp->next;
    }
    else {
        del_head = temp->next;
    }



    node_pointer temp2;
    temp2 = head;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }

    temp2->next = temp;
    strcpy(temp->latestdate, str0);
    temp->next = NULL;

    printf("\n");
    option();
}

void writefile(FILE* fw) {
    node_pointer temp;
    temp = head;
    while (temp != NULL) {
        fprintf(fw, "%s %s %s %s %d\n", temp->name, temp->number, temp->email, temp->latestdate, temp->frequency);
        temp = temp->next;
    }
    temp = del_head;
    while (temp != NULL) {
        fprintf(fw, "%s %s %s %s %d\n", temp->name, temp->number, temp->email, temp->latestdate, temp->frequency);
        temp = temp->next;
    }
}

void searchOperation(){
    int boolean, count = 0;
    char input[20];
    node_pointer temp = head;

    printf("Enter name to be searched: ");
    scanf("%s", input);
    printf("%s\n", input);
    do{
        boolean = does_exist(temp -> name, input);
        if(boolean == 1){

            /* makes a list of the searched results and each will be outputed in format */
            count++;
            printf("%d. Name: %s\n", count, temp -> name);
            printf("\tNumber: %s\n", temp -> number);
            printf("\tEmail: %s\n", temp -> email);
            printf("\tLast searched: %s\n", temp -> latestdate);

            temp -> frequency++; //updates the number of frequencies searched

        }
        /* moves to make next comparison */
        temp = temp -> next;
    }while(temp != NULL);
     
    printf("%d results found for %s.\n", count, input);
    
}

int does_exist(char x[], char y[]){
    
    int i, j;
    char *p, temp[strlen(y)];
    if(strlen(x) >= strlen(y)){
        for(i = 0; i <= (strlen(x) - strlen(y)); i++){
            p = &x[i];
            j = 0;
            while(j != strlen(y)){
                temp[j] = *(p + j);
                j++;
            }
            temp[j] = '\0';
            to_up(temp);
            to_up(y);
            if(strcmp(temp, y) == 0) return 1;
        }
    }
    return 0;
}

void to_up(char *p)
{
    while(*p){
        *p = toupper(*p);
        p++;
    }
}

void alphabetical_sort(){
    node_pointer preNode = NULL;
    node_pointer lastNode = NULL;
//    while(lastNode->next != NULL){
//        lastNode = lastNode->next;
//    }
    node_pointer node1 = head;
    node_pointer node2 = head -> next;
    while(lastNode != head){
        while(node2 != lastNode){
            if(strcmp(node1 -> name, node2 -> name) > 0){
                if(preNode != NULL){
                    preNode->next = node2;
                    node1->next = node2->next;
                    node2->next = node1;
                    // change target
                    preNode = preNode->next;
                    node1 = preNode->next;
                    node2 = node1->next;
                }
                else{
                    head = node2;
                    node1->next = node2->next;
                    node2->next = node1;
                    // change target
                    preNode = head;
                    node1 = preNode->next;
                    node2 = node1->next;
                }
            }
            else{
                preNode = node1;
                node1 = preNode->next;
                node2 = node1->next;
            }
        }
        lastNode = node1;
        preNode = NULL;
        node1 = head;
        node2 = node1->next;
    }
}

void exit_program(){

    FILE* fw;
    fw = fopen("input_project.txt", "w");
    writefile(fw);
    fclose(fw);

    node_pointer preNode = NULL,tmp = head;
    while(tmp != NULL){
        preNode = tmp;
        tmp=tmp->next;
        free(preNode);
    }
    preNode = NULL; tmp = del_head;
    while(tmp != NULL){
        preNode = tmp;
        tmp=tmp->next;
        free(preNode);
    }
    printf("exit program\n");
    exit(0);
}

void L2Distance(ctd_ptr target_node, int *new_ctd){
    float min_dist = MAX_FLOAT;
    int x_freq = target_node->frequency;
    int	y_per = target_node->period;

    for(int i=0; i<CTD_NUM; i++){
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

    for(i=0; i<CTD_NUM; i++){
        CENTROID[i] = (ctd_ptr)malloc(sizeof(centroid));
        CENTROID[i]->frequency = rand()%RANGE;
        CENTROID[i]->period = rand()%RANGE;
        CENTROID[i]->next = NULL;
        CENTROID[i]->tag = ctd;
        CENTROID[i]->u.total = 0;
    }

    for(i=0; i<CTD_NUM-1; i++){
        CENTROID[i]->next = CENTROID[i+1];
    }
}


void update_centroid(){
    for(int i=0; i<CTD_NUM; i++){
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
        if (ctd_tmp->period > 60000){
            printf("%s\n", node_tmp->name);
            printf("%s\n", node_tmp->latestdate);
        }
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

    if(per > 653854){
        printf("%s\n", latestdate);
        printf("%d-%d-%d vs %d-%d-%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, target_year, target_month, target_day);
    }

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
    int MAX_Gradient = CENTROID[0]->frequency?CENTROID[0]->period/CENTROID[0]->frequency: CENTROID[0]->period;
    int del_cluster = 0;
    for(int c = 1; c<CTD_NUM; c++) {
        int gradient = CENTROID[c]->frequency ? CENTROID[c]->period / CENTROID[c]->frequency : CENTROID[c]->period;
        if (MAX_Gradient < gradient) {
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