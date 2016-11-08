#include "utils.c"
#include <pthread.h>
#define OPTION_SZ 6
#define GAME_LIMIT 100

typedef struct game_data{
	pid_t player_one;
	pid_t player_two;
} data_t;

void* game(void*);//for game thread
void create_game_thread(data_t* match_players);
void restart_player_counters(int* players_connected, data_t* local_players);

int main(int argc, char *argv[])
{	
	int players_connected = 0;
	mbuf_t msg_buf;
	int msqid;
	int key = 5555;
	pthread_t send_thread;
	pthread_t receive_thread;

	msqid = create_msgq(key);
	
	msg_buf.mtype = 0;
	data_t local_players;
	while(1) {
		bzero(msg_buf.info.mssg, 20);
		if (msgrcv(msqid, &msg_buf, sizeof(struct msg_info), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Received: \"Player: %d num: %s\"\n", msg_buf.info.player_pid, msg_buf.info.mssg);
        sleep(1);
        int reason = strcmp(msg_buf.info.mssg, "connect");
        if(reason == 0){       	
	        if(players_connected == 2){
	        	create_game_thread(&local_players);
	        	restart_player_counters(&players_connected, &local_players);
	        }else{
	        	++players_connected;
	        	if(local_players.player_one == 0){
	        		local_players.player_one = msg_buf.info.player_pid;
	        	}else{
	        		local_players.player_two = msg_buf.info.player_pid;
	        	}
	        }
        }
	}

	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}

	return 0;
}

void create_game_thread(data_t* match_players){
	pthread_t* thread = malloc(sizeof(pthread_t));
	data_t* g_data = malloc(sizeof(data_t));
	(*g_data).player_one = local_players.player_one;
	(*g_data).player_two = local_players.player_two;
	pthread_create(thread, NULL, game, (void*)g_data);
}

void restart_player_counters(int* players_connected, data_t* local_players){
	*players_connected = 0;
    (*local_players).player_one = 0;
	(*local_players).player_two = 0;
}

void* game(void* arg){
	data_t* g_data = *(data_t*) g_data;
	time_t t;
	srand((unsigned) time(&t));
	int number = rand() % GAME_LIMIT;//number to be guessed
	short winner = 0;

	while(winner != 1){
		//GAME LOGIC
		mbuf_t buf;

		if(msgrcv(msgqid, &buf, sizeof(struct msg_info), 0, 0) == -1){
			perror("msgrcv");
			exit(1);
		}

		int num = atoi(buf.info.mssg);
		if(num == number){
			strcpy(buf.info.mssg, "winner");
			winner = 1;
			printf("Player %d has won\n", buf.info.player_pid);
			send_m
		}
	}

	return NULL;
}