/*
* File: noVowels.c
* Author: wentao zhou
* Purpose: the class is to  reads a series of strings, the first being
* the base pattern, and writes out the strings that are the same if the vowels
* are removed.
*
*/

# include<stdio.h>
# include <stdlib.h>

int containsNonAlpha();
int matched();
void toLower();
int notVowel(char);

/*
* main() -  read in a couple of strings, the first one being the base strings,
* writes out the strings that are the same if the vowels are removed. It assumes each
* word contains only case letters, and at most 64-char long.
*/
int main(){
  char str[65];
  scanf("%64s", str);
  int lengthOfString; // length of first chracter
  int lengthOfFollow; // length of the following chracter.
  int i;
  int count;
  int valid = 1;
  char standard[64]; // the first string without vowel
  for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
  if (containsNonAlpha(str)){ // check if the first string is valid
    fprintf(stderr, "string contains non-alpha\n");
    exit(1);
  }else{
    printf("%s\n", str);
    toLower(str);
    count = 0;
    for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
    for (i = 0; i < lengthOfString; i++){
      if (notVowel(str[i])){
        standard[count]=str[i];
        count ++;
      }
    }
  }
  standard[count] = '\0'; // last letter should be null
  while (scanf("%64s", str) != EOF){
    char strNoVowal[65] = ""; // the strings after the first one which has no vowel.
    for (lengthOfFollow = 0; str[lengthOfFollow] != '\0';lengthOfFollow++){}
    if (containsNonAlpha(str)){
      valid = 0;
      fprintf(stderr, "string contains non-alpha\n");
    }else{
      count = 0;
      for (i = 0; str[i] != '\0'; i++){
        if (notVowel(str[i])){
          strNoVowal[count]=str[i];
          count++;
        }
      }
      int lengthFirst; // the length of the first input string, which is the base string.
      int lengthSecond; // the length of the following strings.
      for (lengthFirst = 0; standard[lengthFirst] != '\0';lengthFirst++){}
      for (lengthSecond = 0; strNoVowal[lengthSecond] != '\0';lengthSecond++){}
      if (lengthFirst == lengthSecond){
        if (matched(strNoVowal, standard, lengthSecond)){
          printf("%s\n",str);
        }
      }
    }
  }
  if (valid){
    exit(0);
  }else{
    exit(1);
  }
}

/* notVowel(char) - check if the chracter is a vowel, return 1 if it's not, otherwise return 0.
* parameter - char c, the character to be checked.
*/
int notVowel(char c){
  if (c != 'a' && c!='e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c!='E' && c != 'I' && c != 'O' && c != 'U'){
    return 1;
  }
  return 0;
}

/*
* toLower(char []): change all the character to lower cases.
* parameter: char c, the char to be checked
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
* containsNonAlpha - check if the word contains non alpha. It returns 0 if it doesn't,
* otherwise returns 1.
*/
int containsNonAlpha(char str[65]){
  int lengthOfString;
  int i;
  for (lengthOfString = 0; str[lengthOfString] != '\0';lengthOfString++){}
  for (i = 0; i < lengthOfString; i++){
    if(!((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))){
      return 1;
    }
  }
  return 0;
}

/* matched - check if the two strings are matched
* parameter: str1 and str2 are the two strings to be checked,
* they have the same length.
* lengthOfString is the length of the two strings.
*/
int matched(char str1[65], char str2[65], int lengthOfString){
  int i;
  toLower(str1);
  toLower(str2);
  for (i = 0; i< lengthOfString;i++){
    if (str1[i]!=str2[i]){
      return 0;
    }
  }
  return 1;
}
