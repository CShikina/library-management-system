#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MAX 2

struct library{
    char name[20];
    char author[20];
    int year;
    char ISBN[15];
}book[MAX];

typedef struct library library;

void createFile(){
    FILE *fp = fopen("library.bin", "wb");

    system("cls");
    printf("Please enter all 5 books.\n");
    for (int i=0; i<MAX; i++){
        printf("\nBook %d\n", i+1);

        printf("Title: ");
        scanf(" %19[^\n]", book[i].name);

        printf("Author: ");
        scanf(" %19[^\n]", book[i].author);

        printf("Year: ");
        scanf("%d", &book[i].year);
        while(getchar() != '\n');

        printf("ISBN: ");
        scanf(" %14[^\n]", book[i].ISBN);
        while(getchar() != '\n');
        fwrite(&book[i], sizeof(library), 1, fp);
    }

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

void modifyBook(){
    FILE *fp = fopen("library.bin", "rb+");
    system("cls");

    for (int i=0; i<MAX; i++){
        fread(&book[i], sizeof(library), 1, fp);
    }

    printf("Enter ISBN of the book you wish to modify: ");
    char bookTemp[15];
    scanf(" %14[^\n]", bookTemp);
    while(getchar()!='\n');

    for (int i=0; i<MAX; i++){
        if (stricmp(bookTemp, book[i].ISBN) == 0){
            printf("\nEnter modified book details\n");
            printf("Title: ");
            scanf(" %19[^\n]", book[i].name);

            printf("Author: ");
            scanf(" %19[^\n]", book[i].author);

            printf("Year: ");
            scanf("%d", &book[i].year);
            while(getchar() != '\n');
            
            printf("ISBN: ");
            scanf(" %14[^\n]", book[i].ISBN);
            while(getchar() != '\n');
            printf("\nBook modified.");
        }
    }

    fseek(fp, 0, SEEK_SET);
    for (int i=0; i< MAX; i++){
        fwrite(&book[i], sizeof(library), 1, fp);
    }

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

void displayBook(){
    FILE *fp = fopen("library.bin", "rb");
    system("cls");

    for (int i=0; i<MAX; i++){
        fread(&book[i], sizeof(library), 1, fp);
    }

    for (int i=0; i<MAX; i++){
        printf("\nBook %d\n", i+1);
        printf("Title: %s\n", book[i].name);
        printf("Author: %s\n", book[i].author);
        printf("Year: %d\n", book[i].year);
        printf("ISBN: %s\n", book[i].ISBN);
    }

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

void sortBook(){
    FILE *fp = fopen("library.bin", "rb+");
    system("cls");

    for (int i=0; i<MAX; i++){
        fread(&book[i], sizeof(library), 1, fp);
    }

    library temp;
    for (int i=0; i<MAX-1; i++){
        for (int j=0; j<MAX-i-1; j++){
            if (book[j].year > book[j+1].year){
                temp = book[j];
                book[j] = book[j+1];
                book[j+1] = temp;
            }
        }
    }

    printf("Sorted Books\n");
    for(int i = 0; i < MAX; i++){
        printf("Book %d\n", i+1);
        printf("Title: %s\n", book[i].name);
        printf("Author: %s\n", book[i].author);
        printf("Year: %d\n", book[i].year);
        printf("ISBN: %s\n\n", book[i].ISBN);
    }

    fseek(fp, 0, SEEK_SET);
    for (int i=0; i< MAX; i++){
        fwrite(&book[i], sizeof(library), 1, fp);
    }

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

int main(){
    int choice=0;
    do {
        system("cls");
        printf("Library Management System\n");
        printf("1. Create file and add books\n");
        printf("2. Modify book\n");
        printf("3. Display books\n");
        printf("4. Sort books\n");
        printf("5. Exit program\n");
        printf(">> ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                createFile();
                break;
            case 2:
                modifyBook();
                break;
            case 3:
                displayBook();
                break;
            case 4:
                sortBook();
                break;
            case 5:
                break;
            default:
                printf("Invalid input");
                printf("\n\nPress any key to continue...");
                getch();
        }
    }while (choice != 5);
    printf("Program terminated.");
}