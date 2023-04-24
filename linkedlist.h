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
int DeleteFromClass(StudentList *ls, int classID);
int DeletebyID(int Class, int stuID ,student *ps, StudentList *psl);
int DeletebyName(char name[],student *ps,StudentList *psl);

int DeletebyIDrew(int stdID, StudentList *psl);
int DeletebyNamerew(char name[], StudentList *psl, void (*pf)(student));
int idExists(StudentList *sl, int ID);
void EditStudentName(StudentList *sl, int idToFind,char newName[]);
void EditStudentClass(StudentList *sl, int idToFind, int newClass);
int showStudentsInClass(StudentList *ls, int classID, void (*pf)(student));
int showStudentsInClassRev(StudentList *ls, int classID, void (*pf)(student));
int SearchByID(int stdID, StudentList *psl, void (*pf)(student));
int SearchByName(char name[], StudentList *psl, void (*pf)(student));
void TraverseList(StudentList *ls, void (*pf)(student));
#endif // LINKEDLIST_H_INCLUDED
