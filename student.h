#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct student {
    unsigned int classID;
    unsigned int ID;
    char  name[100];
}student;

void printStudent(student s);

#endif // STUDENT_H_INCLUDED
