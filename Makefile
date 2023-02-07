# Ce makefile est pour l'ensemble du TP
#
# Deux fichiers main se trouvent dans ce dossier :
#   - linkedList_main.c pour les tests relatifs a la liste chainee
#   - polynomial_main.c pour les tests relatifs aux operations des polynomes
#
# Utiliser la commande 'make linkedList' pour compiler les operations liees a la liste chainee
# et la commande 'make polynomial' pour les operations liees aux polynomes
#

CC = gcc               # choix du compilateur
CFLAGS = -Wall -Wextra # options de compilation
LDFLAGS =              # options de l'edition de lien

#liste des fichiers source et objet communs
SRC_COMMUN = teZZ.c linkedList.c valCell.c
OBJ_COMMUN = linkedList.o valCell.o teZZt.o

#liste des fichiers .c et .h pour la liste chainee
SRC_LL = linkedList_main.c $(SRC_COMMUN)
HEADERS_LL = teZZt.h linkedList.h valCell.h
#liste des fichiers objets pour la liste chainee
OBJ_LL = linkedList_main.o $(OBJ_COMMUN)

#liste des fichiers .c et .h pour les operations des polynomes
SRC_POLY = polynomial_main.c polynomial.c $(SRC_COMMUN)
HEADERS_POLY = $(HEADERS_LL) polynomial.h
#liste des fichiers objets pour les operations des polynomes
OBJ_POLY = $(OBJ_COMMUN) polynomial.o polynomial_main.o

#all : polynomial linkedList

polynomial: $(OBJ_POLY) $(HEADERS_POLY)
	$(CC) $(OBJ_POLY) -o $@ $(LDFLAGS)

linkedList: $(OBJ_LL) $(HEADERS_LL)
	$(CC) $(OBJ_LL) -o $@ $(LDFLAGS)

polynomial_main.o: polynomial_main.c $(HEADERS_POLY)
	$(CC) $(CFLAGS) -o $@ -c $<

linkedList_main.o: linkedList_main.c $(HEADERS_LL)
	$(CC) $(CFLAGS) -o $@ -c $<

linkedList.o: linkedList.c linkedList.h valCell.h
	$(CC) $(CFLAGS) -o $@ -c $<

valCell.o: valCell.c valCell.h
	$(CC) $(CFLAGS) -o $@ -c $<

polynomial.o: polynomial.c $(HEADERS_POLY)
	$(CC) $(CFLAGS) -o $@ -c $<

teZZt.o: teZZt.c teZZt.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean reclean

clean:
	rm -f $(OBJ_POLY)

reclean:
	rm -f $(OBJ_POLY) linkedList_main.o linkedList polynomial
