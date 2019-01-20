
#include <iostream>
using namespace std;

#include <conio.h>	// pour _kbhit() et _getch()
#include <time.h>	// pour time(int)
#include <stdlib.h>	// pour srand(int) et rand()
#include "DeclarationFonctions.h" // Declarations des fonctions
#include "RockUtiles.h"	// pour la gestion de l'écran

//Déclaration des constantes
const short laCouleur = 4;
const int DROITE = 0;
const int GAUCHE = 1;
const int HAUT = 2;
const int BAS = 3;
const int nbLignes = 30, nbColonnes = 70;
const int departX = 0, departY = 0;

int sourisX[10] = {}, sourisY[10] = {};
int serpentX[10] = {}, serpentY[10] = {};

//  Fonction principale
//  -------------------
int main()
{
	//Déclaration des variables
	int posX = 0, posY = 0, direction;
	int sourisX[10];
	int sourisY[10];
	int serpentX[10];
	int serpentY[10];
	int tailleSerpent = 1;

	bool over = false;
	bool collision = false;
	bool enPlus = true;

	do {
		int nbSouris = saisirNiveau();
		Sleep(2000);
		system("CLS");
		afficherTerrain(nbLignes, nbColonnes);
		positionAleatoire(nbLignes, nbColonnes, posX, posY);
		serpentX[0] = posX;
		serpentY[0] = posY;

		for (int i = 1; i < tailleSerpent - 1; i++) {
			serpentX[i] = --posX;
			serpentY[i] = posY;
			gotoXY(serpentX[i], serpentY[i]);
		}

		serpentX[tailleSerpent - 1] = --posX;
		serpentY[tailleSerpent - 1] = posY;

		creerSouris(nbLignes, nbColonnes, sourisX, sourisY, nbSouris);
		direction = calculerDirectionTouche(recupererTouche());

		bool over = false;
		int compteur = 0;
		while (over == false) {
			int test = direction;
			deplacerSerpentI(direction, posX, posY); 
			gotoXY(serpentX[tailleSerpent - 2], serpentY[tailleSerpent - 2]);
			cout << " ";
			serpentX[tailleSerpent - 1] = serpentX[tailleSerpent - 2];
			serpentY[tailleSerpent - 1] = serpentY[tailleSerpent - 2];

			for (int i = tailleSerpent - 2; i > 0; i--) {
				serpentX[i] = serpentX[i - 1];
				serpentY[i] = serpentY[i - 1];
				gotoXY(serpentX[i], serpentY[i]);
				cout << "$";
			}
			serpentX[0] = posX;
			serpentY[0] = posY;

			deplacerSerpentII(direction, serpentX, serpentY, tailleSerpent, sourisX, sourisY, nbSouris);

			if (_kbhit())
				direction = calculerDirectionTouche(recupererTouche());
			if (direction == -1)
				direction = test;

			Sleep(150);

			if (posX == 0 || posX == nbColonnes || posY == nbLignes || posY == 0)
				over = true;
		}

		char rep;
		gotoXY(20, 15);
		cout << "        GAME OVER        " << endl;
		
	} while (enPlus == true);

}



// ************
// * PARTIE I *
// ************
void afficherTerrain(int nbLignes, int nbColonnes)
{
	setDimensionFenetre(150, 150, 150, 150);
	cadre(departX, departY, (departX + nbColonnes), (departY + nbLignes), laCouleur);
	curseurVisible(false);
}

int recupererTouche()
{
	int touche = -1;

	if (_kbhit != NULL) {
		touche = toupper(_getch());
	}
	return touche;
}

int calculerDirectionTouche(int touche)
{
	int direction;

	switch(touche) {
	case 'D':
		direction = DROITE;
		break;
	case 'A':
		direction = GAUCHE;
		break; 
	case 'W':
		direction = HAUT;
		break;
	case 'S':
		direction = BAS;
		break;
	default:
		direction = -1;
		break;
	}
	return direction;
}

void positionAleatoire(int nbLignes, int nbColonnes, int &posX, int &posY)
{
	posX = rand() % (nbColonnes - departX + 1) + departX;
	posY = rand() % (nbLignes - departY + 1) + departY;

	gotoXY(posX, posY);
	cout << "$"; // CREATION DU SERPENT
}

