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
