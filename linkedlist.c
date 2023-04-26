#include <string.h>
#include <stdio.h>
#include "linkedlist.h"
#include "student.h"
#include <stdlib.h>

void createList(StudentList *ls)
{
    ls->current = NULL;
    ls->head = NULL;
    ls->tail = NULL;
    ls->size = 0;
}

int listSize(StudentList *ls)
{
    return ls->size;
}

int listEmpty(StudentList *ls)
{
    return ls->size == 0;
}

int append(StudentList *ls, student s){

    int classState = 1;
    node* new = (node *)malloc(sizeof(node));
    if(new == NULL)
        return -2; // fail to allocate memory
    // add student data
    memcpy(&new->student,&s, sizeof(s));
    // if list empty add node to end of the list
    if(ls->head == NULL){
        new->student.ID = new->student.classID*1000 + 1;
        new->next = NULL;
        new->prv = NULL;
        ls->head = new;
        ls->tail = new;
        ls->current = new;
        ls->size ++;

        return 0 ; // success code
    }

    // if list not empty  search for student class in the list and
    // add at the end of the class

    if(ls->head !=NULL){

        //move current pointer

        // if classID of current student < classID of new student
        // move forward in the list

        if(ls->current->student.classID <= s.classID){

            for (;ls->current != NULL; ls->current = ls->current->next) {

                // check the pos of the end of the class

                // if the class pos at the end of the list
                if(ls->current->student.classID == s.classID &&
                        ls->current->next == NULL){

                    new->student.ID = ls->current->student.ID +1;
                    new->next = NULL;
                    new->prv = ls->tail;
                    ls->tail->next = new;
                    ls->tail = new;
                    ls->current = new;
                    ls->size ++;
                    return 0; // success code
                }

                // if the class pos between two nods
                if(ls->current->next != NULL &&
                        ls->current->next->student.classID > s.classID &&
                        ls->current->student.classID == s.classID){
                    new->student.ID = ls->current->student.ID +1;
                    new->prv = ls->current;
                    new->next= ls->current->next;
                    ls->current->next->prv = new;
                    ls->current->next = new;
                    ls->current = new;
                    ls->size++;
                    return 0; // success code
                }
                classState =0; // class not found
            }
        } else {

            // if classID of current student  > classID of new student
            // move backword in the list

            for(;ls->current != NULL; ls->current = ls->current->prv){

                //check the pos of the end of the class

                if(ls->current->prv != NULL &&
                        ls->current->prv->student.classID < ls->current->student.classID &&
                        ls->current->prv->student.classID == s.classID){

                    new->student.ID = ls->current->prv->student.ID + 1;
                    new->next = ls->current;
                    new->prv = ls->current->prv;
                    ls->current->prv->next = new;
                    ls->current->prv = new;
                    ls->current = new;
                    ls->size++;
                    return 0 ; //success code
                }
                classState =0 ; // class not found
            }
        }

        // if class not found append at the end of the list
        if(classState == 0){

            // find riaght loaction in the list
            ls->current = (ls->current == NULL) ? ls->head : ls->current;

            if(ls->current->student.classID <= s.classID){

                for (;ls->current != NULL; ls->current = ls->current->next) {

                    // check the pos of the end of the class

                    // if the class pos at the end of the list
                    if(ls->current->student.classID < s.classID &&
                            ls->current->next == NULL){

                        new->student.ID = new->student.classID*1000 + 1;
                        new->next = NULL;
                        new->prv = ls->tail;
                        ls->tail->next = new;
                        ls->tail = new;
                        ls->current = new;
                        ls->size ++;
                        return 0; // success code
                    }

                    if(ls->current->next !=NULL
                            &&ls->current->next->student.classID > s.classID){
                        new->student.ID =new->student.classID*1000 + 1;
                        new->prv = ls->current;
                        new->next= ls->current->next;
                        ls->current->next->prv = new;
                        ls->current->next = new;
                        ls->current = new;
                        ls->size++;
                        return 0; // success code
                    }
                }
            }else {
                // if classID of current student  > classID of new student
                // move backword in the list

                for(;ls->current != NULL; ls->current = ls->current->prv){

                    //check the pos of the end of the class

                    // if the class pos at the beggining of the list
                    if(ls->current->prv == NULL
                            && ls->current->student.classID > s.classID){
                        new->student.ID = new->student.classID*1000 + 1;
                        new->prv = NULL;
                        new->next = ls->head;
                        ls->head= new;
                        ls->current = new;
                        ls->size ++;
                        return 0; // success code
                    }

                    if(ls->current->prv->student.classID < ls->current->student.classID &&
                            ls->current->prv->student.classID < s.classID){

                        new->student.ID = new->student.classID*1000 + 1;
                        new->next = ls->current;
                        new->prv = ls->current->prv;
                        ls->current->prv->next = new;
                        ls->current->prv = new;
                        ls->current = new;
                        ls->size++;
                        return 0 ; //success code
                    }
                }
            }
        }
    }

    return -1; // append failed
}

