#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "student.h"

void readName(char *name){
    char str[100];
    int c =0;
    do{
        c= 0;
        fgets(str,100,stdin);
        if(str[0] == '\n')  continue;

        for(int j =0 ; str[j]; j++){
            if(isspace(str[j]))
                c++;
        }
        if(c == strlen(str)) continue;
        //remove leading
        int i =0;
        while (str[i] == ' '|| str[i] == '\t'|| str[i] == '\n'){
            i++;
        }
        for (int k =0, j = i; str[j] != '\0'; j++){
            if(i == 0){
                strcpy(name , str);
                break;
            }
            name[k] = str[j];
            k++;
        }
        name[strlen(name) -1] = '\0';

        // manage letter case
        for(i = 0; i<strlen(name); i++) {
            if (i == 0 && name[i] != ' ' || name[i] != ' ' && name[i-1] == ' ') {
                if(name[i] >= 'a' && name[i]<='z') {
                    name[i] = (char)(('A'-'a') + name[i] );
                }
            } else if (name[i] >= 'A' && name[i] <= 'Z') {
                name[i] = (char)(name[i] + ('a' - 'A'));
            }
        }

    }while(str[0] == '\n' || c == strlen(str));
}

void readClass(int *classNum)
{
    //Only allows digits between 1 and 9
    char c;
    while (1)
    {
        c = getchar();
        if (c >= '1' && c <= '9')
        {
            *classNum = c - '0';
            return;
        }
    }
    return;
}

int readID(int *ID)
{
    char text[7];
    int output = 0;
    do {
        fgets(text, sizeof(text), stdin);
    } while (text[0] == '\n');

    int i = 0;
    for(i = 0; i<strlen(text); i++) {
        if (text[i] >= '0' && text[i] <= '9')
            output = (output * 10) + (text[i]-'0');
        else if (text[i] != '\0' && text[i] != '\n')
        {
            return 0;
        }
    }
    *ID = output;
    return 1;
}

int validMenuChoice(int maxChoice)
{
    char c;
    while (1)
    {
        c = getchar();
        if (c >= '1' && c <= '9')
        {
            if (c-'0' >= 1 && c-'0' <= maxChoice)
                return c-'0';
            else
                return 0;
        } else return 0;
    }
    return -1;
}

void delayMessage(char msg[])
{
    //Adds a delay by asking to click any button before clearing the screen
    //Used to display an error message or a 'click any button to continue'
    printf("%s\n", msg);
    int c = getch();
    fflush(stdin);
}

int main()
{
//    StudentList ls;
//    student s;
//    char name[100];
//
//    readName(name);
//
//    puts(name);
//    return 0;
//
//    while(1)
//    {
//        system("cls");
//        printf("\tStudent Academic Records System\n");
//        printf("1- Add Student\n");
//        printf("2- Delete Student (by ID or Name)\n");
//        printf("3- Edit Student\n");
//        printf("4- Search Student (by ID or Name)\n");
//        printf("5- Show all Students in a class (Sequentially or in Reverse)\n");
//        printf("6- Delete all Students in a class\n");
//        printf("7- Exit\n\n");
//        printf("Enter your selection: ");
//        switch(validMenuChoice(7))
//        {
//            case 1:
//
//            break;
//            case 2:
//
//            break;
//            case 3:
//
//            break;
//            case 4:
//
//            break;
//            case 5:
//
//            break;
//            case 6:
//
//            break;
//            case 7:
//                return 0;
//            break;
//            default:
//            delayMessage("Error: enter a valid input");
//        }
//    }
//    return 0;

StudentList ls;
    student s;
    createList(&ls);
    strcpy(s.name, "Name1");
    s.classID = 2;
    append(&ls, s);
    strcpy(s.name, "Name2");
    s.classID = 2;
    append(&ls, s);
    strcpy(s.name, "Name3");
    s.classID = 2;
    append(&ls, s);
    strcpy(s.name, "Mazin");
    s.classID = 3;
    append(&ls, s);
    strcpy(s.name, "Name5");
    s.classID = 2;
    append(&ls, s);
    strcpy(s.name, "Name6");
    s.classID = 7;
    append(&ls, s);
    //EditStudentName(&ls, 1002, "Name2");
    if(idExists(&ls,3001))
    {
        EditStudentClass(&ls,3001,1);
    }

    TraverseList(&ls, printStudent);

    return 0;
}
