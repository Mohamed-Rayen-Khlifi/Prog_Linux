#include "Handlers_Serv.h"

int main(){
	/*Déclarations */
	server_running = 1;
	int fifo1_fd, fifo2_fd;

	/* Initialisation du générateur de nombres aléatoires */
	srand (getpid()) ;

	/* Création des tubes nommés */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

	/* Installation des Handlers */
	signal(SIGUSR1, hand_reveil);

	/* Déclaration d'un group de signaux */
    int signals[] = {SIGTSTP, SIGQUIT, SIGINT, SIGTERM, SIGHUP};
    int numSignals = sizeof(signals) / sizeof(signals[0]);

    /* Déclaration du sigaction */
    struct sigaction sa;
    sa.sa_handler = fin_serveur;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 

    for (int i = 0; i < numSignals; i++) {
        sigaction(signals[i], &sa, NULL);
    }
	
	/* Boucle de traitement des questions */
	while(server_running){

		/* Ouverture des tubes nommés */
		fifo1_fd = open(FIFO1, O_RDONLY);
		fifo2_fd = open(FIFO2, O_WRONLY);

		/* Envoi du PID serveur au Client */
		pid_t pid = getpid();
		write(fifo2_fd, &pid, sizeof(pid));
		
		/* Lecture d'une question */
		Question question;
		if (read(fifo1_fd, &question, sizeof(Question)) == -1){
			continue;
		};

		printf("Traitement de la demande du client: %d\n", question.client_num);

		/* Construction de la réponse */
		Response response;
		response.count = question.n;
		response.client_num = question.client_num;
		for (int i = 0; i < response.count; i++) {
			response.numbers[i] = (rand() % NMAX) + 1 ;
		}
		
		/* Envoi de la réponse */
		write(fifo2_fd, &response, sizeof(Response));
	
		/* Envoi du signal SIGUSR1 au client concerné */
		kill(question.client_num, SIGUSR1);
		
		/* Fermeture des descripteurs */
		close(fifo1_fd);
		close(fifo2_fd);	
		sleep(1);
		}
	
	return 0;
}
