#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

Question clientList[MAX_CLIENTS]; 
int size ; 
int clients_in_progress = -1;

void question_handling(Question question, int client_size){
    // Append elements to the list
    size++;
	if (client_size < size) {
    //clientList = (int*)realloc(clientList, size * sizeof(Question));
    clientList[size - 1].client_num = question.client_num ;
    clientList[size - 1].n = question.n;
	}
}

// void response_handling(){
//     free(clientList);

// }


int main(){
	/*Déclarations */
	// int fifo1_fd, fifo2_fd;

    // /* Création des tubes nommés */
    // mkfifo(FIFO1, 0666);
    // mkfifo(FIFO2, 0666);
	
	// /*initialisation du générateur de nombres aléatoires*/
	// srand (getpid()) ;

	// /* Ouverture des tubes nommés */
	// fifo1_fd = open(FIFO1, O_RDONLY);
	// fifo2_fd = open(FIFO2, O_WRONLY);

	/* Envoi du PID serveur au Client */
	// pid_t pid = getpid();

    // write(fifo2_fd, &pid, sizeof(pid));

	/* Installation des Handlers */
	signal(SIGUSR1, hand_reveil); // sigaction car signal qcqe
	signal(SIGINT, fin_serveur); /* Faut voir le cas d'un signal quelconque */
	
	server_running = 1;
	int fifo1_fd, fifo2_fd;
		  /* Création des tubes nommés */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);


	//int affichage = 1;
	while(server_running){
	// int fifo1_fd, fifo2_fd;
	// 	  /* Création des tubes nommés */
    // mkfifo(FIFO1, 0666);
    // mkfifo(FIFO2, 0666);
	
	/*initialisation du générateur de nombres aléatoires*/
	srand (getpid()) ;

	/* Ouverture des tubes nommés */
	fifo1_fd = open(FIFO1, O_RDONLY);
	fifo2_fd = open(FIFO2, O_WRONLY);

	pid_t pid = getpid();

    write(fifo2_fd, &pid, sizeof(pid));
		/* lecture d'une question */
		Question question;
		read(fifo1_fd, &question, sizeof(Question));

		clients_in_progress++;	
		//question_handling(question, clients_in_progress);
		//sleep(4);
		//if (affichage) {
		printf("Traitement de la demande du client: %d\n", question.client_num);
		//}
		//affichage = 0;

		/* construction de la réponse*/
			Response response;
			response.count = question.n;
			response.client_num = question.client_num;
			for (int i = 0; i < response.count; i++) {
				response.numbers[i] = (rand() % NMAX) + 1 ;
			}
			
			/* envoi de la réponse*/
			write(fifo2_fd, &response, sizeof(Response));
			//response_handling();
		
			/* envoi du signal SIGUSR1 au client concerné*/
			kill(question.client_num, SIGUSR1);
			close(fifo1_fd);
			close(fifo2_fd);
			// unlink(FIFO1);
			// unlink(FIFO2);
			
		}
		unlink(FIFO1);
		unlink(FIFO2);
		/* Fermeture des tubes nommés et autres ressources */
		// close(fifo1_fd);
		// close(fifo2_fd);
		// unlink(FIFO1);
		// unlink(FIFO2);
	return 0;
}
