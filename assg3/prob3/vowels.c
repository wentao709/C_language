/*
* File: vowels.c
* Author: wentao zhou
* Purpose: check if the vowels in each work is in order if and only if for any
* two vowels v1 and v2 occurring in w, if v1 comes before v2 in the English alphabet,
* then every position in which v1 occurs in w comes before every position in which v2 occurs.
*
*/

# include <stdio.h>
# include <stdlib.h>

void toLower();

/*
* main() -- go through all the input string. check if the vowels in each word is
* in order. I initial e, i, o, u to 0 and one they show up change them to be 1, and then a
* like if I got 'u' again and e == 1, I know the work is not in order. it assumes that
* each word is not longer than 64 charater.
*
*/
int main(){
  char str[65];
  int j;
  int valid = 1; // check if the input is valid
  int exits = 1; // determine the exit statue.
  while (scanf("%64s", str) != EOF){
    toLower(str);
    int e = 0; // 0 means it has not shown up yet;
    int i = 0;
    int o = 0;
    int u = 0;
    int inOrder = 1; // check if the word is in order.
    valid = 1;
    for (j = 0; str[j] != '\0' ;j++){
      if (!(str[j]>='a'&& str[j]<='z')){
        valid = 0; // invalid word
        exits = 0; // should do exit(1)
        fprintf(stderr,"the string contains non-character\n");
	      break;
      }
    }
    if (valid){
      for (j = 0; str[j] != '\0' ;j++){
        if (str[j] == 'a'){
          // if I saw 'a' but e or o or u or i showu up already, it's not in order
          if (e == 1 || i == 1 || o == 1 || u == 1){
            inOrder = 0;
            printf("0\n");
            break;
          }
        }
        if(str[j] == 'e'){
          // if I saw 'e' but o or u or i showu up already, it's not in order
          if (i == 1 || o == 1 || u == 1){
            printf("0\n");
            inOrder = 0;
            break;
          }
          e = 1;
        }
        if(str[j] == 'i'){
          // if I saw 'i' but o or u showu up already, it's not in order
          if (o == 1 || u == 1){
            printf("0\n");
            inOrder = 0;
            break;
          }
          i = 1;
        }
        if(str[j] == 'o'){
          // if I saw 'o' but u or i showu up already, it's not in order
          if (u == 1){
            printf("0\n");
            inOrder = 0;
            break;
          }
          o = 1;
        }
        if(str[j] == 'u'){
          u = 1;
        }
      }
      if (inOrder)
        printf("1\n");
    }
  }
  if(exits){
    exit(0);
  }else{
    exit(1);
  }
}


/* toLower(char []): change all the character to lower cases.
* char[] c: the character to be changed. 
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
