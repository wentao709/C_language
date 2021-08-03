/*
* File: noVowels2.c
* Author: wentao zhou
* Purpose: writing code to divide up a set
* of words into groups where each group is a set of
* words that are noVowel matches of each other
*/

# include<stdio.h>
# include<stdlib.h>
# include<string.h>

// define a node, which doesn't have "down" node
struct node{
  char *string;
  struct node *next;
};

// define another node, which represents the pattern of my linked list.
// it has two links, one goes right and the other goes down.
struct pattern{
  char *string;
  struct node *next;
  struct pattern *down;
};

// initial the head of the linkedlist to null.
struct pattern *list_hd = NULL;

/*
* check if the character is a vowel.
* return 1 if it's not, 0 otherwise.
*/
int notVowel(char c){
  if (c != 'a' && c!='e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c!='E' && c != 'I' && c != 'O' && c != 'U'){
    return 1;
  }
  return 0;
}

/*
* toLower()
* convert the character to lower, because the comparison is case-insensitive.
* parameter: c: the string to be converted
*/
void toLower(char c[65]){
  int i;
  for (i = 0; c[i] != '\0'; ++i){
    if (c[i] >= 'A' && c[i] <= 'Z'){
      c[i] = c[i]-'A'+'a';
    }
  }
  return;
}

/*
* matched()
* check if str1 and str2 matched.
* parameter: str1, str2: the two string to be compared
*/
int matched(char *str1, char *str2){
  char *strLower1 = strdup(str1);
  char *strLower2 = strdup(str2);
  toLower(strLower1);
  toLower(strLower2);
  char noV1[65];
  char noV2[65];
  int i;
  int count1 = 0;
  for (i = 0; strLower1[i] != '\0';i++){
    if (notVowel(strLower1[i])){
      noV1[count1]=strLower1[i];
      count1 ++;
    }
  }
  noV1[count1] = '\0'; // get rid of the vowel in the string
  int count2 = 0;
  for(i = 0; strLower2[i] != '\0';i++){
    if (notVowel(strLower2[i])){
      noV2[count2]=strLower2[i];
      count2 ++;
    }
  }
  noV2[count2] = '\0';
  if (count1 == count2){
    for (i = 0; noV2[i] != '\0' ;i++){
      if (noV1[i] != noV2[i]){
        return 0;
      }
    } // compare the two new string which doesn't have vowels.
  }else{
    return 0;
  }
  return 1;
}

/* print()
* iterator over the linked list and print the results out
*/
void print(){
  struct pattern *goDownNode = malloc(sizeof(struct pattern));
  struct node *tmpNode = malloc(sizeof(struct node));
  goDownNode = list_hd;
  while(goDownNode != NULL){
    if (goDownNode -> next != NULL){
      printf("%s ", goDownNode -> string);
      tmpNode = goDownNode -> next;
      while(tmpNode -> next!= NULL){ // go right first
        printf("%s ", tmpNode -> string);
        tmpNode = tmpNode -> next;
      }
      printf("%s\n", tmpNode -> string);  // the line only have one node.
    }else{
      printf("%s\n", goDownNode -> string);
    }
    goDownNode = goDownNode -> down; // after finish each line, go to next line
  }
}

/* allVowels()
* purpose: for the special case, check if the string are composed of vowels. if it is, ignore it
* parameter: str: the string to be checked
* return 0 if it's an error, 1 otherwise.
*/
int allVowels(char str[65]){
  int i;
  for (i = 0; str[i]!='\0';i++){
    if (str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u' &&
        str[i] != 'A' && str[i] != 'E' && str[i] != 'I' && str[i] != 'O' && str[i] != 'U'){
      return 0;
    }
  }
  return 1;
}

/*
* checkEror()
* purpose: for the error condition, if the string contains non-alphabetic char, it's an eror
* parameter: str: the string to be checked
* return 0 if it's an error, 1 otherwise.
*/
int checkError(char str[65]){
  int i;
  for (i = 0; str[i]!='\0';i++){
    if (!((str[i]>='a' && str[i]<='z') || (str[i] >= 'A' && str[i] <= 'Z'))){
      return 0;
    }
  }
  return 1;
}

/* connectNode()
* each time read in a string, add a new node to the linked list.
* if the new string is matched, move right and add it to the end of the linked list.
* patameter: goDownNode: the node in the vertical linkedlist.
* str: the str stored in the node and add the node to the horizontal linked list.
*/
void connectNode(struct pattern *goDownNode, char str[65]){
  struct node *tmpNode = malloc(sizeof(struct node));
  if (tmpNode==NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  if (goDownNode->next==NULL){ // first node dones't have next node
    tmpNode = malloc(sizeof(struct node));
    if (tmpNode == NULL){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    tmpNode -> string = strdup(str);
    tmpNode -> next = NULL;
    goDownNode -> next = tmpNode;
  }else{
    struct node *goRightNode = malloc(sizeof(struct node));
    if (goRightNode==NULL){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    goRightNode = goDownNode -> next;
    while(goRightNode -> next != NULL){   // going right
      goRightNode = goRightNode -> next;
    } // going right till the end of the linked list
    tmpNode = malloc(sizeof(struct node));
    if (tmpNode == NULL){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    tmpNode -> string = strdup(str);
    tmpNode -> next = NULL;
    goRightNode -> next = tmpNode;
  }
}

/* main()
* purpose: read in the input string, stored in the node, connect node as followed the requirement
* the print the result out. it assumes that each str is no longer than 64 character.
*/
int main(){
  char str[65];
  int error = 0;
  while(scanf("%64s", str) != EOF){
    if (!checkError(str)){
      fprintf(stderr,"contains non-alphabetic\n");
      error = 1;
    }else{
      if (!allVowels(str)){
        if (list_hd == NULL){
          struct pattern *tmpNode = malloc(sizeof(struct pattern));
          if (tmpNode ==NULL){
            fprintf(stderr, "out of memory\n");
            exit(1);
          }
          tmpNode -> string = strdup(str);
          tmpNode -> next = NULL;
          tmpNode -> down = NULL;
          list_hd = tmpNode;// fisrt node in the linked list.
        }else{
          struct pattern *goDownNode = malloc(sizeof(struct pattern));
          if (goDownNode==NULL){
            fprintf(stderr, "out of memory\n");
            exit(1);
          }
          goDownNode = list_hd; // the node keep moving down.
          int match = 0;
          while(goDownNode -> down != NULL){ // keep going down to check match
            if (matched(str, goDownNode->string)){
              match = 1;
              connectNode(goDownNode, str);
            }
            goDownNode = goDownNode -> down;
          }
          //check the last vertical node
          if(matched(str, goDownNode->string)){
            match = 1;
            connectNode(goDownNode, str);
          }
          //check the last vertical node

          if (!match){
            struct pattern *tmpNode = malloc(sizeof(struct pattern));
            if (tmpNode==NULL){
              fprintf(stderr, "out of memory\n");
              exit(1);
            }
            tmpNode -> string = strdup(str);
            if (list_hd -> string==NULL){
              fprintf(stderr, "out of memory\n");
              exit(1);
            }
            tmpNode -> next = NULL;
            tmpNode -> down = NULL;
            goDownNode -> down = tmpNode;
          }// if no node matches, add it to the vertical linked list.
        }
      }
    }
  }
  print();
  if (error){
    exit(1);
  }else{
    exit(0);
  }
}
