#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person_t* head;
int counter = 0;

struct person_t
{
    char name[50+1];
    float height;
    int age;
    struct person_t* next;
    struct person_t* prev;
};


void add()
{
    struct person_t* ptr = head;
    struct person_t* person = (struct person_t*)malloc(sizeof(struct person_t));
    if(head == NULL)
    {
        head = person;
        head->next = NULL;
        head->prev = NULL;
    }
    else
    {
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = person;
        person->next = NULL;
        person->prev = ptr;
    }

    char txt[50+1];
    float gr;
    int age;
    printf("Bitte einen Namen eingeben:");
    scanf("%s", &txt);
    printf("Größe:");
    scanf("%f", &gr);
    printf("Alter:");
    scanf("%d", &age);
    strcpy(person->name, txt);
    person->height = gr;
    person->age = age;
}

void testPersons()
{
    counter++;
    struct person_t* ptr = head;
    struct person_t* person = (struct person_t*)malloc(sizeof(struct person_t));
    if(head == NULL)
    {
        head = person;
        head->next = NULL;
        head->prev = NULL;
    }
    else
    {
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = person;
        person->next = NULL;
        person->prev = ptr;
    }
    char txt[50+1] = "test";
    char value[10+1];
    sprintf(value, "%d", counter);
    strcat(txt, value);
    float gr = counter;
    int age = counter;
    strcpy(person->name, txt);
    person->height = gr;
    person->age = age;
}

void print()
{
    struct person_t* ptr = head;
    while(ptr != NULL)
    {
        printf("%s ist %f groß und %d alt.\n",ptr->name,ptr->height,ptr->age);
        ptr = ptr->next;
    }
    printf("\n");

}

void deleteAll()
{
    struct person_t* ptr = head;
    struct person_t* temp;
    while(ptr != NULL)
    {
        temp = ptr;
        free(ptr);
        ptr = temp->next;
    }
    head = NULL;
}

void deletePerson(char *name)
{
    struct person_t* ptr = head;
    int deleteCounter = 0;
    do
    {
        if(strcmp(ptr->name, name) == 0)
        {
            if(ptr->next != NULL)
            {
                ptr->next->prev = ptr->prev;
            }
            else if(ptr != head)
            {
                ptr->prev->next = NULL;
            }
            else
            {
                head = NULL;
            }

            if(ptr->prev != NULL)
            {
                ptr->prev->next = ptr->next;
            }
            else if(ptr != head && head != NULL)
            {
                ptr->next->prev = NULL;
            }
            else
            {
                head = ptr->next;
            }

            free(ptr);
            deleteCounter++;
        }
        ptr = ptr->next;
    }
    while(ptr != NULL);
    if(deleteCounter==0)
    {
        printf("There's no Person with name %s!\n", name);
    }
    else
    {
        printf("%d Element(s) deleted!\n", deleteCounter);
    }

}


int main()
{

    int auswahl=0;
    char name[20+1];

    while(auswahl!=5)
    {
        printf("Was möchten Sie tun?\n (1) Add Person\n (2) Print all\n (3) Delete Everything\n (4) Delete Person by Name\n (5) End Programm\n (6) Add Group of test Persons\n");
        scanf("%d", &auswahl);
        switch(auswahl)
        {
        case 1:
            add();
            break;
        case 2:
            print();
            break;
        case 3:
            deleteAll();
            break;
        case 4:
            printf("Bitte geben Sie den Namen ein:");
            scanf("%s", &name);
            deletePerson(name);
            break;
        case 5:
            break;
        case 6:
            for (int i=0; i<8; i++)
            {
                testPersons();
            }
            break;
        default:
            printf("Ungültige Eingabe!\n");
        }
    }
    return 0;
}







































