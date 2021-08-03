/*:
* file: calls.c
* author: wentao zhou
*
*/

# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<ctype.h>

struct phone{
  char *number;
  int visited;
  struct phone *down;
  struct call *calls;
  int level;
};

struct call{
  struct phone *phones;
  struct call *calls;
  int times;
};

//item in the queue
struct item{
  struct phone *items;
  struct item *next;
};

int errorFlag = 0;
struct item *queue;
struct phone *list_hd;

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

int mulNumber(char *number){
  struct phone *tmpNode = list_hd;
  while(tmpNode != NULL){
    if (compareString(tmpNode -> number, number)){
      return 1;
    }
    tmpNode = tmpNode -> down;
  }
  free(tmpNode);
  return 0;
}

struct phone *getFirstNumber(char *num1){
  struct phone *tmpNum = NULL;
  struct phone *firstNum=NULL;
  tmpNum = list_hd;
  while(tmpNum != NULL){
    if (compareString(tmpNum ->number, num1)){
      firstNum = tmpNum;
      break;
    }
    tmpNum = tmpNum -> down;
  }
  return firstNum;
}

struct phone *getSecNumber(char *num2){
  struct phone *tmpNum = NULL;
  struct phone *SecNum=NULL;
  tmpNum = list_hd;
  while(tmpNum != NULL){
    if (compareString(tmpNum -> number, num2)){
      SecNum = tmpNum;
      break;
    }
    tmpNum = tmpNum -> down;
  }
  return SecNum;
}

