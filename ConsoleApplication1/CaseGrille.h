#pragma once
class CaseGrille
{
private:
	int ligne;
	int colonne;
	int valeur; 
	bool remplie;//a modifier quand on rempli le tableau
	int degreLibertee;	
	bool affichee; //a modifier quand on gomme

	void gommerValeur(); //utiliser ça plutot que case.remplie = false car ou pourrait avoir besoin d initialiser cette valeur au passage a l avenir
	void setValeur(int);
public:
	CaseGrille(void);
	~CaseGrille(void);
	int getValeur();
	bool getAffichee();
	bool getRemplie();
	int getdegreLibertee();
	int getLigne();
	int getColonne();
	

	friend class Grille;
};

