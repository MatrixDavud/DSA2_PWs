#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <locale.h>
#include "hashtable.h"

/**
 ** @file
 ** @brief test hash table implementation
 **/

/**
 ** @brief read one line of input and get rid of EOL, if any.
 **/
static
bool readline(FILE* fp, size_t maxlen, char line[maxlen]) {
  if (!fgets(line, maxlen, fp))
    return false;
  size_t len = strlen(line);
  if (line[len-1] == '\n') line[len-1] = 0;
  return true;
}

/**
 ** @brief compute time difference in seconds
 **/
static
double timeval_diff(struct timeval tv1, struct timeval tv2) {
  return (tv2.tv_sec-tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)*1E-6;
}

/**
 * main function
 **/
int main(int argc, char* argv[argc]) {

  // sets the locale to the one defined in the environment, 
  // necessary to handle characters with accents correctly. 
  setlocale(LC_ALL,"");

  if (argc<2) {
	    fprintf(stderr,"usage: %s <hastable size>\n",argv[0]);
	    exit(EXIT_FAILURE);
  }

  // create an empty hash
  hashtable* dico = hashtable_create(strtoull(argv[1], 0, 0));

  FILE *fp = fopen("dico-francais.txt", "r");
  if (!fp) {
    perror("Open dico-francais.txt ");
    return EXIT_FAILURE;
  }

  struct timeval tv1;
  gettimeofday(&tv1, 0);

  // insert the whole file into the dictionary
  for (char line[100]; readline(fp, 100, line);) {
    hashtable_set(dico, line, line);
  }

  struct timeval tv2;
  gettimeofday(&tv2, 0);

  printf("size of hash is %zu\n", dico->size);

  struct timeval tv3;

  // search in the hash
  if (argc <=2 ) {
    printf("Please enter a word: ");
    char line[100];
    readline(stdin, sizeof line, line);
    gettimeofday(&tv3, NULL);
    hashtable_get(dico, line);
  } else {
    gettimeofday(&tv3, NULL);
    for (int i = 1; i < argc; ++i)
      hashtable_get(dico, argv[i]);
  }

  struct timeval tv4;
  gettimeofday(&tv4, NULL);

  rewind(fp);

  struct timeval tvC;
  gettimeofday(&tvC, 0);

  // search for the first items
  for (size_t i = 0; i < 20000; ++i) {
    char line[100];
    readline(fp, 100, line);
    hashtable_get(dico, line);
  }

  struct timeval tvD;
  gettimeofday(&tvD, 0);

  fclose(fp);

  printf("----------------- statistics ------------------\n");
  printf("time for dictionary read\t%g sec\n", timeval_diff(tv1, tv2));
  printf("time for search (specified)\t%g sec\n", timeval_diff(tv3, tv4));
  printf("time for dict search (first)\t%g sec\n", timeval_diff(tvC, tvD));
  printf("-----------------------------------------------\n");

  return EXIT_SUCCESS;
}
