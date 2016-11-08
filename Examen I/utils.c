#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGSZ	24

typedef struct msgqbuf
{
  long mtype;
  struct msg_info{
  	int player_pid;
  	char mssg[20];
  } info;
} mbuf_t;

void send_message(int msgqid, mbuf_t* sbuf, long mytype){
 	size_t length = strlen(sbuf->info.mssg)+5;
 	sbuf->mtype = mytype; 
	if (msgsnd(msgqid, sbuf, length, IPC_NOWAIT) == -1){
		perror("msgsnd");
		exit(1);
	}
	printf("Sent message: %s\n", (*sbuf).info.mssg);
}

void receive_message(int msgqid, mbuf_t* buf, long mytype){
	if(msgrcv(msgqid, buf, MSGSZ, mytype, 0) == -1){
		perror("msgrcv");
		exit(1);
	}
}

int create_msgq(int key){
	int msgqid = msgget(key, 0644 | IPC_CREAT);

	if(msgqid == -1) {
		perror("msgget");
		exit(1);
	}
	printf("Created mq: %d with key: %d\n", msgqid, key);
	return msgqid;
}

int connect_msgq(int key){
	int msgqid;
	if ((msgqid = msgget(key, 0644)) == -1) {
		perror("msgget");
		exit(1);
	}
	printf("Connecting to mq: %d with key: %d\n", msgqid, key);
	return msgqid;
}

void delete_msgq(int msgqid){
	if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	printf("msgq deleted %d\n", msgqid);
}