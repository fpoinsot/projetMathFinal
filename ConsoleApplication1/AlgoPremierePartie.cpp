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

void initZero (int* possible, int dimensionTabSudoku)
{
	for (int i=0; i<=dimensionTabSudoku; i++)
	{
		possible[i] = 0;
	}
}

void copieTableau(int* possible, int* newPossible, int dimensionTabSudoku)
{
	for (int i=0; i<=dimensionTabSudoku; i++)
	{
		possible[i] = newPossible[i];
	}
}

void combienPossible (int ligne, int colonne, sudoval*** Sudo3D, int* possible, int dimensionTabSudoku)
{
	int count = 0;
	int* newPossible = new int[dimensionTabSudoku+1];
	initZero(newPossible,dimensionTabSudoku);
	for(int i=0; i<(dimensionTabSudoku);i++)
	{
		for (int j=1; j<=possible[0];j++)
		{
			if (Sudo3D[ligne][colonne][i].val == possible[j] )
			{
				if (Sudo3D[ligne][colonne][i].possible == true)
				{
					count++;
					newPossible[count] = possible[j];
				}
			}
		}
	}
	newPossible[0] = count;
	initZero(possible,dimensionTabSudoku);
	copieTableau(possible,newPossible,dimensionTabSudoku);
	delete[] newPossible;
}

void remplirCase(Grille & cobaye, int degreTabSudoku)
{
	int dimensionTabSudoku = degreTabSudoku*degreTabSudoku;
	Grille* Sudoku = new Grille[degreTabSudoku];
	sudoval*** Sudo3D = new sudoval**[dimensionTabSudoku];
	for (int j = 0; j <dimensionTabSudoku;j++)
	{
		Sudo3D[j] = new sudoval*[dimensionTabSudoku];
		for ( int i = 0; i< dimensionTabSudoku;i++)
		{
			Sudo3D[j][i] = new sudoval[dimensionTabSudoku];
		}
	}
	int* possible = new int[dimensionTabSudoku+1]; //+1 car on a aussi le nombre de possibilités en plus compris dans la case 0
	int nb, valcase;

	//INITIALISATION DU TABLEAU SUDO3D
	for(int i=0; i<(dimensionTabSudoku);i++)
	{
		for(int j=0; j<(dimensionTabSudoku);j++)
		{
			for(int k=0; k<(dimensionTabSudoku);k++)
			{

				((Sudo3D[i])[j])[k].val = k+1;
				Sudo3D[i][j][k].possible = true;
			}
		}
	}

	for(int i=0; i<(dimensionTabSudoku); i++) //ligne
	{
		for(int j=0; j<dimensionTabSudoku; j++) //colonne
		{
			Sudoku->checkPossibilite(i,j,possible);
 
			for(int k=0; k<dimensionTabSudoku; k++) //création des résultats de sudo3D
			{
				bool present = false;
				for(int l=1; l<=possible[0] ; l++) //Vérification de si le chiffre est présent dans la liste des possibles
				{
					if(possible[l] == k+1) present = true; //Si il est présent il est indiqué comme bon 
				}
				if (present == false) Sudo3D[i][j][k].possible = false; //Si il n'est pas présent, ça deviens false. On ne fait pas l'inverse car sinon on aurait des problèmes lors des retours en arrière
			}
			combienPossible(i,j,Sudo3D,possible,dimensionTabSudoku);
			if(possible[0] != 0) //possible[0] indique le nombre de possibilités
			{
				nb = tirerUnIntEntre(1,possible[0]); //on cherche le nombre de case à avancer
				valcase = possible[nb];
				Sudoku->setValeurCase(i,j,valcase);
				int valeur = Sudoku->getValeurCase(i,j);
				Sudo3D[i][j][valcase-1].possible = false;
			}
			else 
			{
				Sudoku -> afficherGrille();
				for(int k=0; k<(dimensionTabSudoku); k++) //Réinitialisation de la case
				{
					Sudo3D[i][j][k].possible = true;
				}

				if (j==0) //Retour en arrière
				{
					i= i-1;
					j= dimensionTabSudoku - 2;
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

//detete[] sudo3D;