#include "stdafx.h"
#include "Grille.h"
#include <iostream>
#include <random>
#include "GestionRandom.h"

Grille::Grille(int paramDegre) : degre(paramDegre), dimensionTabSudoku(paramDegre*paramDegre), nombreCaseAfficheeEtRemplie(0),nombreCaseRemplie(0)
{
	if(paramDegre > 0)
	{
		tabSudoku = new CaseGrille[dimensionTabSudoku*dimensionTabSudoku];

		//initialiser tout les degre de libertée des case au maximum = (degré de la grille)²
		for(int i = 0; i<dimensionTabSudoku;i++)
		{
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				CaseGrille & cursor = getCase(i,j);
				cursor.degreLibertee=0;
				cursor.ligne=i;
				cursor.colonne=j;
			}
		}

	}
}


Grille::~Grille(void)
{
	delete[] tabSudoku;
}

CaseGrille & Grille::getCase(int ligne, int colonne)
{
	CaseGrille & caseSelect = tabSudoku[ligne*dimensionTabSudoku + colonne];
	return caseSelect;
}

bool Grille::setValeurCase(int ligne, int colonne, int valeur)
{
	//verifier valeurs

	for(int i = 0; i<dimensionTabSudoku; i++)
	{
		CaseGrille & cursor = getCase( ligne , i);
		if( cursor.remplie == true && cursor.valeur == valeur) return false;
	}
	for(int i = 0; i<dimensionTabSudoku; i++)
	{
		CaseGrille & cursor = getCase( i, colonne);
		if( cursor.remplie == true && cursor.valeur == valeur) return false;
	}

	//tout est bon
	if( !getCase(ligne, colonne).remplie)
	{
		nombreCaseRemplie ++;
		nombreCaseAfficheeEtRemplie++;
	}
	getCase(ligne, colonne).setValeur(valeur);
	
	return true;
}

bool Grille::setValeurTableau(int* tabValeur)
{
	bool reussite = true;
	for ( int i=0;i<dimensionTabSudoku;i++)
	{
		for(int j =0;j<dimensionTabSudoku;j++)
		{
			if (this->setValeurCase(i,j,tabValeur[i*dimensionTabSudoku + j]) == false )reussite = false;;
		}
	}
	return reussite;
}


int Grille::getValeurCase(int ligne, int colonne)
{
	return getCase(ligne, colonne).getValeur();
}

void Grille::getValeurLigne(int ligne, int * resultat)
{
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		CaseGrille & cursor = getCase(ligne,i);
		if(cursor.remplie && cursor.affichee) resultat[i]= cursor.getValeur();
		else resultat[i]= -1;
	}
}

void Grille::getValeurCollone(int colonne, int * resultat)
{
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		CaseGrille & cursor = getCase(i,colonne);
		if(cursor.remplie && cursor.affichee) resultat[i]= cursor.getValeur();
		else resultat[i]= -1;
	}
}

void Grille::getValeurCarre(int ligne, int colonne,int* resultat)
{
	int numLignePremiereCaseCarre = ligne - (ligne % degre);
	int numColonnePremiere = colonne - (colonne%degre);

	int index = 0;	
	for(int i = numLignePremiereCaseCarre;i<(numLignePremiereCaseCarre + degre);i++)
	{
		for(int j = numColonnePremiere;j<(numColonnePremiere + degre);j++)
		{
			CaseGrille & cursor = getCase(i,j);
			if(cursor.remplie && cursor.affichee) resultat[index]= cursor.getValeur();
			else resultat[index]= -1;
			index++;
		}
	}

}

