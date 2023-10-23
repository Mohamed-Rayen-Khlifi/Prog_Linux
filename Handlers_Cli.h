#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include "serv_cli_fifo.h"

void hand_reveil(int sig) {
	/* Réception d'une réponse du serveur */
    printf("J'ai bien reçu la réponse du serveur\n");
    //kill(getppid(), SIGUSR1);


}
#endif