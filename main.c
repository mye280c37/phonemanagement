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
    int try = 0;

    printf("1. view all\n");
    printf("2. search\n");
    printf("3. garbage\n");
    printf("4. exit\n");

    printf("\nchoose option: ");
    scanf("%d", &key);

    while(try < 3 && (key <1  || key >4)){
        printf("this is WRONG key. please enter right key from 1 to 4\n");
        printf("\nchoose option: ");
        scanf("%d", &key);
        try++;
    }

    if (try >= 3){
        printf("eixt program\n");
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
    
    if (count == 0){
        printf("\nNo results found for %s.\n", count, input);
    }
    else {
        printf("%d results found for %s.\n", count, input);
    }
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
            if(strcmp(strupr(temp), strupr(y)) == 0) return 1;
        }
    }
    return 0;
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
