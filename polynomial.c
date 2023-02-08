#include <stdio.h>
#include <stdlib.h>
//#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON
//#include <math.h>

#include "linkedList.h"


/** TO DO
 * @brief compute 'in place' the derive of a polynomial 
 * @param [in, out] xxx address of a polynomial's head pointer
 */
void poly_derive(cell_t ** head)
{
	cell_t * current = *head;

    if (current->val.degree == 0)
    {
        LL_del_cell(head);
    }
    while (current != NULL)
    {
        current->val.coef *= current->val.degree;
        current->val.degree -= 1; 
        current = current->next;
    }
}

/** TO DO
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t ** P1, cell_t ** P2)
{
    int cmp = 0;
    double sumCoeff;
	cell_t * currentP1 = *P1;
    cell_t * currentP2 = *P2;

    monom_t newMonome = {0, 0};
    cell_t * newCell;


    while (currentP2 != NULL)
    {   
        // On se déplace dans P1, jusqu'à avoir un monôme de même degré ou supérieur au degré de currentP2
        while (currentP1 != NULL && (cmp = monom_degree_cmp(&currentP1->val, &currentP2->val)) < 0)
        {
            currentP1 = currentP1->next;
        }
        

        if (currentP1 != NULL && cmp == 0) 
        {
            // Si c'est le même degré
            sumCoeff = currentP1->val.coef + currentP2->val.coef;
            if (sumCoeff != 0)
            {
                // Si la somme des coefficients != 0
                currentP1->val.coef = sumCoeff;
                currentP1 = currentP1->next;
            }
            else
            {
                // Si la somme des coefficients = 0, il faut supprimer la case de P1
                LL_del_cell(LL_search_prev(P1, currentP1, monom_degree_cmp));
                currentP1 = currentP1->next;
            }
        }
        else
        {
            // Si le mônome de P2 a un degré différent absent de P1
            newMonome.coef = currentP2->val.coef;
            newMonome.degree = currentP2->val.degree;
            newCell = LL_create_cell(&newMonome);
            LL_add_cell(LL_search_prev(P1, newCell, monom_degree_cmp), newCell);
        }
        LL_del_cell(LL_search_prev(P2, currentP2, monom_degree_cmp));
        currentP2 = *P2;
    }
    *P2 = NULL;

}

/** TO DO
 * @brief compute P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */
cell_t* poly_prod(cell_t* poly1, cell_t* poly2)
{
    cell_t * head  = NULL;
    cell_t* current_on_1 = poly1;
    cell_t* current_on_2;
    cell_t * monom_cell;
    monom_t monom;
    
    int current_degree = 0;


    int stop = 0;

    
    while (!stop)
    {
        monom.degree = current_degree;
        monom.coef = 0.00;

        current_on_1 = poly1;
    
        while (current_on_1 != NULL && current_on_1->val.degree <= current_degree)
        {
            current_on_2 = poly2;

            while (current_on_2 != NULL && current_on_2->val.degree < current_degree - current_on_1->val.degree)
            {
                current_on_2 = current_on_2->next;
            }

            if (current_on_2 != NULL && current_on_2->val.degree + current_on_1->val.degree == current_degree)
            {
                monom.coef += current_on_1->val.coef * current_on_2->val.coef;
            }

            current_on_1 = current_on_1->next;
        }

        
        if (monom.coef != 0.0)
        {
            monom_cell = LL_create_cell(&monom);
            LL_add_cell(LL_search_prev(&head,monom_cell,monom_degree_cmp),monom_cell);
        }        

        current_degree += 1;
    

        stop = (current_on_1 == NULL && current_on_2 == NULL);
        
        
    }

    return head;
}
