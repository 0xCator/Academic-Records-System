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
        c =  getche();
        puts("");
        fflush(stdin);
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
    fflush(stdin);
    char c;
    while (1)
    {
        c = getchar();
        if (c >= '1' && c <= '9')
        {
            if (c-'0' >= 1 && c-'0' <= maxChoice)
            {
                return c-'0';
            }
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

void DeleteStudentMenu(StudentList *ls)
{
    unsigned int ID;
    char name[100];
    while(1)
    {
        system("cls || clear");
        printf("\tDelete Student\n");
        printf("1- Delete by name\n");
        printf("2- Delete by ID\n");
        printf("3- Back\n\n");
        printf("Enter your selection: ");
        switch(validMenuChoice(3))
        {
            case 1:
                system("cls || clear");
                printf("\tDelete Student by name\n");
                printf("Name: ");
                readName(name);
                int flag = DeletebyName(name, ls, printStudent);
                if (flag == 0)
                    delayMessage("Student successfully deleted!");
                else if (flag == 1)
                {
                    if (!readID(&ID))
                    {
                        delayMessage("Error: Enter valid ID");
                        continue;
                    }
                    if (DeletebyID(ID, ls))
                        delayMessage("Student successfully deleted!");
                    else
                        delayMessage("Error: No student with this ID exists");
                }
                else
                    delayMessage("Error: No student with this name exists");
            break;
            case 2:
                while(1)
                {
                    system("cls || clear");
                    printf("\tDelete Student by ID\n");
                    printf("ID: ");
                    if (!readID(&ID))
                    {
                        delayMessage("Error: Enter valid ID");
                        continue;
                    }
                    if (DeletebyID(ID, ls))
                        delayMessage("Student successfully deleted!");
                    else
                        delayMessage("Error: No student with this ID exists");
                    break;
                }
            break;
            case 3:
                return;
            break;
            default:
                delayMessage("Error: enter a valid input");
        }
    }
}

void EditStudentMenu(StudentList *ls)
{
    unsigned int ID, classID;
    char name[100];
    while(1)
    {
        system("cls || clear");
        printf("\tEdit Student\n");
        printf("ID: ");
        if (!readID(&ID))
        {
            delayMessage("Error: Enter valid ID");
            continue;
        }
        if (idExists(ls, ID))
        {
            while (1)
            {
                system("cls || clear");
                printf("\tEdit Student\n");
                printf("1- Edit name\n");
                printf("2- Change Class\n");
                printf("3- Back\n\n");
                printf("Enter your selection: ");
                switch(validMenuChoice(3))
                {
                    case 1:
                        system("cls || clear");
                        printf("\tEdit Student's name\n");
                        printf("Name: ");
                        readName(name);
                        EditStudentName(ls, ID, name);
                        delayMessage("Name successfully changed!");
                        return;
                    break;
                    case 2:
                        system("cls || clear");
                        printf("\tChange Student's class\n");
                        printf("Class: ");
                        readClass(&classID);
                        EditStudentClass(ls, ID, classID);
                        if (classID == ID/1000)
                            delayMessage("Same class, nothing was changed");
                        else
                            delayMessage("Class successfully changed!");
                        return;
                    break;
                    case 3:
                        return;
                    break;
                    default:
                        delayMessage("Error: enter a valid input");
                }
            }
        }
        else
            delayMessage("Error: No student with this ID exists");
    }
}

void SearchStudentMenu(StudentList *ls)
{
    unsigned int ID;
    char name[100];
    while(1)
    {
        system("cls || clear");
        printf("\tSearch Student\n");
        printf("1- Search by name\n");
        printf("2- Search by ID\n");
        printf("3- Back\n\n");
        printf("Enter your selection: ");
        switch(validMenuChoice(3))
        {
            case 1:
                system("cls || clear");
                printf("\tSearch Student(s) by name\n");
                printf("Name: ");
                readName(name);
                if (SearchByName(name, ls, printStudent))
                    delayMessage("Press any key to return");
                else
                    delayMessage("Error: No student with this name exists");
            break;
            case 2:
                while(1)
                {
                    system("cls || clear");
                    printf("\tSearch Student by ID\n");
                    printf("ID: ");
                    if (!readID(&ID))
                    {
                        delayMessage("Error: Enter valid ID");
                        continue;
                    }
                    if (SearchByID(ID, ls, printStudent))
                        delayMessage("Press any key to return");
                    else
                        delayMessage("Error: No student with this ID exists");
                    break;
                }
            break;
            case 3:
                return;
            break;
            default:
                delayMessage("Error: enter a valid input");
        }
    }
}

void ShowStudentsMenu(StudentList *ls)
{
    unsigned int classID;
    while(1)
    {
        system("cls || clear");
        printf("\tShow all Students in a class\n");
        printf("1- Show sequentially\n");
        printf("2- Show in reverse order\n");
        printf("3- Back\n\n");
        printf("Enter your selection: ");
        switch(validMenuChoice(3))
        {
            case 1:
                system("cls || clear");
                printf("\tShow all Students in a class (Sequentially)\n");
                printf("Class: ");
                readClass(&classID);
                if (showStudentsInClass(ls, classID, printStudent))
                    delayMessage("Press any key to return");
                else
                    delayMessage("Error: Class doesn't exist");
            break;
            case 2:
                system("cls || clear");
                printf("\tShow all Students in a class (Reversed)\n");
                printf("Class: ");
                readClass(&classID);
                if (showStudentsInClassRev(ls, classID, printStudent))
                    delayMessage("Press any key to return");
                else
                    delayMessage("Error: Class doesn't exist");
            break;
            case 3:
                return;
            break;
            default:
                delayMessage("Error: enter a valid input");
        }
    }
}

int main()
{
    StudentList ls;
    student s;
    createList(&ls);
    char name[100];
    unsigned int classID, ID, flag;
    while(1)
    {
        system("cls || clear");
        printf("\tStudent Academic Records System\n");
        printf("1- Add Student\n");
        printf("2- Delete Student (by ID or Name)\n");
        printf("3- Edit Student\n");
        printf("4- Search Student (by ID or Name)\n");
        printf("5- Show all Students in the system\n");
        printf("6- Show all Students in a class (Sequentially or in Reverse)\n");
        printf("7- Delete all Students in a class\n");
        printf("8- Exit\n\n");
        printf("Enter your selection: ");
        switch(validMenuChoice(8))
        {
            case 1: //Add student
                system("cls || clear");
                printf("\tAdd Student\n");
                printf("Name: ");
                readName(name);
                printf("Class: ");
                readClass(&classID);
                strcpy(s.name,name);
                s.classID=classID;
                if (append(&ls,s) == 0)
                    delayMessage("Student successfully added!");
                else
                    delayMessage("Error: An error occurred");
            break;
            case 2: //Delete Student
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                DeleteStudentMenu(&ls);
            break;
            case 3: //Edit Student
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                EditStudentMenu(&ls);
            break;
            case 4: //Search Student
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                SearchStudentMenu(&ls);
            break;
            case 5:
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                system("cls || clear");
                printf("\tShow all Students:\n");
                TraverseList(&ls, printStudent);
                delayMessage("Press any key to continue");
            break;
            case 6: //Show all Students in a class
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                ShowStudentsMenu(&ls);
            break;
            case 7: //Delete all Students in a class
                if (listEmpty(&ls))
                {
                    delayMessage("Error: List is empty");
                    break;
                }
                do
                {
                    system("cls || clear");
                    printf("\tDelete class\n");
                    printf("Class: ");
                    readClass(&classID);
                    flag = DeleteFromClass(&ls, classID);
                    if (flag)
                        delayMessage("Class successfully deleted!");
                    else
                        delayMessage("Error: Class doesn't exist");
                } while (!flag);
            break;
            case 8:
                exit(0);
            break;
            default:
            delayMessage("Error: enter a valid input");
        }
    }
    return 0;
}
