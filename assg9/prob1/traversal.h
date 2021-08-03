#ifndef _traversal_H
#define _traversal_H

struct vertice{
  char *name;
  int visited;
  int isTarget;
  struct command *commands;
  struct edge *edges;
  struct vertice *down;
};

struct command{
  char *name;
  struct command *next;
};

struct edge{
  struct vertice *vertices;
  struct edge *next;
};

extern struct vertice *list_hd;

void addTarget(char *str);
struct vertice *getTarget(char *string);
struct vertice *getNode(char *name);
struct vertice *getTarget(char *string);
void freeList();
struct vertice *existed(char *str);
void addSources(char *str);

void postOrder(struct vertice *target);


#endif
