#include "stdafx.h"
#include "AlgoDeuxiemePartie.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>


void cacherNormal(Grille & cobaye)
{
	CaseGrille * caseG;
	do{
		caseG = cobaye.tirerCaseDegree(0);
		if ( caseG != NULL){
			int ligne = caseG->getLigne();
			int colonne = caseG->getColonne();
			cobaye.cacherCase(ligne,colonne);
		}
	}while(caseG != NULL);
}

void gommerGrille(Grille & cobaye ,std::string difficulte)
{
	if(difficulte == "normal")
	{
		cacherNormal(cobaye);
	}
	else std::cout << " cette option n est pas disponible";
}

Grille* creerGrilleTest()
{
	Grille* GrilleTest = new Grille(3);
	int tabValeur[81] ={2,7,3,4,5,6,9,8,1,9,4,5,1,2,8,7,6,3,1,6,8,9,3,7,4,5,2,3,5,1,2,7,9,8,4,6,6,2,9,8,4,1,3,7,5,4,8,7,3,6,5,2,1,9,8,3,6,7,1,2,5,9,4,7,1,2,5,9,4,6,3,8,5,9,4,6,8,3,1,2,7};
	GrilleTest->setValeurTableau(tabValeur);
	return GrilleTest;
}