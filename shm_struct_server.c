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
{   int option;
    int shmID;
    int i;
    struct nota *evernota;
    shmID = shmget(1000, sizeof(struct nota)*20 , 0666 | IPC_CREAT);
    printf("shmID = %d\n", shmID);
    if(shmID < 0){
        printf("Failed to create shm\n");
        exit(1);
    }
    printf("plz select one option: \n 1- calculate the two number from client \n 2- print all data in the shm");
scanf("%d",&option);
if(option ==1){//calculate two value 
    evernota =  shmat(shmID, NULL, 0);
    evernota[0].sum=evernota[0].firstNumber+evernota[0].secondNumber;
    printf("sumation is value:  %d\n",evernota[0].sum);
    evernota[0].ready=1;
    evernota[0].avalabil=1;///finish the
}
  else{
    evernota =  shmat(shmID, NULL, 0);
	for(i=0;i<20;i++){////print all shm contant 
 	printf("contant of shm by index %d,first number %d, second number %d, sumation %d\n",i, evernota[i].firstNumber,evernota[i].secondNumber,evernota[i].sum);
}
    //evernota =  (struct nota *)shmat(shmID, NULL, 0);   
    // evernota[1].firstNumber=100; 
    //printf("Sent value:  %d\n", evernota[1].sum);
    
}
 shmdt(evernota);
return 0 ;
}
