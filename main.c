#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINES 35

struct person_t {
    char name[50 + 1];
    float height;
    int age;
    struct person_t *next;
    struct person_t *prev;
};

void deleteAll(struct person_t **head);

void deletePerson(struct person_t **head, char *searchBy, char *name);

void editRecord(struct person_t *head, char *searchBy, char *name);

void addRecord(struct person_t **head, char *name, float height, int age);

void enterData(struct person_t **head);

int readFile(struct person_t **head, char *filename);

void printAll(struct person_t *head, char *selection);

void search(struct person_t *head, char *searchBy, char *name);

void calculateMem(struct person_t *head);

void writeFile(struct person_t **head);

void print_menu(void);

void print_submenu_sort(void);

void print_submenu_delete(void);

void print_submenu_show(void);

void print_submenu_parameters(void);

void submenu_parameter_selection(struct person_t **head, char *methodSelection);

void print_submenu_print_all(void);

void clearscreen(int lines);

int countElements(struct person_t *head);

void bubblesort(struct person_t **head);

void insertionsort(struct person_t **head);

//INPUT: [OPTIONAL] Argumente die in der Console mitgegeben werden
//Hauptschleife, von wo die Funktionen, die der Nutzer auswählt, aufgerufen wird
int main(int argc, const char **argv) {

    struct person_t *head = NULL;
    char filename[50 + 1];
    char choice;
    int result;

    clearscreen(LINES);
    printf("\tWelcome to your personnel Management System\n");
    printf("\t------------------\n\n");
    if (argc == 1) {
        printf("\t1. You specified no file name to import data!\n\n");
    } else if (argc == 2) {
        strcpy(filename, argv[1]);
        result = readFile(&head, filename);
        if (result == 1) {
            printf("\t1. Data from file \"%s\" was read!\n\n", filename);
        }
    }
    printf("Press enter to get started\n");
    getchar();
    clearscreen(LINES);
    print_menu();
    choice = getchar();
    getchar();

    while (choice != '0') {
        switch (choice) {
            case '1' :
                enterData(&head);
                break;
            case '2' :
                submenu_parameter_selection(&head, "edit");
                break;
            case '3' : {
                clearscreen(LINES);
                print_submenu_show();
                choice = getchar();
                getchar();
                while (choice != '0') {
                    switch (choice) {
                        case '1' :
                            clearscreen(LINES);
                            print_submenu_print_all();
                            choice = getchar();
                            getchar();
                            while (choice != '0') {
                                switch (choice) {
                                    case '1':
                                        printAll(head, "ASC");
                                        break;
                                    case '2':
                                        printAll(head, "DESC");
                                        break;
                                    case '0':
                                        break;
                                    default:
                                        printf("\n-> Please use a valid input.\n\n");
                                        break;
                                }

                                printf("Press ENTER to continue.\n");
                                getchar();
                                clearscreen(LINES);
                                print_submenu_print_all();
                                choice = getchar();
                                getchar();
                            }
                            break;
                        case '2' :
                            submenu_parameter_selection(&head, "search");
                            break;
                        case '0' :
                            break;
                        default  :
                            printf("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearscreen(LINES);
                    print_submenu_show();
                    choice = getchar();
                    getchar();
                } /* end of while */
                printf("\n-> Thanks for using the show functions.\n\n");
            };
                break;
            case '4' : {
                clearscreen(LINES);
                print_submenu_delete();
                choice = getchar();
                getchar();
                while (choice != '0') {
                    switch (choice) {
                        case '1' :
                            deleteAll(&head);
                            break;
                        case '2' :
                            submenu_parameter_selection(&head, "delete");
                            break;
                        case '0' :
                            break;
                        default  :
                            printf("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearscreen(LINES);
                    print_submenu_delete();
                    choice = getchar();
                    getchar();
                } /* end of while */
                printf("\n-> Thanks for using the deleting functions.\n\n");
            };
                break;
            case '5' :
                writeFile(&head);
                break;
            case '6' :
                printf("Please enter your Filename:");
                scanf("%s", &filename);
                readFile(&head, filename);
                break;
            case '7' : {
                clearscreen(LINES);
                print_submenu_sort();
                choice = getchar();
                getchar();
                while (choice != '0') {
                    switch (choice) {
                        case '1' :
                            bubblesort(&head);
                            break;
                        case '2' :
                            insertionsort(&head);
                            break;
                        case '0' :
                            break;
                        default  :
                            printf("\n-> Please use a valid input.\n\n");
                            break;
                    }
                    printf("Press ENTER to continue.\n");
                    getchar();
                    clearscreen(LINES);
                    print_submenu_sort();
                    choice = getchar();
                    getchar();
                } /* end of while */
                printf("\n-> Thanks for using the sorting functions.\n\n");
            };
                break;
            case '8' :
                calculateMem(head);
                break;
            case '0' :
                break;
            default  :
                printf("\n-> Please use a valid input.\n\n");
                break;
        } /* end of switch */

        printf("Press ENTER to continue.\n");
        getchar();
        clearscreen(LINES);
        print_menu();
        choice = getchar();
        getchar();
    } /* end of while */
    printf("\n-> Thanks for using My Filecard System.\n\n");
    getchar();

    return (0);
}

//INPUT: Doppelter Pointer auf den Headpointer, Pointer auf den Personennamen, Größe, Alter
//Erstellt ein neues Struct mit den übergebenen Parametern und fügt ihn ans ende der Double linked list ein
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

//INPUT: Doppelter Pointer auf den Headpointer
//Funktion, die den Nutzer nach den Parametern Name, Größe und Alter abfragt,
// diese grob Validiert (nicht alle möglichen Falscheingaben sind abgedeckt).
//Am ende wird addRecord mit den eingegebenen Parametern aufgerufen, um die Person zu erstellen
void enterData(struct person_t **head) {
    char name[50 + 1];
    float height;
    int age;
    int valid;
    char buffer[100];
    char *endptr;

    printf("Please enter a name:");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Height (m):");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            valid = 0;
            printf("Unexpected error. Please enter a valid input for height (m):");
        }
        height = strtod(buffer, &endptr);
        if ((*endptr == '\0') || (isspace(*endptr) != 0)) {
            valid = 1;
        } else {
            valid = 0;
            printf("Please enter a valid input for height (m):");
        }
    } while (valid != 1);
    printf("Age (years):");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            valid = 0;
            printf("Unexpected error. Please enter a valid input for height (m):");
        }
        age = strtod(buffer, &endptr);
        if ((*endptr == '\0') || (isspace(*endptr) != 0)) {
            valid = 1;
        } else {
            valid = 0;
            printf("Please enter a valid input for height (m):");
        }
    } while (valid != 1);
    addRecord(head, name, height, age);

}

