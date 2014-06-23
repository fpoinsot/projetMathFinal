#pragma once
#include "CaseGrille.h"
#include "Grille.h"
#include "GestionRandom.h"
#include <string>

struct sudoval;

void initZero (int* possible, int dimensionTabSudoku);
void copieTableau(int* possible, int* newPossible, int dimensionTabSudoku);
void combienPossible (int ligne, int colonne, sudoval*** Sudo3D, int* possible, int dimensionTabSudoku);
void remplirCase(Grille & cobaye, int dimensionTabSudoku);