#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


static void *thread_function() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread: %d\n", i);
        sleep(1); 
    }
    return NULL;
}

void create_thread(){
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        printf("Ошибка создания потока\n");
    }
    pthread_detach(thread);
}


int main(int argc, char *argv[]) {
    create_thread();
    sleep(1);
    create_thread();

sleep(20);
printf("program stop\n");
    return 0;}
