#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
 
 
struct nota{
    int firstNumber;
    int secondNumber;
    int sum;
    int avalabil;//one means free cells 
    int ready;////sumation is done 

};

int main()
{ int firstNumber;
  int secondNumber;
    int shmID;
    struct nota *evernota;
printf("plzenter two value \n");
printf("first number is :\n");
scanf("%d",&firstNumber);
printf("second number is :\n");
scanf("%d",&secondNumber);
    shmID = shmget(1000, sizeof(struct nota)*20 , 0666 | IPC_CREAT);
    printf("shmID = %d\n", shmID);
    if(shmID < 0){
        printf("Failed to create shm\n");
        exit(1);
    }
    evernota =  (struct nota *)shmat(shmID, NULL, 0);  
    evernota[0].firstNumber=firstNumber; 
    evernota[0].secondNumber=secondNumber;
    printf("Sent values from client first value  %d second value:  %d\n",     evernota[0].firstNumber,evernota[0].secondNumber);
    evernota =  shmat(shmID, NULL, 0);
    printf("Recevied sumation value from server:  %d\n", evernota[0].sum);
 shmdt(evernota);
  return 0;
}
