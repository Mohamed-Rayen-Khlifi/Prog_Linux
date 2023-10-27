#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include "../serv_cli_fifo.h"

void hand_reveil() {
	/* Réception d'une réponse du serveur */
    printf("Réponse reçue\n");
    //kill(getppid(), SIGUSR1);


}
#endif