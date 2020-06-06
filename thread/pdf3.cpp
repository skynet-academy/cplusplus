#include <iostream>
#include<pthread.h>
#include<stdio.h>
#include<thread>
#include<vector>
#include<future>
#include<mutex>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#define _OPEN_THREADS
#define FILENAME "play"


enum {NTHREADS = 8};
pthread_mutex_t file_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t nalive_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t alldead_cond = PTHREAD_COND_INITIALIZER;
pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_key_t key_name;
int nalive = 0;
FILE *file;
sigset_t mask;
pthread_t tid[NTHREADS];



void _sem_wait(sem_t *sem){
    while(sem_wait(sem) !=0){ }
}
void key_destructor(void *arg){
    printf("key destructor\n");
    char *name = (char*) arg;
    free(name);
}
void thread_init(void){
    pthread_key_create(&key_name, key_destructor);
}
void cleanup_lock(void *arg){
    printf("cleanup_lock\n");
    pthread_mutex_t *lock = (pthread_mutex_t *) arg;
    pthread_mutex_unlock(lock);
}

void clean_file(void *arg){
    printf("cleanup_file\n");
    fclose(file);
}

void cleanup_death(void *arg){
    printf("cleanup_death\n");
    pthread_mutex_lock(&file_lock);
    file = fopen(FILENAME, "a");
    fprintf(file, "%s is dead\n", (char *) pthread_getspecific(key_name));
    pthread_mutex_unlock(&file_lock);

    pthread_mutex_lock(&nalive_lock);
    if(--nalive == 0){
        pthread_mutex_unlock(&nalive_lock);
        printf("The last character is dead.\n");
        pthread_cond_signal(&nalive_lock);
    }
    pthread_mutex_unlock(&nalive_lock);
}
void *character(void *arg){
    pthread_once(&init_done, thread_init);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    char *name = (char *) malloc(strlen(arg));
    strcpy(name, arg);
    pthread_setspecific(key_name, name);
    pthread_mutex_lock(&nalive_lock);
    nalive++;
    pthread_mutex_unlock(&nalive_lock);
    pthread_cleanup_push(cleanup_death, NULL);
    for(;;){
        fprintf(stderr, "I am %s \n", name);
        pthread_mutex_lock(&file_lock);
        pthread_cleanup_push(cleanup_lock, NULL);
        file = fopen(FILENAME, "a");
        pthread_cleanup_push(cleanup_file, NULL);
        fprintf(file, "%s was here \n", (char *) pthread_getspecific(key_name));
        pthread_cleanup_pop(0);
        fclose(file);
        pthread_cleanup_pop(0);
        pthread_mutex_unlock(&file_lock);
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return NULL;
}

void *grim_reaper(void *arg){
    for(;;){
        int signo;
        int rc = sigwait(&mask, &signo);
        if(rc !=0){
            fprintf(stderr, "sigwait() failded");
            exit(1);
        }
        switch(signo){
            case SIGQUIT:
            printf("SIGQUIT received\n");
            if(nalive > 0){
                struct drand48_data rand48_buffer;
                srand48_r(time(NULL), &rand48_buffer);
                int rc;
                do{
                    long int char_id;
                    lrand48_r(&rand48_buffer, &char_id);
                    char_id %= NTHREADS;
                    rc = pthread_cancel(tid[char_id]);
                } while (rc == ESRCH);
            }
            break;
            default: printf("Unspec. signal\n");
            exit(1);
        }
    }
}


int main(int argc, const char *argv[]){
    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    sigset_t oldmask;
    int rc = pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
    file = fopen(FILENAME, "w");
    fclose(file);
    pthread_t thr_reaper;
    pthread_create(&thr_reaper, NULL,grim_reaper, NULL);
    pthread_create(&tid[0], NULL,character, "Hamlet");
    pthread_create(&tid[1], NULL,character, "Ophelia");
    pthread_create(&tid[2], NULL,character, "Gertrude");
    pthread_create(&tid[3], NULL,character, "Claudius");
    pthread_create(&tid[4], NULL,character, "Polonius");
    pthread_create(&tid[5], NULL,character, "Laertes");
    pthread_create(&tid[6], NULL,character, "Rosencrantz");
    pthread_create(&tid[7], NULL,character, "Guildenstern");
    pthread_mutex_lock(&nalive_lock);
    while(nalive > 0){
        pthread_cond_wait(&alldead_cond, &nalive_lock);
    }
    pthread_mutex_unlock(&nalive_lock);
    for(int tid_i = 0; tid_i < NTHREADS; tid_i++){
        pthread_join(tid[tid_i], NULL);
    }
    file = fopen(FILENAME, "a");
    fprintf(file, "The rest is silence. \n");
    fclose(file);
    pthread_cancel(thr_reaper);
    pthread_join(thr_reaper,NULL);
    return 0;
}