//INPUT: Doppelter Pointer auf den Headpointer, Pointer auf den Dateinamen
//RETURN: 0 wenn Fehler, 1 wenn erfolgreich
//Öffnet den Dateinamen, der Übergeben wird und liest den Inhalt aus.
//Die Personen werden ans ende der Liste angehängt
int readFile(struct person_t **head, char *filename) {
    char name[50 + 1];
    float height;
    int age;
    char line[700 + 1];
    FILE *myFile;
    myFile = fopen(filename, "r");
    if (myFile == NULL) {
        printf("Could not open file!\n");
        return 0;
    }

    while (fgets(line, 700 + 1, myFile) != NULL) {
        if (strncmp(line, "//", 2) != 0) {

            strcpy(name, strtok(line, ";"));
            height = strtof(strtok(NULL, ";"), 0);
            age = strtol(strtok(NULL, ";"), 0, 10);
            addRecord(head, name, height, age);
        }
    }
    fclose(myFile);
    return 1;
}

//INPUT: Doppelter Pointer auf den Headpointer
//Löscht alle Elemente der Liste
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

//INPUT: Doppelter Pointer auf den Headpointer, Pointer auf den Parameter nach dem gelöscht werden soll
//INPUT: Pointer auf den Namen der gelöscht werden soll
//Löscht alle Personen, die den eingegebenen Parameter enthalten
void deletePerson(struct person_t **head, char *searchBy, char *name) {
    int deleteCounter = 0;
    char searchName[50 + 1];
    char buffer[50 + 1];

    if (*head) {
        struct person_t *ptr = *head;
        do {
            if (strcmp(searchBy, "name") == 0) strcpy(searchName, ptr->name);
            else if (strcmp(searchBy, "height") == 0) strcpy(searchName, itoa(ptr->height, buffer, 10));
            else if (strcmp(searchBy, "age") == 0) strcpy(searchName, itoa(ptr->age, buffer, 10));
            if (strcmp(searchName, name) == 0) {
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
        printf("There's no Person with %s %s!\n", searchBy, name);
    } else {
        printf("%d Element(s) deleted!\n", deleteCounter);
    }

}

//INPUT: Pointer auf den Headpointer, Pointer auf den Parameter nach dem die zu bearbeitenden Personen ausgewählt werden sollen
//INPUT: Pointer auf den Namen der gelöscht werden soll
void editRecord(struct person_t *head, char *searchBy, char *name) {
    int searchCounter = 0;
    char txt[50 + 1];
    char searchName[50 + 1];
    char buffer[50 + 1];
    float gr;
    int age;
    if (head) {
        struct person_t *ptr = head;
        do {
            if (strcmp(searchBy, "name") == 0) strcpy(searchName, ptr->name);
            else if (strcmp(searchBy, "height") == 0) strcpy(searchName, itoa(ptr->height, buffer, 10));
            else if (strcmp(searchBy, "age") == 0) strcpy(searchName, itoa(ptr->age, buffer, 10));
            if (strcmp(searchName, name) == 0) {

                printf("Please enter a new name for %s:", ptr->name);
                getchar();
                fgets(txt, 50, stdin);
                txt[strcspn(txt, "\n")] = 0;
                printf("Height:");
                scanf("%f", &gr);
                printf("Age:");
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
        printf("There's no Person with %s %s!\n", searchBy, name);
    } else {
        printf("%d Element(s) changed!\n", searchCounter);
    }
}

//INPUT: Pointer auf den Headpointer
//RETURN: Anzahl der Elemente in der Liste
//Zählt wie viele Elemente in der Liste enthalten sind
int countElements(struct person_t *head) {
    struct person_t *ptr = head;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

//INPUT: Doppelter Pointer auf den Headpointer
//wendet Bubblesort auf die Liste an, und sortiert nach dem Namen
void bubblesort(struct person_t **head) {
    int length = countElements(*head);
    struct person_t *ptr = *head;
    struct person_t *tmp;
    struct person_t *tmp1;
    for (int k = 0; k < length - 1; k++) {
        for (int j = 0; j < length - 1; j++) {
            if (strcmp(ptr->name, ptr->next->name) == 1) {

                tmp = ptr->prev;
                tmp1 = ptr->next->next;

                ptr->prev = ptr->next;
                ptr->next->next = ptr;
                ptr->next->prev = tmp;
                ptr->next = tmp1;

                if (ptr->next) {
                    ptr->next->prev = ptr;
                }
                if (ptr->prev->prev) {
                    ptr->prev->prev->next = ptr->prev;
                }

                if (ptr == *head) {
                    *head = ptr->prev;
                }
            } else {
                ptr = ptr->next;
            }
        }
        ptr = *head;
    }
}

//INPUT: Doppelter Pointer auf den Headpointer
//wendet Insertionsort auf die Liste an, und sortiert nach dem Namen
void insertionsort(struct person_t **head) {
    int length = countElements(*head);
    struct person_t *ptr = *head;
    struct person_t *tmp;
    struct person_t *tmp1;
    int z = 0;
    for(int i = 0; i< 20; i++) {
        ptr = *head;
        for (int k = 1; k < length; k++) {
            z = 0;
            ptr = ptr->next;
            tmp1 = *head;
            while (strcmp(ptr->name, tmp1->name) > 0) {
                z++;
                tmp1 = tmp1->next;
            }

            if (strcmp(ptr->name, tmp1->name) != 0) {
                tmp = ptr;
                tmp->prev->next = ptr->next;
                if (tmp->next) {
                    tmp->next->prev = ptr->prev;
                }

                tmp->prev = tmp1->prev;
                if (tmp1->prev) {
                    tmp1->prev->next = tmp;
                }
                tmp1->prev = tmp;
                tmp->next = tmp1;

                if (tmp1 == *head) {
                    *head = tmp;
                }
            }
        }
    }
}

//INPUT: Pointer auf den Headpointer, Pointer auf die Wahl des Nutzers
//gibt alle einträge aus der Liste Aufsteigend oder Absteigend aus
void printAll(struct person_t *head, char *selection) {
    struct person_t *ptr = head;
    if (strcmp(selection, "ASC") == 0) {
        while (ptr != NULL) {
            printf("%s ist %f gross und %d alt.\n", ptr->name, ptr->height, ptr->age);
            ptr = ptr->next;
        }
    } else {
        while (ptr != NULL && ptr->next != NULL) {
            ptr = ptr->next;
        }
        while (ptr != NULL) {
            printf("%s ist %f gross und %d alt.\n", ptr->name, ptr->height, ptr->age);
            ptr = ptr->prev;
        }
    }
    printf("\n");

}

//INPUT: Pointer auf den Headpointer, Pointer auf den Parameter nach dem gesucht werden soll
//INPUT: Pointer auf den Namen des Parameters
//Gibt die Personen aus, die dem gewünschten Parameter entsprechen
void search(struct person_t *head, char *searchBy, char *name) {

    int searchCounter = 0;
    char searchName[50 + 1];
    char buffer[50 + 1];
    if (head) {
        struct person_t *ptr = head;
        do {
            if (strcmp(searchBy, "name") == 0) strcpy(searchName, ptr->name);
            else if (strcmp(searchBy, "height") == 0) strcpy(searchName, itoa(ptr->height, buffer, 10));
            else if (strcmp(searchBy, "age") == 0) strcpy(searchName, itoa(ptr->age, buffer, 10));
            if (strcmp(searchName, name) == 0) {
                printf("%s ist %2f gross und %d alt.\n", ptr->name, ptr->height, ptr->age);
                searchCounter++;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (searchCounter == 0) {
        printf("There's no Person with %s %s!\n", searchBy, name);
    } else {
        printf("%d Element(s) shown!\n", searchCounter);
    }
    getchar();
}

//INPUT: Pointer auf den Headpointer
//Berechnet den belegten Speicherplatz und gibt diesen aus
void calculateMem(struct person_t *head) {
    int structCounter = 0;
    if (head) {
        struct person_t *ptr = head;
        do {
            structCounter++;
            ptr = ptr->next;
        } while (ptr != NULL);
    }
    if (structCounter == 0) {
        printf("There's no Memory allocated!\n");
    } else {
        float allocatedMem = sizeof(struct person_t) * structCounter;
        if (allocatedMem >= 1024) {
            printf("%.3f kB Memory allocated!\n", allocatedMem / 1024);
        } else {
            printf("%.f Bytes Memory allocated!\n", allocatedMem);
        }
    }
}

//INPUT: Doppelter Pointer auf den Headpointer
//Schreibt die gesamte Liste in die Datei mit Namen "file.txt"
void writeFile(struct person_t **head) {
    FILE *file;
    file = fopen("file.txt", "w+");
    struct person_t *ptr = *head;
    if (file == NULL) {
        printf("Could not open file!");
    }
    fprintf(file, "//[name];[height];[age]\n");
    while (ptr != NULL) {

        fprintf(file, "%s;%.2f;%d\n", ptr->name, ptr->height, ptr->age);

        ptr = ptr->next;
    }
    fclose(file);
}

//Printed das Hauptmenü
void print_menu(void) {
    printf("\tMy Filecard System\n");
    printf("\t------------------\n\n");
    printf("\t1. Input record\n");
    printf("\t2. Edit record\n");
    printf("\t3. Show records\n");
    printf("\t4. Delete record\n");
    printf("\t5. File records\n");
    printf("\t6. Load records\n");
    printf("\t7. Sort records\n");
    printf("\t8. Calculate used memory\n");
    printf("\t0. End Program\n\n");
    printf("Your choice is: ");
}

//Printed das Menü um den Sortieralgorithmus auszuwählen
void print_submenu_sort(void) {
    printf("\tChoose a sorting algorithm\n");
    printf("\t--------------------------\n\n");
    printf("\t1. bubblesort\n");
    printf("\t2. insertionsort\n");
    printf("\t0. back to main menu\n\n");
    printf("Your choice is: ");
}

//Printed das Submenue, wo ausgewählt werden kann was gelöscht werden soll
void print_submenu_delete(void) {
    printf("\tChoose delete method\n");
    printf("\t--------------------------\n\n");
    printf("\t1. Delete all\n");
    printf("\t2. Delete by parameter\n");
    printf("\t0. back to main menu\n\n");
    printf("Your choice is: ");
}

//Printed das Submenue, wo ausgewählt werden kann was angezeigt werden soll
void print_submenu_show(void) {
    printf("\tChoose delete method\n");
    printf("\t--------------------------\n\n");
    printf("\t1. Show all\n");
    printf("\t2. Search by parameter\n");
    printf("\t0. back to main menu\n\n");
    printf("Your choice is: ");
}

//Printed das Submenue, wo ausgewählt werden kann nach welchem Parameter Gesucht/Gelöscht werden soll
void print_submenu_parameters(void) {
    printf("\tSelect a parameter:\n");
    printf("\t--------------------------\n\n");
    printf("\t1. name\n");
    printf("\t2. height\n");
    printf("\t3. age\n");
    printf("\t0. back to main menu\n\n");
    printf("Your choice is: ");
}

//INPUT: Doppelter Pointer auf den Headpointer, Pointer auf die ausgewählte Methode (Edit, Select, Delete)
//Fragt den Nutzer nach dem Namen ODER Größe ODER Alter nach dem bearbeitet/ausgesucht oder gelöscht werden soll
void submenu_parameter_selection(struct person_t **head, char *methodSelection) {
    char name[20 + 1];
    char selection[20 + 1];
    char choice;

    clearscreen(LINES);
    print_submenu_parameters();
    choice = getchar();
    getchar();
    while (choice != '0') {
        switch (choice) {
            case '1':
                strcpy(selection, "name");
                printf("Please enter a name:");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                break;
            case '2':
                strcpy(selection, "height");
                printf("Please enter a height:");
                scanf("%s", name);
                break;
            case '3':
                strcpy(selection, "age");
                printf("Please enter a age:");
                scanf("%s", name);
                break;
            case '0':
                break;
            default:
                printf("\n-> Please use a valid input.\n\n");
                break;
        }
        if (choice == '1' || choice == '2' || choice == '3') {
            if (methodSelection == "edit") editRecord(*head, selection, name);
            else if (methodSelection == "search") search(*head, selection, name);
            else if (methodSelection == "delete") deletePerson(head, selection, name);
        }

        printf("Press ENTER to continue.\n");
        getchar();
        getchar();
        clearscreen(LINES);
        print_submenu_parameters();
        choice = getchar();
        getchar();
    }
}

//Printed das Menü, wo der Nutzer auswählen kann, ob er die Liste Vorwärts oder Rückwärts ausgibt
void print_submenu_print_all(void) {
    printf("\tHow do you want to print your list?:\n");
    printf("\t--------------------------\n\n");
    printf("\t1. ASC\n");
    printf("\t2. DESC\n");
    printf("\t0. back to main menu\n\n");
    printf("Your choice is: ");
}

//schiebt den Text in der Konsole aus dem Bild
void clearscreen(int lines) {
    char i;
    for (i = 0; i < lines; i++) printf("\n");
}






































