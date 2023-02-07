/**
 * @file linkedList_main.c
 * @brief Programme pour les tests de fonctions de gestion de liste chainee
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(linkedList)


TEST(monom_degree_cmp) {
	monom_t v1 = {5.11, 7};
	monom_t v2 = {3., 5};
	monom_t v3 = {5.25, 7};

	printf("\nComparaison des monomes : \n");
	CHECK( monom_degree_cmp(&v1, &v2) > 0 );
	CHECK( monom_degree_cmp(&v2, &v1) < 0 );
	CHECK( monom_degree_cmp(&v1, &v3) == 0 );
}



TEST(monom_save2file) {
	monom_t v = {5., 7};

	// creation du flux de texte => buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &v);

	fclose(file);

	CHECK( 0 == strcmp(buffer, "5.000 7\n") ); 
}



TEST(LL_init_list) {
	cell_t *list; 

	printf("\nInitialization of the linked list : \n");
	LL_init_list(&list);

	REQUIRE ( list == NULL );
}


TEST(LL_create_cell) { // test de creation de cellule
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};

	printf("\nCreate a new cell (3.245 17) : \n");
	new = LL_create_cell(&m1);
	REQUIRE ( NULL != new );
	CHECK ( NULL == new->next );

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &(new->val));
	fclose(file);
	CHECK( 0 == strcmp(buffer, "3.245 17\n") ); 
}



// test d'insertion de cellule - liste a une cellule
TEST(LL_add_cell) { 
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};

	printf("\nAdd a cell in a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );

	LL_add_cell(&list, new);
	CHECK( list == new ); 

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	LL_save_list_toFile(list, file, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "3.245 17\n") ); 

	free(new); // liberer la liste
	list = NULL;
}



// test d'insertion de cellule - liste a n cellules
TEST(LL_add_celln) {

	cell_t *list = NULL;
	monom_t m1 = {3.0, 17};
	cell_t *cell1 = LL_create_cell(&m1);

	monom_t m2 = {2.0, 5};
	cell_t *cell2 = LL_create_cell(&m2);

	monom_t m3 = {4.0, 6};
	cell_t *cell3 = LL_create_cell(&m3);

	monom_t m4 = {8.0, 3};
	cell_t *cell4 = LL_create_cell(&m4);


	REQUIRE ( cell1 != NULL );

	LL_add_cell(&list, cell1);
	CHECK( list == cell1 ); 

	LL_add_cell(LL_search_prev(&list, cell2, monom_degree_cmp), cell2);
	LL_add_cell(LL_search_prev(&list, cell3, monom_degree_cmp), cell3);
	LL_add_cell(LL_search_prev(&list, cell4, monom_degree_cmp), cell4);


	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	LL_save_list_toFile(list, file, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "8.000 3\n2.000 5\n4.000 6\n3.000 17\n") ); 

	LL_free_list(&list); // liberer la liste
	list = NULL;
}

// test pour la creation d'un polynome a partir d'un fichier - exemple
TEST(LL_create_list_fromFileName0) {
	cell_t *list;

	printf("\nCreate a linked list from file name0: \n");

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );

	LL_create_list_fromFileName(&list, "notExist.txt");
	CHECK( NULL == list );

}



//test pour la creation d'un polynome a partir d'un fichier
TEST(LL_create_list_fromFileName) {
	cell_t *list;

	LL_create_list_fromFileName(&list, "toto.txt");

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	LL_save_list_toFile(list, file, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "5.678 3\n2.400 5\n5.000 8\n2.405 10\n") ); 

	LL_free_list(&list); // liberer la liste
	list = NULL;

}



TEST(LL_print_list) { // test pour l'affichage d'un polynome sur un flux de sortie
	cell_t *list;

	LL_create_list_fromFileName(&list, "toto.txt");

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	LL_print_list(file, list, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "5.678 3\n2.400 5\n5.000 8\n2.405 10\n") ); 

	LL_free_list(&list); // liberer la liste
	list = NULL;
}


TEST(LL_search_prev) { // test pour la fonction de recherche d'une valeur
	cell_t *list = NULL;
	monom_t m1 = {3.0, 17};
	cell_t *cell1 = LL_create_cell(&m1);

	monom_t m2 = {2.0, 5};
	cell_t *cell2 = LL_create_cell(&m2);

	monom_t m3 = {4.0, 6};
	cell_t *cell3 = LL_create_cell(&m3);

	monom_t m4 = {8.0, 3};
	cell_t *cell4 = LL_create_cell(&m4);

	cell_t **previous;


	REQUIRE ( cell1 != NULL );

	LL_add_cell(&list, cell1);
	CHECK( list == cell1 ); 

	LL_add_cell(LL_search_prev(&list, cell2, monom_degree_cmp), cell2);
	LL_add_cell(LL_search_prev(&list, cell3, monom_degree_cmp), cell3);
	LL_add_cell(LL_search_prev(&list, cell4, monom_degree_cmp), cell4);

	previous = LL_search_prev(&list, cell3, monom_degree_cmp);
	
	CHECK( (*previous) == cell3);
}


TEST(LL_del_cell) { // test de la suppression d'un element

	cell_t *list = NULL;
	monom_t m1 = {3.0, 17};
	cell_t *cell1 = LL_create_cell(&m1);

	monom_t m2 = {2.0, 5};
	cell_t *cell2 = LL_create_cell(&m2);

	monom_t m3 = {4.0, 6};
	cell_t *cell3 = LL_create_cell(&m3);

	monom_t m4 = {8.0, 3};
	cell_t *cell4 = LL_create_cell(&m4);

	cell_t **previous;


	REQUIRE ( cell1 != NULL );

	LL_add_cell(&list, cell1);
	CHECK( list == cell1 ); 

	LL_add_cell(LL_search_prev(&list, cell2, monom_degree_cmp), cell2);
	LL_add_cell(LL_search_prev(&list, cell3, monom_degree_cmp), cell3);
	LL_add_cell(LL_search_prev(&list, cell4, monom_degree_cmp), cell4);

	previous = LL_search_prev(&list, cell3, monom_degree_cmp);
	LL_del_cell(previous);


	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	LL_save_list_toFile(list, file, monom_save2file);
	fclose(file);
	LL_save_list_toFileName(list, "toto2.txt", monom_save2file);
	CHECK( 0 == strcmp(buffer, "8.000 3\n2.000 5\n3.000 17\n") ); 

	LL_free_list(&list); // liberer la liste
	list = NULL;
}


TEST(LL_free_list) { // test de la liberation de liste
	cell_t *list = NULL;

	monom_t m1 = {3.0, 17};
	cell_t *cell1 = LL_create_cell(&m1);

	monom_t m2 = {2.0, 5};
	cell_t *cell2 = LL_create_cell(&m2);

	monom_t m3 = {4.0, 6};
	cell_t *cell3 = LL_create_cell(&m3);

	monom_t m4 = {8.0, 3};
	cell_t *cell4 = LL_create_cell(&m4);



	REQUIRE ( cell1 != NULL );

	LL_add_cell(&list, cell1);
	CHECK( list == cell1 ); 

	LL_add_cell(LL_search_prev(&list, cell2, monom_degree_cmp), cell2);
	LL_add_cell(LL_search_prev(&list, cell3, monom_degree_cmp), cell3);
	LL_add_cell(LL_search_prev(&list, cell4, monom_degree_cmp), cell4);


	LL_free_list(&list); // liberer la liste
	CHECK( list == NULL);
}


END_TEST_GROUP(linkedList)

int main(void) {
	RUN_TEST_GROUP(linkedList);
	return EXIT_SUCCESS;
}
