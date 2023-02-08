/**
 * @file polynomial_main.c
 * @brief Programme pour les tests des operations sur les polynomes
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "polynomial.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(polynomial)

TEST(LL_init_list) {
	cell_t *list;

	printf("\nInitialization of the linked list : \n");
	LL_init_list(&list);

	REQUIRE ( list == NULL );
}


TEST(Poly_derive1) {  // exemple  // Réviser le code
	cell_t *poly = NULL;
	FILE   *file = NULL;
	char   buffer[1024];

	printf("\nDerive of polynomial 1 : \n");

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	LL_create_list_fromFileName(&poly, "poly1.txt");
	LL_print_list(file, poly, monom_print);
	fclose(file);
	LL_print_list(stdout, poly, monom_print);
	printf("\n");
	CHECK( 0 == strcmp(buffer, "(5.00, 1) (4.00, 2) (5.00, 3) (6.00, 4) (3.00, 5) ") );

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	poly_derive(&poly);
	LL_print_list(file, poly, monom_print);
	fclose(file);
	// LL_print_list(stdout, poly, monom_print);
	// printf("\n");
	CHECK( 0 == strcmp(buffer, "(5.00, 0) (8.00, 1) (15.00, 2) (24.00, 3) (15.00, 4) ") );
	LL_free_list(&poly);
}
/*

TEST(Poly_derive) { // test sur la derivation d'un polynome
	cell_t *list;

	//TO DO
}


TEST(Poly_addition) { // test sur l'addition de deux polymones
	cell_t *list;

	//TO DO
}
*/

TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
	cell_t * prod;

	cell_t * poly1 = NULL;
	cell_t * poly2 = NULL;
	FILE * file = NULL;

	char buffer[1024];

	file = fmemopen(buffer, 1024, "w");
	REQUIRE(NULL != file);

	LL_create_list_fromFileName(&poly1,"poly1.txt");
	REQUIRE(NULL != poly1);

	LL_create_list_fromFileName(&poly2,"poly2.txt");
	REQUIRE(NULL != poly2);

	
	prod = poly_prod(poly1,poly2);

	REQUIRE(NULL != prod);

	LL_print_list(file,prod,monom_print);

	fclose(file);

	LL_save_list_toFileName(prod,"prod12.txt",monom_print);


	LL_free_list(&poly1);
	LL_free_list(&poly2);
	LL_free_list(&prod);

}


/*

TEST(LL_save_list_toFileName) { // test pour l'ecriture d'un polynome dans un fichier
	cell_t *list;

	//TO DO
}
*/

END_TEST_GROUP(polynomial)

int main(void) {
	RUN_TEST_GROUP(polynomial);
	return EXIT_SUCCESS;
}
