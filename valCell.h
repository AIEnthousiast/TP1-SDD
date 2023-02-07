/**
 * @file valCell.h
 * @brief relative to the value of linked list's cells
 */

#ifndef __VALCELL_H__
#define __VALCELL_H__


#include <stdio.h>
#include <stdio.h>

/** TO DO
 * @struct monom_t 
 * @brief Data structure of monomial (value of linked list's cell)
 * 2 fields :
 * 		- 'coef' : double precision real  
 * 		- 'degree' : integer
 */

typedef struct monom_t
{
    double coef;
    int degree;
} monom_t;


/** TO DO
 * @brief Compare the degree of two monomials
 * @param [in] xxx address of the first monomial
 * @param [in] xxx address of the second monomial
 * @return <0 if m1.degree<m2.degree; =0 if m1.degree=m2.degree;  >0 if m1.degree>m2.degree
 */
// monom_degree_cmp();


int monom_degree_cmp(monom_t* , monom_t*);

/** TO DO
 * @brief write the information of a monomial to the given output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx address of a monomial
 */
// monom_save2file();

void monom_save2file(FILE* , monom_t*);


/**
 * @brief print in an human readable fashion the given monom_t
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx adress of a monomial
 * 
*/


void monom_print(FILE* , monom_t* );

#endif