#include "server.h"

int stc;
int cts;
char *buffer;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        free(buffer);
        printf("\nServer exit\n");
        exit(1);
    }
}

void clear_buffer(char *buffer){
	int i;
	for(i=0;i<BUFFER_SIZE;i++){
		buffer[i]='\0';
	}
}

void toClient(char msg[2048]){
	char string[2048];
	strcpy(string,msg);

	int n = strlen(string)+1;
	write(stc, &n, sizeof(int));
	write(stc, string, sizeof(char) * n);
}


void print_array(char ** input){
        int i = 1;
        printf("0) %s\n",input[0]);
        while(1){
                printf("%d) %s\n",i,input[i]);
                i++;
                if(input[i]==NULL){
                        printf("%d) %s\n",i,input[i]);
                        break;
                }
        }
}


void parse_args(char ** end, char * line, char * d){
        char *token;
        char *p;
        p = line;
        int counter = 0;

        while(p){
                token = strsep(&p,d);
                end[counter] = token;
                counter++;
        }
        end[counter] = NULL;
}

int arraylen(char **array){
	int counter;
	while(array[counter]!=NULL){
		counter++;
	}

	return counter;

}

int quizID_gen(){

	srand(time(NULL));
	int id = rand()%10000;

	char *file= "id.txt";
	int fd = open(file, O_RDONLY);

	struct stat *buf;
	buf = malloc(sizeof(struct stat));
	stat(file, buf);
	int size = buf->st_size;
	printf("Size of id.txt: %d\n",size);

	free(buf);

	char *raw_content = malloc(sizeof(char) * (size+25));
	read(fd, raw_content, size);

	printf("raw_content:\n%s", raw_content);

	char **processed_content = malloc(sizeof(char **));

	char *token;
        int counter = 0;

        while(raw_content){
                token = strsep(&raw_content,"\n");
                processed_content[counter] = token;
                counter++;
        }
        processed_content[counter] = NULL;

	print_array(processed_content);
	int array_len = arraylen(processed_content);

	printf("num element in processed_content: %d\n",array_len);

	int id_txt;
	int i;
	while(1){
		printf("In While Loop\n");
		for(i=0; i<array_len; i++){
			printf("In For Loop: i=%d\n",i);

			sscanf(&processed_content[i][0], "%d", &id_txt);

			printf("rand id: %d\n",id);
			printf("id_txt: %d\n",id_txt);

			if(id==id_txt){
				printf("NEW RAND_INT\n");
				id = rand()%10000;
				break;
			}
			else if(i+1==array_len){
				free(processed_content);
				free(raw_content);
				printf("last id element checked\n");
				return id;
			}
		}

	}


	close(fd);
	return 0;
}