int idExists(StudentList *sl, int ID)
{
    sl->current=sl->head;
    while(sl->current)
    {
        if(sl->current->student.ID == ID)
            return 1;
        if(sl->current->next != NULL)
            sl->current=sl->current->next;
        else
            return 0;
    }
    return 0;
}
void EditStudentName(StudentList *sl, int idToFind,char newName[])
{
    int dir = (sl->current->student.ID > idToFind) ? 1 : 0; //Decide to go forwards or backwards
    while(sl->current)
    {
        if(sl->current->student.ID == idToFind)
        {
            strcpy(sl->current->student.name,newName);
            return;
        }
        if(dir)
        {
            sl->current=sl->current->prv;
        }
        else
            sl->current=sl->current->next;
    }
}

void EditStudentClass(StudentList *sl, int idToFind, int newClass)
{
    // ignores in case it's the same class
    if(sl->current->student.classID == newClass)
        return;
    // updates in case there is only 1 node
    if(sl->size==1)
    {
        sl->current->student.classID = newClass;
        sl->current->student.ID = (newClass*1000)+1;
        return;
    }
    node *temp = sl->current;
    node *clonedStudent = (node *)malloc(sizeof(node));
    strcpy(clonedStudent->student.name,sl->current->student.name);
    clonedStudent->student.classID = newClass;
    clonedStudent->student.ID = newClass * 1000;
    int dir = (sl->current->student.ID > clonedStudent->student.ID) ? 1 : 0; //Decide to go forwards or backwards
                            // 3001      1001
    while(sl->current)
    {
        if(dir)
        {
            // prev
            if(sl->current->prv != NULL)
            {
                if(sl->current->prv->student.classID < newClass)
                {
                    clonedStudent->next=sl->current;
                    clonedStudent->prv=sl->current->prv;
                    sl->current->prv->next=clonedStudent;
                    sl->current->prv=clonedStudent;
                    sl->current=clonedStudent;
                    clonedStudent->student.ID++;
                    break;

                }
                else if(sl->current->prv->student.classID == newClass)
                {
                    clonedStudent->next=sl->current;
                    clonedStudent->prv=sl->current->prv;
                    sl->current->prv->next=clonedStudent;
                    sl->current->prv=clonedStudent;
                    sl->current=clonedStudent;
                    clonedStudent->student.ID=clonedStudent->prv->student.ID +1;
                    break;
                }
                sl->current=sl->current->prv;

            }
            else
            {
                //first in list
                clonedStudent->student.ID++;
                sl->head->prv=clonedStudent;
                clonedStudent->next=sl->head;
                clonedStudent->prv = NULL;
                sl->head=clonedStudent;
                sl->current=clonedStudent;
                break;
            }


            //
        }
        else
        {
            //next
            if(sl->current->next != NULL)

                {
                    if(sl->current->next->student.classID > newClass
                       && sl->current->student.classID == newClass)
                    {
                        clonedStudent->prv=sl->current;
                        clonedStudent->next=sl->current->next;
                        sl->current->next->prv=clonedStudent;
                        sl->current->next=clonedStudent;
                        sl->current=clonedStudent;
                        clonedStudent->student.ID = sl->current->prv->student.ID +1;
                        break;
                    }
                    if(sl->current->next->student.classID > newClass)
                    {
                        clonedStudent->prv=sl->current;
                        clonedStudent->next=sl->current->next;
                        sl->current->next->prv=clonedStudent;
                        sl->current->next=clonedStudent;
                        sl->current=clonedStudent;
                        clonedStudent->student.ID++;
                        break;
                    }
                    sl->current=sl->current->next;
                }
            else
            {
                //last in list
                if(sl->tail->student.classID == newClass)
                    clonedStudent->student.ID = sl->tail->student.ID +1 ;
                else
                    clonedStudent->student.ID++;
                sl->tail->next=clonedStudent;
                clonedStudent->prv=sl->tail;
                clonedStudent->next = NULL;
                sl->tail=clonedStudent;
                sl->current=clonedStudent;
                break;
            }
        }


    }

    if(temp == sl->head)
        {
            sl->head=sl->head->next;
            sl->head->prv = NULL;
        }
    else if(temp == sl->tail)
        {
            sl->tail=sl->tail->prv;
            sl->tail->next = NULL;
        }
    else
        {
            temp->prv->next = temp->next;
            temp->next->prv = temp->prv;
        }

    free(temp);
}

