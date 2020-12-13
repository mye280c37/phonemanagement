#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define IS_FULL (ptr) (!(ptr))
#define MAX_SIZE 150;

typedef struct node* node_pointer;
typedef struct contact{
       char name[MAX_SIZE];
       char phoneNum[MAX_SIZE];
       char email[MAX_SIZE];
       int frequency;
       char date;
       node_pointer next;
};

/* GLOBAL VARIABLES */

FILE *fp;      /*     input file     */
FILE *fp2     /*     output file   */
clock_t start_t, end_t, total_t;

//void menu(char[]);

/*void display(char []); */ //displays contact information in format
void menuButton(); /* button to return to main menu */
int doesExist(char char1[], char char2[]); /* checks if contact (that is searched) exists or not */
void search(FILE *fp); /* finds searched name */
void alphabeticalSort(char name[], char phoneNum[], char email[], char date[], char days[]);  /* alphabetically sorts names */

/*int main(void){
       //FILE *fp;
       int range;
       //char menu[], email[MAX_SIZE], phoneNum[MAX_SIZE], email[MAX_SIZE], date [MAX_SIZE], days[MAX_SIZE];

       fp = fopen("input.txt");
       fp2 = fopen("output.txt");

       if (fp == NULL){
              printf("Couldn't Search for file!\n");
              exit(0);
       }

       /* scanning inputs from "input.txt" */
       /* range = fgetc(fp);
       while (fp != NULL &&  fp != EOF){
              fscanf(fp, "%c %ld %c %ld %d\n", &name[i], &phoneNum[i], &email[i], &date[i], &days[i]);
              alphabeticalSort(&name[i], &phoneNum[i], &email[i], &date[i], &days[i]);
       }

       /* MENU */
       /* switch (menu){
              case 1:
              searchI();
              case 2:
              case 3:
              default:
       } */

       //areturn 0;
//}

/* sorts contact list in alphabetical order */
void alphabeticalSort(FILE *fp){
       int count = 0;
       char temp[MAX_SIZE], str[MAX_SIZE];
       while(fp != NULL && fp != EOF){
              count++;
              fscanf(fp, "%", &str[count]);
       }
       for (int i = 0; i < count; i++){
              for (j = i + 1; j < count; j++){
                     if (strcmp()){
                            /*exchange(next, node); */
                            strcpy(temp, str[i]);
                            strcpy(str[i], str[j]);
                            strcpy(str[j], temp);
                     }
              }
       }
}

/* void exchange(char a[], char b[]){
       char temp[MAX_SIZE];

} */

/* void menu(){

} */

void search(FILE *fp){
       Contact index;
       char searchInput[MAX_SIZE];
       int result, count = 0;
       printf("\n\n\n\t\t=============== [ SEARCH ] ==============\n\n\n")
       printf("Enter Contact to Be Searched For: ")
       scanf("%c", &searchInput[]);
       while (fread(&index, sizeof(index), 1, fp) == 1){
              result = doesExist(&index,name,  searchInput)
              if (result == 1){
                     count++;
                     end_t = clock();
                     printf("\t\t Name : %s \n\t\t Email : %s \n\t\t Phone No : %s \n\t\t Date Last Searched : %d", index.name, index.phoneNum, index.email, index. date);

              }

       }
       fclose(fp);
       printf("Showing %d results for : %s", count, searchInput);

       menuButton();
}

int doesExist(char char1[], char char2[]){
       int count;
       char *ptr,  tmp[strlen(char1)];
       if (strlen(char1) > strlen(char2)){
              for (int i = 0; i < (strlen(char1) - strlen(char2)); i++){
                     ptr = &char1[i];
                     count = 0;
                     while (count ++ != strlen(b)){
                            tmp[count] = *(p + k);
                     }
                     tmp[count] = '\0';
                     if (strcmp(strupr(tmp), strupr(b)) == 0) return 1;
              }
       }
       return 0;
}

/*void display(contact , contact ){
       contact person1;
       printf("Name : %s\n", person1.name);
       printf("Phone Number : %s\n", person1.phoneNum);
       printf("Email : %s\n", person1. email);
       printf("Date Last Searched : %d\n", person1.date);
       printf("Frequency : %d\n", person1.frequency);
} */

void menuButton(){
       char button;
       printf("\n\n\t\t PRESS ANY KEY TO RETURN TO MAIN MENU  . . . \t\t");
       button = getche();
       if(button != ' ' ) system("cls");
       /* insert return to main menu function here */
}
