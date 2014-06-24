#pragma once
#include "CaseGrille.h"
#include "stdafx.h"

class Grille
{
private:
	CaseGrille (*tabSudoku); //poiteur vers le premier element du tableau de valeur
	int nombreCaseAfficheeEtRemplie;
	int nombreCaseRemplie;
public:
	const int degre;
	const int dimensionTabSudoku;// carré du degré mais bon...

	Grille(int=3); // creer une grille vide degré de libertée = (degré grille)² pour chaques case
	~Grille(void);

	CaseGrille & getCase(int ligne,int colonne);  // numero de la ligne, nummero de la collone
	bool setValeurCase(int ligne, int colonne, int valeur); //retourne true si ça c est bien passé, false sinon
	bool setValeurTableau(int*);
	int getValeurCase(int ligne, int colonne);

	void cacherCase(int ligne, int colonne);
	void faireApparaitreCase(int ligne, int colonne); 
	void gommerCase(int ligne, int colonne);
	bool getAfficheCase(int ligne, int colonne);
	bool getRemplieCase(int ligne, int colonne);

	// ces tableaux font la taille de dimensionTabSudoku et doivent etre créé par l utilisateur pour eviter fuite de memoire
	// ils retourne dans le tableau envoyé en parametre la liste des valeurs correspondant, affichée et remplie
	//sinon renvoye -1 a cette position	
	void getValeurLigne(int ligne, int * resultat); // de gauche a droite
	void getValeurCollone(int colonne, int * resultat); // de haut vers bas
	void getValeurCarre(int ligne, int colonne, int * resultat); // retourne le carré auquel fait partie cette case, gauche vers droite et haut vers bas

	void getLigne(int ligne, CaseGrille** resultat);
	void getColonne(int colonne, CaseGrille** resultat);
	void getCarre(int ligne, int colonne, CaseGrille** resultat);
	void getCarreTronque(int ligne, int colonne, CaseGrille** resultat);

	CaseGrille & tirerCaseRemplieEtAffichee();
	CaseGrille * tirerCaseDegree(int,CaseGrille** = NULL);

	void afficherGrille();
	void verifierInitialisationDebutSecondAlgo();

	double degreSensibiliteTableau();
	double* degreSensibiliteCase(int ligne,int colonne);
private:
	void checkDegreLiberte(int ligne, int colonne);
	void checkDegreLiberteApparrition(int ligne, int colonne);
public:
	void checkPossibilite(int ligne, int colonne, int* possible);
};

