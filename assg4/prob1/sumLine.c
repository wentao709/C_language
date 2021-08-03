#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int emptyLine();
int invalidLine();

int main(){
  char *line = NULL;
  size_t len = 0;
  int getError = 0;
  while(getline(&line, &len, stdin) != EOF){
    getError = 0;
    if (emptyLine(line) || invalidLine(line)){
      getError = 1;
      fprintf(stderr, "invalid line\n");
    }else{
      char *linePtr = line;
      int offset;
      int number;
      int sum = 0;
      while (sscanf(linePtr, "%d %n", &number, &offset) == 1){
        printf("%d num\n", number);
        printf("%d off\n", offset);
        if (number < 0){
          printf("%d\n", number);
          getError = 1;
          fprintf(stderr, "it should be positive number\n");
          break;
        }
        sum += number;
        linePtr += offset;
      }
      if (!getError){
        printf("%d\n", sum);
      }
    }
  }
  if (getError){
    exit(1);
  }else{
    exit(0);
  }
}

int emptyLine(char *line){
  if(*line == '\0'){
    return 0;
  }
  while(*line != '\0'){
    if (!isspace(*line)){
      return 0;
    }
    line++;
  }
  return 1;
}

int invalidLine(char *line){
  while(*line != '\0'){
    if (!isdigit(*line) && !isspace(*line)){
      return 1;
    }
    line++;
  }
  return 0;
}
