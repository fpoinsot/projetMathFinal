#include "stdafx.h"
#include "CaseGrille.h"


CaseGrille::CaseGrille(void):remplie(false),affichee(true)
{
}


CaseGrille::~CaseGrille(void)
{
}

int CaseGrille::getValeur()
{
	return valeur;
}

void CaseGrille::setValeur(int val)
{
	valeur = val;
	remplie = true;
}

void CaseGrille::gommerValeur()
{
	remplie= false;
}

bool CaseGrille::getAffichee(){ return affichee;}
bool CaseGrille::getRemplie(){return remplie;}
int CaseGrille::getdegreLibertee(){return degreLibertee;}
int CaseGrille::getLigne(){return ligne;}
int CaseGrille::getColonne(){return colonne;}

