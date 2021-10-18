/*
 *  File name: p3-pub.c
 *
 *  Author: 2021/20222 P1 AED Team
 *
 *  Release date: 2021/10/12
 *
 *  Description: See the handout.
 *
 *  Version: 1.0
 *
 *  Change log:
 *    V1.0 - 2021/10/12 -  First version
 *
 */



/* Header Inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "VecDynList.h"



/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
  FILE *fp;
  VecDyn *vecDyn = (VecDyn*) NULL;
  char *fileNameIn;
  char buffer[256], *bufptr, cmd;
  int i, val1, val2, idx1;
  int exitProcessing = 0;

  /* Check number of arguments */
  if(argc < 2) {
    printf("Usage: LAIp3 filename\n");
    exit(1);
  }

  /* Open input file */
  fileNameIn = argv[1];

  fp  = fopen(fileNameIn, "r");
  if(fp == NULL) {
    printf("Open error of input file.\n");
    exit(2);
  }

  /* Read and process commands */
  /* Cycle through all data in input file */

  while(!feof(fp)) {

     bufptr = fgets(buffer, 256, fp);
     cmd = buffer[0];
     for (i = 0; (buffer[i] == ' ') || (buffer[i] == '\t'); i++) {
        cmd = buffer[i];
     }
     i++;

     /* what is the command */
     switch (cmd) {
     case '#':
        /* just a comment */
        break;
     case 'i':
        sscanf(bufptr+i, "%d", &val1);
        vecDyn = insertVecDyn(vecDyn, val1);
        break;
     case 'g':
        sscanf(bufptr+i, "%d", &idx1);
        val2 = getVecDynValue(vecDyn, idx1);
        printf("%d\n", val2);
        break;
     case 'c':
        sscanf(bufptr+i, "%d %d", &idx1, &val1);
        modifyVecDynValue(vecDyn, idx1, val1);
        break;
     case 'p':
        printVecDyn(vecDyn);
        break;
     case 'd':
        deleteVecDyn(vecDyn);
        break;
     case 'o':
        val2 = occupancyVecDyn(vecDyn);
        printf("%d\n", val2);
        break;
     case 'M':
        val1 = maxVecDynValue(vecDyn);
        printf("%d\n", val1);
        break;
     case 'm':
        val1 = minVecDynValue(vecDyn);
        printf("%d\n", val1);
        break;
     case 's':
        val2 = sizeVecDyn(vecDyn);
        printf("%d\n", val2);
        break;
     case 'l':
        vecDyn = shiftLeftVecDyn(vecDyn);
        break;
     case 'r':
        fscanf(fp, "%d", &val1);
        vecDyn = shiftRightVecDyn(vecDyn, val1);
        break;
     case 'x':
        break;
     case 'y':
        sscanf(bufptr+i, "%d", &val1);
        break;
     case 'w':
        break;
     case 'z':
        sscanf(bufptr+i, "%d", &val1);
        break;
     case 'e':
        exitProcessing = 1;
        break;
     case '\n':
        exitProcessing = 1;
        break;
     default:
        printf("error: unknown command '%c'\n", cmd);
        exit(1);
     }

    if(feof(fp)) break;

    /* are we going out ? */
    if (exitProcessing == 1) {
       break;
    }

  }

  /* Close input file                                             */
  fclose(fp);

  /* Free memory allocated to vector                              */
  if (vecDyn != (VecDyn*)NULL) {
     freeVecDyn(vecDyn);
  }

  return 0;
}




