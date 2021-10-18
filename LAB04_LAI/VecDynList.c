/*
 *  File name: VecDynList.c
 *
 *  Author: 2016/2017 Fall Semester AED Team
 *
 *  Release date: 2016/10/19
 *
 *  Description: C-Implementation of VecDynlist.h
 *
 *  Version: 1.0
 *
 *  Change log:
 *    1.0 - 2016/10/19 -   First version
 *
 */



/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>



/* Include Header File with Data Type and Function Prototypes     */
#include"VecDynList.h"





/*
 *  Data Type: _VecNode
 *
 *  Description: Structure with:
 *                 1) index of the vector
 *                 2) value of the vector correspondinf to the inde
 *                 2) Pointer to next node of the linked list.
 */
 struct _vec_dyn {
  int size;        /* number of table entries in this table segment */
  int free;        /* number of non-occupied=free entries */
  int *table;      /* pointer to table segment itself */
  struct _vec_dyn *next;    /* next table segment in list */
};



/*
 *  Function:
 *    initVecDynSegment
 *
 *  Description:
 *    Initializes a new dynamic table segment
 *
 *  Arguments:
 *    size of table segment
 *      (int) size
 *
 *  Return value:
 *    pointer to dynamic table segment
 *      (VecDyn *) vecDyn
 */
VecDyn *initVecDynSegment(int size)
{
  VecDyn * snew;

  /* Memory allocation                                            */
  snew = (VecDyn *) malloc(sizeof(VecDyn));

  /* Check memory allocation errors                               */
  if( snew == ((VecDyn*)NULL) )
    return ((VecDyn*) NULL);

  /* Memory allocation                                            */
  snew->table = (int *) malloc(sizeof(int) * size);

  /* Check memory allocation errors                               */
  if( snew->table == ((int*)NULL) ) {
    /* if the table failed to allocate, abort everything          */
    free(snew);
    return ((VecDyn*) NULL);
  }
  snew->size = size;
  snew->free = size;
  snew->next = (VecDyn*) NULL;

  return snew;
}



/*
 *  Function:
 *    freeVecDynSegment
 *
 *  Description:
 *    Frees the memory allocated to a segment of the dynamic table.
 *
 *  Arguments:
 *    Pointer to the segment of the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    None
 */
void freeVecDynSegment(VecDyn * vecDyn)
{
  free(vecDyn->table);
  free(vecDyn);

  return;
}



/*
 *  Function:
 *    initVecDyn
 *
 *  Description:
 *    Initializes a new dynamic table.
 *
 *  Arguments:
 *    (none)
 *
 *  Return value:
 *    Returns the pointer to a new dynamic table
 *      (VecDyn *) vecDyn
 */
VecDyn * initVecDyn()
{
  VecDyn *new;

  /* Memory allocation for table data */
  new = initVecDynSegment(1);

  if( new == ((VecDyn*)NULL) )
    return ((VecDyn*) NULL);

  return new;
}


/*
 *  Function:
 *    freeVecDyn
 *
 *  Description:
 *    Frees the memory allocated to a dynamic table.
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (Vec *) vec
 *
 *  Return value:
 *    None
 */
void freeVecDyn(VecDyn * vecDyn)
{
  VecDyn *aux;

  /* Cycle from the first to the last element                     */
  for(aux = vecDyn; aux != NULL; aux = vecDyn) {
    /* Keep trace of the next node                                */
    vecDyn = aux->next;

    /* Free current node                                          */
    freeVecDynSegment(aux);
  }

  return;
}



/*
 *  Function:
 *    sizeVecDyn
 *
 *  Description:
 *    Determines the length of a dynamic table implemented as a list
 *    of table segments of decreasing powers of 2 size
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    Returns the size of the dynamic table
 */
int sizeVecDyn(VecDyn * vecDyn)
{

  return (2*vecDyn->size - 1);
}



/*
 *  Function:
 *    occupancyVecDyn
 *
 *  Description:
 *    Determines how many elements are currently in the dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *   The number of elements
 *
 */
int occupancyVecDyn(VecDyn * vecDyn)
{
  return (2*vecDyn->size - 1 - vecDyn->free);
}



/*
 *  Function:
 *    insertVecDyn
 *
 *  Description:
 *    Inserts an element in the dynamic table in the first free position.
 *    Allocates new space if the table is full
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *    Value to insert in the corresponding index:
 *      (int) val
 *
 *  Return value:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn;
 *    or NULL if the insertion failed
 *
 */
