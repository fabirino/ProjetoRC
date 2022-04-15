#ifndef FUNC_H
#define FUNC_H

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 1024

typedef struct {
    char nome[500];
    float preco_inicial;
} acao;

typedef struct {
    char nome[500];
    acao acoes[3];
    int num_acoes;
} mercado;

// fifo
typedef struct {
    char nome[500];
    char password[500];
    float saldo_inicial;
    mercado mercados[2];
    int num_mercados;
} utilizador;

typedef struct {
    utilizador user;
    bool ocupado;
} utilizadores;

typedef struct{
    pid_t c_pid;
    bool ocupado;
}processo;

//------

typedef struct {
    char admin[2][500]; // [0]AdminName [1]AdminPassword
    int num_utilizadores;
    utilizadores users[10];
    mercado mercados[2];
    int num_mercados;
    int refresh_time;

    int clientes_atuais; // numero de clientes a acessar o servidor ao mesmo tempo

    sem_t *mutex_compras;
    sem_t *mutex_menu;
    // sem_t *mutex_login;
    processo atuais[5];

} SM;

void erro(char *msg);

int login(int fd, SM *shared_memory);

int login_admin(int s, SM *shared_memory);

void config(char *path, SM *shared_memory);

void terminar(int shm_id, SM *shared_memory);

void add_cpid(int cliente, SM *shared_memory);

void remove_cpid(int cliente, SM *shared_memory);

#endif