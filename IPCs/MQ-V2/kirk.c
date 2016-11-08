/*
** kirk.c -- writes to a message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
	long mtype;
	char mtext[200];
};

struct pirate_msgbuf {
    long mtype;  /* must be positive */
    struct pirate_info {
        char name[30];
        char ship_type;
        int notoriety;
        int cruelty;
        int booty_value;
    } info;
};

int main(void)
{
	// struct my_msgbuf buf;

	struct pirate_msgbuf buf = {2, { "L'Olonais", 'S', 80, 10, 12035 } };

	int msqid;
	key_t key;

	if ((key = ftok("kirk.c", 'B')) == -1) {
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}

	printf("Enter lines of text, ^D to quit:\n");

	buf.mtype = 1; /* we don't really care in this case */
	char test[20];
	while(fgets(test, sizeof(test), stdin) != NULL) {
		/* ditch newline at end, if it exists */
		//if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

		if (msgsnd(msqid, &buf, sizeof(struct pirate_info), 0) == -1) /* +1 for '\0' */
			perror("msgsnd");
	}

	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}

	return 0;
}
