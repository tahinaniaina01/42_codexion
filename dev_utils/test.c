#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *func(void *c){
    for(int i=0; i<10;i++){
        usleep(500);
        printf("func %d \n", i);
    }
    return c;
}

void *f(void *c){
    for(int i=0; i<10;i++){

        usleep(500);
        printf("f %d \n", i);
    }
    return c; 
}

int main(){
    pthread_t p1;
    pthread_t p2;

    pthread_create(&p1, NULL, func, NULL);
    pthread_create(&p2, NULL, f, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
} 