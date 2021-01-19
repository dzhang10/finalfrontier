#include "client.h"

char *buffer;
char *response;


static void sighandler(int signo) {
    if (signo == SIGINT) {
	free(response);
	free(buffer);
        printf("\nClient exit\n");
        exit(1);
    }
}

void clear_buffer(char * buffer){
	int i;
	for(i=0;i<BUFFER_SIZE; i++){
		buffer[i]='\0';
	}
}

int main() {

	signal(SIGINT, sighandler);

    	mkfifo("stc", 0644);
    	//printf("[Client] Pipe Created\n");

    	int cts = open("cts", O_WRONLY);
	//printf("[Client Handshake] connected to server\n");


    	write(cts,"stc",10);
    	//printf("[Client Handshake] Sent stc pipe\n");
	//printf("[Client Handshake] Waiting for Connection...\n");
	int stc = open("stc", O_RDONLY);
	//printf("[Client Handshake] server connected\n");

	remove("stc");
	//printf("[Client Handshake] removed pipe\n");

    	char msg[32];
    	read(stc, msg,sizeof(msg));
    	//printf("[Client Handshake] Received ack <%s>\n", msg);

    	write(cts, msg,sizeof(msg));
    	//printf("[Client Handshake] Sent ack\n");
	//printf("[Client Handshake] Complete\n");


    	while(1){

		printf("WELCOME TO QUIZZIFY!\n\nWhat would you like to do?\nChoices: Make, Take, or Results\n>> ");

		response = malloc(2048);
		buffer = malloc(2048);


		while(1){

			fgets(buffer, 2000, stdin);
			//*strchr(buffer, '\n') = '\0';
			buffer[strlen(buffer)-1]='\0';

			//printf("client: sending \"%s\"\n",buffer);

			if(strlen(buffer)==0)
				printf("Please enter a command\n");

			if(strcmp(buffer,"Reset")==0)
				break;
			else{
				int n = strlen(buffer)+1;
				write(cts, &n, sizeof(int));

				write(cts, buffer, sizeof(char) * n);
				clear_buffer(buffer);


				read(stc, &n, sizeof(int));
				read(stc, response, sizeof(char) * n);
				if(strcmp(response,"END")==0)
					break;
				printf("%s", response);
				clear_buffer(response);
			}
		}

 	}

	return 0;
}


