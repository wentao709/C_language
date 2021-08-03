/* File: linked.c
* author: wentao zhou
* purpose: use a graph to create a model of linked web pages, and
* answer queries about whether one page is connected to another
* through a chain of links
*/

# include<stdio.h>
# include<stdlib.h>
# include<string.h>


// the page node
struct page{
  char *name;
  int visited;
  struct page *down; // next node
  struct link *links;
};

// the link node
struct link{
  struct page *pages;
  struct link *next;
};

/* getCommend
* return 1 if the conmand is @addPages
* return 2 if the command is @addLinks
* return 3 if the command is @isConnected
* otherwise reutrn 0
*/
int getCommand(char *command){
  int length;
  for (length = 0; command[length]!='\0' ;length++){}
  if (length == 9){
    if (command[0] == '@' && command[1] == 'a' && command[2] == 'd' && command[3] == 'd' &&
        command[4] == 'P' && command[5] == 'a' && command[6] == 'g' && command[7] == 'e' &&
        command[8] == 's'){
          return 1;
    }else if(command[0] == '@' && command[1] == 'a' && command[2] == 'd' && command[3] == 'd' &&
        command[4] == 'L' && command[5] == 'i' && command[6] == 'n' && command[7] == 'k' &&
        command[8] == 's'){
          return 2;
    }
  }else if(length == 12){
    if (command[0] == '@' && command[1] == 'i' && command[2] == 's' && command[3] == 'C' &&
        command[4] == 'o' && command[5] == 'n' && command[6] == 'n' && command[7] == 'e' &&
        command[8] == 'c' && command[9] == 't' && command[10] == 'e' && command[11] == 'd'){
        return 3;
    }
  }
  return 0;
}

struct page *list_hd; // set the head of the linkedlist

