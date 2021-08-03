# include<stdio.h>
# include<stdlib.h>
#include <time.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
  struct stat stbuf;
  long date = stbuf.st_mtime;
  stat("f1", &stbuf);
  printf("modification time: %s\n", ctime(&date));
  return 0;
}

/*void POT(struct vertice *target){
  if (target -> visited){
    return;
  }
  target -> visited = 1;
  struct stat stbuf;
  stat(target -> name, &stbuf);
  printf("modification time: %f\n", difftime(stbuf.st_mtime, stbuf.st_mtime));
  struct command *tmpCmd = target -> commands;
    while(tmpCmd != NULL){
      printf("%s\n", tmpCmd -> name);
      system(tmpCmd -> name);
      tmpCmd = tmpCmd -> next;
    }

}
