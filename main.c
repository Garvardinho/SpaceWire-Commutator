#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct msgbuf
{
    long mtype;
    char mtext[80];
} message;

int main(int argc, char *argv[])
{
    int adress, length, length1, length2;
    int m_msqid, m_msqid31, m_msqid32, m_msqid33, m_msqid35;
    int msgflg = IPC_CREAT | 0666;
    message mess;
    message mess1, mess2;
    long error;

    adress = atoi(argv[1]);

    switch (adress) {
    case 31:

        if ((m_msqid = msgget(31, 0)) < 0) {
            printf("Can't create queue!\n");
        }

        length = sprintf(mess.mtext, "Test! long Message 1\n");

        if (length < 0) {
            printf("Can't write message\n");
        }

        mess.mtype = length;

        if (msgsnd(m_msqid, &mess, (unsigned long long) length, 0) < 0) {
            printf("Can't send\n");
        }

        break;
    case 32:
        if ((m_msqid = msgget(32, 0)) < 0) {
            printf("Can't create queue!\n");
        }
        length = sprintf(mess.mtext, "Test! long Message 2\n");
        if (length < 0) {
            printf("Can't write message");
        }

        mess.mtype = length;

        if (msgsnd(m_msqid, &mess, (unsigned long long) length, 0) < 0) {
            printf("Can't send\n");
        }

        break;
    case 33:

        if ((m_msqid = msgget(33, msgflg)) < 0) {
            printf("Can't create queue!\n");
        }

        printf("%i\n", m_msqid);
        error = msgrcv(m_msqid, &mess, sizeof(mess), 0, 0);
        printf("message: ");
        puts(mess.mtext);
        printf("\n");

        break;

    case 35:

        if ((m_msqid = msgget(35, msgflg)) < 0) {
            printf("Can't create queue!\n");
        }
        printf("%i\n", m_msqid);

        error = msgrcv(m_msqid, &mess, sizeof(mess), 0, 0);
        printf("message: ");
        puts(mess.mtext);
        printf("\n");

        break;
    case 100: //switch
        //receiver
        if ((m_msqid31 = msgget(31, msgflg)) < 0) {
            printf("Can't create queue!\n");
        }

        error = msgrcv(m_msqid31, &mess, sizeof(mess), 0, 0);
        if (error < 0) {
            printf("Error1\n");
        }

        length1 = sprintf(mess1.mtext, mess.mtext);
        mess1.mtype = length1;

        if (length1 < 0) {
            printf("Can't write message from 31");
        }

        printf("message: ");
        puts(mess.mtext);
        printf("\n");

        //receiver
        if ((m_msqid32 = msgget(32, msgflg)) < 0) {
            printf("Can't create queue!\n");
        }

        error = msgrcv(m_msqid32, &mess, sizeof(mess), 0, 0);
        if (error < 0) {
            printf("Error2\n");
        }

        length2 = sprintf(mess2.mtext, mess.mtext);
        mess2.mtype = length2;

        if (length2 < 0) {
            printf("Can't write message from 32");
        }

        printf("message: ");
        puts(mess.mtext);
        printf("\n");

        //sender
        if ((m_msqid33 = msgget(33, 0)) < 0) {
            printf("Can't create queue!\n");
        }
        printf("%i\n", m_msqid33);

        if (msgsnd(m_msqid33, &mess1, (unsigned long long) length1, 0) < 0) {
            printf("Can't send to 33\n");
        }

        //sender
        if ((m_msqid35 = msgget(35, 0)) < 0) {
            printf("Can't create queue!\n");
        }

        printf("%i\n", m_msqid35);
        int status;
        if ((status = msgsnd(m_msqid35, &mess2, (unsigned long long) length2, 0)) < 0) {
            printf("Can't send to 35\n");
            printf("status[%i], errno[%i]", status, errno);
        }

        break;
    default:
        break;
    }

    return 0;
}
