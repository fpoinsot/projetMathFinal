// ConsoleApplication1.cpp�: d�finit le point d'entr�e pour l'application console.
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
#include <chrono>

int _tmain(int argc, _TCHAR* argv[])
{
	initialiserRand();

	Grille* GrilleTest = creerGrilleTest();
	GrilleTest->afficherGrille();
	std::string arret;

	gommerGrille(*GrilleTest,"normal");
	GrilleTest->afficherGrille();
	std::cin>> arret;
	return 0;
}



