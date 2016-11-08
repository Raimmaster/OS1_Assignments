#include "utils.c"
#include <pthread.h>
#define OPTION_SZ 6
#define GAME_LIMIT 10

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
	int msqid;
	int key = 5555;
	srand(time(NULL));
	msqid = create_msgq(key);
	mbuf_t *msg_buf = malloc(sizeof(mbuf_t));
		//receive_message(msqid, sbuf, 2);
	//printf("recibio %s\n", sbuf->info.mssg);
	data_t local_players;
	local_players.player_one=0;
	local_players.player_two=0;
	while(1) {
		bzero(msg_buf->info.mssg, 20);
		receive_message(msqid, msg_buf, 2);
        printf("Received: \"Player: %d num: %s\"\n", msg_buf->info.player_pid, msg_buf->info.mssg);
        sleep(1);
        int reason = strcmp(msg_buf->info.mssg, "connect");
        if(reason == 0){
        	++players_connected;
        	printf("entro en reason\n");       	
	        if(players_connected == 2){
	        	printf("entro en create thread\n");
        		local_players.player_two = msg_buf->info.player_pid;
	        	create_game_thread(&local_players);
	        	restart_player_counters(&players_connected, &local_players);
	        }else{
	        	printf("entro en reason1\n"); 
	        	if(local_players.player_one == 0){
	        		printf("entro en reason2\n"); 
	        		local_players.player_one = msg_buf->info.player_pid;
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
	(*g_data).player_one = (*match_players).player_one;
	(*g_data).player_two = (*match_players).player_two;
	pthread_create(thread, NULL, game, (void*)g_data);
}

void restart_player_counters(int* players_connected, data_t* local_players){
	*players_connected = 0;
    (*local_players).player_one = 0;
	(*local_players).player_two = 0;
}

void* game(void* arg){
	data_t* g_data = (data_t*) arg;
	int number = rand() % GAME_LIMIT;//number to be guessed
	printf("GUESS NUMBER: %d\n",number );
	short winner = 0;
	int m_key_player1 = (*g_data).player_one;
	int m_key_player2 = (*g_data).player_two;
	int msgqid_p1 = connect_msgq(m_key_player1);
	int msgqid_p2 = connect_msgq(m_key_player2);
	mbuf_t buf;
	bzero(buf.info.mssg, 20);
	strcpy(buf.info.mssg, "ready");
	send_message(msgqid_p1, &buf, 1);
	send_message(msgqid_p2, &buf, 1);

	int turn = 0;
	mbuf_t *rbuf=malloc(sizeof(mbuf_t));
	while(winner != 1){
		//GAME LOGIC
		int msgqid = turn % 2 == 0 ? msgqid_p1 : msgqid_p2;
		receive_message(msgqid, rbuf, 2);
		printf("Received: %s from %d\n",rbuf->info.mssg, msgqid);
		int num = atoi(rbuf->info.mssg);
		if(num == number){
			strcpy(buf.info.mssg, "winner");
			winner = 1;
			printf("Player %d has won\n", buf.info.player_pid);
		 	strcpy(buf.info.mssg, "winner");
			send_message(msgqid, &buf, 1);
		 	
		 	int loser;
		 	loser = buf.info.player_pid == m_key_player1 ? m_key_player2 : m_key_player1; 
			printf("Player %d has lost\n", loser);
			msgqid = msgqid == msgqid_p1 ? msgqid_p2 : msgqid_p1;
			bzero(buf.info.mssg, 20);
			buf.info.player_pid = loser;
			strcpy(buf.info.mssg, "loser");
			send_message(msgqid, &buf, 1);
		}else if(num< number){
			bzero(buf.info.mssg, 20);
			strcpy(buf.info.mssg, "higher");
			send_message(msgqid, &buf, 1);
		}else{
			bzero(buf.info.mssg, 20);
			strcpy(buf.info.mssg, "lower");
			send_message(msgqid, &buf, 1);
		}
		++turn;
	}
	free(rbuf);
	return NULL;
}