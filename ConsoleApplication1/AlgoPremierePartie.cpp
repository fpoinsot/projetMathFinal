#include "stdafx.h"
#include "AlgoPremierePartie.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>



void remplirCase(Grille & cobaye, int dimensionTabSudoku)
{
	Grille* Sudoku = new Grille[dimensionTabSudoku];
	CaseGrille* CaseSudo;
	int* possible = new int[dimensionTabSudoku+1]; //+1 car on a aussi le nombre de possibilités en plus compris dans la case 0
	int nb, valcase;
	for(int i=0; i<(dimensionTabSudoku); i++) //ligne
	{
		for(int j=0; i<dimensionTabSudoku; j++) //colonne
		{
			Sudoku->checkPossibilite(i,j,possible);
			if(possible[0] != 0) //possible[0] indique le nombre de possibilités
			{
				nb = tirerUnIntEntre(1,possible[0]); //on cherche le nombre de case à avancer
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