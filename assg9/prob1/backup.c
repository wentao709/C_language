/*
* File : mymake.c
* Author: Wentao Zhou
* Purpose: reading in a file specifying dependencies and rules as in
* make, constructing a dependency tree and  traversing the tree starting 
* with some specified target
*/

# include <ctype.h>
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include"traversal.h"

// the head of the linked list
struct vertice *list_hd;

/*
* compareString()
* comapre the two strings
* parameter: 
* num1 and num2: the string to be compared
*/
int compareString(char *num1, char *num2){
  int length1 = 0;
  int length2 = 0;
  for(length1 = 0; num1[length1] != '\0'; length1++){}
  for(length2 = 0; num2[length2] != '\0'; length2++){}
  if (length1 == length2){
    int i;
    for (i = 0; num1[i]!='\0' ;i++){
      if (num1[i] != num2[i]){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

/*
* checkColon()
* check if the string contains ":"
* parameter: 
* line: the string to be checked
*/
int checkColon(char *line){
  char *ptr = NULL;
  for (ptr = line; *ptr != '\0';ptr++){
    if (*ptr==':'){
      return 1;
    }
  }
  return 0;
}

/*
* addEdges()
* add source file to the target file
* parameter:
* target: the target file to be connected
* source: the source file to be connected
*/
void addEdges(struct vertice *target, struct vertice *source){
  struct edge *tmpNode = malloc(sizeof(struct edge));
  if (tmpNode == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpNode -> vertices = source;
  tmpNode -> next = NULL;
  if (target -> edges == NULL){
    target -> edges = tmpNode;
  }else{
    struct edge *move = target -> edges;
    while(move -> next != NULL){
      move = move -> next;
    }
    move -> next = tmpNode;
  }
}

/*
* getTarget()
* get the target file as a vertice node
* parameter: 
* string: the name of the target file
*/
struct vertice *getTarget(char *string){
  struct vertice *tmpNode = NULL;
  tmpNode = list_hd;
  while(tmpNode != NULL){
    if (compareString(tmpNode -> name, string)){
      return tmpNode;
    }
    tmpNode = tmpNode -> down;
  }
  return NULL;
}

/*
* addTarget()
* add the target to the linked list
* parameter:
* str: the name ofthe target file
*/
void addTarget(char *str){
  struct vertice *tmpVer = malloc(sizeof(struct vertice));
  if (tmpVer == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpVer -> name = strdup(str);
  if (tmpVer == NULL){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  tmpVer -> visited = 0;
  tmpVer -> isTarget = 1;
  tmpVer -> commands = NULL;
  tmpVer -> edges = NULL;
  tmpVer -> down = list_hd;
  list_hd = tmpVer;
}

/*
* getNode()
* get the node which has the parameter "name"
* parameter:
* name: the string to be searched
*/
struct vertice *getNode(char *name){
  struct vertice *tmpNode;
  tmpNode = list_hd;
  while(tmpNode != NULL){
    if (compareString(tmpNode ->name,name)){
      return tmpNode;
    }
    tmpNode = tmpNode -> down;
  }
  return NULL;
}

/*
* addSources()
* add the source file to the linkedlist as node
* parameter:
* str: the name of the source file
*/
void addSources(char *str){
  if (checkColon(str))
    str[strlen(str) - 1] = '\0';
  struct vertice *tmpVer = malloc(sizeof(struct vertice));
  if (tmpVer == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpVer -> name = strdup(str);
  if (tmpVer -> name == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpVer -> visited = 0;
  tmpVer -> isTarget = 0; // the only differnece
  tmpVer -> commands = NULL;
  tmpVer -> edges = NULL;
  tmpVer -> down = list_hd;
  list_hd = tmpVer;
}

/*
* existed(char *str)
* check if the node with the name str existed already
* parameter:
* str: the name of the node to be checked
*/
struct vertice *existed(char *str){
  struct vertice *tmpNode = list_hd;
  while(tmpNode != NULL){
    if (compareString(tmpNode -> name, str)){
      return tmpNode;
    }
    tmpNode = tmpNode -> down;
  }
  return NULL;
}

/*
* addCommand()
* add the command to the target file
* parameter: 
* target: the target file to be added the command
* command: the command to be added
*/
void addCommand(struct vertice *target, char *command){
  if (command[strlen(command)-1] =='\n'){
    command[strlen(command)-1] = '\0';
  }
  if (strlen(command)>0){
  struct command *tmpCmd = malloc(sizeof(struct command));
  if (tmpCmd == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpCmd -> name = strdup(command);
  if (tmpCmd -> name == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpCmd -> next = NULL;
  if (target -> commands == NULL){
    target -> commands = tmpCmd;
  }else{
    struct command *move = target -> commands;
    while(move -> next != NULL){
      move = move -> next;
    }
    move -> next = tmpCmd;
  }}
}

/*
* freeList()
* free up all the memory in the linked list, including the target, source and command
*/
void freeList(){
  struct vertice *tmpVer, *tVer;
  struct edge *tmpEdge, *tEdge;
  struct command *tmpCmd, *tCmd;
  tmpVer = list_hd;
  while(tmpVer != NULL){
    tmpEdge = tmpVer -> edges;
    tmpCmd = tmpVer -> commands;
    while(tmpEdge != NULL){
      tEdge = tmpEdge;
      tmpEdge = tmpEdge -> next;
      free(tEdge);
    }
    while(tmpCmd != NULL){
      tCmd = tmpCmd;
      tmpCmd = tmpCmd -> next;
      free(tCmd -> name);
      free(tCmd);
    }
    tVer = tmpVer;
    tmpVer = tmpVer -> down;
    free(tVer -> name);
    free(tVer);
  }
}

/*
* removeSpace()
* parsing the string, remove white space at the head of the string
* parameter: 
* line: the string to be parsed
*/
char *removeSpace(char *line){
  while(isspace(*line)){
    line++;
  }
  return line;
}

/*
* main()
* read in the input, create the linkedlist and print out the output.
* parameter: 
* argc: the number of argument
* argv[]: the list of argument
*/
int main(int argc, char *argv[]){
  if (argc != 3){
    fprintf(stderr, "no input file or no target or too many argument\n");
    exit(1);
  }
  FILE *inFile = fopen(argv[1],"r");
  if (inFile == NULL){
    perror(argv[1]);
    exit(1);
  }
  char *line = NULL;
  size_t len = 0;
  struct vertice *targetNode = NULL;
  while(getline(&line, &len, inFile) != EOF){
    char *linePtr = line;
    int offset = 0;
    char string[65];
    int colonFlag = 1;// check if the colon showed up already, check it to 0 after it shows up
    int firstSrc = 1;// check if the source file is the first source file
    if (line[0]!='\t'){ // the target specification
      linePtr = removeSpace(linePtr);
      if (strlen(linePtr)>0){
      sscanf(linePtr, "%64s %n", string, &offset);
      linePtr += offset;
      if (checkColon(string)){
        colonFlag = 0;
        string[strlen(string) - 1] = '\0';
      }
      struct vertice *tmpNode = existed(string);
      if (tmpNode != NULL){
        if (tmpNode -> isTarget){
	  free(line);
	  freeList();
	  fclose(inFile);
          fprintf(stderr, "target existed already\n");
          exit(1);
        }else{
          tmpNode -> isTarget = 1;
        }
      }else{
        addTarget(string);
      }
      targetNode = getNode(string);
      while (sscanf(linePtr, "%64s %n", string, &offset)!=EOF) { // the sources
	if (colonFlag && string[0]!=':'){
	  free(line);
	  freeList();
	  fclose(inFile);
	  fprintf(stderr, "invalid target\n");
	  exit(1);
	}
        if (checkColon(string) && strlen(string) == 1 && colonFlag){ // the colon
          colonFlag = 0;
          sscanf(linePtr, "%64s %n", string, &offset);
          linePtr += offset;
        }else{
          char *parseString = string;
          if (checkColon(string) && !colonFlag){
	    freeList();
	    free(line);
	    fclose(inFile);
            fprintf(stderr, "illegal line\n");
	    exit(1);
          }
	  if(checkColon(string) && colonFlag && firstSrc){
	    parseString ++;
	    colonFlag = 0;
	    firstSrc = 0;
	  }// the first source file has the colon and the colon has not shown up yet
          struct vertice *tmpNode = existed(parseString);
          if (tmpNode != NULL){
            struct vertice *SourceNode = getNode(parseString); // source
            addEdges(targetNode, SourceNode);
          }else{
            // add to target
            addSources(parseString);
            struct vertice *SourceNode = getNode(parseString); // source
            addEdges(targetNode, SourceNode);
          }
          linePtr += offset;
        }
      }}
    }else{ // the command
	if (targetNode == NULL){
	  fprintf(stderr, "error in file, command with no target\n");
	  free(line);
          freeList();
          fclose(inFile);
	  exit(1);
	} // the case that the command without target
	char * parseLine = removeSpace(linePtr);
        addCommand(targetNode, parseLine);
    }
  }
  free(line);
  fclose(inFile);
  targetNode = getNode(argv[2]);
  if (targetNode == NULL || !targetNode->isTarget){
    freeList();
    fprintf(stderr, "target is not existed\n");
    exit(1);
  }
  postOrder(targetNode);
  freeList();
  exit(0);
}

