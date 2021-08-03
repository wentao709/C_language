# include<stdio.h>
# include<stdlib.h>
# include <ctype.h>
# include<string.h>

struct node{
  char *string;
  int count;
  struct node *next;
};

struct node *list_hd = NULL;

char* strClean(char *str){
  char *tail;
  while (!(*str>='a' && *str<='z') && *str!='\0'){
    str += 1;
  }
  tail = str;
  int length;
  for (length = 0; str[length]!='\0';length++){}
  if (length>0){
    tail += (length-1);
    while (!(*tail>='a' && *tail<='z')){
      if (*(tail-1)>='a' && *(tail-1)<='z'){
        *tail = '\0';
        break;
      }
      tail--;
    }
  }
  return str;
}

void sort_list(){
  struct node *ptr1;
  struct node *ptr2;
  char *tmp;
  int tempInt;
  int swapped = 1;
  while (swapped){
    swapped = 0;
    for (ptr1 = list_hd; ptr1!=NULL; ptr1 = ptr1 -> next){
      for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2 -> next){
        if (strcmp(ptr1->string, ptr2->string) > 0){
          swapped = 1;
          tmp = ptr1 -> string;
          tempInt = ptr1 -> count;
          ptr1 -> string = ptr2 -> string;
          ptr1 -> count = ptr2 -> count;
          ptr2 -> string = tmp;
          ptr2 -> count = tempInt;
        }
      }
    }
  }
}

int contain(char *str){
  struct node *tmp = list_hd;
  int length1;
  for (length1 = 0; str[length1]!='\0';length1++){}
  while(tmp != NULL){
    int length2;
    for (length2 = 0; tmp->string[length2]; length2++){}
    if (length1==length2){
      int i = 0;
      int equal = 1;
      for (i = 0;str[i]!='\0' ;i++){
        if (str[i] != tmp->string[i]){
          equal = 0;
          break;
        }
      }
      if (equal){
        tmp -> count += 1;
        return 1;
      }
    }
    tmp = tmp -> next;
  }
  return 0;
}

int main(){
  char str[129];
  while(scanf("%128s", str)!=EOF){
    struct node *tmpNode;
    tmpNode = malloc(sizeof(struct node));
    if (tmpNode == NULL){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    int i;
    for(i = 0; str[i]!='\0';i++){
      str[i] = tolower(str[i]);
    }
    char *strPtr = strClean(str);
    if (*strPtr!='\0'){
      if (!contain(strPtr)){
        tmpNode -> string = strdup(strPtr);
        tmpNode -> next = list_hd;
        tmpNode -> count = 1;
        list_hd = tmpNode;
      }
    }
  }
  sort_list();
  struct node *list = list_hd;
  while(list != NULL){
    printf("%s %d\n", list->string, list->count);
    list = list -> next;
  }
  exit(0);
}
