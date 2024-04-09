#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "person.h"

int add(char* name, int age){
    Person p;
    strcpy(p.name, name);
    p.age = age;
    int file = open(DB, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if(file == -1){
        perror("open");
        return -1;
    }
    if(write(file, &p, sizeof(Person)) == -1){
        perror("write");
        return -1;
    }
    close(file);
    return 0;
}

// int add(char* name, int age){
//     int ret = 0;
//     Person p;
//     p.age = age;
//     strcpy(p.name, name);
//     int fd = open(DB, O_WRONLY | O_CREAT | O_APPEND, 0640);
//     if(fd == -1){
//         perror("open");
//         ret = -1;
//     }
//     if(write(fd, &p, sizeof(Person)) == -1){
//         perror("write");
//         ret = -1;
//     }
//     close(fd);
//     return ret;
// }

int list (int n){
    Person p;
    int bytes_read;
    int file = open(DB, O_RDONLY);
    if(file == -1){
        perror("open");
        return -1;
    }
    for(int i = 0; i<n; i++){
        bytes_read = read(file, &p, sizeof(Person));
        if(bytes_read == -1){
            perror("read");
            close(file);
            return -1;
        }
        if(bytes_read == 0) break;
        printf("Pessoa número %d -> %s %d\n", i, p.name, p.age);
    }
    close(file);
    return 0;
}

// int list(int n){
//     int fd = open(DB, O_RDONLY);
//     int bytes_read, ret = 0;
//     Person p;
//     if(fd == -1){
//         perror("open");
//         ret = -1;
//     }
//     while((bytes_read = read(fd, &p, sizeof(Person))) > 0 && n>0){
//         if(bytes_read == -1){
//             perror("read");
//             ret = -1;
//         }
//         printf("Nome: %s  Idade: %d\n", p.name, p.age);
//         n--;
//     }
//     close(fd);
//     return ret;
// }

int update(char* name, int new_age){
    int bytes_read;
    Person p;
    int file = open(DB, O_RDWR);
    if(file == -1){
        perror("open");
        return -1;
    }
    while((bytes_read = read(file, &p, sizeof(Person)))>0){
        if(bytes_read == -1){
            perror("read");
            return -1;
        }
        if(strcmp(name, p.name) == 0){
            lseek(file, -sizeof(Person), SEEK_CUR);
            p.age = new_age;
            write(file, &p, sizeof(Person));
            close(file);
            return 0;
        }
    }
    close(file);
    return 0;
}

// int update(char* name, int new_age){
//     int ret = 0, bytes_read;
//     int fd = open(DB, O_RDWR);
//     Person p;
//     if(fd == -1){
//         perror ("open");
//         ret = -1;
//     }
//     while((bytes_read = read(fd, &p, sizeof(Person))) > 0){
//         if(strcmp(name, p.name) == 0){
//             lseek(fd, -sizeof(Person), SEEK_CUR);
//             p.age = new_age;
//             write(fd, &p, sizeof(Person));
//         }
//     }

//     close(fd);
//     return ret;
// }

int update2(int position, int new_age){
    int ret = 0, bytes_read, n = 1;
    Person p;
    int fd = open(DB, O_RDWR);
    if(fd == -1){
        perror ("open");
        ret = -1;
    }
    while((bytes_read = read(fd, &p, sizeof(Person))) > 0 && n<=position){
        if(n == position){
            lseek(fd, -sizeof(Person), SEEK_CUR);
            p.age = new_age;
            write(fd, &p, sizeof(Person));
        }
        n++;
    }

    close(fd);
    return ret;
}