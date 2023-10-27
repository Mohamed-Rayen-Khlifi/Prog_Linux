#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H
#include "../serv_cli_fifo.h"


void hand_reveil() {
    /*  Confirmation de la réception de réponse par le client */  
    printf("Réponse delivrée\n");
    }
 
void fin_serveur(int sig) {
    printf("J'ai reçu le signal: %d\n", sig);
    server_running = 0;
    exit(0);
    unlink(FIFO1);
    unlink(FIFO2);
}
#endif