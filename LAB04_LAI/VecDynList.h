/*
 *  File name: VecDynList.h
 *
 *  Author: 2016/2017 Fall Semester AED Team
 *
 *  Release date: 2016/10/19
 *
 *  Description: Header file for an Implementation of
 *               Dynamic Tables as a list of Table segments
 *
 *  Data type list:
 *    Dynamic Table Node: VecDyn
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initVecDyn
 *        freeVecDyn
 *
 *    B) Properties
 *        sizeVecDyn
 *        occupancyVecDyn
 *
 *    C) Insertion and Removal; *        insertVecDyn
 *        insertVecDyn
 *
 *    D) File representation
 *        readVecDynFile
 *        writeVecDynFile
 *
 *
 *  Dependencies:
 *    stdio.h
 *    stdlib.h
 *
 *  Version: 1.1
 *
 *  Change log:
 *    1.0 - 2016/10/19 -    First version
 *
 */


/* Prevent multiple inclusions                                      */
#ifndef VecDynListHeader
#define VecDynListHeader



/*
 *  Data type: Vec
 *
 *  Description: Vec data type. Contains a vector described by the
 *              dimension and a linked list with the elements of the
 *              vector.
 */
typedef struct _vec_dyn VecDyn;



/*
 *  Function:
 *    initVecDyn
 *
 *  Description:
 *    Initializes a new dynamic table.
 *
 *  Arguments:
 *      (none)
 *
 *  Return value:
 *    Returns the pointer to a new dynamic table
 */
VecDyn * initVecDyn();



/*
 *  Function:
 *    freeVecDyn
 *
 *  Description:
 *    Frees the memory allocated by the dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    None
 */
void freeVecDyn(VecDyn * vecDyn);


/*
 *  Function:
 *    sizeVecDyn
 *
 *  Description:
 *    Return size of memory entries allocated by the dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    int size
 */
int sizeVecDyn(VecDyn * vecDyn);


/*
 *  Function:
 *    sizeVecDyn
 *
 *  Description:
 *    Return size of memory entries allocated by the dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    int size
 */
int sizeVecDyn(VecDyn * vecDyn);


/*
 *  Function:
 *    occupancyVecDyn
 *
 *  Description:
 *    Retuns numbe of positions occupied in the dynamic table
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    number of occupied positions in the table
 */
int occupancyVecDyn(VecDyn * vecDyn);



/*
 *  Function:
 *    insertVecDyn
 *
 *  Description:
 *    Inserts an element in the dynamic table.
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn;
 *    Value to insert in table
 *      (int) val
 *
 *  Return value:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn;
 *    or NULL if the insertion failed
 *
 *  Note:
 *    Insert is in the first open position from 0.
 */
VecDyn *insertVecDyn(VecDyn * vecDyn, int val);


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
int getVecDynValue(VecDyn * vecDyn, int index);



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
void modifyVecDynValue(VecDyn * vecDyn, int idx, int val);



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
int maxVecDynValue(VecDyn * vecDyn);


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
int minVecDynValue(VecDyn * vecDyn);


/*
 *  Function:
 *    shiftLeftVecDynValue
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
VecDyn *shiftLeftVecDyn(VecDyn * vecDyn);



/*
 *  Function:
 *    shiftRightVecDynValue
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
VecDyn *shiftRightVecDyn(VecDyn * vecDyn, int value);



/*
 *  Function:
 *    printVecDyn
 *
 *  Description:
 *    Print the contents of a VecDyn vector
 *
 *  Arguments:
 *    Pointer to the dynamic table:
 *      (VecDyn *) vecDyn
 *
 *  Return value:
 *    0 in case of success, 1 in case of failure
 */
void printVecDyn(VecDyn * vecDyn);


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
void deleteVecDyn(VecDyn * vecDyn);


/* End of: Protect multiple inclusions                              */
#endif
