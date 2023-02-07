/**
 * @file linkedList.h
 * @brief Header file of linked list module
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "valCell.h"

/** TO DO
 * @struct cell_t
 * @brief Data structure of the linked list's cell
 * 2 fields :
 *      - 'val' : value of a cell
 *      - 'next' : pointer to the next cell
 */

typedef struct cell_t
{
    monom_t  val;
    struct cell_t * next;
} cell_t;


/** Example
 * @fn void LL_init_list(cell_t **adrHeadPt)
 * @brief Initialize a void list
 * @param [in, out] adrHeadPt address of head pointer of the list 
 */
void LL_init_list(cell_t **adrHeadPt);

/** TO DO
 * @brief create a new cell for linked list from its data 
 * @param [in] xxx address of the data
 * @return address of the new cell
 */
 
 cell_t* LL_create_cell(monom_t* );

/** TO DO
 * @brief Insert a cell into a linked list at the given position
 * @param [in, out]  xxx address of previous pointer of the cell
 * @param [in]  xxx address of the cell to be added to the linked list
 */
 
 void LL_add_cell(cell_t ** , cell_t *);

/** TO DO
 * @brief Create a linked list from a file
 * @param [in, out] xxx address of head pointer of a linked list
 * @param [in] xxx name of a file containing the data for a linked list
 * @param xxx fonction pointer for comparison of two cell's value
 * @return head pointer of the linked list
 */
cell_t ** LL_create_list_fromFileName(cell_t ** , char * , int (*)(monom_t*, monom_t*));

/**
 * @brief Print/Write the linked list on/to an output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx head pointeur of a linked list
 * @param xxx fonction pointer for printing the data of a cell on an output stream
 */
void LL_print_list(FILE* , cell_t*, void (*)(FILE*, cell_t*));


/**
 *  @brief Save a linked list into an ouptput stream
 *  @param [in] xxx head pointer of a linked list
 *  @param [in] xxx file pointeur of an output stream
 *  @param xxx fonction pointeur for saving the data of a cell on an output stream
*/

void LL_save_list_toFile(cell_t*, FILE *, void(*)(FILE*, monom_t*));

/** TO DO
 * @brief Save a linked list into a file
 * @param [in, out] xxx head pointer of a linked list
 * @param [in] xxx name of the backup file
 * @param xxx fonction pointer for writing the data of a cell to a output stream
 */
 
 void LL_save_list_toFileName(cell_t* , char *, void (*)(FILE *, monom_t*));

/** TO DO
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] xxx address of the head pointer
 * @param [in] xxx address of the value to search
 * @param  xxx fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */

cell_t** LL_search_prev(cell_t ** , cell_t* , int (*)(monom_t* , monom_t*));

/** TO DO
 * @brief Delete a cell from a linked list
 * @param [in, out] xxx address of the previous pointer of the cell to delete
 */
void LL_del_cell(cell_t** previous);


/** TO DO
 * @brief Free the memory location occupied by the cells of a linked list
 * @param [in, out] xxx address of head pointer of a linked list
 */
void LL_free_list(cell_t**);


#endif