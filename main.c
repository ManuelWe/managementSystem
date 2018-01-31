#include <stdio.h>
#include <string.h>

int nummer =0;

struct person_t{
        char name[50+1];
        float height;
        int age;
    };


void add(struct person_t* ptr){
    ptr += nummer;
    nummer++;
    char txt[50+1];
    float gr;
    int age;
    printf("Bitte einen Namen eingeben:");
    scanf("%s", &txt);
    printf("Gr��e:");
    scanf("%f", &gr);
    printf("Alter:");
    scanf("%d", &age);
    strcpy(ptr->name, txt);
    ptr -> height = gr;
    ptr -> age = age;
}

void print(struct person_t* ptr){
    for(int i=0;i<nummer;i++){
        printf("%s ist %f gro� und %d alt.\n",ptr->name,ptr->height,ptr->age);
        ptr++;
    }
}

void deleteP(struct person_t* ptr){
    nummer =0;
    for(int i=0;i<nummer;i++){
        strcpy(ptr->name, "");
        ptr->height = 0;
        ptr->age = 0;
        ptr++;
    }
}


int main(){

    struct person_t person[100];
    int auswahl=0;
    while(auswahl!=4){
        printf("Was m�chten Sie tun?\n (1) Add Person\n (2) Print all\n (3) Delete Person\n (4) End Programm\n");
        scanf("%d", &auswahl);
        switch(auswahl){
        case 1: add(person);
            break;
        case 2: print(person);
            break;
        case 3: deleteP(person);
            break;
        }
    }
return 0;
}







































