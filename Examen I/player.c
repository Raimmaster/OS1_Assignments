#include "utils.c"
#define OPTION_SZ 6
#define GAME_LIMIT 100

void connect_to_server();

int main(int argc, char *argv[])
{
	int msgqid;
	mbuf_t buf;
	int value = getpid();
	printf("Player: %d;\n", value);
	int key = 5555;
	msgqid = connect_msgq(key);
	
	char name[20];
	sprintf(name, "%d", value);	
	buf.info.player_pid = value;

	time_t t;
	srand((unsigned) time(&t));
	
	connect_to_server();

	while(1){
		bzero(buf.info.mssg, 20);
		if(msgrcv(msgqid, &buf, sizeof(struct msg_info), 0, 0) == -1){
			perror("msgrcv");
			exit(1);
		}

		int message = strcmp(buf.info.mssg, "connect");

		if(message == 0){
			//code for connecting with game;
			break;
		}

		sleep(1);
	}

	printf("Game!\n");
	return 0;
}

void connect_to_server(){
	mbuf_t buf;
	bzero(buf.info.mssg, 20);		
	strcpy(buf.info.mssg, "connect");
        
    if (msgsnd(msgqid, &buf, sizeof(struct msg_info), 0) == -1)
        perror("msgsnd");
}

void send_random_num(){
	int game_ended = 0;
	while(game_ended != 1){
		mbuf_t buf;
		char num[20];
		int rand_num = rand() % GAME_LIMIT;
		
		bzero(buf.info.mssg, 20);
		bzero(num, 20);
		sprintf(num, "%d", rand_num);
		strcpy(buf.info.mssg, num);
			
		printf("Rand num is: %d\n", rand_num);
	        
	    if (msgsnd(msgqid, &buf, sizeof(struct msg_info), 0) == -1)
	        perror("msgsnd");

	    sleep(1);

	    //check response
	    if(msgrcv(msgqid, &buf, sizeof(struct msg_info), 0, 0) == -1){
			perror("msgrcv");
			exit(1);
		}
		int reason = strcmp(buf.info.mssg, "winner");

		if(reason == 0){
			game_ended = 1;
		}
	}	
}