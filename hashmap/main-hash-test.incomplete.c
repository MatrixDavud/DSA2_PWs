
/**
 * Use compiler clang to build,
 * or with gcc, compile with : gcc -Wall -std=c99 main-hash-test.c -o main-hash-test  -lm
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

/**
 ** @file
 ** @brief test different hash functions
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
 ** @brief comparison function used in quick sort
 **/
int compare_size(const void * a, const void * b) {
  size_t const* A = a;
  size_t const* B = b;
  long aA = *A;
  long bB = *B;
  return aA - bB;
}



/**
 ** @brief statistics on hash table usage
 **/
void stats(size_t table_size, size_t table[table_size], char const*id) {
  size_t min = -1;
  size_t max = 0;
  size_t sum = 0;
  double avg = 0;
  double stddev;

  for (size_t i=0; i<table_size;i++) {
    avg += table[i];
    if (table[i] < min)
      min=table[i];
    if (table[i] > max)
      max=table[i];
  }
  avg /= table_size;
  for (size_t i=0; i<table_size;i++) {
    sum += (table[i]-avg)*(table[i]-avg);
  }
  stddev=sqrt(sum/table_size);
  qsort (table, table_size, sizeof(size_t), compare_size);
  printf("\n** stats on %zu elements. Method is: %s\n",table_size,id);
  printf("\tmin/max\t\t%zu/%zu\n\tavg/stddev\t%.2f/%.2f\n\tmedian\t\t%zu\n",min,max,avg,stddev,table[table_size/2]);
}


/**
 ** @brief hash function: compute an integer from the null-terminated
 ** string @a s and the length @a table_size of the hash table.
 **
 ** This function produces an integer based on the values of the two
 ** first characters.
 **/
unsigned hash_simple(char const*s, size_t table_size) {
  return 0;
}


/**
 ** @brief hash function: compute an integer from the null-terminated
 ** string @a s and the length @a table_size of the hash table.
 **
 ** This function produces an integer based on the sum of characters
 ** making up the string.
 **/
unsigned hash_sum(char const*s, size_t table_size) {
  return 0;
}

unsigned int base=31;

/**
 ** @brief hash function: compute an integer from the null-terminated
 ** string @a s and the length @a table_size of the hash table.
 **
 ** This function produces an integer based on the characters' value
 ** represented in a given basis B: for a word=c1c2..cn, first compute
 ** r = (c1*B^{n-1} + c2*B^{n-2} + ... + cn) and then return (r mod
 ** table_size)
 **/
unsigned hash_base(char const*s, size_t table_size) {
  return 0;
}

/**
 ** @brief hash function: compute an integer from the null-terminated
 ** string @a s and the length @a table_size of the hash table.
 **
 ** Similar to hash_base(), but reduce each internal computation mod
 ** table_size to avoid overflow.
 **/
unsigned hash_base_mod(char const*s, size_t table_size) {
  return 0;
}


#define DICO "dico-francais.txt"

int main(int argc, char* argv[argc]) {
  struct timeval tv0;
  gettimeofday(&tv0, 0);
  // sets the locale to the one defined in the environment,
  // necessary to handle characters with accents correctly.
  setlocale(LC_ALL,"");

  size_t m;
  size_t nblines;
  FILE *fp = fopen(DICO, "r");
  if (!fp) {
    perror("Open " DICO ":");
    return EXIT_FAILURE;
  }

  if (argc <3 ) {
    printf("Usage: %s <size of hash array> <nblines read in file> [<base>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  m = strtoul(argv[1],0,0);
  nblines = strtoul(argv[2],0,0);
  if (argc > 3) base = strtoul(argv[3], 0, 0);

  printf("Hastable size is %zu\n", m);

  size_t *tableS = malloc(sizeof(size_t[m]));
  size_t *table = malloc(sizeof(size_t[m]));
  size_t *tableB = malloc(sizeof(size_t[m]));
  size_t *tableM = malloc(sizeof(size_t[m]));


  // read the first nblines lines
  size_t const lineLength = 100;
  char (*lines)[lineLength] = malloc(sizeof(char[nblines][lineLength]));

  struct timeval tv1;
  gettimeofday(&tv1, 0);
  for (size_t i = 0; i < nblines; ++i) {
    readline(fp, lineLength, lines[i]);
  }
  // run the hash functions on each of the lines and collect
  // statistics.
  struct timeval tv2;
  gettimeofday(&tv2, 0);
  for (size_t i = 0; i < nblines; ++i) {
    tableS[hash_simple(lines[i],m)] ++;
  }
  struct timeval tv3;
  gettimeofday(&tv3, 0);
  for (size_t i = 0; i < nblines; ++i) {
    table[hash_sum(lines[i],m)] ++;
  }
  struct timeval tv4;
  gettimeofday(&tv4, 0);
  for (size_t i = 0; i < nblines; ++i) {
    tableB[hash_base(lines[i],m)] ++;
  }
  struct timeval tv5;
  gettimeofday(&tv5, 0);
  for (size_t i = 0; i < nblines; ++i) {
    tableM[hash_base_mod(lines[i],m)] ++;
  }
  struct timeval tv6;
  gettimeofday(&tv6, 0);

  printf("----------------- statistics ------------------\n");
  printf("initialization\t%e sec\n", timeval_diff(tv0, tv1));
  printf("file read\t%e sec\n", timeval_diff(tv1, tv2));
  printf("function 1\t%e sec\n", timeval_diff(tv2, tv3));
  printf("function 2\t%e sec\n", timeval_diff(tv3, tv4));
  printf("function 3\t%e sec\n", timeval_diff(tv4, tv5));
  printf("function 4\t%e sec\n", timeval_diff(tv5, tv6));
  printf("-----------------------------------------------\n");

  stats(m, tableS,"h(c1c2) = (c1+c2) mod m");
  stats(m, table,"h(c1c2...cn) = Sum c_i mod m");
  stats(m, tableB,"h(base,c1c2...cn) = Sum c_i*B^{n-i-1}");
  stats(m, tableM,"h(base,c1c2...cn) = Sum c_i*B^{n-i-1} with mod");

  fclose(fp);
  free(tableS);
  free(table);
  free(tableB);
  free(tableM);
  free(lines);
  return EXIT_SUCCESS;
}
