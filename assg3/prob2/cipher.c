/*
* File: cipher.c
* Author: wentao zhou
* Purpose:  read in an integer N and one or more strings,
* each alphanumeric string will be rotated by the amount N and be printed out.
*
*/

# include<stdio.h>
# include <stdlib.h>
# include <ctype.h>

/*
* main() -- get the integer go through all the input strings. only rotate the
* letters,  rotating an upper-case letter produces an upper-case letter,
* and similarly with lower-case letters
*
*/
int main(){
  int N;
  char str[65];
  int status = scanf("%d",&N);
  if (status < 1){ // can't read in the first integers.
    fprintf(stderr,"the first input is not a number\n");
    exit(1);
  }
  int i;
  int j;
  int valid = 1; // check if the input is valid
  int exits = 1; // determine the exit statue.
  while (scanf("%64s", str) != EOF){
    valid = 1;
    for (i = 0;  str[i] != '\0';i++){
      if (!isalnum(str[i])){
        valid = 0; // invalid word
	      exits = 0; // should do exit(1)
        fprintf(stderr, "Not alpha-numeric string, it should not contain non-alphanumeric characters.\n");
        break;
      }
      if (N>=0){ // N is positive or 0;
        if (str[i] >= 'a' && str[i] <= 'z'){
          for (j = 0; j<N ;j++){
            str[i] += 1;
            if (str[i] > 'z'){ // the last letter, go back to the first, which is 'a'
              str[i] = 'a';
            }
          }
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
          for (j = 0; j<N ;j++){
            str[i] += 1;
            if (str[i] > 'Z'){ // the last letter, go back to the first, which is 'a'
              str[i] = 'A';
            }
          }
        }
      }else{
        if (str[i] >= 'a' && str[i] <= 'z'){
          for (j = 0; j<-N ;j++){
            str[i] -= 1;
            if (str[i] < 'a'){ // the first letter, go back to the last, which is 'z'
              str[i] = 'z';
            }
          }
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
          for (j = 0; j<-N ;j++){
            str[i] -= 1;
            if (str[i] < 'A'){ // the first letter, go back to the last, which is 'Z'
              str[i] = 'Z';
            }
          }
        }
      }
    }
    if (valid)
      printf("%s\n", str);
  }
  if (exits){
    exit(0);
  }else{
    exit(1);
  }
}
