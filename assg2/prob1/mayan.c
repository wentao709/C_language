/*
* File: mayan.c
* Author: wentao zhou
* Purpose: the class will read in a base-20 representation of a number
* and write it out as a base-10 (decimal) number.
*
*/

# include<stdio.h>
# include <stdlib.h>

void toLower();
int valid(char []);

/*
* main() - go through all the mayan numbers and print out the corresponding
* decimal values until EOF is encountered.
* it assumes each base-20 number is at most 6 characters long; and
* there are no negative or fractional values.
*/
int main(){
  char str[7];
  int lengthOfString;
  int i;
  int valids;
  while (scanf("%6s", str) != EOF){
    toLower(str); // it's case-insensitive, so change all the char to lower case.
    for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
    int digits;
    int sum = 0;
    for (i = 0; i < lengthOfString; i++){
      if (!valid(str)){
        fprintf(stderr,"it is not a valid base-20 numeral\n");
        valids = 0;
        break;
      }else{
        int num = str[i]-97; // 'a' is 97, and it should be 0 in the case, so I minus it by 97, b is 1, etc..
        for (digits = 0; digits< lengthOfString-i-1;digits++){
          num *= 20; // the numebr times the 20^digits
        }
        sum += num;
      }
    }
    if (valid(str))
      printf("%d\n",sum);
  }
  if (!valids){
    exit(1);
  }else{
    exit(0);
  }
}

/*
* valid(char): checkif the input is valid
* char c[]: all the input char is lowered.
*/
int valid(char c[]){
  int i;
  for (i = 0; c[i] != '\0'; ++i){
    if (c[i] < 'a' || c[i] > 't'){
      return 0;
    }
  }
  return 1;
}

/* toLower(char []): change all teh character to lower cases.
*/
void toLower(char c[7]){
  int i;
  for (i = 0; c[i] != '\0'; ++i){
    if (c[i] >= 'A' && c[i] <= 'T'){
      c[i] = c[i]-'A'+'a';
    }
  }
  return;
}
