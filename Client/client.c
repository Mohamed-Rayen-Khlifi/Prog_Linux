#include "Handlers_Cli.h"

int main(){
	/* Déclarations des descripteurs */
	int fifo1_fd, fifo2_fd;

	/* Initialisation du générateur de nombres aléatoires */
	srand (getpid()) ;
	
	/* Ouverture des tubes nommés */
    fifo1_fd = open(FIFO1, O_WRONLY);
    fifo2_fd = open(FIFO2, O_RDONLY);
	
	/* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
	
	/* Récuperation du PID du serveur */
	pid_t PID_Server;
	while (read(fifo2_fd, &PID_Server, sizeof(PID_Server)) == -1){
		printf("Problème PID serveur.\n");
	};

	/* Construction et envoi d'une question */
	Question question;
	question.client_num = getpid();
	question.n = (rand() % NMAX) + 1 ;

	printf("Demande de %d nombres aléatoires: \n", question.n);

	write(fifo1_fd, &question, sizeof(Question));

	/* Attente de la réponse */
	Response response;
	while (read(fifo2_fd, &response, sizeof(Response)) == -1){
		printf("Pas de réponse du serveur.\n");
	};

	/* Envoi du signal SIGUSR1 au serveur; Reception de réponse */
	kill(PID_Server, SIGUSR1);

	/* Lecture de la réponse */
	printf("Client %d:\nResponse = ", response.client_num);
	for (int i = 0; i < response.count; i++) {
        printf("|%d  ", response.numbers[i]);
    }
	printf("\n");
	
	/* Fermeture des descripteurs */
	close(fifo1_fd);
    close(fifo2_fd);
	return 0;
}