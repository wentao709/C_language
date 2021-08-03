/*
* File: tarversal.c
* author : wentao zhou
* do the POT algorithm
*/

# include<stdio.h>
# include<stdlib.h>
# include"traversal.h"
# include <time.h>
# include<stdio.h>
# include<fcntl.h>
# include<sys/stat.h>
# include<sys/types.h>
# include<unistd.h>

int cmdExe = 0; // a flag to see if the cmd executed

/*
* POT()
* basically copy the algorithm from the spec, run the cmd if the
* target doesn't existed or the target existed and it's dependency file is more updated
*/
void POT(struct vertice *target){
  if (target -> visited){
    return;
  }
  target -> visited = 1;
  struct stat stbuf;
  stat(target -> name, &stbuf);
  target -> fileDate = stbuf.st_mtime;
  target -> doesExisted = stat(target -> name, &stbuf);
  if(target -> doesExisted!=0){
    if (!target -> isTarget){
      freeList();
      fprintf(stderr ,"No rule to make target\n");
      exit(1);
    }else{
      target -> mustBuild = 1;
    }
  }
  struct edge *tmpEdge = target -> edges;
  while(tmpEdge != NULL){
    struct vertice *tmpNode = tmpEdge -> vertices;
    POT(tmpNode);
    if(!tmpNode -> completed){
      fprintf(stderr, "cycle found\n");
    }else if(!target -> mustBuild){
      stat(tmpNode -> name, &stbuf);
      tmpNode -> fileDate = stbuf.st_mtime;
      if(tmpNode -> doesExisted!=0 || difftime(tmpNode -> fileDate,target -> fileDate)>0){
        target -> mustBuild = 1;
      } // check if the target existed or it's dependency is more updated than it
    }
    tmpEdge = tmpEdge -> next;
  }
  if (target -> mustBuild){
    struct command *tmpCmd = target -> commands;
    while(tmpCmd != NULL){
      printf("%s\n", tmpCmd -> name);
      int sys =  system(tmpCmd -> name);
      if (sys != 0){
	freeList();
	fprintf(stderr, "Command failed\n");
	exit(1);
      }
      cmdExe = 1;
      tmpCmd = tmpCmd -> next;
    }
    stat(target -> name, &stbuf);
    target -> fileDate = stbuf.st_mtime;
    target -> doesExisted = 0;
  }
  target -> completed = 1;
}

/*
* uptodate()
* print target is up to date if no cmd executed
*/
void uptodate(char *name){
  if(!cmdExe){
    printf("%s is up to date.\n", name);
  }
}
