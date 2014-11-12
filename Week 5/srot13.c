// McKenna Galvin
// 604290168
// srot13.c
// CS 35L week 5

#include <stdio.h>
#include <stdlib.h>

// returns negative if a < b, positive if a > b, 0 if a = b

int rot13cmp (const void *a, const void *b) {

  const char *aa = *(const char **)a;
  const char *bb = *(const char **)b;

  while (1) {

    // reach new line
    if (*aa == '\n' && *bb == '\n')
      return 0;
    else if (*aa == '\n')
      return -1;
    else if (*bb == '\n')
      return 1;

    // get integer representation of characters so we can change them
    // to decode (since the pointers being passed are constant)
    int aaa = (int) *aa;
    int bbb = (int) *bb;
    
    // if a-m, add 13 to get decoded char
    // if n-z, subtract 13 to get decoded char
    if ((*aa >= 65 && *aa <=77) || (*aa >= 97 && *aa <= 109))
      aaa += 13;
    else if ((*aa >= 78 && *aa <= 90) || (*aa >= 110 && *aa <= 122))
      aaa -=13;
    if ((*bb >= 65 && *bb <=77) || (*bb >= 97 && *bb <= 109))
      bbb += 13;
    else if ((*bb >= 78 && *bb <= 90) || (*bb >= 110 && *bb <= 122))
      bbb -=13;

    // get difference between a and b, return positive or negative number
    // depending on which is larger. If 0, continue to next char in each word
    int difference = aaa - bbb;
    if (difference != 0)
      return difference;

    // move on to next char
    aa++;
    bb++;
  }
  
}

int main() {

  int size = 1024;
  int totalChars = 0;
  char *input = (char*)malloc(size * sizeof(char));

  // deal with error
  if (input == NULL) {
    fprintf(stderr, "Couldn't allocate memory");
    exit(1);
  }

  int c;
  // get input
  while (1) {
    c = getchar();
    if (c == EOF)
      break;
    input[totalChars] = (char) c;
    totalChars++;
    // reallocate more space if reached end of buffer
    if (totalChars == size) {
      input = (char*) realloc(input, size * 2);
      // deal with error
      if (input == NULL) {
	fprintf(stderr, "Couldn't allocate memory");
	exit(1);
      }
      size *= 2;
    }
  }

  if (totalChars < 1)
    exit(0);
  
  // if no newline at end, add a newline character
  if (input[totalChars-1] != '\n') {
    // reallocate more space if reached end of buffer
    if (totalChars == size) {
      input = (char*) realloc(input, size * 2);
      // deal with error
      if (input == NULL) {
	fprintf(stderr, "Couldn't allocate memory");
	exit(1);
      }
      size *= 2;
    }
    totalChars++;
    input[totalChars-1] = '\n';
  }

  // find number of words
  int numWords = 0;
  int m;
  for (m = 0; m < totalChars; m++) {
    if (input[m] == '\n')
      numWords++;
  }
  
  // create array of pointers to words
  char **words = (char**)malloc(sizeof(char*) * numWords);

  // deal with error
  if (words == NULL) {
    fprintf(stderr, "Couldn't allocate memory");
    exit(1);
  }

  // fill words array with pointers to the start of each word
  char *temp = input;
  int wordIndex = 0;
  int n;
  for (n = 0; n < numWords; n++) {
    words[wordIndex] = temp;
    wordIndex++;
    while (*temp != '\n')  // move to next word
      temp++;
    temp++; // have to move past new line character to get to actual word
  }

  // sort the words!
  qsort(words, wordIndex, sizeof(char*), rot13cmp);

  // print the words
  int p;
  for (p = 0; p < numWords; p++) {
    char *c = words[p];
    while (*c != '\n') {
      printf("%c", *c);
      c++;
    }
    printf("%c", *c);
  }

  // free memory
  free(input);
  free(words);

  // program executed successfully
  exit(0);
}