/*
* addPages()
* when get @addPages command, add the page to the page linkedlist
*/
void addPages(char *pageName){
  struct page *tmpPage;
  tmpPage = malloc(sizeof(struct page));
  if (tmpPage == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  char * temStr = strdup(pageName);
  if (temStr == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpPage -> name = temStr;
  tmpPage -> visited = 0;
  tmpPage -> links = NULL;
  tmpPage -> down = list_hd;
  list_hd = tmpPage;
}

/*
* compareString()
* comapre the two strings
* parameter: source: the name of source page
* name: the name of the target page
*/
int compareString(char *source, char *name){
  int length1 = 0;
  int length2 = 0;
  for(length1 = 0; source[length1] != '\0'; length1++){}
  for(length2 = 0; name[length2] != '\0'; length2++){}
  if (length1 == length2){
    int i;
    for (i = 0; source[i]!='\0' ;i++){
      if (source[i] != name[i]){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

/*
* connectedPages()
* when the @addLinks command, add the link to the linkedlist for each page
* parameter:
* source: the source page node
* tmpTo: the to page node
*/
void connectPages(struct page *source, struct page *tmpTo){
  struct link *tmpLinks;
  tmpLinks = malloc(sizeof(struct link));
  if (tmpLinks == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  tmpLinks -> pages = tmpTo;
  tmpLinks -> next = NULL;
  if(source -> links  == NULL){
    source -> links = tmpLinks;
  }else{
    struct link *moveLink;
    moveLink = source -> links;
    while(moveLink -> next != NULL){
      moveLink  = moveLink  -> next;
    } // add to the end of the string
    moveLink -> next  = tmpLinks;
  }
}

/*
* getFromPage()
* get the from page, use it when I do isConnected command
*/
struct page *getFromPage(char *page1){
  struct page *tmpPage = NULL;
  struct page *fromPage=NULL;
  tmpPage = list_hd;
  while(tmpPage != NULL){
    if (compareString(tmpPage -> name, page1)){
      fromPage = tmpPage;
      break;
    }
    tmpPage = tmpPage -> down;
  }
  return fromPage;
}

/*
* getToPage()
* get the to page, , use it when I do isConnected command
*/
struct page *getToPage(char *page2){
  struct page *tmpPage = NULL;
  struct page *toPage = NULL;
  tmpPage = list_hd;
  while(tmpPage != NULL){
    if (compareString(tmpPage -> name, page2)){
      toPage = tmpPage;
      break;
    }
    tmpPage = tmpPage -> down;
  }
  return toPage;
}

/*
* setVisit()
* reset all the node statue to 0.
*/
void setVisit(){
  struct page *tmpPage;
  tmpPage = list_hd;
  while(tmpPage != NULL){
    tmpPage -> visited = 0;
    tmpPage = tmpPage -> down;
  }
  free(tmpPage);
}

/*
* dfs()
* basically follow the structure on the spec
* start from the frompage, and search for the toPage
* parameter:
* fromPage: stare from this page
* toPage: looking for this page
*/
int dfs(struct page *fromPage, struct page *toPage){
  if (compareString(fromPage -> name, toPage -> name)){
    return 1;
  }
  if (fromPage -> visited){
    return 0;
  }
  fromPage -> visited = 1;
  struct link *nextLink;
  nextLink = fromPage -> links;
  while(nextLink != NULL){
    if (dfs(nextLink -> pages, toPage)){
      return 1;
    }
    nextLink = nextLink -> next;
  }
  return 0;
}

/*
* freeList()
* free up the memory in the linked list
* including the page linkedlist and link linkedlist
*/
void freeList(){
  struct link *tmpLink, *tLinks;
  struct page *tmpPages, *tPages;
  tmpPages = list_hd;
  while(tmpPages != NULL){
    tmpLink = tmpPages -> links;
    while(tmpLink != NULL){
      tLinks = tmpLink;
      tmpLink = tmpLink -> next;
      free(tLinks);
    }
    tPages = tmpPages;
    tmpPages = tmpPages -> down;
    free(tPages->name);
    free(tPages);
  }
}

/*
* mulPage
* when I do @addPages command, check if the node is existed already
*/
int mulPage(char *names){
  struct page *tmpNode = list_hd;
  while(tmpNode != NULL){
    if (compareString(tmpNode -> name, names)){
      return 1;
    }
    tmpNode = tmpNode -> down;
  }
  free(tmpNode);
  return 0;
}

/*
* main()
* use a graph to create a model of linked web pages, and
* answer queries about whether one page is connected to another
* through a chain of links.
* check multiple error conditions
* parameter:
* argc: the number of argument
* argv[]: list of argument
*/
int main(int argc, char *argv[]){
  int errorFlag = 0; // decide the exit statue
  FILE *inFile = NULL;
  if (argc == 1){
    inFile = stdin;
  }else if (argc == 2){
    inFile = fopen(argv[1],"r");
    if (inFile == NULL){
      fprintf(stderr, "not such file\n");
      exit(1);
    }
  }else if (argc > 2){
    inFile = fopen(argv[1],"r");
    if (inFile == NULL){
      fprintf(stderr, "not such file\n");
      exit(1);
    }
    fprintf(stderr, "too much file\n");
    errorFlag = 1;
  }
  char *line = NULL;
  size_t len = 0;
  while(getline(&line, &len, inFile) != EOF){ // read input per one line
    char *linePtr = line;
    int offset;
    char string[65];
    if (sscanf(linePtr, "%64s %n", string, &offset) == 1){
      linePtr += offset;
      if (getCommand(string) == 1){ // addpage command
        while (sscanf(linePtr, "%64s %n", string, &offset) == 1){
          if(!mulPage(string)){ // print error message if add same page more than once
	    addPages(string);
	  }else{
	    fprintf(stderr ,"multiple pages\n");
	    errorFlag = 1;
	  }
	  linePtr += offset;
        }
      }else if(getCommand(string) == 2){ // add link command
        struct page *sourcePage = NULL;
        struct page *toPage = NULL;
	if (sscanf(linePtr, "%64s %n", string, &offset)  == 1){
          char *tepStr = strdup(string);
	  if (tepStr == NULL){
	    fprintf(stderr, "out of memory\n");
	    exit(1);
	  }
	  sourcePage = getFromPage(tepStr);
	  if (sourcePage == NULL){ // no source page is given
	    fprintf(stderr , "no such source page\n");
	    errorFlag = 1;
	  }
	  free(tepStr);
          linePtr+=offset;
        }else{ // the command followed by nothing
          fprintf(stderr, "no source page is given\n");
	  errorFlag = 1;
        }
	if (sourcePage != NULL){// source page is given, then check the target page
	  while (sscanf(linePtr, "%64s %n", string, &offset) == 1){
	    char *tepStr = strdup(string);
	    if (tepStr == NULL){
	    	fprintf(stderr, "out of memory\n");
	    	exit(1);
	    }
            toPage = getToPage(tepStr);
	    if (sourcePage == NULL || toPage == NULL){
	      fprintf(stderr,"no such link page\n");
	      errorFlag = 1;// the page to be linked is not added to the linkedlist
	    }else{
	      connectPages(sourcePage, toPage);
	    }
	    free(tepStr);
            linePtr += offset;
          }
	}
      }else if(getCommand(string) == 3){ // is connected command
	int printFlag = 0;
	int flag = 0;
        struct page *page1 = NULL, *page2 = NULL;
	int status = sscanf(linePtr, "%64s %n", string, &offset);
        if (status == 1){
          char *tepStr = strdup(string);
	  if (tepStr == NULL){
	    fprintf(stderr, "out of memory\n");
	    exit(1);
	  }
	  page1 = getFromPage(tepStr); // get the from page
	  if (page1 == NULL){ // no source page is give
	    fprintf(stderr, "page doesn't exist\n");
	    errorFlag = 1;
	  }
	  free(tepStr);
          linePtr += offset;
        }else{ // the from page is not given
	  fprintf(stderr, "no from page given\n");
	  errorFlag = 1;
	}
	if (status == 1 && page1!=NULL){
          if (sscanf(linePtr, "%64s %n", string, &offset) == 1){
            char *tepStr = strdup(string);
	    if (tepStr == NULL){
	    	fprintf(stderr, "out of memory\n");
	        exit(1);
	    }
	    page2 = getToPage(tepStr);
	    if (page2 == NULL){ // no target page is given
	      fprintf(stderr, "page doesn't exist\n");
	      errorFlag = 1;
	      flag = 1;
	    }
	    free(tepStr);
	    linePtr += offset;
          }else{ // the target page is not given
	    fprintf(stderr, "No target page given\n");
	    errorFlag = 1;
	  }
	}
	if (status == 1 && !flag && page1!=NULL && sscanf(linePtr, "%64s %n", string, &offset) == 1){
	  fprintf(stderr,"too many argument\n");
	  errorFlag = 1;
	  printFlag = 1;
	}
        setVisit();// reset all the visited statue to 0.
	if (page1!=NULL && page2 != NULL && !printFlag){
          printf("%d\n", dfs(page1, page2));
	}
      }else{
	fprintf(stderr, "wrong command\n");
	errorFlag = 1;
      }
    }
  }
  free(line);
  freeList();
  if(argc >= 2){
    fclose(inFile);
  }
  if (errorFlag){exit(1);}
  exit(0);
}
