# include<stdio.h>
# include"traversal.h"

void postOrder(struct vertice *target){
  if (target -> visited){
    return;
  }
  target -> visited = 1;
  struct edge *tmpEdge = target -> edges;
  while(tmpEdge != NULL){
    postOrder(tmpEdge -> vertices);
    tmpEdge = tmpEdge -> next;
  }
  printf("%s\n", target -> name);
  if (target -> commands != NULL){
    struct command *tmpCmd = target -> commands;
    while(tmpCmd != NULL){
      printf("  %s\n", tmpCmd -> name);
      tmpCmd = tmpCmd -> next;
    }
  }
}
