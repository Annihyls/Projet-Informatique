/*
   Un programme C pour le TP final de projet informatique.
   Ce fichier code source contient toutes les fonctions 
   nécessaire pour le bon fonctionnement du fichier 
   principal (simuLapin.c).
   Codé par Vincent Gimbert et Lucas Ciszowski.
*/

#include "Fonction_Matsumoto.h"
#include "Fonction_Lapin.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**********************************************************FONCTION**********************************************************/
/**********************************************************fibonacci**********************************************************/
/* -------------------------------------------------------------------- */
/*fibonacci				Calcule la suite de fibonacci					*/
/*																		*/
/*  En entrée : un entier n.											*/
/*																		*/
/*	En sortie : Retourne récursivement la fonction fibonacci.			*/
/* -------------------------------------------------------------------- */
int fibonacci(int n)
{
	if (n <= 1)
	{
        return n;
	}
	else
    {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

/**********************************************************FONCTION**********************************************************/
/**********************************************************uniform***********************************************************/
/* -------------------------------------------------------------------- */
/*uniform 		Génère un nombre pseudo-aléatoire dans un interval	    */
/*																		*/
/*  En entrée : min, max Deux double précision.							*/
/*																		*/
/*	En sortie : Un nombre pseudo-aléatoire a partir de l'interval		*/
/*				donné en paramètre (compris entre min et max.)			*/
/* -------------------------------------------------------------------- */
double uniform(double min, double max)
{
	return min + (max - min) * genrand_real1();
}


/**********************************************************FONCTION**********************************************************/
/****************************************************generatorByTabPercent***************************************************/
/* -------------------------------------------------------------------- */
/*generatorByTabPercent			Génère un tableau échantilloné			*/
/*																		*/
/*  En entrée : inTaille, inNbreEssais, deux entier.					*/
/*				un pointeur sur un tableau double, pourcenTab.			*/
/*				un pointeur sur un grand tableau d'entiers, Echantillon.*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void generatorByTabPercent(double *pourcenTab, int inTaille, int inNbreEssais, long long int *Echantillon)
{
	int                 i,j;

	double 	            random;

	double            * cumulTab = (double *)calloc(inTaille, sizeof(double));

	if (cumulTab == NULL)
    {
        printf("Fonction_Lapin - error : generatorByTabPercent\n");
        exit(-1);
    }

	for(i=0; i<inTaille; i++)
	{
		if(i == 0)
		{
			cumulTab[i] = pourcenTab[i];
		}
		else
		{
			cumulTab[i] = (pourcenTab[i] + cumulTab[i-1]);
		}
	}

	for(i=0; i<inNbreEssais; i++)
	{
		random = uniform(0,1);

		for(j=0; j<inTaille; j++)
		{
			if (random < cumulTab[j])
			{
				Echantillon[j]++;
				break;
			}
		}
	}
	free(cumulTab);
}


/**********************************************************FONCTION**********************************************************/
/*****************************************************intervalDeConfiance****************************************************/
/* -------------------------------------------------------------------- */
/*intervalDeConfiance			affiche l'intervalle de confiance		*/
/*																		*/
/*  En entrée : moyennePopulationTab, un tableau de double.				*/
/*				inNbEssais, un entier représentant la taille du tableau.*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void intervalDeConfiance(double *moyennePopulationTab, int inNbEssais)
{
	int		            i;

	double	            meanPopulationTotal,
                        s, r;

	double              tableCoef[34] = {12.706, 4.303, 3.182, 2.776, 2.571, 2.447,
                                        2.365, 2.308, 2.262, 2.228, 2.201, 2.179,
                                        2.160, 2.145, 2.131, 2.120, 2.110, 2.101,
                                        2.093, 2.086, 2.080, 2.074, 2.069, 2.064,
                                        2.060, 2.056, 2.052, 2.048, 2.045, 2.042,
                                        2.021, 2.000, 1.980, 1.960};

	meanPopulationTotal = 0;
	s = 0;

	for (i=0; i<inNbEssais; i++)
	{
		meanPopulationTotal = meanPopulationTotal + moyennePopulationTab[i];
	}

	meanPopulationTotal = meanPopulationTotal / inNbEssais;
	printf("\nVoici la moyenne obtenue : %lf \n", meanPopulationTotal);
	
	for (i=0; i<inNbEssais; i++)
	{
		s = s + ((moyennePopulationTab[i] -  meanPopulationTotal) * (moyennePopulationTab[i] -  meanPopulationTotal));
	}

	s = s / (inNbEssais - 1);
	s = s / inNbEssais;
	s = sqrt(s);

	/*Cette partie permet juste d'utiliser le bon coefficient de la loi de Student*/
	if (inNbEssais <= 30)
	{
		r = tableCoef[inNbEssais - 1] * s;
	}
	else if ((inNbEssais < 80) && (inNbEssais > 40))
	{
		r = tableCoef[30] * s;
	}
	else if ((inNbEssais < 120) && (inNbEssais > 80))
	{
		r = tableCoef[31] * s;
	}
	else if (inNbEssais == 120)
	{
		r = tableCoef[32] * s;
	}
	else
	{
		r = tableCoef[33] * s;
	}
	/*----------------------------------------------------------------------------*/
	printf("\nVoici l'interval de confiance :[ %lf ; %lf ]\n",  meanPopulationTotal - r,  meanPopulationTotal + r);
}


/**********************************************************FONCTION**********************************************************/
/**********************************************************naissance*********************************************************/
/* -------------------------------------------------------------------- */
/*naissance			calcule le nombre de naissance par portées			*/
/*																		*/
/*  En entrée : inPortee, inFemelle, un entier.							*/
/*				tabAge, un grand tableau 2D d'entier.					*/
/*																		*/
/*	Retourne le compteur de naissances.  								*/
/* -------------------------------------------------------------------- */
long long int naissance(long long int inPortee, long long int inFemelle, long long int **tabAge)
{
	double 	            tabPetitParPorteePourcent[7] = {0.035, 0.13, 0.23, 0.23, 0.23, 0.13, 0.035},
                        random;

	long long int	    tabPetitParPorteeEchantillon[7] = {0,0,0,0,0,0,0},
                        bbFemelle,
						cmptNaissance,
                        bbMale;

    int                 i, j;
	
	bbMale = 0;
	bbFemelle = 0;
	cmptNaissance = 0;
	
	if(inFemelle < inPortee)
	{
		inPortee = inFemelle;
	}
	generatorByTabPercent(tabPetitParPorteePourcent, 7, inPortee, tabPetitParPorteeEchantillon);

	for(i=0; i<7; i++)
	{
		for(j=0; j<tabPetitParPorteeEchantillon[i]; j++)
		{
			random = uniform(0,1);

			if (random <=0.5)
			{
				bbMale = bbMale + (i+1) * tabPetitParPorteeEchantillon[i];
			}
			else
			{
				bbFemelle = bbFemelle + (i+1) * tabPetitParPorteeEchantillon[i];
			}
			
			cmptNaissance = cmptNaissance + (i+1) * tabPetitParPorteeEchantillon[i];
		}
		tabAge[0][0] = bbMale;
		tabAge[1][0] = bbFemelle;
	}
	return cmptNaissance;
}


/**********************************************************FONCTION**********************************************************/
/**********************************************************infertile*********************************************************/
/* -------------------------------------------------------------------- */
/*infertile			Calcule le nombre de femelles infertile par an		*/
/*																		*/
/*  En entrée : inFemelle, un entier.									*/
/*																		*/
/*	En sortie : Retourne le nombre de femelles infertiles.				*/
/* -------------------------------------------------------------------- */
long long int infertile(long long int inFemelle)
{
	double	            random;

	long long int		inFemelleInfertile = 0;

	for(int i=0; i<inFemelle; i++)
	{
		random = uniform(0,1);

		if(random <= 0.1)
		{
			inFemelleInfertile++;
		}
	}
	return inFemelleInfertile;
}


/**********************************************************FONCTION**********************************************************/
/**********************************************************ageLapin**********************************************************/
/* -------------------------------------------------------------------- */
/*ageLapin 		Permet de connaitre l'âge des lapins en mois		    */
/*																		*/
/*  En entrée : tabAge, un grand tableau 2D d'entier.		            */
/*				tailleTabAge, un entier représentant la taille du 		*/
/*														 tableau.		*/
/*																		*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void ageLapin(long long int **tabAge, int tailleTabAge)
{
	for(int i=0; i<2; i++)
	{
		for(int j=(tailleTabAge-1); j>0; j--)
		{
			tabAge[i][j] = tabAge[i][j-1];
		}
	}
	tabAge[0][0] = 0;
	tabAge[1][0] = 0;
}


/**********************************************************FONCTION**********************************************************/
/*****************************************************setIntervalleDeMort****************************************************/
/* -------------------------------------------------------------------- */
/*setIntervalleDeMort	Calcule le pourcentage de "chance" de mourir	*/
/*																		*/
/*  En entrée : inNbMois, un entier symbolisant l'âge du lapin.			*/
/*																		*/
/*																		*/
/*	En sortie : Retourne un double, le pourcentage de chance de mourir.	*/
/* -------------------------------------------------------------------- */
double setIntervalleDeMort(int inNbMois)
{
    double inItervalleMort = 0.0;

    if (inNbMois < 7)
    {
        inItervalleMort = 0.5;
    }
    else if (inNbMois >= 7 && inNbMois < 85)
    {
        inItervalleMort = 0.25;
    }
    else if (inNbMois >= 85 && inNbMois < 97)
    {
        inItervalleMort = 0.40;
    }
    else if (inNbMois >= 97 && inNbMois < 109)
    {
        inItervalleMort = 0.55;
    }
    else if (inNbMois >= 109 && inNbMois < 121)
    {
        inItervalleMort = 0.70;
    }
    else if (inNbMois >= 121 && inNbMois < 133)
    {
        inItervalleMort = 0.85;
    }
    else if (inNbMois >= 133 && inNbMois < 144)
    {
        inItervalleMort = 0.90;
    }
    else if (inNbMois == 144)
    {
        inItervalleMort = 1.0;
    }

    return inItervalleMort;
}


/**********************************************************FONCTION**********************************************************/
/**********************************************************mortLapin*********************************************************/
/* -------------------------------------------------------------------- */
/*mortLapin 		Simule la mort des lapins							*/
/*																		*/
/*  En entrée : tabAge, un grand tableau 2D d'entier.				    */
/*				tailleTabAge, un entier représentant la taille du 		*/
/*														 tableau.		*/
/*				cmptMort, un pointeur long entier qui compte le nombre 	*/
/*															de morts.	*/
/*																		*/
/*																		*/
/*	En sortie : retourne le nombre de morts de femelles infertiles.		*/
/* -------------------------------------------------------------------- */
long long int mortLapin(long long int **tabAge, int tailleTabAge, long long int *cmptMort)
{
	long long int       mortFemelleInfertile = 0;

    int                 i,j,k;

	double              random;

	for(i=0; i<2; i++)
	{
		for(j=0; j<tailleTabAge; j++)
		{
			k = 0;
			while(k <= tabAge[i][j])
			{
				random = uniform(0,1);

				if (random <= setIntervalleDeMort(j))
				{
					if (tabAge[i][j] > 0)
					{
						if (i == 1 && j > 7)
						{
							random = uniform(0,1);
							if (random <= 0.5)				//on considère que les femelles infertiles on autant de chance de mourir que les femelles fertiles
							{
								mortFemelleInfertile++;
							}
						}
						tabAge[i][j]--;
						*cmptMort = *cmptMort + 1;
					}
				}
				k++;
			}
		}
	}
	return mortFemelleInfertile;
}


/**********************************************************FONCTION**********************************************************/
/********************************************************verifNbrLapin*******************************************************/
/* -------------------------------------------------------------------- */
/*verifNbrLapin		Vérifie si il y a aucune erreur sur la population	*/
/*																		*/
/*  En entrée : inFemelle, inMale, Un pointeur sur un entier.			*/
/*              laperaux, un grand tableau d'entier.                    */
/*              tabAge, un grand tableau 2D d'entier.				    */
/*				tailleTabAge, un entier représentant la taille du 		*/
/*													    tableau tabAge.	*/
/*																		*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void verifNbrLapin(long long int *inFemelle, long long int *inMale, long long int *laperaux, long long int **tabAge, int tailleTabAge)
{
	int                 j;

	laperaux[0] = 0;
	laperaux[1] = 0;
	*inMale = 0;
	*inFemelle = 0;

	for(j=0; j<7; j++)
	{
		laperaux[0] = laperaux[0] + tabAge[0][j];
	}

	for(j=0; j<7; j++)
	{
		laperaux[1] = laperaux[1] + tabAge[1][j];
	}

	for(j=7; j<tailleTabAge; j++)
	{
		*inMale = *inMale + tabAge[0][j];
	}

	for(j=7; j<tailleTabAge; j++)
	{
		*inFemelle = *inFemelle + tabAge[1][j];
	}
}


/**********************************************************FONCTION**********************************************************/
/**********************************************************Creatab2D*********************************************************/
/* -------------------------------------------------------------------- */
/*creatab2D 		Permet de créer un tableau a 2 dimensions		 	*/
/*																		*/
/*  En entrée : ligne, colonne, deux entiers.							*/
/*																		*/
/*																		*/
/*	En sortie : Retourne un tableau 2D initialisé à 0.					*/
/* -------------------------------------------------------------------- */
long long int **creatabLL2D(int ligne, int colonne)
{
	long long int   **  Tableau = NULL;

	Tableau = (long long int**)calloc(ligne,sizeof(long long int*));

	if (Tableau == NULL)
	{
		return NULL;
	}

	for(int i=0; i<ligne; i++)
    {
		Tableau[i] = (long long int*)calloc(colonne,sizeof(long long int));

		if (Tableau[i] == NULL)
		{
			for(int j=0; j<i; j++)
			{
				free(Tableau[j]);
			}
			free(Tableau);
			return NULL;
		}
	}
	return Tableau;
}


/**********************************************************FONCTION**********************************************************/
/*********************************************************LibereTab2D********************************************************/
/* -------------------------------------------------------------------- */
/*LibereTab2D 		Permet de libérer un tableau à 2 dimensions		 	*/
/*																		*/
/*  En entrée : T, un pointeur sur un grand tableau 2D.					*/
/*				n, un entier représentant le nombre de lignes du tableau*/
/*																		*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void LibereTab2D(long long int **T, int n)
{
	if(T != NULL)
    {
		for(int i=0; i<n; i++)
		{
			if (T[i] != NULL)
			{
				free(T[i]);
			}
		}
		free(T);
	}
}


/**********************************************************FONCTION**********************************************************/
/******************************************************AfficheTabLLInt2D*****************************************************/

/* -------------------------------------------------------------------- */
/*afficheTabLLInt2D 		Permet d'afficher un tableau 2D d'entier	*/
/*																		*/
/*  En entrée : T, un pointeur sur un grand tableau 2D.					*/
/*				n, un entier représentant le nombre de lignes du tableau*/
/*				colonne, un entier.										*/
/*																		*/
/*	Aucune sortie.														*/
/* -------------------------------------------------------------------- */
void afficheTabLLInt2D(long long int **T, int n, int colonne)
{
	for(int i=0; i<n; i++)
    {
		printf("\n\n");

		for(int j=0; j<colonne; j++)
        {
			printf("   %lli", T[i][j]);
		}
	}
	printf("\n\n");
}


/**********************************************************FONCTION**********************************************************/
/******************************************************afficheTabLLInt*******************************************************/
/* -------------------------------------------------------------------- */
/*afficheTabLLInt				Affiche le tableau d'entier				*/
/*																		*/
/*  En entrée : pointeur sur un grand tableau d'entier T.			    */
/*				n, un entier.											*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void afficheTabLLInt(long long int *T, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i%10 == 0)
		{
			printf("\n");
		}
		printf("%lli   ", T[i]);
	}
	printf("\n");
}


/**********************************************************FONCTION**********************************************************/
/*****************************************************afficheTabDouble*******************************************************/
/* -------------------------------------------------------------------- */
/*afficheTabDouble				Affiche le tableau de double			*/
/*																		*/
/*  En entrée : pointeur sur un tableau de double T.					*/
/*				n, un entier.											*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void afficheTabDouble(double *T, int n)
{
	for(int i=0; i<n; i++)
	{
		if (i%10 == 0)
		{
			printf("\n");
		}
		printf("%lf   ", T[i]);
	}
	printf("\n");
}


/**********************************************************FONCTION**********************************************************/
/*********************************************************initTabInt*********************************************************/
/* -------------------------------------------------------------------- */
/*initTabInt			Réinitialise un tableau en 1 dimension			*/
/*																		*/
/*  En entrée : tab, un pointeur sur un tableau de d'entier.			*/
/*				inTaille, un entier.									*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */

void initTabLLInt(long long int * tab, int inTaille)
{
    for(int i = 0; i < inTaille; i++)
    {
        tab[i] = 0;
    }
}

/**********************************************************FONCTION**********************************************************/
/*********************************************************initTab2DInt*********************************************************/
/* -------------------------------------------------------------------- */
/*initTab2DInt			Réinitialise un tableau de 2 dimensions			*/
/*																		*/
/*  En entrée : tab, pointeur sur un tableau 2D d'entier.				*/
/*				inTailleX, un entier représentant les lignes			*/
/*				inTailleY, un entier représentant les colonnes			*/
/*																		*/
/*	Aucune sortie. 														*/
/* -------------------------------------------------------------------- */
void initTab2DLLInt(long long int ** tab, int inTailleX, int inTailleY)
{
    for(int i = 0; i < inTailleX; i++)
    {
        for(int j = 0; j < inTailleY; j++)
        {
            tab[i][j] = 0;
        }
    }
}
