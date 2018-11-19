// #include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gst.h"
#include "rbt.h"
#include <ctype.h>
#include "string.h"
#include "scanner.h"

#define redblack 0
#define green 1

char *cleanString(char *s);

int main(int argc, char **argv) {

  // process args
  if (strcmp(argv[1], "-v") == 0) {
    printf("Written by Mayank Agarwal\n");
    return 0;
  }
  int type = (strcmp(argv[1], "-g") == 0) ? green : redblack;
  char *corpusfile = argv[argc - 2];
  char *commandfile = argv[argc - 1];

  // define tree
  RBT *rtree = 0;
  GST *gtree = 0;
  if (type == redblack) {
    rtree = newRBT(compareSTRING);
    setRBTdisplay(rtree, displaySTRING);
    setRBTfree(rtree, freeSTRING);
  } else {
    gtree = newGST(compareSTRING);
    setGSTdisplay(gtree, displaySTRING);
    setGSTfree(gtree, freeSTRING);
  }

  // construct tree
  FILE *corpus = fopen(corpusfile, "rb");
  while (!feof(corpus)) {
    char *s;
    if (stringPending(corpus)) s = readString(corpus);
    else s = readToken(corpus);
    if (s) s = cleanString(s);
    if (s) {
      // printf("%s\n", s);
      // s = cleanString(s);
      if (s[0]) {
        // printf("%s\n", s);
        if (rtree) insertRBT(rtree, newSTRING(s));
        else insertGST(gtree, newSTRING(s));
      }
      // if (s) free(s);
    }
  }
  fclose(corpus);

  // run commands
  FILE *commands = fopen(commandfile, "rb");
  while (!feof(commands)) {
    char command = readChar(commands);
    if (command) {
      char *str;
      if (command != 's' && command != 'r') {
        if (stringPending(commands)) str = readString(commands);
        else str = readToken(commands);
        if (str) str = cleanString(str);
      }
      // printf("%c %s\n", command, str);
      switch (command) {
        case 's':
          if (rtree) {
            if (sizeRBT(rtree) == 0) printf("EMPTY\n");
            displayRBT(rtree, stdout);
          }
          else {
            if (sizeGST(gtree) == 0) printf("EMPTY\n");
            displayGST(gtree, stdout);
          }
          break;
        case 'r':
          if (rtree) statisticsRBT(rtree, stdout);
          else statisticsGST(gtree, stdout);
          break;
        case 'f':
          printf("Frequency of %s: ", str);
          int f = rtree ? freqRBT(rtree, str) : freqGST(gtree, str);
          printf("%d\n", f);
          break;
        case 'i':
          if (str[0]) {
            if (rtree) insertRBT(rtree, newSTRING(str));
            else insertGST(gtree, newSTRING(str));
          }
          break;
        case 'd':;
          if (str[0]) {
            STRING *s = newSTRING(str);
            // int code = rtree ? deleteRBT(rtree, s) : deleteGST(gtree, s);
            // if (code == -1) printf("Value %s not found.\n", str);
            if (rtree) {
              if (freqRBT(rtree, s) == 0) printf("Value %s not found.\n", str);
              else if (freqRBT(rtree, s) > 1) deleteRBT(rtree, s);
              else {
                STRING *x = findRBT(rtree, s);
                setRBTfree(rtree, 0);
                deleteRBT(rtree, s);
                setRBTfree(rtree, freeSTRING);
                freeSTRING(x);
              }
            } else { //if (gtree) {
              if (freqGST(gtree, s) == 0) printf("Value %s not found.\n", str);
              else if (freqGST(gtree, s) > 1) deleteGST(gtree, s);
              else {
                STRING *x = findGST(gtree, s);
                setGSTfree(gtree, 0);
                deleteGST(gtree, s);
                setGSTfree(gtree, freeSTRING);
                freeSTRING(x);
              }
            }
            freeSTRING(s);
          }
          break;
      }
      
      // if (str) free(str);
    }
  }
  fclose(commands);
  
  return 0;
}

void trim(char *input) {
  char *dst = input, *src = input;
  char *end;

  // Trimp at front...
  while (isspace((unsigned char)*src))  ++src;

  // Trim at end...
  end = src + strlen(src) - 1;
  while (end > src && isspace((unsigned char)*end)) *end-- = 0;

  // Move if needed.
  if (src != dst) while ((*dst++ = *src++));
}

char *cleanString(char *s) {
  int len = strlen(s), j = 0;
  char *res = malloc(len + 1);
  for (int i = 0; i < len; i++) {
    char c = s[i];
    if (isupper(c)) c = tolower(c);
    if (isalpha(c) || isspace(c)) res[j++] = c;
  }
  res[j++] = '\0';
  trim(res);
  if (s) free(s);
  return res;
  // s = res;
  // return s;
}