void deplacerSerpentI(int direction, int &posX, int &posY)
{
	gotoXY(posX, posY);
	cout << "";

	switch (direction) {
	case DROITE:
		posX += 1;
		break;
	case GAUCHE:
		posX -= 1;
		break;
	case HAUT:
		posY -= 1;
		break;
	case BAS:
		posY += 1;
		break;
	
	}
	gotoXY(posX, posY);
	cout << "$";
}


// *************
// * PARTIE II *
// *************
int saisirNiveau()
{
	int saisirNiveau, nbSouris;
	bool ex = false;

	cout << " !!!!!!MENU DU JEU SNAKE ****>> !!!!!! " << endl;

	cout << endl;
	cout << endl;

	cout << " ****** NIVEAU 1 // 1 ****** " << endl;
	cout << " ****** NIVEAU 2 // 2 ****** " << endl;
	cout << " ****** NIVEAU 3 // 3 ****** " << endl;
	cout << " ****** NIVEAU 4 // 4 ****** " << endl;
	cout << " ****** NIVEAU 5 // 5 ****** " << endl;

	cout << endl; 
	cout << endl;


	do {
		cout << "  Saisir un niveau du jeu :) : ";
		cin >> saisirNiveau;

		if (cin.fail() || cin.peek() != '\n') {
			cout << "  Ce niveau n'est pas dans le menu" << endl;
			cin.clear();
			cin.ignore(512, '\n');
		
		} else if ((saisirNiveau != 1) && (saisirNiveau != 2) && (saisirNiveau != 3) && (saisirNiveau != 4) && (saisirNiveau != 5)) {
			cout << "Choisir un niveau qui est dans le menu :-) : " << endl;

		} else {
			ex = true;
		}

	} while (!ex);

	if (saisirNiveau == 1) {
		nbSouris = 4;

	} else if (saisirNiveau == 2) {
		nbSouris = 6;

	} else if (saisirNiveau == 3){
		nbSouris = 8;

	} else if (saisirNiveau == 4) {
		nbSouris = 16;

	} else {
		nbSouris = 24;
	}

	return nbSouris;

}

void creerSouris(int nbLignes, int nbColonnes,
	int sourisX[], int sourisY[], int nbSouris)
{
	srand((unsigned int)time(0));

	//LIGNES
	for (int i = 0; i < nbSouris; i++) {
		int posY = rand() % ((nbLignes - 4) - departY + 1) + departY;
		sourisX[i] = posY;
	}

	//COLONNES
	for (int i = 0; i < nbSouris; i++) {
		int posX = rand() % ((nbColonnes - 4) - departX + 5) + departX;
		sourisY[i] = posX;
	}

	for (int i = 0; i < nbSouris; i++) {
		gotoXY(sourisY[i], sourisX[i]);
		cout << "x";
	}
}

void afficherSouris(int sourisX[], int sourisY[], int nbSouris)
{
	creerSouris(nbLignes, nbColonnes, sourisX, sourisY, nbSouris);

	//CREATION DE LA SOURIS 
	for (int i = 0; i < nbSouris; i++) {
		gotoXY(sourisY[i], sourisX[i]);
		cout << "x";
	}
}

void deplacerSerpentII(int direction, int serpentX[], int serpentY[],
	int &tailleSerpent,
	int sourisX[], int sourisY[], int &nbSouris)
{
	bool collision = false;
	collision = testerCollision(serpentX[0], serpentY[0], sourisX, sourisY, nbSouris); //Appel la fonction de test de collusion 

	if (collision) {

		gotoXY(serpentX[tailleSerpent - 1], serpentY[tailleSerpent - 1]);
		cout << "$";
		sourisX[serpentX[0]] = sourisX[nbSouris - 1];
		sourisX[serpentY[0]] = sourisY[nbSouris - 1];
		nbSouris--;
		tailleSerpent++;
	}
}

bool testerCollision(int posX, int posY,
	int sourisX[], int sourisY[], int &nbSouris)
{
	bool testCol = false;

	for (int i = 0; i < nbSouris; i++) {

		if ((posX == sourisX[i]) && (posY == sourisY[i])) {

			testCol = true;
		}
	}
	return testCol;
}







