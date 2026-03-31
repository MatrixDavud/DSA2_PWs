#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <locale.h>
#include "dict.h"

/**
 ** @file
 ** @brief test different implementation for dict.h
 **
 ** These tests only need the interface and can be linked with
 ** different implementations to test the dictionary functionality.
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
 ** @brief search for key @a search and remove it if present
 **/
static
dict* dict_test_search(dict* dico, char const search[]) {
  dict_value val = { { 0 } };
  dict_key k;
  key_init(&k, search);
  bool found = dict_search(dico, &k, &val);
  if (found) 
    printf("Found key %s, value is %s \n", search, value_string(&val));
  else 
    printf("key %s not found\n", search);
  return dico;
}

/**
 * main function
 **/
int main(int argc, char* argv[argc]) {

  // sets the locale to the one defined in the environment, 
  // necessary to handle characters with accents correctly. 
  setlocale(LC_ALL,"");

  size_t qty = 2000;
  if (argc < 2) {
    fprintf(stderr, "* Error: usage: %s <textfile> [n]\n", argv[0]);
    fprintf(stderr, "  where <textfile> is a list of unique keys\n");
    fprintf(stderr, "        [n] (optional) the first n items to manipulate (default=%zu).\n", qty);
    return EXIT_FAILURE;
  }
  if (argc==3)
    qty = atoi(argv[2]); // modify default value with optional parameter


  // create an empty dictionary
  dict* dico = dict_create();

  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    perror("Open file");
    return EXIT_FAILURE;
  }

  struct timeval tv1;
  gettimeofday(&tv1, 0);
  // insert the whole file into the dictionary
  for (char line[100]; readline(fp, key_size, line);) {
    dict_value val;
    value_init(&val, line);
    dict_key k;
    key_init(&k, line);
    dico = dict_insert(dico, &k, &val);
  }

  struct timeval tv2;
  gettimeofday(&tv2, 0);
  printf("size of dictionary is %zu\n", dict_size(dico));

  // search for a specific word in the dictionary
  printf("Please enter a word to search for: ");
  char line[100];
  readline(stdin, sizeof line, line);
  struct timeval tv3;
  gettimeofday(&tv3, NULL);
  dico = dict_test_search(dico, line); 
  struct timeval tv4;
  gettimeofday(&tv4, NULL);

 // remove an item from the dictionary
  printf("Please enter a word to remove: ");
  readline(stdin, sizeof line, line);
  struct timeval tv5;
  gettimeofday(&tv5, NULL);
  dico = dict_test_search(dico, line);  // search and remove
  struct timeval tv6;
  gettimeofday(&tv6, NULL);


  struct timeval tvA;
  gettimeofday(&tvA, 0);
  // search for the first n items
  printf("* Search for the first %zu items ...\n", qty);
  rewind(fp);
  for (size_t i = 0; i < qty; ++i) {
    char line[100];
    readline(fp, key_size, line);
    dict_value val;
    dict_key k;
    key_init(&k, line);
    dict_search(dico, &k, &val);
  }
  struct timeval tvB;
  gettimeofday(&tvB, 0);

  // Computing size of dictionary
  struct timeval tvC;
  gettimeofday(&tvC, NULL);
  size_t size = dict_size(dico);
  struct timeval tvD;
  gettimeofday(&tvD, NULL);
  printf("size of dictionary is %zu\n", size);


  // mass removal in the dictionary
  printf("* Remove the first %zu items ...\n", qty);
  struct timeval tv7;
  gettimeofday(&tv7, NULL);
  rewind(fp);
  for (size_t i = 0; i < qty; ++i) {
    char line[100];
    readline(fp, key_size, line);
    dict_key k;
    key_init(&k, line);
    dico = dict_remove(dico, &k);
  }
  struct timeval tv8;
  gettimeofday(&tv8, NULL);
  fclose(fp);

  // Delete whole dict
  struct timeval tv9;
  gettimeofday(&tv9, NULL);
  dico = dict_delete(dico);
  struct timeval tv10;
  gettimeofday(&tv10, NULL);
  printf("size of dictionary is %zu\n", dict_size(dico));
  
  printf("----------------- statistics ------------------\n");
  printf("time for dictionary full insertion\t%g sec\n", timeval_diff(tv1, tv2));
  printf("time for search (specified)\t\t%g sec\n", timeval_diff(tv3, tv4));
  printf("time for dict search (first %zu)\t%g sec\n", qty, timeval_diff(tvA, tvB));
  printf("time for dictionary size\t\t%g sec\n", timeval_diff(tvC, tvD));
  printf("time for remove (specified)\t\t%g sec\n", timeval_diff(tv5, tv6));
  printf("time for remove (first %zu)\t\t%g sec\n", qty, timeval_diff(tv7, tv8));
  printf("time for dictionary delete\t\t%g sec\n", timeval_diff(tv9, tv10));
  printf("-----------------------------------------------\n");

  return EXIT_SUCCESS;
}
