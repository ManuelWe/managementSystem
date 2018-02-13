#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINES 35                          /* lines to be cleared for clearscreen */

struct person_t {
    char name[50 + 1];
    float height;
    int age;
    struct person_t *next;
    struct person_t *prev;
};

void deleteAll(struct person_t **head);
void deletePerson(struct person_t **head, char *name);
void editRecord(struct person_t *head, char *name);
void addRecord(struct person_t **head, char *name, float height, int age);
void enterData(struct person_t **head);
void testPersons(struct person_t **head);
void readFile(struct person_t **head);
void printAll(struct person_t *head);
void search(struct person_t *head, char *name);
void calculateMem(struct person_t *head);
void writeFile(struct person_t **head);
void print_menu (void);
void print_submenu_sort (void);
void print_submenu_delete (void);
void print_submenu_show (void);
void clearscreen (int lines);
int countElements(struct person_t *head);
void bubblesort(struct person_t **head);

int main() {

    struct person_t *head;

    char choice;
    char name[20 + 1];
    clearscreen (LINES);
    print_menu ();

    choice = getchar ();
    getchar ();
    while (choice!='0')
    {
        switch (choice)
        {
            case '1' : enterData(&head);
                break;
            case '2' : printf("Bitte geben Sie den Namen ein:");
                scanf("%s", &name);
                editRecord(head, name);
                break;
            case '3' : {
                clearscreen (LINES);
                print_submenu_show ();
                choice = getchar ();
                getchar ();
                while (choice!='0')
                {
                    switch (choice)
                    {
                        case '1' : printAll(head);
                            break;
                        case '2' :
                            printf("Please enter a name:");
                            scanf("%s", &name);
                            search(head, name);
                            break;
                        case '0' : break;
                        default  : printf ("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf ("Press ENTER to continue.\n");
                    getchar ();
                    clearscreen (LINES);
                    print_submenu_show ();
                    choice = getchar ();
                    getchar ();
                } /* end of while */
                printf ("\n-> Thanks for using the show functions.\n\n");
            };
                break;
            case '4' : {
                clearscreen (LINES);
                print_submenu_delete ();
                choice = getchar ();
                getchar ();
                while (choice!='0')
                {
                    switch (choice)
                    {
                        case '1' : deleteAll(&head);
                            break;
                        case '2' :
                            printf("Bitte geben Sie den Namen ein:");
                            scanf("%s", &name);
                            deletePerson(&head, name);
                            break;
                        case '0' : break;
                        default  : printf ("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf ("Press ENTER to continue.\n");
                    getchar ();
                    clearscreen (LINES);
                    print_submenu_delete ();
                    choice = getchar ();
                    getchar ();
                } /* end of while */
                printf ("\n-> Thanks for using the deleting functions.\n\n");
            };
                break;
            case '5' : writeFile(&head);
                break;
            case '6' : readFile(&head);
                break;
            case '7' : {
                clearscreen (LINES);
                print_submenu_sort ();
                choice = getchar ();
                getchar ();
                while (choice!='0')
                {
                    switch (choice)
                    {
                        case '1' : bubblesort(&head);
                            break;
                        case '2' : printf ("\n-> Option \"quicksort\" is currently not implemented.\n\n");
                            break;
                        case '0' : break;
                        default  : printf ("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf ("Press ENTER to continue.\n");
                    getchar ();
                    clearscreen (LINES);
                    print_submenu_sort ();
                    choice = getchar ();
                    getchar ();
                } /* end of while */
                printf ("\n-> Thanks for using the sorting functions.\n\n");
            };
                break;
            case '8' : calculateMem(head);
                break;
            case '0' : break;
            case '9' : for(int i=0; i<8; i++) {                   //zu debugging zwecken; muss entfernt werden
                    testPersons(&head);
                }
            default  : printf ("\n-> Please use a valid input.\n\n");
                break;
        } /* end of switch */

        printf ("Press ENTER to continue.\n");
        getchar ();
        clearscreen (LINES);
        print_menu ();
        choice = getchar ();
        getchar ();
    } /* end of while */
    printf ("\n-> Thanks for using My Filecard System.\n\n");
    getchar ();

    return (0);
}

void addRecord(struct person_t **head, char *name, float height, int age) {

    struct person_t *ptr = *head;
    struct person_t *person = (struct person_t *) malloc(sizeof(struct person_t));
    if (*head == NULL) {
        person->next = NULL;
        person->prev = NULL;
        *head = person;
    } else {
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = person;
        person->next = NULL;
        person->prev = ptr;
    }

    strcpy(person->name, name);
    person->height = height;
    person->age = age;
}

void enterData(struct person_t **head){
    char name[50 + 1];
    float height;
    int age;

    printf("Bitte einen Namen eingeben:");
    scanf("%s", &name);
    printf("Groesse:");
    scanf("%f", &height);
    printf("Alter:");
    scanf("%d", &age);
    addRecord(head, name, height, age);

}

void testPersons(struct person_t **head) {
    int counter=5;
    struct person_t *ptr = *head;
    struct person_t *person = (struct person_t *) malloc(sizeof(struct person_t));
    if (*head == NULL) {
        person->next = NULL;
        person->prev = NULL;
        *head = person;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = person;
        person->next = NULL;
        person->prev = ptr;
    }
    char txt[50 + 1] = "test";
    char value[10 + 1];
    sprintf(value, "%d", counter);
    strcat(txt, value);
    float gr = counter;
    int age = counter;
    strcpy(person->name, txt);
    person->height = gr;
    person->age = age;
}

void readFile(struct person_t **head){
    char name[50+1];
    float height;
    int age;
    char line[700+1];
    FILE *myFile;
    myFile = fopen("file.txt", "r");
    if (myFile == NULL){
        printf("Could not open file!\n");
    }

    while(fgets(line, 700+1, myFile)!= NULL) {
        if(strncmp(line, "//", 2)!=0){

            strcpy(name,strtok(line, ";"));
            height = strtof(strtok(NULL, ";"), 0);
            age = strtol(strtok(NULL, ";"), 0 ,10);
            addRecord(head ,name, height, age);
        }
    }
    fclose(myFile);
}

void deleteAll(struct person_t **head) {
    struct person_t *ptr = *head;
    struct person_t *temp;
    int deleteCounter = 0;
    while (ptr != NULL) {
        deleteCounter++;
        temp = ptr;
        free(ptr);
        ptr = temp->next;
    }
    *head = NULL;

    if (deleteCounter == 0) {
        printf("Nothing to delete!\n");
    } else {
        printf("%d Element(s) deleted!\n", deleteCounter);
    }
}

void deletePerson(struct person_t **head, char *name) {
    int deleteCounter = 0;
    if(*head) {
        struct person_t *ptr = *head;
        do {
            if (strcmp(ptr->name, name) == 0) {
                if (ptr->next != NULL) {
                    ptr->next->prev = ptr->prev;
                } else if (ptr != *head) {
                    ptr->prev->next = NULL;
                } else {
                    *head = NULL;
                }

                if (ptr->prev != NULL) {
                    ptr->prev->next = ptr->next;
                } else if (ptr != *head && *head != NULL) {
                    ptr->next->prev = NULL;
                } else {
                    *head = ptr->next;
                }

                free(ptr);
                deleteCounter++;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (deleteCounter == 0) {
        printf("There's no Person with name %s!\n", name);
    } else {
        printf("%d Element(s) deleted!\n", deleteCounter);
    }
    getchar();

}

void editRecord(struct person_t *head, char *name){
    int searchCounter = 0;
    char txt[50 + 1];
    float gr;
    int age;
    if(head) {
        struct person_t *ptr = head;
        do {
            if (strcmp(ptr->name, name) == 0) {

                printf("Please enter a new name for %s:", name);
                scanf("%s", &txt);
                printf("Groesse:");
                scanf("%f", &gr);
                printf("Alter:");
                scanf("%d", &age);
                strcpy(ptr->name, txt);
                ptr->height = gr;
                ptr->age = age;
                searchCounter++;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (searchCounter == 0) {
        printf("There's no Person with name %s!\n", name);
    } else {
        printf("%d Element(s) changed!\n", searchCounter);
    }
    getchar();
}

int countElements(struct person_t *head){
    struct person_t *ptr = head;
    int count = 0;
    while(ptr != NULL){
        count ++;
        ptr = ptr->next;
    }
    return count;
}

void bubblesort(struct person_t **head){
    int length = countElements(*head);
    struct person_t *ptr = *head;
    struct person_t *tmp;
    struct person_t *tmp1;
    for(int k=0; k<length-1; k++){
        for(int j=0; j<length-1; j++){
            if(strcmp(ptr->name, ptr->next->name) == 1){
                tmp = ptr->prev;
                tmp1 = ptr->next->next;

                ptr->prev = ptr->next;
                ptr->next->next = ptr;
                ptr->next->prev = tmp;
                ptr->next = tmp1;

                if(ptr->next) {
                    ptr->next->prev = ptr;
                }
                if(ptr->prev->prev) {
                    ptr->prev->prev->next = ptr->prev;
                }

                if(ptr == *head){
                    *head = ptr->prev;
                }
            }else {
                ptr = ptr->next;
            }
        }
        ptr = *head;
    }
}

void printAll(struct person_t *head) {
    struct person_t *ptr = head;
    while (ptr != NULL) {
        printf("%s ist %f gross und %d alt.\n", ptr->name, ptr->height, ptr->age);
        ptr = ptr->next;
    }
    printf("\n");

}

void search(struct person_t *head, char *name) {
    int searchCounter = 0;
    if(head) {
        struct person_t *ptr = head;
        do {
            if (strcmp(ptr->name, name) == 0) {
                printf("%s ist %f gross und %d alt.\n", ptr->name, ptr->height, ptr->age);
                searchCounter++;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (searchCounter == 0) {
        printf("There's no Person with name %s!\n", name);
    } else {
        printf("%d Element(s) shown!\n", searchCounter);
    }
    getchar();
}

void calculateMem(struct person_t *head){
    int structCounter = 0;
    if(head) {
        struct person_t *ptr = head;
        do {
            structCounter++;
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (structCounter == 0) {
        printf("There's no Memory allocated!\n");
    } else {
        float allocatedMem = sizeof(struct person_t)*structCounter;
        if(allocatedMem>=1024) {
            printf("%.3f kB Memory allocated!\n", allocatedMem/1024);
        }else{
            printf("%.f Bytes Memory allocated!\n", allocatedMem);
        }
    }
}

void writeFile(struct person_t **head){
    FILE *myFile;
    myFile = fopen("file.txt", "w+");
    printf("%d", myFile);
    struct person_t * ptr = *head;
    if(myFile==NULL){
        printf("Could not connect to file!");
    }
    fprintf(myFile, "//[name];[height];[age];\n");
    while(ptr != NULL) {

        fprintf(myFile, "%s;%.2f;%d\n", ptr->name, ptr->height, ptr->age);

        ptr = ptr->next;
    }
    fclose(myFile);
}

/* The function print_menue only prints a menu text on the screen */
void print_menu (void){
    printf ("\tMy Filecard System\n");
    printf ("\t------------------\n\n");
    printf ("\t1. Input record\n");
    printf ("\t2. Edit record\n");
    printf ("\t3. Show records\n");
    printf ("\t4. Delete record\n");
    printf ("\t5. File records\n");
    printf ("\t6. Load records\n");
    printf ("\t7. Sort records\n");
    printf ("\t8. Calculate used memory\n");
    printf ("\t0. End Program\n\n");
    printf ("Your choice is: ");
}

/* The function print_submenu_sorte only prints the submenu text on the screen */
void print_submenu_sort (void){
    printf ("\tChoose a sorting algorithm\n");
    printf ("\t--------------------------\n\n");
    printf ("\t1. bubblesort\n");
    printf ("\t2. quicksort\n");
    printf ("\t0. back to main menu\n\n");
    printf ("Your choice is: ");
}

void print_submenu_delete (void){
    printf ("\tChoose delete method\n");
    printf ("\t--------------------------\n\n");
    printf ("\t1. Delete all\n");
    printf ("\t2. Delete by name\n");
    printf ("\t0. back to main menu\n\n");
    printf ("Your choice is: ");
}

void print_submenu_show (void){
    printf ("\tChoose delete method\n");
    printf ("\t--------------------------\n\n");
    printf ("\t1. Show all\n");
    printf ("\t2. Search by name\n");
    printf ("\t0. back to main menu\n\n");
    printf ("Your choice is: ");
}

/* The function clearscreen does multiple LF to move the text from the screen.       */
void clearscreen (int lines){
    char i;
    for (i=0; i<lines; i++) printf ("\n");
}






