int showStudentsInClass(StudentList *ls, int classID, void (*pf)(student))
{
    int classExists = 0; //A flag in case a class didn't exist
    node *pn = ls->head;
    //If the class doesn't exist between the first and last students, return. (Students are sorted by class)
    if (!(classID >= ls->head->student.classID && classID <= ls->tail->student.classID))
        return 0;
    while (pn)
    {
        if (pn->student.classID == classID)
        {
            (*pf)(pn->student); //Printing the students if they exist
            classExists = 1;
        }
        //When the current class is higher than the ID (all students are shown or none), break.
        else if (pn->student.classID > classID)
            break;

        pn = pn->next;
    }
    return (classExists);
}

int showStudentsInClassRev(StudentList *ls, int classID, void (*pf)(student))
{
    int classExists = 0; //A flag in case a class didn't exist
    node *pn = ls->tail;
    //If the class doesn't exist between the first and last students, return. (Students are sorted by class)
    if (!(classID >= ls->head->student.classID && classID <= ls->tail->student.classID))
        return 0;
    while (pn)
    {
        if (pn->student.classID == classID)
        {
            (*pf)(pn->student); //Printing the students if they exist
            classExists = 1;
        }
        //When the current class is lower than the ID (all students are shown or none), break.
        else if (pn->student.classID < classID)
            break;

        pn = pn->prv;
    }
    return (classExists);
}


int DeleteFromClass(StudentList *ls, int classID){
    // delete all student in the class
    node *tmp;
    int classExists= 0;
    ls->current = (ls->head->student.classID == classID)?
                    ls->head : (ls->tail->student.classID == classID)?
                                ls->tail : ls->current ;

    // moving current
    if(ls->current->student.classID == classID){
        classExists = 1;
        while (ls->current != NULL&&
                ls->current->student.classID == classID) {
            tmp = ls->current;
            ls->current = (ls->current->next != NULL)?
                        ls->current->next : ls->current;
            ls->head = (tmp->prv == NULL)? ls->head->next: ls->head;
            ls->tail = (tmp->next == NULL)? ls->tail->prv: ls->tail;

            if (tmp->prv != NULL)
                tmp->prv->next = tmp->next;

            if (tmp->next != NULL)
                tmp->next->prv = tmp->prv;
            free(tmp);
            ls->size--;
            ls->current = (ls->current->prv != NULL&&
                    ls->current->prv->student.classID == classID)?
                ls->current->prv : ls->current;
        }
        return (classExists);
    }

    if(ls->current->student.classID <= classID){
        for(;ls->current != NULL&&
                ls->current->student.classID <= classID;){
            if(classID == ls->current->student.classID)
            {
                classExists = 1;
                tmp = ls->current;
                ls->current = (ls->current->next == NULL)? ls->current->prv
                    : ls->current->next;
                if (tmp->prv != NULL)
                    tmp->prv->next = tmp->next;

                if (tmp->next != NULL)
                    tmp->next->prv = tmp->prv;
                free(tmp);
                ls->size--;
                continue;
            }
            ls->current = ls->current->next;
        }
        return (classExists);
    }

    if(ls->current->student.classID >= classID){
        for(;ls->current != NULL &&
                ls->current->student.classID >= classID;){
            if(classID == ls->current->student.classID)
            {
                classExists = 1;
                tmp = ls->current;
                tmp = ls->current;
                ls->current = (ls->current->prv == NULL)? ls->current->next
                    : ls->current->prv;
                if (tmp->prv != NULL)
                    tmp->prv->next = tmp->next;

                if (tmp->next != NULL)
                    tmp->next->prv = tmp->prv;
                free(tmp);
                ls->size--;
                continue;
            }
            ls->current = ls->current->prv;
        }
        return (classExists);
    }

 return (classExists);
}

