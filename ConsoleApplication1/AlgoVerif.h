#pragma once
#include "CaseGrille.h"
#include "Grille.h"
#include "GestionRandom.h"
#include <string>

struct sudoval;

void initZeroVerif (int* possible, int dimensionTabSudoku);
void copieTableauVerif(int* possible, int* newPossible, int dimensionTabSudoku);
void combienPossibleVerif (int ligne, int colonne, sudoval*** Sudo3D, int* possible, int dimensionTabSudoku);
void resolution (Grille * cobaye, bool correct , bool unique);