void Grille::afficherGrille()
{
	for(int i =0;i<dimensionTabSudoku;i++)
	{
		for(int j = 0;j<dimensionTabSudoku;j++)
		{
			CaseGrille & caseG = this->getCase(i,j);
			if ( caseG.remplie == true && caseG.affichee == true)
			{
				int val = caseG.getValeur();
				std::cout << val << ' ';
			}
			else std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Grille::getAfficheCase(int ligne, int colonne){ return getCase(ligne,colonne).affichee;}

bool Grille::getRemplieCase(int ligne, int colonne){ return getCase(ligne,colonne).remplie;}

void Grille::gommerCase(int ligne, int colonne)
{
	CaseGrille & cursor = getCase(ligne, colonne);
	if(cursor.remplie)
	{
		nombreCaseRemplie --;
		if (cursor.affichee) nombreCaseAfficheeEtRemplie--;
	}
	cursor.gommerValeur();
}

void Grille::faireApparaitreCase(int ligne, int colonne)
{
	CaseGrille & cursor = getCase(ligne, colonne);
	if(!cursor.remplie)	return; //pas d interet
	if(cursor.affichee) return; //pas d interet
	cursor.affichee = true;
	nombreCaseAfficheeEtRemplie++;

	checkDegreLiberteApparrition(ligne,colonne);
}

void Grille::cacherCase(int ligne, int colonne)
{
	CaseGrille & cursor = getCase(ligne, colonne);
	if(!cursor.remplie)	return; //pas d interet
	if(!cursor.affichee) return; //pas d interet
	cursor.affichee= false;
	nombreCaseAfficheeEtRemplie--;

	checkDegreLiberte(ligne,colonne);
}

CaseGrille & Grille::tirerCaseRemplieEtAffichee()
{
	int dice_roll = tirerUnIntEntre(0,nombreCaseAfficheeEtRemplie-1);
	int index =0;
	while (dice_roll >0)
	{
		if(tabSudoku[index].remplie && tabSudoku[index].affichee) dice_roll--;
		index++;
	}

	return tabSudoku[index];
}

void Grille::getLigne(int ligne, CaseGrille** resultat)
{
	for(int i = 0; i <dimensionTabSudoku;i++)
	{
		resultat[i]=&getCase(ligne,i);
	}
}

void Grille::getColonne(int colonne,CaseGrille** resultat)
{
	for(int i = 0; i <dimensionTabSudoku;i++)
	{
		resultat[i]=&getCase(i,colonne);
	}
}

void Grille::getCarre(int ligne, int colonne,CaseGrille** resultat)
{
	int numLignePremiereCaseCarre = ligne - (ligne % degre);
	int numColonnePremiere = colonne - (colonne%degre);

	int index = 0;	
	for(int i = numLignePremiereCaseCarre;i<(numLignePremiereCaseCarre + degre);i++)
	{
		for(int j = numColonnePremiere;j<(numColonnePremiere + degre);j++)
		{
			CaseGrille & cursor = getCase(i,j);

			index++;
		}
	}
}

void Grille::getCarreTronque(int ligne, int colonne, CaseGrille** resultat)
{
	getCarre(ligne,colonne,resultat);
	for(int i =0;i<dimensionTabSudoku;i++)
	{
		if ((resultat[i]->getLigne() == ligne) || (resultat[i]->colonne == colonne))
		{
			resultat[i] = NULL;
		}
	}
}

void Grille::checkDegreLiberte(int ligne, int colonne)
{
	int valeur = getCase(ligne,colonne).getValeur();
	
	//verifier la ligne modifiée
	CaseGrille** resultat = new CaseGrille*[dimensionTabSudoku];
	getLigne(ligne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i]->colonne != colonne)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool = new int[dimensionTabSudoku];
			getValeurCollone(resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCarre(ligne,resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee++;
			delete[] pool;
		}
	}

	getColonne(colonne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i]->ligne != ligne)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool= new int[dimensionTabSudoku];
			getValeurLigne(resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCarre(ligne,resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee++;
			delete[] pool;
		}
	}

	getCarreTronque(ligne,colonne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i] != NULL)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool= new int[dimensionTabSudoku];
			getValeurLigne(resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCollone(resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee++;
			delete[] pool;
		}
	}
	getCase(ligne,colonne).degreLibertee++;

	delete[] resultat;
}

void Grille::checkDegreLiberteApparrition(int ligne, int colonne)
{
	int valeur = getCase(ligne,colonne).getValeur();
	
	//verifier la ligne modifiée
	CaseGrille** resultat = new CaseGrille*[dimensionTabSudoku];
	getLigne(ligne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i]->colonne != colonne)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool = new int[dimensionTabSudoku];
			getValeurCollone(resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCarre(ligne,resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee--;
			delete[] pool;
		}
	}

	getColonne(colonne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i]->ligne != ligne)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool= new int[dimensionTabSudoku];
			getValeurLigne(resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCarre(ligne,resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee--;
			delete[] pool;
		}
	}

	getCarreTronque(ligne,colonne,resultat);
	for(int i = 0;i<dimensionTabSudoku;i++)
	{
		if(resultat[i] != NULL)
		{
			//pour chaques case de la ligne, verifier si la valeur est dans leur pool
			bool decrementer = true;
			
			int* pool= new int[dimensionTabSudoku];
			getValeurLigne(resultat[i]->ligne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}
			getValeurCollone(resultat[i]->colonne,pool);
			for(int j=0;j<dimensionTabSudoku;j++)
			{
				if(valeur == pool[j]) decrementer = false;
			}

			if( decrementer == true) resultat[i]->degreLibertee--;
			delete[] pool;
		}
	}
	getCase(ligne,colonne).degreLibertee--;

	delete[] resultat;
}

