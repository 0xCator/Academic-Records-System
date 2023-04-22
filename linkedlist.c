#include <string.h>
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
                goto CNO;
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
                goto CNO;
            }
        }

        // if class not found append at the end of the list
CNO:
        if(classState == 0){

            // find riaght loaction in the list

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
