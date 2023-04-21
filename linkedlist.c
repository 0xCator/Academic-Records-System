#include "linkedlist.h"
#include "student.h"
#include <stdlib.h>





int append(StudentList *ls, student *s){

    int classState = 1;
    node* new = (node *)malloc(sizeof(node));
    if(new == NULL)
        return -2; // fail to allocate memory

    new->student = s; // add student date 

    // if list empty add node to end of the list
    if(ls->head == NULL){
        new->student->ID = new->student->classID*1000 + 1;
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

        if(ls->current->student->classID <= s->classID){

            for (;ls->current != NULL; ls->current = ls->current->next) {

                // check the pos of the end of the class
               
                // if the class pos at the end of the list
                if(ls->current->student->classID == s->classID &&
                        ls->current->next == NULL){

                    new->student->ID = ls->current->student->ID +1;
                    new->next = NULL;
                    new->prv = ls->tail;
                    ls->tail->next = new;
                    ls->tail = new;
                    ls->size ++;
                    return 0; // success code 
                }

                // if the class pos between two nods
                if(ls->current->next->student->classID > s->classID){
                    new->student->ID = ls->current->student->ID +1;
                    new->prv = ls->current;
                    new->next= ls->current->next;
                    ls->current->next->prv = new;
                    ls->current->next = new;
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

                if(ls->current->prv->student->classID < ls->current->student->classID && 
                        ls->current->prv->student->classID == s->classID){

                    new->student->ID = ls->current->prv->student->ID + 1;
                    new->next = ls->current;
                    new->prv = ls->current->prv;
                    ls->current->prv->next = new;
                    ls->current->prv = new;
                    ls->size++;
                    return 0 ; //success code 
                }
                classState =0 ; // class not found
            }
        }

        // if class not found append at the end of the list

        if(classState == 0){

            // find riaght loaction in the list 

            if(ls->current->student->classID <= s->classID){

                for (;ls->current != NULL; ls->current = ls->current->next) {

                    // check the pos of the end of the class

                    // if the class pos at the end of the list
                    if(ls->current->student->classID == s->classID &&
                            ls->current->next == NULL){

                        new->student->ID = 1;
                        new->next = NULL;
                        new->prv = ls->tail;
                        ls->tail->next = new;
                        ls->tail = new;
                        ls->size ++;
                        return 0; // success code 
                    }

                    if(ls->current->next->student->classID > s->classID){
                        new->student->ID = 1;
                        new->prv = ls->current;
                        new->next= ls->current->next;
                        ls->current->next->prv = new;
                        ls->current->next = new;
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
                            && ls->current->student->classID > s->classID){
                        new->student->ID = new->student->classID*1000 + 1;
                        new->prv = NULL;
                        new->next = ls->head;
                        ls->head= new;
                        ls->size ++;
                        return 0; // success code 
                    }

                    if(ls->current->prv->student->classID < ls->current->student->classID && 
                            ls->current->prv->student->classID < s->classID){

                        new->student->ID = new->student->classID*1000 + 1;
                        new->next = ls->current;
                        new->prv = ls->current->prv;
                        ls->current->prv->next = new;
                        ls->current->prv = new;
                        ls->size++;
                        return 0 ; //success code 
                    }
                }
            }
        }
    }

    return -1; // append failed  
}

