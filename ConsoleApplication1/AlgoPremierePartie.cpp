#include "stdafx.h"
#include "AlgoPremierePartie.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>

struct sudoval
{
	int val;
	bool possible;
};

void remplirCase(Grille & cobaye, int dimensionTabSudoku)
{

	Grille* Sudoku = new Grille[dimensionTabSudoku];
	sudoval* Sudo3D = new sudoval[dimensionTabSudoku][dimensionTabSudoku][dimensionTabSudoku];
	int* possible = new int[dimensionTabSudoku+1]; //+1 car on a aussi le nombre de possibilit�s en plus compris dans la case 0
	int nb, valcase;
	for(int i=0; i<(dimensionTabSudoku); i++) //ligne
	{
		for(int j=0; i<dimensionTabSudoku; j++) //colonne
		{
			Sudoku->checkPossibilite(i,j,possible);
			if(possible[0] != 0) //possible[0] indique le nombre de possibilit�s
			{
				for(int k=0; k<dimensionTabSudoku; k++) //cr�ation des r�sultats de sudo3D
				{
					Sudo3D[i][j][k].val = k+1;
					bool present = false;
					for(int l=1; l<=possible[0] ; l++) //V�rification de si le chiffre est pr�sent dans la liste des possibles
					{
						if(possible[l] == k+1) present = true; //Si il est pr�sent il est indiqu� comme bon 
					}
					Sudo3D[i][j][k].possible = present;
				}
				nb = tirerUnIntEntre(1,possible[0]); //on cherche le nombre de case � avancer
				valcase = possible[nb];
				Sudoku->setValeurCase(i,j,valcase);
			}
			else
			{
				if (j==0) 
				{
					i= i-1;
					j= dimensionTabSudoku - 1;
				}
				else
				{
					j= j - 2;
				}
			}
		}
	}
	Sudoku -> afficherGrille();
}

