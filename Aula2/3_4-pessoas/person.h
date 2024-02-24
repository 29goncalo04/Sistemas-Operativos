// TO DO
#ifndef PERSON_H
#define PERSON_H

#define DB "file_pessoas"

typedef struct person {
    char name[100];
    int age;
} Person;

int add(char* name, int age);

int list(int n);

int update(char* name, int new_age);

int update2(int position, int new_age);

#endif