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
*/



TEST(Poly_addition) { // test sur l'addition de deux polymones
	cell_t *P1 = NULL;
	char   buffer[1024];
	FILE *file;

	monom_t m1 = {8.0, 3};
	cell_t *cellP1_1 = LL_create_cell(&m1);
	monom_t m2 = {2.0, 5};
	cell_t *cellP1_2 = LL_create_cell(&m2);
	monom_t m3 = {4.0, 6};
	cell_t *cellP1_3 = LL_create_cell(&m3);
	monom_t m4 = {3.0, 17};
	cell_t *cellP1_4 = LL_create_cell(&m4);

	LL_add_cell(&P1, cellP1_1);
	LL_add_cell(LL_search_prev(&P1, cellP1_2, monom_degree_cmp), cellP1_2);
	LL_add_cell(LL_search_prev(&P1, cellP1_3, monom_degree_cmp), cellP1_3);
	LL_add_cell(LL_search_prev(&P1, cellP1_4, monom_degree_cmp), cellP1_4);


	cell_t *P2 = NULL;
	monom_t m1_2 = {4.0, 2};
	cell_t *cellP2_1 = LL_create_cell(&m1_2);
	monom_t m2_2 = {-2.0, 5};
	cell_t *cellP2_2 = LL_create_cell(&m2_2);
	monom_t m3_2 = {4.5, 6};
	cell_t *cellP2_3 = LL_create_cell(&m3_2);
	monom_t m4_2 = {-4.0, 17};
	cell_t *cellP2_4 = LL_create_cell(&m4_2);
	monom_t m5_2 = {5.0, 22};
	cell_t *cellP2_5 = LL_create_cell(&m5_2);

	LL_add_cell(&P2, cellP2_1);
	LL_add_cell(LL_search_prev(&P2, cellP2_2, monom_degree_cmp), cellP2_2);
	LL_add_cell(LL_search_prev(&P2, cellP2_3, monom_degree_cmp), cellP2_3);
	LL_add_cell(LL_search_prev(&P2, cellP2_4, monom_degree_cmp), cellP2_4);
	LL_add_cell(LL_search_prev(&P2, cellP2_5, monom_degree_cmp), cellP2_5);

	// Résultat: "4.000 2\n8.000 3\n8.500 6\n-1.000 17\n5.000 22\n"
	poly_add(&P1, &P2);

	
	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	LL_print_list(file, P1, monom_print);
	fclose(file);


	CHECK(0 == strcmp(buffer, "(4.00, 2) (8.00, 3) (8.50, 6) (-1.00, 17) (5.00, 22) "));


	//Vérifier que P2 est bien un pointeur vide.
	CHECK(P2 == NULL);

	LL_free_list(&P1);
	LL_free_list(&P2);

}


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
