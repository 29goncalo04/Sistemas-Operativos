#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "person.h"

// TO DO

int add(char* name, int age){

    int ret = 0;
    Person p;
    p.age = age;
    strcpy(p.name, name);

    int fd = open(DB, O_WRONLY | O_CREAT | O_APPEND, 0640);
    if(fd == -1){
        perror("open");
        ret = -1;
    }
    
    if(write(fd, &p, sizeof(Person)) == -1){
        perror("write");
        ret = -1;
    }

    close(fd);
    return ret;
}

int list(int n){
    int fd = open(DB, O_RDONLY);
    int bytes_read, ret = 0;
    Person p;

    if(fd == -1){
        perror("open");
        ret = -1;
    }

    while((bytes_read = read(fd, &p, sizeof(Person))) > 0 && n>0){
        if(bytes_read == -1){
            perror("read");
            ret = -1;
        }
        printf("Nome: %s  Idade: %d\n", p.name, p.age);
        n--;
    }

    return ret;
}

//int update(char* name, int new_age){
//
//}