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

	cobaye.afficherGrille();
}

void gommerGrille(Grille & cobaye ,std::string difficulte)
{
	if(difficulte == "normal")
	{
		cacherNormal(cobaye);
	}
	else std::cout << " cette option n est pas disponible";
}