void makequiz(){

	toClient("Let's Make A Quiz!\nQuiz Name: ");
	int n;

	//QUIZ NAME
	char quiz_name[250];
	read(cts, &n,sizeof(int));
	read(cts, &quiz_name,sizeof(char) * n);
	printf("Quiz Name Received: %s\n",quiz_name);

	//NUMBER OF QUESTIONS
	char *ques_num = malloc(sizeof(char)*5);
	toClient("How many questions are in your quiz? ");
	read(cts, &n,sizeof(int));
	read(cts,ques_num,sizeof(char) * n);
	printf("# of Question(s) received in char: %s\n",ques_num);

	int quesNum;
	sscanf(ques_num, "%d", &quesNum);
	printf("# of Question(s) received in int: %d\n",quesNum);

	free(ques_num);

	//QUIZ PIN
	char *pin = malloc(sizeof(char) * 6);
	toClient("Enter a 4-Digit Pin for your quiz ");
	read(cts, &n, sizeof(int));
	read(cts,pin,sizeof(char) * n);
	printf("Pin Received in char: %s\n", pin);

	int pinNum;
	sscanf(pin, "%d", &pinNum);
	printf("Pin Received in int: %d\n", pinNum);
	free(pin);

	//GENERATE AN UNUSED QUIZID
	int id = quizID_gen();
	printf("QuizID Generated: %d\n",id);


	//ADD QUESTIONS
	char content[quesNum+2][3000];
	int i;
	for(int i=1; i<=quesNum; i++){

		//content[i] = q;

		char msg[50];
		char num[5];
		sprintf(num, "%d", i);
		strcpy(msg,"Number ");
		strcat(msg,num);
		strcat(msg,"\nQuestion: ");
		toClient(msg);

		char question[500];
		read(cts, &n, sizeof(int));
		read(cts, &question, sizeof(char) * n);
		printf("Question received: %s\n",question);

		char type[5];
		while(1){
			char response[5];
			toClient("Type (M for Multiple Choice & S for short response): ");
			read(cts, &n, sizeof(int));
			read(cts, &response, sizeof(char) * n);
			printf("Type received: %s\n", response);

			if(strcmp(response,"M") == 0 || strcmp(response,"S")== 0){
				strcpy(type,response);
				break;
			}
		}

		strcat(content[i],question);
		strcat(content[i],"\\");
		strcat(content[i],type);
		strcat(content[i],"\\");

		if(strcmp(type,"M")==0){
			char A[250];
			toClient("Choice A: ");
			read(cts, &n, sizeof(int));
			read(cts, &A, sizeof(char) * n);
			printf("A received: %s\n",A);

			char B[250];
			toClient("Choice B: ");
			read(cts, &n, sizeof(int));
			read(cts, &B, sizeof(char) * n);
			printf("B received: %s\n",B);

			char C[250];
			toClient("Choice C: ");
			read(cts, &n, sizeof(int));
			read(cts, &C, sizeof(char) * n);
			printf("C received: %s\n",C);

			char D[250];
			toClient("Choice D: ");
			read(cts, &n, sizeof(int));
			read(cts, &D, sizeof(char) * n);
			printf("D received: %s\n",D);

			strcat(content[i],A);
			strcat(content[i],"\\");
			strcat(content[i],B);
			strcat(content[i],"\\");
			strcat(content[i],C);
			strcat(content[i],"\\");
			strcat(content[i],D);
			strcat(content[i],"\\");

		}

		char correctanswer[100];
		toClient("Correct Answer: ");
		read(cts, &n, sizeof(int));
		read(cts, &correctanswer, sizeof(char) * n);
		printf("AK received: %s\n", correctanswer);

		strcat(content[i],correctanswer);
		printf("Together: %s\n",content[i]);
	}

	printf("Question 1: %s\n", content[1]);

	//CONFIRMATION
	while(1){
		toClient("Type \"Go\" to make your quiz live!\n>>");
		char response[5];
		read(cts, &n, sizeof(int));
		read(cts, &response, sizeof(int) * n);

		if(strcmp(response,"Go") == 0)
			break;
	}


	//CREATE QUIZFILE

	char filename[100];
	char quizID_S[10];
	sprintf(quizID_S, "%d", id);
	strcpy(filename, quizID_S);
	strcat(filename,".txt");

	char *quiz_file = malloc(sizeof(char) * 100);
	strcpy(quiz_file,"quizzes/");
	strcat(quiz_file, filename);

	printf("qf name: %s\n", quiz_file);

	int qf = open(quiz_file, O_CREAT | O_APPEND | O_WRONLY, 0764);

	//Add Quiz Content into the QuizFile

	n = strlen(quiz_name);
	write(qf, quiz_name, n);

	for(i=1; i<=quesNum; i++){
		n = strlen(content[i]);
		write(qf, "\n", 1);
		write(qf, content[i], n);
	}
	close(qf);
	free(quiz_file);

	//CREATE RESULTFILE AND ADD QUIZ NAME
	char *result_file = malloc(sizeof(char) * 100);
	strcpy(result_file,"results/");
	strcat(result_file, filename);

	printf("rf name: %s\n", result_file);

	n = strlen(quiz_name);

	int rf = open(result_file, O_CREAT | O_APPEND | O_WRONLY, 0764);
	write(rf, quiz_name, n);

	close(rf);
	free(result_file);


	//APPEND THE QUIZ ID AND PIN TO RESPECTIVE FILE
	char pin_S[10];
	sprintf(pin_S, "%d", pinNum);;

	int pinFile = open("pin.txt", O_CREAT | O_APPEND | O_WRONLY, 0764);
	n= strlen(pin_S);
	write(pinFile, "\n", 1);
	write(pinFile, pin_S, n);
	close(pinFile);

	int idFile = open("id.txt",O_CREAT | O_APPEND | O_WRONLY, 0764);
	n = strlen(quizID_S);
	write(idFile, "\n", 1);
	write(idFile, quizID_S, n);
	close(idFile);


	//REMINDER TO WRITE DOWN QUIZID AND PIN
	char remind[520];
	strcpy(remind,"Please write down your unique QuizId and Pin Number\nQuizID: ");
	strcat(remind,quizID_S);
	strcat(remind,"\nQuiz Pin: ");
	strcat(remind,pin_S);
	strcat(remind,"\nType Done to Finish\n>>");

	char remind_reply[100];
	toClient(remind);
	read(cts, &n, sizeof(int));
	read(cts, &remind_reply, sizeof(char) * n);
	printf("End of MakeQuiz\n");
}


