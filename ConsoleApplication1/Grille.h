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
	const int dimensionTabSudoku;// carr� du degr� mais bon...

	Grille(int=3); // creer une grille vide degr� de libert�e = (degr� grille)� pour chaques case
	~Grille(void);

	CaseGrille & getCase(int ligne,int colonne);  // numero de la ligne, nummero de la collone
	bool setValeurCase(int ligne, int colonne, int valeur); //retourne true si �a c est bien pass�, false sinon
	bool setValeurTableau(int*);
	int getValeurCase(int ligne, int colonne);

	void cacherCase(int ligne, int colonne);
	void faireApparaitreCase(int ligne, int colonne); 
	void gommerCase(int ligne, int colonne);
	bool getAfficheCase(int ligne, int colonne);
	bool getRemplieCase(int ligne, int colonne);

	// ces tableaux font la taille de dimensionTabSudoku et doivent etre cr�� par l utilisateur pour eviter fuite de memoire
	// ils retourne dans le tableau envoy� en parametre la liste des valeurs correspondant, affich�e et remplie
	//sinon renvoye -1 a cette position	
	void getValeurLigne(int ligne, int * resultat); // de gauche a droite
	void getValeurCollone(int colonne, int * resultat); // de haut vers bas
	void getValeurCarre(int ligne, int colonne, int * resultat); // retourne le carr� auquel fait partie cette case, gauche vers droite et haut vers bas

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

