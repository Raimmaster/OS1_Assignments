/*
** spock.c -- reads from a message queue
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
	//struct my_msgbuf buf;

	struct pirate_msgbuf buf; //= {2, { "L'Olonais", 'S', 80, 10, 12035 } };

	//msgsnd(msqid, &pmb, sizeof(struct pirate_info), 0);
	int msqid;
	key_t key;

	if ((key = ftok("kirk.c", 'B')) == -1) {  /* same key as kirk.c */
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
		perror("msgget");
		exit(1);
	}

	printf("spock: ready to receive messages, captain.\n");

	for(;;) { /* Spock never quits! */
		if (msgrcv(msqid, &buf, sizeof(struct pirate_info), 0, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}
		printf("spock: \"%s\"\n", buf.info.name);
	}

	return 0;
}
