// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//
#include "CaseGrille.h"
#include "Grille.h"
#include "GestionRandom.h"
#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include "AlgoDeuxiemePartie.h"
#include "AlgoPremierePartie.h"
#include "AlgoVerif.h"
#include <chrono>

int _tmain(int argc, _TCHAR* argv[])
{
	initialiserRand();

	Grille* GrilleTest = new Grille(3);
	remplirCase(GrilleTest,3);
	std::string arret;

	std::cout << "grille complete" << std::endl;
	GrilleTest->afficherGrille();
	gommerGrille(*GrilleTest,"normal");
	GrilleTest->afficherGrille();
	std::cin>> arret;

	bool unique;
	bool correct;
	resolution(GrilleTest, correct, unique);
	return 0;
}



