#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main()
{
  key_t key;
  int shmid;
  char * data;

  // set up shared memory
  key = ftok("mykey", 'f');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, 0);

  if (* data)
  {
    printf("Here's what's currently in the segment: %s\n", data);
  }
  else
  {
    printf("Empty shared memory segment with 200 bytes.\n");
  }

  char buffer[200];
  buffer[0] = '\0';

  while (strcmp(buffer, "y\n") != 0 && strcmp(buffer, "n\n") != 0)
  {
    printf("\n");
    printf("Would you like to write somthing into the segment?: ( y or n ) ");
    fflush(stdout);

    fgets(buffer, 200, stdin);
  }

  if (!strcmp(buffer, "y\n"))
  {
    printf("\n");
    printf("What would you like to write?\n");

    fgets(buffer, 200, stdin);
    strcpy(data, buffer);
  }

  buffer[0] = '\0';

  while (strcmp(buffer, "y\n") != 0 && strcmp(buffer, "n\n") != 0)
  {
    printf("\n");
    printf("Would you like to delete the segment?: ( y or n ) ");
    fflush(stdout);

    fgets(buffer, 200, stdin);
  }

  if (!strcmp(buffer, "y\n"))
  {
    printf("\n");
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("The segment has been deleted.\n");
  }
  else
  {
    printf("\nAlright. The segment still exists.\n");
  }

}
