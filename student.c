#include "student.h"
#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

void printStudent(student s)
{
    printf("Name: %s\nID: %d\nClass: %d\n\n", s.name, s.ID, s.classID);
}
