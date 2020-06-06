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

#define CLIENTE THREADS 4
#define REQ_READ 1
#define REQ_WRITE 2
#define REQ_QUIT 3
typedef struct request_tag{
    struct request_tag *next;
    int operation;
    int synchronous;
    int done_flag;
    pthread_cond_t done;
    char prompt[32];
    char text[128];
} request_t;

typedef struct tty_server_tag{
    request_t *first;
    request_t *last;
    int running;
    pthread_mutex_t mutex;
    pthread_cond_t request;
} tty_server_t;

tty_server_t tty_server ={NULL, NULL, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
int client_threads;
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clients_done = PTHREAD_COND_INITIALIZER;
void *tty_server_routine(void *arg){
    static pthread_mutex_t prompt_mutex = PTHREAD_MUTEX_INITIALIZER;
    request_t *request;
    int operation, len;
    for(;;){
        pthread_mutex_lock(&tty_server.mutex);
        while(tty_server.first == NULL){
            pthread_cond_wait(&tty_server.request, &tty_server.mutex);
        }
        request = tty_server.first;
        tty_server.first = request->next;
        if(tty_server.first = NULL)
            tty_server.last = NULL;
        pthread_mutex_unlock(&tty_server.mutex);
        operation = request->operation;
        switch (operation){
            case REQ_QUIT: break;
            case REQ_READ:
                if(strlen(request->prompt) > 0)
                    printf(request->prompt);
                if(fgets(request->text, 128, stdin)== NULL)
                    request->text[0] = '\0';
                len = strlen(request->text);
                if(len > 0 && request -> text[len - 1]== '\n')
                    request->text[len-1] = '\0';
                break;
            case REQ_WRITE:
                puts(request->text);
                break;
            default:break;
        }
        if(request->synchronous){
            pthread_mutex_lock(&tty_server.mutex);
            request->done_flag = 1;
            pthread_cond_signal(&request->done);
            pthread_mutex_unlock(&tty_server.mutex);
        } else
            free(request);
        if(operation == REQ_QUIT)
            break;
    }
    return NULL;
}

void tty_server_request(int operation, int sync, const char *prompt, char *string){
    request_t *request;
    int status;
    pthread_mutex_lock(&tty_server.mutex);
    if(!tty_server.running){
        pthread_t thread;
        pthread_attr_t detached_attr;
        pthread_attr_init(&detached_attr);
        pthread_attr_setdetachstate(&detached_attr, PTHREAD_CREATE_DETACHED);
        tty_server.running = 1;
        pthread_create(&thread, &detached_attr, tty_server_routine, NULL);
        pthread_attr_destroy(&detached_attr);
    }
    request = (request_t *) malloc(sizeof(request_t));
    request->next = NULL;
    request->operation = operation;
    request->synchronous = sync;
    if(sync){
        request->done_flag = 0;
        pthread_cond_init(&request->done, NULL);
    }
    if(prompt != NULL)
        strncpy(request->prompt, prompt,32);
    else
        request->prompt[0] = '\0';
    if(operation == REQ_WRITE && string !=NULL)
        strncpy(request->text, string, 128);
    else
        request->text[0] = '\0';
    pthread_cond_signal(&tty_server.request);
    if(sync){
        while(!request->done_flag)
            pthread_cond_wait(&request->done, &tty_server.mutex);
        if(operation == REQ_READ){
            if(strlen(request->text)> 0)
                strcpy(string, request->text);
            else
                string[0] = '\0';
        }
        pthread_cond_destroy(&request->done);
        free(request);
    }
    pthread_mutex_unlock(&tty_server.mutex);
}

void *client_routine(void *arg){
    int my_number = (int)arg, loops;
    char prompt[32], string[128], formatted[128];
    sprintf(prompt, "Client %d>", my_number);
    for(;;){
        tty_server_request(REQ_READ, 1, prompt, string);
        if(strlen(string)== 0) break;
        for(loops = 0; loops < 4; loops++){
            sprintf(formatted, "(%d#%d) %s", my_number, loops, string);
            tty_server_request(REQ_WRITE, 0, NULL, formatted);
            sleep(1);
        }
    }
    pthread_mutex_lock(&client_mutex);
    if(--client_threads <=0)
        pthread_cond_signal(&clients_done);
    pthread_mutex_unlock(&client_mutex);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t thread;
    int count, status;
    client_threads = client_threads;
    for(count = 0;count < client_threads; count++){
        pthread_create(&thread, NULL, client_routine,(void *) count);
    }
    pthread_mutex_lock(&client_mutex);
    while(client_threads > 0)
        pthread_cond_wait(&clients_done, &client_mutex);
    pthread_mutex_unlock(&client_mutex);
    printf("All clients done\n");
    tty_server_request(REQ_QUIT, 1, NULL, NULL);
    return 0;
}
