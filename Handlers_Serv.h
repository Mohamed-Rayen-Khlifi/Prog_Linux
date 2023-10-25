#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H
#include "serv_cli_fifo.h"

int clientList[MAX_CLIENTS]; 

void hand_reveil(int sig) {
    /* Deux cas : 
    Réception d'une question du client ou bien 
    Confirmation de la réception de réponse par le client
    */  

    /* Cas1: Ajout d'un client à la liste après la réception de sa question */
    // for (int i = 0; i < MAX_CLIENTS; i++) {
    //     if (clientList[i] == 0 || clientList[i] == question.client_num) {
    //         clientList[i] = question.client_num;
    //         break;
    //     }
    // }

}

void fin_serveur(int sig) {
    printf("J'ai reçu le signal: SIG%d\n", sig);
    server_running = 0;
    exit(0);
}
#endif