void takequiz(){
	toClient("Let's Take A Quiz!\nQuiz ID: ");
	int n;


	//TAKE IN QUIZID
	char quiz_id[25];
        read(cts, &n,sizeof(int));
        read(cts, &quiz_id,sizeof(char) * n);
        printf("QuizID Received: %s\n",quiz_id);


	//TAKE IN USER'S NAME
	char user_name[250];
	toClient("Your name: ");
        read(cts, &n,sizeof(int));
        read(cts, &user_name,sizeof(char) * n);
        printf("User Name Received: %s\n",user_name);


	//Convert ID to corresponding txt file
	char *fileName = malloc(sizeof(char) * 50);;
	strcpy(fileName,"quizzes/");
	strcat(fileName,quiz_id);
	strcat(fileName,".txt");
	printf("fileName: %s\n",fileName);


	//OPEN THE QUIZ FILE AND READ IT IN

	int fd = open(fileName, O_RDONLY);

	struct stat *buf;
	buf = malloc(sizeof(struct stat));
	stat(fileName, buf);
	int size = buf->st_size;
	printf("Size of %s: %d\n", fileName, size);
	free(buf);
	free(fileName);
	char *raw_content = malloc(size+100);
	read(fd, raw_content, size);


	char **processed_content = malloc(size*2);

        char *token;
        int counter = 0;

        while(raw_content){
                token = strsep(&raw_content,"\n");
                processed_content[counter] = token;
                counter++;
        }
        processed_content[counter] = NULL;

        print_array(processed_content);
        int quesNum = arraylen(processed_content) - 1 ;
 	printf("num element in processed_content: %d\n",quesNum);
	free(raw_content);

	//SETUP 2 ARRAYS: ONE FOR USER ANSWER AND ONE FOR CORRECT ANSWER
	char **user_answer = malloc(quesNum * 500);
	char **correct_answer = malloc(quesNum *500);

	//ASK QUESTION, GET USER RESPONSE, AND PUT CORRECT ANSWER INTO CORRECT_ANSWER
	int i;
	for(i=1; i<= quesNum ; i++){
		char **question_content = malloc(quesNum * 1500);
		printf("In For Loop and memory allocated\n");

     		counter = 0;
        	while(processed_content[i]){
                	token = strsep(&processed_content[i],"\\");
                	question_content[counter] = token;
                	counter++;
        	}
        	question_content[counter] = NULL;

        	print_array(question_content);
        	int array_len = arraylen(question_content);
        	printf("num element in question_content: %d\n",array_len);


		char num[5];
		sprintf(num, "%d", i);

		char question_toClient[2000];
		if(strcmp(question_content[1],"M")==0){
			printf("multiple choice; i=%d\n",i);
			strcpy(question_toClient,"\nQuestion Number ");
			strcat(question_toClient, num);
			strcat(question_toClient,"\n");

			strcat(question_toClient,question_content[0]);
			printf("added question\n");
			strcat(question_toClient,"\n(A) ");
			strcat(question_toClient,question_content[2]);
			printf("added choice A\n");
			strcat(question_toClient,"\n(B) ");
			strcat(question_toClient,question_content[3]);
			printf("added choice B\n");
			strcat(question_toClient,"\n(C) ");
			strcat(question_toClient,question_content[4]);
			printf("added choice C\n");
			strcat(question_toClient,"\n(D) ");
			strcat(question_toClient,question_content[5]);
			printf("added choice D\n");
			strcat(question_toClient,"\nYour Answer: ");

			correct_answer[i-1] = question_content[6];
			printf("Correct answer: %s\n",correct_answer[i-1]);

			char *response = malloc(sizeof(char) * 250);
			toClient(question_toClient);
			read(cts, &n, sizeof(int));
			read(cts, response, sizeof(char) * n);
			user_answer[i-1] = response;
			printf("user_answer[%d]: %s\n",i-1,user_answer[i-1]);

		}
		else{
			printf("\nShort response; i=%d\n",i);
			strcpy(question_toClient,"\nQuestion Number ");
                        strcat(question_toClient, num);
                        strcat(question_toClient,"\n");
			strcat(question_toClient,question_content[0]);
                        strcat(question_toClient,"\nYour Answer: ");

			correct_answer[i-1] = question_content[2];
			printf("Correct answer: %s\n",correct_answer[i-1]);

			char *response = malloc(sizeof(char) * 250);
			toClient(question_toClient);
			read(cts, &n, sizeof(int));
			read(cts, response, sizeof(char) * n);
			user_answer[i-1] = response;
			printf("user_answer[%d]: %s\n",i-1,user_answer[i-1]);

		}
	}

	printf("Time to Grade\nCorrect Answers\n");
	print_array(correct_answer);
	printf("\nUser Answers\n");
	print_array(user_answer);

	//Grading
	char ** mistakes = malloc(sizeof(char) * quesNum * 10);
	int mistake_counter=0;
	int score = 0;
	for(i=0; i< quesNum; i++){
		printf("in for loop: i=%d\n",i);
		if(strcmp(correct_answer[i],user_answer[i])==0)
			score++;
		else{
			char *num = malloc(sizeof(char) * 4);
			sprintf(num, "%d", i+1);
			mistakes[mistake_counter] = num;
			mistake_counter++;
		}
	}

	double percent = (double)score/quesNum*100;
	printf("Score: %d    Percentage: %f\n",score,percent);
	print_array(mistakes);

	free(correct_answer);
	free(user_answer);

	char score_C[5];
        sprintf(score_C, "%d", score);

        char quesNum_C[5];
        sprintf(quesNum_C, "%d", quesNum);

        char percent_C[18];
        sprintf(percent_C, "%f", percent);

	//ADD THE RESULTS IN THE QUIZ'S RESULT'S FILE

	char result_msg[1000];
	strcpy(result_msg,user_name);
	strcat(result_msg,",");
	strcat(result_msg,percent_C);

	for(i=0; i<arraylen(mistakes); i++){
		strcat(result_msg, ",");
		strcat(result_msg,mistakes[i]);
	}

	char *result_file = malloc(100);
        strcpy(result_file,"results/");
        strcat(result_file, quiz_id);
	strcat(result_file, ".txt");
	printf("result file: %s\n",result_file);

	printf("result_msg: %s\n", result_msg);

	n = strlen(result_msg);

	int rf = open(result_file, O_APPEND | O_WRONLY, 0764);
	write(rf,"\n",1);
	write(rf,result_msg, n);

	close(rf);
	free(result_file);
	//RETURNS THE USER THEIR SCORE (PERCENT AND FRACTION)

	char score_msg[2000];
	strcpy(score_msg,"\nHere is your score:\n\tScore: ");
	strcat(score_msg,score_C);
	strcat(score_msg," of ");
	strcat(score_msg,quesNum_C);
	strcat(score_msg,"\n\tPercentage: ");
	strcat(score_msg,percent_C);
	strcat(score_msg,"\n\nType Done to Finish\n");
	toClient(score_msg);

	char reply[100];
        read(cts, &n, sizeof(int));
        read(cts, &reply, sizeof(char) * n);

	printf("End of TAKEQUIZ\n");
}