VecDyn * insertVecDyn(VecDyn * vecDyn, int val)
{
  VecDyn *new = vecDyn;

  // Caso de ser o primeiro no
  if (vecDyn == NULL) {
    new = (VecDyn *) calloc (1, sizeof(VecDyn));
    if (new == NULL) {
      exit(1);
    }
    if (new->next == NULL) {
      new->table = (int *) malloc (sizeof(int));
      if (new->table == NULL) {
        exit(1);
      }
      new->table[0] = val;
      new->free = 0;
      new->size = 1;
    }
    return new;
  }

  if (vecDyn->free == 0) {
    new = (VecDyn *) malloc (sizeof(VecDyn));
    if (new == NULL) {
      exit(1);
    }
    new->next = vecDyn;
    new->table = (int *) calloc (1, sizeof(int) * (2 * new->next->size));
    if (new->table == NULL) {
        exit(1);
    }
    new->table[0] = val;
    new->size = 2 * new->next->size;
    new->free = new->size - 1;
  } else {
    vecDyn->free--;
    for (int i = 0; i < vecDyn->size; i++) {
      if (vecDyn->table[i] == 0) {
        vecDyn->table[i] = val;
        break;
      }
    }
  }
  return new;
}



/*
 *  Function:
 *    getVecDynValue
 *
 *  Description:
 *    Gets an element in the dynamic table in a given position
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *    Index to fetch value from:
 *      (int) index
 *
 *  Return value:
 *    Value stored in the dynamic table on the given position:
 *      (int) vecDyn;
 *    or function will exit(1) if the index position is invalid
 *
 */
int getVecDynValue(VecDyn * vecDyn, int index)
{
  int val;

  /* check if outside table bounds */
  if ((index < 0) || (index > (2 * vecDyn->size - 2) - vecDyn->free))
    exit(1);

  /* determine the right segment */
  for(;;) {
    if (index < (vecDyn->size - 1)) {
      vecDyn = vecDyn->next;
    } else {
      val = vecDyn->table[index - (vecDyn->size-1)];
      break;
    }

  }

  return val;
}



/*
 *  Function:
 *    modifyVecDynValue
 *
 *  Description:
 *    Modifies element at a given index. Element must exist
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *    Index to modify
 *      (int) idx
 *    Value to insert in the corresponding index:
 *      (int) val
 *
 *  Return value:
 *    None
 *      (void)
 *
 */
void modifyVecDynValue(VecDyn * vecDyn, int idx, int val)
{
  /* check if outside table bounds */
  if ((idx < 0) || (idx > (2 * vecDyn->size - 2) - vecDyn->free))
    exit(1);

  /* determine the right segment */
  for(;;) {
    if (idx < (vecDyn->size - 1)) {
      vecDyn = vecDyn->next;
    } else {
      vecDyn->table[idx - (vecDyn->size-1)] = val;
      break;
    }

  }
  return;
}


/*
 *  Function:
 *    maxVecDynValue
 *
 *  Description:
 *    Computes maximum value of a VecDyn vector
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    maximum value
 *      (int)
 *
 */
int maxVecDynValue(VecDyn * vecDyn)
{
   int max = 0;

   return(max);
}


/*
 *  Function:
 *    minVecDynValue
 *
 *  Description:
 *    Computer minimum value of a VecDyn vector
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    Minimum value
 *      (int)
 *
 */
int minVecDynValue(VecDyn * vecDyn)
{
   int min = 0;

   return(min);
}




/*
 *  Function:
 *    shiftLeftVecDyn
 *
 *  Description:
 *    Shifts a VecDyn left (towards index 0)
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    pointer to dynamic table segment
 *      (VecDyn *) vecDyn
 *
 */
VecDyn *shiftLeftVecDyn(VecDyn * vecDyn)
{
   VecDyn *result = (VecDyn*) NULL;

   return(result);
}


/*
 *  Function:
 *    shiftRightVecDyn
 *
 *  Description:
 *    Shifts a VecDyn Right (adding a new element at index 0)
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *    New value to insert at index 0
 *      int value
 *
 *  Return value:
 *    pointer to dynamic table segment
 *      (VecDyn *) vecDyn
 *
 */
VecDyn *shiftRightVecDyn(VecDyn * vecDyn, int value)
{
   VecDyn *result = (VecDyn*) NULL;

   return(result);
}



/*
 *  Function:
 *    printVecDynFileRecur
 *
 *  Description:
 *    Print the contents of dynamic table, segment by segment.
 *
 *  Arguments:
 *    Pointer to the dynamic table segment:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    None.
 */
void printVecDynRecur(VecDyn * vecDyn)
{
   int i;

   /* recursive print implementation */
   if(vecDyn->next != ((VecDyn*)NULL)) {
      printVecDynRecur(vecDyn->next);
   }

   /* Print current segment of dynamic table                       */
   for ( i = 0; i < (vecDyn->size - vecDyn->free); i++) {
      printf("%d ", vecDyn->table[i]);
   }

   printf("\t");
   return;
}


/*
 *  Function:
 *    printVecDyn
 *
 *  Description:
 *    Prints the content of a dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    None.
 */
void printVecDyn(VecDyn * vecDyn)
{
   /* recursive print implementation */
   if (vecDyn != ((VecDyn*)NULL)) {
      printVecDynRecur(vecDyn);
   }

   printf("\n");

   return;
}


/*
 *  Function:
 *    deleteVecDyn
 *
 *  Description:
 *    Delete a dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    None.
 */
void deleteVecDyn(VecDyn * vecDyn)
{
   freeVecDyn(vecDyn);

   return;
}
