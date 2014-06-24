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
#include <fstream>

int _tmain(int argc, _TCHAR* argv[])
{
	initialiserRand();
	std::ofstream myfile;
	myfile.open ("sortie.txt", std::ios::out);
	myfile << "";
	myfile.close();

	Grille* GrilleTest = new Grille(3);
	remplirCase(GrilleTest,3);
	std::string arret;

	std::cout << "grille complete" << std::endl;
	GrilleTest->afficherGrille();
	gommerGrille(*GrilleTest,"normal");
	GrilleTest->afficherGrille();
	

	bool unique = true;
	bool correct = true;
	resolution(GrilleTest, correct, unique);
	std::cin>> arret;
	return 0;
}



