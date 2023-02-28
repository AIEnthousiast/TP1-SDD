#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

// #include "linkedList.h"

/** 
 * @brief compute 'in place' the derive of a polynomial
 * @param [in, out] xxx address of a polynomial's head pointer
 */
void poly_derive(cell_t ** head);

/** 
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t ** P1, cell_t ** P2);

/** 
 * @brief P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */

cell_t* poly_prod(cell_t* poly1, cell_t* poly2);

#endif