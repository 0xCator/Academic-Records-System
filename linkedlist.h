#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "student.h"

typedef struct Node{
    struct student student;
    struct Node *next;
    struct Node *prv;
} node;


typedef struct StudentList{
    node *head;
    node *tail;
    node *current;
    int size;
} StudentList;

void createList(StudentList *ls);
int listSize(StudentList *ls);
int listEmpty(StudentList *ls);
int append(StudentList *ls, student s);

int showStudentsInClass(StudentList *ls, int classID, void (*pf)(student));
int showStudentsInClassRev(StudentList *ls, int classID, void (*pf)(student));

#endif // LINKEDLIST_H_INCLUDED
