#include "stdafx.h"
#include "AlgoVerif.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>

struct sudoval
{
	int val;
	bool possible;
};


bool retourArriere (int* i, int* j, Grille* Sudoku, bool** original)
{
	int dimensionTabSudoku = Sudoku -> dimensionTabSudoku;
	if(*i==0 && *j==0)
	{
		return false;
	}
	else
	{
		if (*j==0) //Retour en arrière
		{
			*i= *i-1;
			*j= dimensionTabSudoku - 1;
		}
		else
		{
			*j= *j - 1;
		}

		if(original[*i][*j] == true)
		{
			return retourArriere (i,j,Sudoku,original);
		}
		else
		{
			return true;
		}
	}
}

void initZeroVerif (int* possible, int dimensionTabSudoku)
{
	for (int i=0; i<=dimensionTabSudoku; i++)
	{
		possible[i] = 0;
	}
}

void copieTableauVerif(int* possible, int* newPossible, int dimensionTabSudoku)
{
	for (int i=0; i<=dimensionTabSudoku; i++)
	{
		possible[i] = newPossible[i];
	}
}

void combienPossibleVerif (int ligne, int colonne, sudoval*** Sudo3D, int* possible, int dimensionTabSudoku)
{
	int count = 0;
	int* newPossible = new int[dimensionTabSudoku+1];
	initZeroVerif(newPossible,dimensionTabSudoku);
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
	initZeroVerif(possible,dimensionTabSudoku);
	copieTableauVerif(possible,newPossible,dimensionTabSudoku);
	delete[] newPossible;
}


bool verifResteDesTrucs (sudoval*** Sudo3D, int dimensionTabSudoku)
{
	bool reste = false;
	for(int i=0; i<dimensionTabSudoku; i++)
	{
		for(int j=0; j<dimensionTabSudoku; j++)
		{
			for(int k=0; k<dimensionTabSudoku; k++)
			{
				if(Sudo3D[i][j][k].possible == true)
				{
					reste = true;
				}
			}
		}
	}

	return reste;
}


void resolution (Grille * cobaye, bool correct , bool unique)
{

	Grille* Sudoku = cobaye;
	int dimensionTabSudoku = Sudoku -> dimensionTabSudoku;
	sudoval*** Sudo3D = new sudoval**[dimensionTabSudoku];
	for (int j = 0; j <dimensionTabSudoku;j++)
	{
		Sudo3D[j] = new sudoval*[dimensionTabSudoku];
		for ( int i = 0; i< dimensionTabSudoku;i++)
		{
			Sudo3D[j][i] = new sudoval[dimensionTabSudoku];
		}
	}

	bool** original = new bool*[dimensionTabSudoku];
	for (int i=0; i<dimensionTabSudoku;i++)
	{
		original[i] = new bool[dimensionTabSudoku];
	}

	int nombrepossible = 0;

	//INITIALISATION DU TABLEAU SUDO3D
	for(int i=0; i<(dimensionTabSudoku);i++)
	{
		for(int j=0; j<(dimensionTabSudoku);j++)
		{
			for(int k=0; k<(dimensionTabSudoku);k++)
			{

				((Sudo3D[i])[j])[k].val = k+1;
				if (Sudoku -> getCase(i,j).getAffichee() == true)
				{
					Sudo3D[i][j][k].possible = false;
					original[i][j] = true;
				}
				else
				{
					Sudo3D[i][j][k].possible = true;
					original[i][j] = false;
				}
			}
		}
	}

	int* possible = new int[dimensionTabSudoku+1]; //+1 car on a aussi le nombre de possibilités en plus compris dans la case 0
	int nb, valcase;
	bool restedestrucs = true;

	for(int i=0; i<(dimensionTabSudoku); i++) //ligne
	{
		for(int j=0; j<dimensionTabSudoku; j++) //colonne
		{

			if(original[i][j] == false) //on saute les valeurs "originales" elles ne seront jamais touchées.
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
				combienPossibleVerif(i,j,Sudo3D,possible,dimensionTabSudoku);
				if(possible[0] != 0) //possible[0] indique le nombre de possibilités
				{
					nb = tirerUnIntEntre(1,possible[0]); //on cherche le nombre de case à avancer
					valcase = possible[nb];
					Sudoku->setValeurCase(i,j,valcase);
					Sudoku->faireApparaitreCase(i,j);
					int valeur = Sudoku->getValeurCase(i,j);
					Sudo3D[i][j][valcase-1].possible = false;
					Sudoku -> afficherGrille();
				}
				else 
				{
				
					for(int k=0; k<(dimensionTabSudoku); k++) //Réinitialisation de la case
					{
						Sudo3D[i][j][k].possible = true;
						Sudoku -> gommerCase (i,j);
					}

					retourArriere(&i,&j,Sudoku,original);
					if (j==0) //Retour en arrière
					{
						i= i-1;
						j= dimensionTabSudoku - 1;
					}
					else
					{
						j = j - 1;
					}
				}
			}
			if ((i == (dimensionTabSudoku-1)) && (j == (dimensionTabSudoku - 1)))
			{
				nombrepossible = nombrepossible+1;
				for(int k=0; k<(dimensionTabSudoku); k++) //Réinitialisation de la case
				{
					Sudo3D[i][j][k].possible = true;
					Sudoku -> gommerCase (i,j);
				}
				j = j - 2;
			}
		}
	}

	if (nombrepossible==0)
	{
		correct = false;
		unique = false;
	}
	else if (nombrepossible==1)
	{
		correct = true;
		unique = true;
	}
	else if (nombrepossible>1)
	{
		correct = true;
		unique = false;
	}

	std::cout << " correct : " << correct << " unique : " << unique   << std::endl;
}