void addPhones(char *number){
  struct phone *tmpPhone;
  tmpPhone = malloc(sizeof(struct phone));
  if (tmpPhone == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  char * temStr = strdup(number);
  tmpPhone -> number = temStr;
  tmpPhone -> visited = 0;
  tmpPhone -> calls = NULL;
  tmpPhone -> down = list_hd;
  list_hd = tmpPhone;
}

int called(struct phone *phone1, struct phone *phone2){
  struct call *tmpCall;
  tmpCall = phone1 -> calls;
  while(tmpCall != NULL){
    if (tmpCall -> phones == phone2){
      return 1;
    }
    tmpCall = tmpCall -> calls;
  }
  return 0;
}

struct call *getCall(struct phone *phone1, struct phone *phone2){
  struct call *tmpCall;
  tmpCall = phone1 -> calls;
  while(tmpCall != NULL){
    if (tmpCall -> phones == phone2){
      return tmpCall;
    }
    tmpCall = tmpCall -> calls;
  }
  return NULL;
}

void addCalls(struct phone *phone1, struct phone *phone2){
  struct call *fromCall1;
  struct call *fromCall2;
  fromCall1 = malloc(sizeof(struct call));
  if(fromCall1 == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  fromCall2 = malloc(sizeof(struct call));
  if (fromCall2 == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  fromCall1 -> phones = phone2;
  fromCall1 -> calls = NULL;
  fromCall1 -> times = 1;
  if (phone1 -> calls == NULL){
    phone1 -> calls = fromCall1;
  }else{
    struct call *moveCall;
    moveCall = phone1 -> calls;
    while(moveCall -> calls != NULL){
      moveCall = moveCall -> calls;
    }
    moveCall -> calls = fromCall1;
  }

  fromCall2 -> phones = phone1;
  fromCall2 -> calls = NULL;
  fromCall2 -> times = 1;
  if(phone2 -> calls == NULL){
    phone2 -> calls = fromCall2;
  }else{
    struct call *moveCall;
    moveCall = phone2 -> calls;
    while(moveCall -> calls != NULL){
      moveCall = moveCall -> calls;
    }
    moveCall -> calls = fromCall2;
  }
}

void resetStatus(){
  struct phone *tmpPhone = list_hd;
  while(tmpPhone != NULL){
    tmpPhone -> visited = 0;
    tmpPhone -> level = 0;
    tmpPhone = tmpPhone -> down;
  }
}

void enqueue(struct phone *phones){
  struct item *tmpItem = malloc(sizeof(struct item));
  tmpItem -> items = phones;
  tmpItem -> next = NULL;
  if (queue == NULL){
    queue = tmpItem;
  }else{
    struct item *move = queue;
    while(move -> next != NULL){
      move = move -> next;
    }
    move -> next = tmpItem;
  }
}

void dequeue(){
  struct item *tmpItems = queue;
  queue = queue -> next;
  free(tmpItems);
}

int BFS(struct phone *start, struct phone *target){
  start -> visited = 1;
  start -> level = 0;
  enqueue(start);
  while(queue != NULL){
    struct phone *head = queue -> items;
    dequeue();
    if(head == target){
      return head -> level -1;
    }
    struct call *tmpCall = head -> calls;
    while(tmpCall != NULL){
      if (tmpCall -> phones -> visited == 0){
        tmpCall -> phones -> visited = 1;
        tmpCall -> phones -> level = head -> level + 1;
        enqueue(tmpCall -> phones);
      }
      tmpCall = tmpCall -> calls;
    }
  }
  return -1;
}

int checkFormat(char *num){
  int length;
  for (length = 0; num[length]!='\0';length++){}
  if (length == 12){
    if (isdigit(num[0]) && isdigit(num[1]) && isdigit(num[2]) && num[3] == '-' &&
    isdigit(num[4]) && isdigit(num[5]) && isdigit(num[6]) && num[7] == '-' &&
    isdigit(num[8]) && isdigit(num[9]) && isdigit(num[10]) && isdigit(num[11])){
      return 1;
    }
  }
  return 0;
}

void emptyQueue(){
  struct item *tmpItems, *tItems;
  tmpItems = queue;
  while(tmpItems != NULL){
    tItems = tmpItems;
    tmpItems = tmpItems -> next;
    free(tItems);
  }
  queue = NULL;
}

void query(){
  FILE *inFile = NULL;
  inFile = stdin;
  char *line = NULL;
  size_t len = 0;
  while(getline(&line, &len, inFile) != EOF){
    char *linePtr = line;
    char num1[14], num2[14], bad[2];
    int retVal = sscanf(linePtr, "%13s %13s %1s",num1, num2, bad);
    if (mulNumber(num1) && mulNumber(num2)){
      if (checkFormat(num1) && checkFormat(num2) && !compareString(num1, num2)){
        if (retVal == 2){
          struct phone *phone1 = getFirstNumber(num1);
          struct phone *phone2 = getSecNumber(num2);
          if (phone1 != NULL && phone2!=NULL){
            int num;
            resetStatus();
            emptyQueue();
            if (called(phone1, phone2)){
              num = getCall(phone1, phone2) -> times;
              printf("Talked %d times\n", num);
            }else{
              num = BFS(phone1, phone2);
              if (num != -1){
                printf("Connected through %d numbers\n", num);
              }else{
                printf("Not connected\n");
              }
            }
          }
        }else if(retVal > 2 || retVal == 1 || retVal == 0){
	  fprintf(stderr, "wrong number of string\n");
  	  errorFlag = 1;
	}
      }else{
        fprintf(stderr, "invalid format\n");
        errorFlag = 1;
      }
    }else{
      fprintf(stderr, "no such phone\n");
      errorFlag = 1;
    }
  }
  free(line);
}

void freeList(){
  struct phone *tmpPhone, *tPhones;
  struct call *tmpCall, *tCalls;
  tmpPhone = list_hd;
  while(tmpPhone != NULL){
    tmpCall = tmpPhone -> calls;
    while(tmpCall != NULL){
      tCalls = tmpCall;
      tmpCall = tmpCall -> calls;
      free(tCalls);
    }
    tPhones = tmpPhone;
    tmpPhone = tmpPhone -> down;
    free(tPhones->number);
    free(tPhones);
  }

}

int main(int argc, char *argv[]){
  if (argc <= 1){
    fprintf(stderr, "no input file\n");
    exit(1);
  }
  int i;
  FILE *inFile = NULL;
  for (i = 1;  i < argc; i++){
    inFile = fopen(argv[i],"r");
    if (inFile == NULL){
      fprintf(stderr, "not such file\n");
      errorFlag = 1;
    }else{
      char *line = NULL;
      size_t len = 0;
      while(getline(&line, &len, inFile) != EOF){
        char *linePtr = line;
        char num1[14], num2[14], bad[2];
        int retVal = sscanf(linePtr, "%13s %13s %1s", num1, num2, bad);
        if (retVal == 2){
          if (checkFormat(num1) && checkFormat(num2) && !compareString(num1, num2)){
            if (!mulNumber(num1)){
              addPhones(num1);
            }
            if (!mulNumber(num2)){
              addPhones(num2);
            }
            struct phone *phone1 = getFirstNumber(num1);
            struct phone *phone2 = getSecNumber(num2);
            if (called(phone1, phone2)){
              struct call *fromCall1 = getCall(phone1, phone2);
              struct call *fromCall2 = getCall(phone2, phone1);
              fromCall1 -> times += 1;
              fromCall2 -> times += 1;
            }else{
              addCalls(phone1, phone2);
            }
          }else{
            fprintf(stderr, "invalid format\n");
            errorFlag = 1;
          }
        }else if(retVal > 2 || retVal == 1 || retVal == 0){
          fprintf(stderr, "do not have exactly 2 phone numbers\n");
          errorFlag = 1;
        }
      }
      free(line);
    }
    if (inFile!= NULL){
      fclose(inFile);
    }
  }
  query();
  freeList();
  if (errorFlag){
    exit(1);
  }else{
    exit(0);
  }
}