int main() {

	signal(SIGINT, sighandler);

	while(1){
		//printf("[Server Setup] cts created (aka WKP)\n");
		mkfifo("cts", 0644);

		printf("Waiting for client connection...\n");
		cts = open("cts", O_RDONLY);

		//printf("[Server Setup] client connection initiated\n");

		char pipe_name[32];
    		read(cts,pipe_name,sizeof(pipe_name));
		//printf("[Server Handshake] received client pipe name: %s\n",pipe_name);
    		remove("cts");
		//printf("[Server Handshake] cts (aka WKP) removed \n");

    		stc = open("stc", O_WRONLY);
		//printf("[Server Handshake] connected to client\n");


    		write(stc,"HELLO",6);
		//printf("[Server Handshake] Acknowledgement sent\n");

    		char msg[32];
    		read(cts, msg,sizeof(msg));
    		//printf("[Server Handshake] Acknowledgement Received <%s>\n", msg);


		printf("connection established\n");


			buffer = malloc(2048);
			int n;
			while(read(cts, &n,sizeof(int)) && read(cts, buffer,sizeof(char) * n)){
				printf("Inital Command \"%s\" from client\n", buffer);

				if(strcmp(buffer,"Make")==0){
					makequiz();
					toClient("END");
				}
				else if(strcmp(buffer,"Take")==0){
					takequiz();
					toClient("END");
				}
				else if(strcmp(buffer,"Result")==0){
					toClient("Let's See What We Have!");
				}
				else{
					toClient("Not a valid inital command. Please type: Make, Take, or Result\n>> ");
				}

				clear_buffer(buffer);
			}
    	}
}
