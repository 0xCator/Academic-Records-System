#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "student.h"

void readName(char *name){
    char str[100];
    do{
        fgets(str,100,stdin);
        if(str[0] == '\n')  continue;

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

    }while(str[0] == '\n');
}

int main()
{
    StudentList ls;
    student s;
    createList(&ls);
    strcpy(s.name, "Name1");
    s.classID = 1;
    append(&ls, s);
    strcpy(s.name, "Name6");
    s.classID = 1;
    append(&ls, s);
    strcpy(s.name, "Name3");
    s.classID = 1;
    append(&ls, s);
    strcpy(s.name, "Name6");
    s.classID = 3;
    append(&ls, s);
    strcpy(s.name, "Name5");
    s.classID = 2;
    append(&ls, s);
    strcpy(s.name, "Name6");
    s.classID = 7;
    append(&ls, s);

    return 0;
}
