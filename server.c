#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

int main(){
	/*Déclarations */
	int fifo1_fd, fifo2_fd;

    /* Création des tubes nommés */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);
	
	/*initialisation du générateur de nombres aléatoires*/
	srand (getpid()) ;

	/* Ouverture des tubes nommés */
	fifo1_fd = open(FIFO1, O_RDONLY);
	fifo2_fd = open(FIFO2, O_WRONLY);

	/* Envoi du PID serveur au Client */
	pid_t pid = getpid();
    write(fifo2_fd, &pid, sizeof(pid));


	/* Installation des Handlers */
	signal(SIGUSR1, hand_reveil);
	signal(SIGINT, fin_serveur); /* Faut voir le cas d'un signal quelconque */
	
	server_running = 1;
	//while(server_running){
		printf("Avant lecture question\n");
		/* lecture d'une question */
		Question question;
		read(fifo1_fd, &question, sizeof(Question));

		printf("Après\n");
		/* construction de la réponse*/
        Response response;
		response.count = question.n;
		response.client_num = question.client_num;
        for (int i = 0; i < response.count; i++) {
            response.numbers[i] = (rand() % NMAX) + 1 ;
        }
		
		/* envoi de la réponse*/
        write(fifo2_fd, &response, sizeof(Response));
		printf("Après envoie réponse");
		
		/* envoi du signal SIGUSR1 au client concerné*/
	    kill(question.client_num, SIGUSR1);
	//}
	
	/* Fermeture des tubes nommés et autres ressources */
    close(fifo1_fd);
    close(fifo2_fd);
    unlink(FIFO1);
    unlink(FIFO2);
	return 0;
}