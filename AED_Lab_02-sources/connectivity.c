/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int op_find = 0;
   unsigned long int op_union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      /* do search first */
      op_find += 2;  // read id[p] and id[q]; total of 2 times
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      op_union += 1;    // read id[p] at the beggining of for loop
      for (t = id[p], i = 0; i < N; i++) {
         if (id[i] == t) {
            id[i] = id[q];
            op_union += 2;    // read id[q] and write id[i]
         }
         op_union += 1;    // read id[i]
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of Nodes is %d\n", N);
   printf("QF: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("QF: %ld find operations and %ld union operations for a total of %ld operations.\n", op_find, op_union, op_find + op_union);
   
   print_conjuntos(id, N, links_cnt);
   
   return;
}

/******************************************************************************
 * print_conjuntos()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            links_cnt - number of links
 * Returns: (void)
 * Side-Effects: changes the id[] table
 *
 * Description: Prints group with the same id[]
 *****************************************************************************/

void print_conjuntos(int *id, int N, int links_cnt) {

   int t = 0;   // auxiliary variable

   /* first_time is 0 = true; is 1 = false; allows to know what is the first  */
   /* element of a group to display                                           */
   int first_time = 0;

   printf("\n");

   for (int i = 0; i < (N - links_cnt); i++) {
      for (int j = 0; j < N; j++) {
         if (id[j] == -1) {
            continue;
         }
         if (first_time == 0) {
            t = id[j];
            printf("%-d", j);
            id[j] = -1;

            first_time = 1;
         }

         if (t == id[j]) {
            printf("-%d", j);
            id[j] = -1;
         }
      }
      first_time = 0;
      printf("\n");   
   }
   printf("Número de conjuntos:\t%d\n", N - links_cnt);
}

/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int op_find = 0;
   unsigned long int op_union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      while (i != id[i]) {
         i = id[i];
         op_find += 2;     // per loop, 2 reads from id[i]
      }
      op_find += 1;     // when while condition = 0, there is 1 read of id[i]
      while (j != id[j]) {
         j = id[j];
         op_find += 2;     // per loop, 2 reads from id[j]
      }
      op_find += 1;     // when while condition = 0, there is 1 read of id[j]
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      id[i] = j;
      op_union += 1;    // write to id[i]
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of Nodes is %d\n", N);
   printf("QU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("QU: %ld find operations and %ld union operations for a total of %ld operations.\n", op_find, op_union, op_find + op_union);
}

/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int op_find = 0;
   unsigned long int op_union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i])
         op_find += 2;     // 2 reads per loop
      op_find += 1;     // when if condition = 0, 1 read of id[i]
      for (j = q; j != id[j]; j = id[j])
         op_find += 2;     // 2 reads per loop
      op_find += 1;     // when if condition = 0, 1 read of id[j]

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         op_union += 5;    // 2 sz[] reads, 2 sz[] writes and 1 id[] write
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         op_union += 5;    // 2 sz[] access from if statement, 1 id[] write and 1 read and write from sz[]
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of Nodes is %d\n", N);
   printf("WQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("WQU: %ld find operations and %ld union operations for a total of %ld operations.\n", op_find, op_union, op_find + op_union);

}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int op_find = 0;
   unsigned long int op_union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i])
         op_find += 2;     // 2 read id[i] per loop
      op_find += 1;     // when if condition = 0, 1 read of id[i]
      for (j = q; j != id[j]; j = id[j])
         op_find += 2;     // 2 read id[j] per loop
      op_find += 1;     // when if condition = 0, 1 read of id[j]

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         t = j;
         op_union += 5;    // 2 sz[] reads, 2 sz[] writes and 1 id[] write
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         t = i;
         op_union += 5;    // 2 sz[] access from if statement, 1 id[] write and 1 read and write from sz[]
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      for (i = p; i != id[i]; i = x) {
         x = id[i];
         id[i] = t;
         op_union += 3;    // 2 id[i] reads and 1 id[i] write
      }
      op_union += 1;    // when if condition = 0, 1 id[i] read
      for (j = q; j != id[j]; j = x) {
         x = id[j];
         id[j] = t;
         op_union += 3;    // 2 id[j] reads and 1 id[j] write
      }
      op_union += 1;    // when if condition = 0, 1 id[j] read
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of Nodes is %d\n", N);
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("CWQU: %ld find operations and %ld union operations for a total of %ld operations.\n", op_find, op_union, op_find + op_union);

   return;
}