void Grille::verifierInitialisationDebutSecondAlgo(){

	bool degreLiberteOk = true;
	for (int i = 0;i<dimensionTabSudoku;i++)
	{
		for( int j = 0; j<dimensionTabSudoku;j++)
		{
			CaseGrille & caseG = getCase(i,j); 
			if( caseG.degreLibertee != 0)
			{
				std::cout << "cette case n est pas a 0 au degre de liberte : ligne " << i << " colonne " << j << std::endl;
				degreLiberteOk = false;
			}
		}
	}
	if (degreLiberteOk) std::cout << "degre de liberte OK " << std::endl;


	if(nombreCaseAfficheeEtRemplie != dimensionTabSudoku*dimensionTabSudoku) std::cout << "le nombre de case affiche et remplie est de " << nombreCaseAfficheeEtRemplie << " au lieu de " << dimensionTabSudoku*dimensionTabSudoku << std::endl;
	else std::cout << "nombre de case affiche et remplie OK " << std::endl;

	if(nombreCaseRemplie != dimensionTabSudoku*dimensionTabSudoku) std::cout << "le nombre de case replie est de " << nombreCaseRemplie << " au lieu de "<< dimensionTabSudoku*dimensionTabSudoku << std::endl;
	else std::cout << "nombre de case remplie OK" << std::endl;
}

CaseGrille * Grille::tirerCaseDegree(int degreEtudie,CaseGrille** tabDejaFait )
{
	int nbCase=0;
	for (int i = 0;i<dimensionTabSudoku;i++)
	{
		for( int j = 0; j<dimensionTabSudoku;j++)
		{
			CaseGrille & caseG = getCase(i,j); 
			if (caseG.degreLibertee == degreEtudie) nbCase++;
		}
	}

	if (nbCase == 0) return NULL;
	int alea = tirerUnIntEntre(1,nbCase);

	for (int i = 0;i<dimensionTabSudoku;i++)
	{
		for( int j = 0; j<dimensionTabSudoku;j++)
		{
			CaseGrille & caseG = getCase(i,j); 
			if (caseG.degreLibertee == degreEtudie) alea--;
			if ( alea == 0) return &caseG;
		}
	}

	//normalement jamais croisé
	return NULL;
}



void Grille::checkPossibilite(int ligne, int colonne, int* possible)
{
	int k = 0;
	for(int i=0;i<dimensionTabSudoku;i++)
	{
		bool test = true;
		int* pool = new int[dimensionTabSudoku];
		getValeurLigne(ligne,pool);
		for(int j=0;j<dimensionTabSudoku;j++)
		{
			if((i+1) == pool[j]) test = false;
		}
		getValeurCollone(colonne,pool);
		for(int j=0;j<dimensionTabSudoku;j++)
		{
			if((i+1) == pool[j]) test = false;
		}
		getValeurCarre(ligne,colonne,pool);
		for(int j=0;j<dimensionTabSudoku;j++)
		{
			if((i+1) == pool[j]) test = false;
		}
		if(test==true)
		{
			k = k+1;
			possible[k] = i+1; 
		}
	}
	possible[0] = k;
}

double Grille::degreSensibiliteTableau()
{
	double moyenne=0;
	int nbCase=0;
	for (int i =0;i<dimensionTabSudoku;i++)
	{
		for (int j =0;j<dimensionTabSudoku;j++)
		{
			moyenne+= getCase(i,j).degreLibertee;
			nbCase++;
		}
	}
	return moyenne/ nbCase;
}

double* Grille::degreSensibiliteCase(int ligne, int colonne)
{
	double* tabDegre = new double[3];
	for (int i = 0;i<3;i++) tabDegre[i]=0;
	CaseGrille** resultat = new CaseGrille*[dimensionTabSudoku];
	getLigne(ligne,resultat);

	for (int i = 0;i<dimensionTabSudoku;i++)	tabDegre[0]+=resultat[i]->degreLibertee;
	tabDegre[0]= tabDegre[0]/dimensionTabSudoku;

	getColonne(colonne,resultat);
	for(int i =0;i<dimensionTabSudoku;i++)	tabDegre[1]+= resultat[i]->degreLibertee;
	tabDegre[1] = tabDegre[1]/dimensionTabSudoku;

	getCarre(ligne,colonne,resultat);
	for (int i=0;i<dimensionTabSudoku;i++) tabDegre[2]+=resultat[i]->degreLibertee;
	tabDegre[2] = tabDegre[2]/dimensionTabSudoku;

	delete[] resultat;

	return tabDegre;
}