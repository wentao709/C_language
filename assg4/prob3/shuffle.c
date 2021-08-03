#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int checkInt();

int main(){
  char *line1 = NULL;
  size_t len1 = 0;
  char *line2 = NULL;
  size_t len2 = 0;
  getline(&line1, &len1, stdin);
  int error = 0;
  if(checkInt(line1)){
    error = 1;
    fprintf(stderr,"invalid input\n");
  }
  getline(&line2, &len2, stdin);
  if(checkInt(line2)){
    error = 1;
    fprintf(stderr,"invalid input\n");
  }
  if (!error){
    int offset1;
    int number1;
    int offset2;
    int number2;
    while (sscanf(line1, "%d %n", &number1, &offset1) == 1){
      printf("%d\n", number1);
      line1+=offset1;
      if(sscanf(line2, "%d %n", &number2, &offset2) == 1){
        printf("%d\n", number2);
        line2+=offset2;
      }
    }

    while (sscanf(line2, "%d %n", &number2, &offset2) == 1){
      printf("%d\n", number2);
      line2+=offset2;
    }
  }
  if (error){
    exit(1);
  }

  exit(0);
}

int checkInt(char *line){
  char *str = malloc(sizeof(line));
  int offset = 0;
  while(sscanf(line, "%s %n", str, &offset)==1){
    int i = 0;
    while(str[i] != '\0'){
      if (str[i] == '-' && i == 0){
        if (str[i+1]=='\0'){
          return 0;
        }
      }else if(!isdigit(str[i])){
        return 0;
      }
      i++;
    }
    line+=offset;
  }

  return 1;
}
