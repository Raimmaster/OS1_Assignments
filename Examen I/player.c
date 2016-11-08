#include "utils.c"
#define OPTION_SZ 6
#define GAME_LIMIT 10
#define SERVER_KEY 5555

void connect_to_server();
int set_buf_message(int msgqid, mbuf_t *buf, int *, int *, int);
void send_random_num(int msgqid);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int msgqid;
	mbuf_t *buf = malloc(sizeof(mbuf_t));
	int key = getpid();
	printf("Player: %d;\n", key);
	msgqid = create_msgq(key);
	
	buf->info.player_pid = key;
	printf("About to connect, dude!\n");
	connect_to_server(connect_msgq(SERVER_KEY));
	printf("Connected yo!\n");
	
	bzero(buf->info.mssg, 20);
	receive_message(msgqid, buf, 1);

	int message = strcmp(buf->info.mssg, "ready");

	if(message == 0){
		//code for connecting with game;
		send_random_num(msgqid);
	}

	sleep(1);
	free(buf);
	printf("Game!\n");
	return 0;
}

void connect_to_server(int msgqid){
	mbuf_t sbuf;
	sbuf.info.player_pid = getpid();
	bzero(sbuf.info.mssg, 20);		
	strcpy(sbuf.info.mssg, "connect");  
    send_message(msgqid, &sbuf, 2);
}

void send_random_num(int msgqid){
	int game_ended = 0;
	mbuf_t *buf=malloc(sizeof(mbuf_t));
	int lower_limit=0; 
	int upper_limit= GAME_LIMIT;
	int used_number=0;
	while(game_ended != 1){
		
		used_number=set_buf_message(msgqid, buf, &lower_limit, &upper_limit, used_number);
	    sleep(1);

	    //check response
	    bzero(buf->info.mssg, 20);
	    receive_message(msgqid, buf, 1);
	    printf("Receive %s\n", buf->info.mssg);
		int reason = strcmp(buf->info.mssg, "winner");
		int reason2 = strcmp(buf->info.mssg, "loser");
		if(reason == 0 || reason2 == 0){
			game_ended = 1;
		}
	}
	free(buf);
}
int get_random_number(int lower_limit, int upper_limit){
	int rand_num = rand() % upper_limit + lower_limit;
}
int set_buf_message(int msgqid, mbuf_t *rbuf, int *lower_limit, int *upper_limit, int used_number){
	mbuf_t buf;
	int rand_num= GAME_LIMIT;
	switch (rbuf->info.mssg[0]){
		case 'h':
			rand_num = get_random_number(used_number, *upper_limit);
			*lower_limit = used_number;
		break;
		case 'l':
			rand_num = get_random_number(*lower_limit, used_number);
			*upper_limit = used_number;
		break;
		default:
			rand_num = get_random_number(*lower_limit, *upper_limit);
	}
	
	bzero((buf).info.mssg, 20);
	sprintf((buf).info.mssg, "%d", rand_num);
	send_message(msgqid, &buf, 2);
	printf("Rand num is: %d\n", rand_num);
	return rand_num;
}