void TraverseList(StudentList *ls, void (*pf)(student))
{
    node *pn = ls->head;
    while (pn)
    {
        (*pf)(pn->student);
        pn = pn->next;
    }
}

int DeletebyID(int stdID, StudentList *psl)
{
    int dir = (psl->current->student.ID > stdID) ? 1 : 0; //Decide to go forwards or backwards
    while (psl->current)
    {
        if (psl->current->student.ID == stdID)
        {
            node *pTemp = psl->current;
            if (psl->current == psl->head)
            {
                if (psl->current == psl->tail)
                {
                    psl->head = NULL;
                    psl->tail = NULL;
                    psl->current = NULL;
                }
                else
                {
                    psl->current->next->prv = NULL;
                    psl->head = psl->current->next;
                    psl->current = psl->head;
                }
            }
            else if (psl->current == psl->tail)
            {
                psl->current->prv->next = NULL;
                psl->tail = psl->current->prv;
                psl->current = psl->tail;
            }
            else
            {
                psl->current->prv->next = psl->current->next;
                psl->current->next->prv = psl->current->prv;
                psl->current = psl->current->next;
            }
            free(pTemp);
            psl->size--;
            return 1;
        }

        if (dir)
        {
            if (psl->current->prv != NULL && psl->current->prv->student.ID >= stdID)
                psl->current = psl->current->prv;
            else
                return 0;
        }
        else
        {
            if (psl->current->next != NULL && psl->current->next->student.ID <= stdID)
                psl->current = psl->current->next;
            else
                return 0;
        }
    }
    return -1;
}

int DeletebyName(char name[], StudentList *psl, void (*pf)(student))
{
    int stuWthSameName=0;
    node *pn = psl->head,*ptemp= psl->head;
    // to know if the number of students with the same name in the entire list
    while(pn){
        if(strcmp(name,pn->student.name)==0){
            stuWthSameName++;
            psl->current=pn;
        }
        pn=pn->next;
    }
    //1->there is only 1 student with this name
    if(stuWthSameName == 1 ){
        node *tmp = psl->current;
        if(psl->current==psl->head){
            if (psl->current == psl->tail)
            {
                psl->head = NULL;
                psl->tail = NULL;
                psl->current = NULL;
            }
            else
            {
                psl->head = tmp->next;
                psl->head->prv = NULL;
                psl->current = psl->head;
            }
        }
        else if(psl->current==psl->tail) {
            psl->tail = tmp->prv;
            psl->tail->next = NULL;
            psl->current = psl->tail;
        }
        else{
            psl->current->prv->next = psl->current->next;
            psl->current->next->prv = psl->current->prv;
            psl->current = psl->current->next;
        }
        free(tmp);
        psl->size--;
        return 0;
    }


    //>10> there is more than 1 student with the same name and weneed the id to delete specific student
    if(stuWthSameName>1){
        int id;
        while(ptemp){
            if(strcmp(name,ptemp->student.name)==0){
                (*pf)(ptemp->student);
            }
            ptemp=ptemp->next;
        }
        printf("Enter the studentID that will be deleted: ");
        return 1;
    }

    return -1;
}

int SearchByID(int stdID, StudentList *psl, void (*pf)(student))
{
    int dir = (psl->current->student.ID > stdID) ? 1 : 0; //Decide to go forwards or backwards
    while (psl->current)
    {
        if (psl->current->student.ID == stdID)
        {
            (*pf)(psl->current->student);
            return 1;
        }

        if (dir)
        {
            if (psl->current->prv != NULL && psl->current->prv->student.ID >= stdID)
                psl->current = psl->current->prv;
            else
                return 0;
        }
        else
        {
            if (psl->current->next != NULL && psl->current->next->student.ID <= stdID)
                psl->current = psl->current->next;
            else
                return 0;
        }
    }
    return  -1;
}

int SearchByName(char name[], StudentList *psl, void (*pf)(student))
{
    int nameExists = 0;
    node *pn = psl->head;
    while (pn)
    {
        if (strcmp(name,pn->student.name)==0)
        {
            (*pf)(pn->student);
            nameExists = 1;
        }
        pn = pn->next;
    }
    return nameExists;
}
