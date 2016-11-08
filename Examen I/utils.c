#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgqbuf
{
  long mtype;
  struct msg_info{
  	pid_t player_pid;
  	char mssg[20];
  } info;
} mbuf_t;

void send_message(char* message, int msgq_id){
	mbuf_t msg_buf;
	msg_buf.mtype = 2;
	bzero(msg_buf.info.mssg, 20);
	
	strcpy(msg_buf.info.mssg, message);
	int len = strlen(msg_buf.info.mssg);

	if (msgsnd(msgq_id, &msg_buf, len+1, 0) == -1)
		perror("msgsnd");
}

int create_msgq(int key){
	int msgqid = msgget(key, 0644 | IPC_CREAT);

	if(msgqid == -1) {
		perror("msgget");
		exit(1);
	}

	return msgqid;
}

int connect_msgq(int key){
	int msgqid;
	if ((msgqid = msgget(key, 0644)) == -1) {
		perror("msgget");
		exit(1);
	}

	return msgqid;
}

void delete_msgq(int msgqid){
	//return;
	if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	printf("msgq deleted %d\n", msgqid);
}