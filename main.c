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
            exit(0);
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
            printf("exit program\n");
            exit(0);
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
    printf("\n[all]\n");
    write(head);
    printf("\n");
    option();
}

void search()
{
    printf("\nsearch\n\n");
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
    printf("\nrecover\n\n");
    option();
}
