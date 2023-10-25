#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

int main(){
	/* Déclarations */
	int fifo1_fd, fifo2_fd;
	
	/* Ouverture des tubes nommés */
    fifo1_fd = open(FIFO1, O_WRONLY);
    fifo2_fd = open(FIFO2, O_RDONLY);
	
	/* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
	
	/* Récuperation du PID du serveur*/
	pid_t PID_Server;
	read(fifo2_fd, &PID_Server, sizeof(PID_Server));
	printf("Le PID du serveur: %d\n",PID_Server);

	/* Construction et envoi d'une question */
	Question question;
	question.client_num = getpid();
	question.n = (rand() % NMAX) + 1 ;
	printf("J'ai demandé %d nombres aléatoires\n", question.n);
	
	write(fifo1_fd, &question, sizeof(Question));
	
	/* Envoi du signal SIGUSR1 au serveur; Envoi d'une question */
	kill(PID_Server, SIGUSR1);

	/* Attente de la réponse */
	Response response;
	read(fifo2_fd, &response, sizeof(Response));
	
	/* Envoi du signal SIGUSR1 au serveur; Reception de réponse */
	
	/* Lecture de la réponse */
	printf("Client %d:\nResponse = ", response.client_num);
	for (int i = 0; i < response.count; i++) {
        printf("%d\t", response.numbers[i]);
    }
	printf("\n");
	
	/* Traitement local de la réponse */
	close(fifo1_fd);
    close(fifo2_fd);
	return 0;
}