#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "student.h"

typedef struct Node{
    struct student *student;
    struct Node *next;
    struct Node *prv;
} node;


typedef struct StudentList{
    node *head;
    node *tail;
    node *current;
    int size;
} StudentList;

int append(StudentList *ls, student *s);

#endif // LINKEDLIST_H_INCLUDED
