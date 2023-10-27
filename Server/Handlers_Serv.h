#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H
#include "../serv_cli_fifo.h"


void hand_reveil() {
    /*  Confirmation de la réception de réponse par le client */  
    printf("Réponse delivrée au client avec succès.\n\n");  
}
 
void fin_serveur(int sig) {
    printf("\nJ'ai reçu le signal numéro %d.\n", sig);
    server_running = 0;

    unlink(FIFO1);
    unlink(FIFO2);
    
    exit(0);
}
#endif