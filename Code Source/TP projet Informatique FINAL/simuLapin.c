/*
   Un programme C pour le TP final de projet informatique.
   Ce fichier code source contient le programme
   principal pour calculer l'évolution de la
   population de lapins.
   Codé par Vincent Gimbert et Lucas Ciszowski.
*/
#include <stdio.h>
#include <stdlib.h>
#include "Fonction_Matsumoto.h"
#include "Fonction_Lapin.h"


int main()
{
	unsigned long       init[4]={0x123, 0x234, 0x345, 0x456},
                        length = 4;

    int 		        nbMoisTotal,
                        nbEssais,
                        popDebut = 0,
                        mois,
                        moisParAn,
                        tailleTabAge,
						an,
						cmptFinExp,
						cmptFinExpMale,
                        i, j, k;

    long long int       populationTotale,
                        femelleInfertile,
                        femelleFertile,
                        femelle,
						cmptNaissance,
						cmptMort,
                        male;

	long long int   *   popTabParMois,
					*	maleTabParMois,
					*	femelleTabParMois,
					*	femelleFertileTabParMois,
					*	femelleInfertileTabParMois,
					*	laperauxTabParMois,
                    *	tabPortee,
                    *	laperaux,
					*	naissanceTabParMois,
					*	mortTabParMois,
					*	mortMiseBasParAn;

    long long int   **	tabAge;

	double		    *   tabDeMoyennePopTotale,
					*	tabDeMoyenneMale,
					*	tabDeMoyenneFemelle,
					*	tabDeMoyenneFemelleFertile,
					*	tabDeMoyenneFemelleInfertile,
					*	tabDeMoyenneLaperaux,
					*	tabDeMoyenneNaissance,
					*	tabDeMoyenneMort,
					*	tabDeMoyenneMortMiseBas;

	double		 	    moyennePopulationPourEssais,
						moyenneMalePourEssais,
						moyenneFemellePourEssais,
						moyenneFemelleFertilePourEssais,
						moyenneFemelleInfertilePourEssais,
						moyenneLaperauxPourEssais,
						moyenneNaissancePourEssais,
						moyenneMortMiseBasPourEssais,
						moyenneMortPourEssais,
                        random,
                        tabPorteePourcent[12] = {0.002, 0.003, 0.015, 0.07, 0.14, 0.18,
												 0.22, 0.18, 0.14, 0.07, 0.018, 0.002};


	/*--------------------ici, on demande à l'utilisateur de choisir ses paramètres--------------------*/
	
	printf("Combien d'experiences voulez vous effectuer ? Tapez un entier:");
	scanf("%d", &nbEssais);

	printf("Combien de mois voulez vous simuler (par experiences) ? Tapez un entier:");
	scanf("%d", &nbMoisTotal);

	while(popDebut < 2)
	{
		printf("Quelle population de lapin au depart ? Tapez un entier superieur ou egal a 2:");
		scanf("%d", &popDebut);
	}
	
	/*-------------------------------------------------------------------------------------------------*/

	/*Ici, on initialise le générateur aléatoire et on créer nos tableau en fonction des paramètre choisis par l'utilisateur*/
	
	init_by_array(init, length);

	tailleTabAge = nbMoisTotal + 9;
	cmptFinExp = 0;
	cmptFinExpMale = 0;

	tabDeMoyennePopTotale = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneMale = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneFemelle = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneFemelleFertile = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneFemelleInfertile = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneLaperaux = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneNaissance = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneMort = (double *)calloc(nbEssais, sizeof(double));
	tabDeMoyenneMortMiseBas = (double *)calloc(nbEssais, sizeof(double));
	tabPortee = (long long int *)calloc(13, sizeof(long long int));
	popTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	maleTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	femelleTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	femelleFertileTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	femelleInfertileTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	laperauxTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	naissanceTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	mortTabParMois = (long long int *)calloc(nbMoisTotal, sizeof(long long int));
	mortMiseBasParAn = (long long int *)calloc(((nbMoisTotal/12)+1), sizeof(long long int));
	laperaux = (long long int *)calloc(2, sizeof(long long int));
	tabAge = creatabLL2D(2, tailleTabAge);

	if(tabDeMoyennePopTotale == NULL)
    {
        printf("main - error : tabDeMoyennePopTotale\n");
        return EXIT_FAILURE;
    }

    if(popTabParMois == NULL)
    {
        printf("main - error : popTabParMois\n");
        return EXIT_FAILURE;
    }

	if(tabPortee == NULL)
    {
        printf("main - error : tabPortee\n");
        return EXIT_FAILURE;
    }

	if(laperaux == NULL)
    {
        printf("main - error : laperaux\n");
        return EXIT_FAILURE;
    }

	if (tabAge == NULL) 
	{
        printf("main - error : creatabLL2D\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneMale == NULL)
    {
        printf("main - error : tabDeMoyenneMale\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneFemelle == NULL)
    {
        printf("main - error : tabDeMoyenneFemelle\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneFemelleInfertile == NULL)
    {
        printf("main - error : tabDeMoyenneFemelleInfertile\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneFemelleFertile == NULL)
    {
        printf("main - error : tabDeMoyenneFemelleFertile\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneLaperaux == NULL)
    {
        printf("main - error : tabDeMoyenneLaperaux\n");
        return EXIT_FAILURE;
    }
	
	if(maleTabParMois == NULL)
    {
        printf("main - error : maleTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(femelleTabParMois == NULL)
    {
        printf("main - error : femelleTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(femelleFertileTabParMois == NULL)
    {
		printf("main - error : femelleFertileTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(femelleInfertileTabParMois == NULL)
    {
        printf("main - error : femelleInfertileTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(laperauxTabParMois == NULL)
    {
        printf("main - error : laperauxTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(mortMiseBasParAn == NULL)
    {
        printf("main - error : mortMiseBasParAn\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneMortMiseBas == NULL)
    {
        printf("main - error : tabDeMoyenneMortMiseBas\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneMort == NULL)
    {
        printf("main - error : tabDeMoyenneMort\n");
        return EXIT_FAILURE;
    }
	
	if(mortTabParMois == NULL)
    {
        printf("main - error : mortTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(naissanceTabParMois == NULL)
    {
        printf("main - error : naissanceTabParMois\n");
        return EXIT_FAILURE;
    }
	
	if(tabDeMoyenneNaissance == NULL)
    {
        printf("main - error : tabDeMoyenneNaissance\n");
        return EXIT_FAILURE;
    }
	/*------------------------------------------------------------------------------------------------------------------------*/

	for(i=0; i<nbEssais; i++)
	{
		/*----------------------ici sont effectué les initialisations de variable relative à une expérience----------------------*/
		mois = 0;
		moisParAn = 0;
		an = 0;
		cmptMort = 0;
		cmptNaissance = 0;
		femelleInfertile = 0;
		populationTotale = popDebut;				//réinitialise la population de Lapins à chaque expériences (avec le nombre de lapin au départ choisis)

		male = popDebut / 2;						//la moitié de la population de base sont des males
		femelle = (popDebut / 2) + (popDebut % 2);	//la moitié de la pop de base sont des femelles, + le reste si le nombre choisi au départ est impair
		femelleFertile = femelle;					//on suppose qu'au début de l'expérience, toutes les femelles sont fertiles

		/*boucle qui réinitialise tous les tableaux de population par mois à chaques expériences*/
		initTabLLInt(laperaux, 2);
		
		initTabLLInt(mortMiseBasParAn, (nbMoisTotal/12)+1);
		
		initTabLLInt(popTabParMois, nbMoisTotal);
		initTabLLInt(maleTabParMois, nbMoisTotal);		
		initTabLLInt(femelleTabParMois, nbMoisTotal);
		initTabLLInt(femelleFertileTabParMois, nbMoisTotal);
		initTabLLInt(femelleInfertileTabParMois, nbMoisTotal);
		initTabLLInt(popTabParMois, nbMoisTotal);
		initTabLLInt(laperauxTabParMois, nbMoisTotal);
		initTabLLInt(mortTabParMois, nbMoisTotal);
		initTabLLInt(naissanceTabParMois, nbMoisTotal);
		
		initTab2DLLInt(tabAge, 2, tailleTabAge);
	
		tabAge[0][8] = male;					//on suppose qu'au début de l'expérience, tous les lapins ont le même âge
		tabAge[1][8] = femelle;					//on suppose qu'au début de l'expérience, tous les lapins ont le même âge
		/*----------------------------------------------------------------------------------------------------------------------*/
		while(mois < nbMoisTotal && male > 0 && femelleFertile > 0)
		{
			printf("Expérience n° %d au mois %d\n", i, mois);
			cmptNaissance = 0;
			cmptMort = 0;
			if (moisParAn == 0)											//si 1 an est passé, alors :
			{
				for(j=0; j<12; j++)
				{
					tabPortee[j] = 0;									//boucle qui réinitialise tabPortee pour chaque années passées
				}
				femelleInfertile += infertile(femelle);
				femelleFertile = femelle - femelleInfertile;

				for(j=0; j<femelleFertile; j++)							//cette boucle calcule la mort suite à une mise bas
				{
					random = uniform(0, 1);

					if (random <= 0.15)
					{
						femelleFertile--;
						cmptMort++;
						mortMiseBasParAn[an]++;

						for(k=8; k<tailleTabAge; k++)
						{
							if(tabAge[1][k] > 0)
							{
								tabAge[1][k]--;
								break;
							}
						}
					}
				}

				femelle = femelleFertile + femelleInfertile;									//après la mise à mort, on revérifie la population de femelle

				generatorByTabPercent(tabPorteePourcent, 12, femelleFertile, tabPortee);		//j'initialise le tableau de portée pour cette année (mettre ici tout ce qui est relatif à l'année et evolutif)
				
				/*Dans cette partie, on calcule la mort des lapins ainsi que leur âge et on vérifie la population après ces changements*/
				
				femelleInfertile = mortLapin(tabAge, tailleTabAge, &cmptMort);
				
				ageLapin(tabAge, tailleTabAge);
				verifNbrLapin(&femelle, &male, laperaux, tabAge, tailleTabAge);

				femelleFertile = femelle - femelleInfertile;
				/*---------------------------------------------------------------------------------------------------------------------*/
			}
			else
			{
				/*Dans cette partie, on calcule la mort des lapins ainsi que leur âge et on vérifie la population après ces changements*/
				
				femelleInfertile = mortLapin(tabAge, tailleTabAge, &cmptMort);
				
				ageLapin(tabAge, tailleTabAge);
				verifNbrLapin(&femelle, &male, laperaux, tabAge, tailleTabAge);

				femelleFertile = femelle - femelleInfertile;

				/*---------------------------------------------------------------------------------------------------------------------*/
				cmptNaissance = naissance(tabPortee[moisParAn], femelleFertile, tabAge);
				verifNbrLapin(&femelle, &male, laperaux, tabAge, tailleTabAge);

				femelleFertile = femelle - femelleInfertile;
			}
			
			if (femelleFertile < 0)
			{
				femelleFertile = 0;
			}
			
			if (femelleInfertile < 0)
			{
				femelleInfertile = 0;
			}
			
			if (femelle < 0)
			{
				femelle = 0;
			}
			
			if (male < 0)
			{
				male = 0;
			}

			if (laperaux[0] < 0)
			{
				laperaux[0] = 0;
			}

			if (laperaux[1] < 0)
			{
				laperaux[1] = 0;
			}
			
			/*on met à jour nos tableaux  de population pour pouvoir plus tard les étudiers*/
			populationTotale = male + femelle + laperaux[0] + laperaux[1];
			popTabParMois[mois] = populationTotale;
			maleTabParMois[mois] = male;
			femelleTabParMois[mois] = femelle;
			femelleFertileTabParMois[mois] = femelleFertile;
			femelleInfertileTabParMois[mois] = femelleInfertile;
			laperauxTabParMois[mois] = laperaux[0] + laperaux[1];
			naissanceTabParMois[mois] = cmptNaissance;
			mortTabParMois[mois] = cmptMort;
			/*-----------------------------------------------------------------------------*/
			mois++;
			moisParAn++;

			if (moisParAn == 12)
			{
				moisParAn = 0;
				an++;
			}
			
			if(male == 0 || femelleFertile == 0)
			{
				if(male == 0)
				{
					cmptFinExpMale++;
				}
				cmptFinExp++;
			}
		}
		
		for(j=0; j<mois; j++)
		{
			moyennePopulationPourEssais += popTabParMois[j];
			moyenneMalePourEssais += maleTabParMois[j];
			moyenneFemellePourEssais += femelleTabParMois[j];
			moyenneFemelleFertilePourEssais += femelleFertileTabParMois[j];
			moyenneFemelleInfertilePourEssais += femelleInfertileTabParMois[j];
			moyenneLaperauxPourEssais += laperauxTabParMois[j];
			moyenneMortPourEssais += mortTabParMois[j];
			moyenneNaissancePourEssais += naissanceTabParMois[j];
		}
		
		for(j=0; j<(mois/12)+1; j++)
		{
			moyenneMortMiseBasPourEssais += mortMiseBasParAn[j];
		}
		
		moyennePopulationPourEssais = moyennePopulationPourEssais / mois; 
		moyenneMalePourEssais = moyenneMalePourEssais / mois;
		moyenneFemellePourEssais = moyenneFemellePourEssais / mois;
		moyenneFemelleFertilePourEssais = moyenneFemelleFertilePourEssais / mois;
		moyenneFemelleInfertilePourEssais = moyenneFemelleInfertilePourEssais / mois;
		moyenneLaperauxPourEssais = moyenneLaperauxPourEssais / mois;
		moyenneMortPourEssais = moyenneMortPourEssais / mois;
		moyenneNaissancePourEssais = moyenneNaissancePourEssais / mois;
		moyenneMortMiseBasPourEssais = moyenneMortMiseBasPourEssais / ((mois/12)+1);
		
		tabDeMoyennePopTotale[i] = moyennePopulationPourEssais;					
		tabDeMoyenneFemelle[i] = moyenneFemellePourEssais;
		tabDeMoyenneMale[i] = moyenneMalePourEssais;
		tabDeMoyenneFemelleFertile[i] = moyenneFemelleFertilePourEssais;
		tabDeMoyenneFemelleInfertile[i] = moyenneFemelleInfertilePourEssais;
		tabDeMoyenneLaperaux[i] = moyenneLaperauxPourEssais;
		tabDeMoyenneMort[i] = moyenneMortPourEssais;
		tabDeMoyenneNaissance[i] = moyenneNaissancePourEssais;
		tabDeMoyenneMortMiseBas[i] = moyenneMortMiseBasPourEssais;
		
	}
	/*ici, on affiche les tableaux de résultats ainsi que l'intervalle de confiance pour chacun d'entre eux*/
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de la population totale pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyennePopTotale, nbEssais);
	intervalDeConfiance(tabDeMoyennePopTotale, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de mâles pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneMale, nbEssais);
	intervalDeConfiance(tabDeMoyenneMale, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de femelles pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneFemelle, nbEssais);
	intervalDeConfiance(tabDeMoyenneFemelle, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de femelles fertiles pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneFemelleFertile, nbEssais);
	intervalDeConfiance(tabDeMoyenneFemelleFertile, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de morts suite aux mises-bas pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneMortMiseBas, nbEssais);
	intervalDeConfiance(tabDeMoyenneMortMiseBas, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de femelles infertiles pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneFemelleInfertile, nbEssais);
	intervalDeConfiance(tabDeMoyenneFemelleInfertile, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de naissances pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneNaissance, nbEssais);
	intervalDeConfiance(tabDeMoyenneNaissance, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de laperaux pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneLaperaux, nbEssais);
	intervalDeConfiance(tabDeMoyenneLaperaux, nbEssais);
	printf("###############################################################################################\n");
	
	printf("\n###############################################################################################");
	printf("\n#Tableau sur la moyenne de morts pour chaque expériences#\n");
	afficheTabDouble(tabDeMoyenneMort, nbEssais);
	intervalDeConfiance(tabDeMoyenneMort, nbEssais);
	printf("###############################################################################################\n");
	
	printf("L'expérience s'est arrêtée en cours de route %d fois, dont %d fois par manque de mâles et %d fois par manque de femelles.\n", cmptFinExp, cmptFinExpMale, (cmptFinExp - cmptFinExpMale));
	
	free(tabPortee);
	free(laperaux);
	free(tabDeMoyennePopTotale);
	free(tabDeMoyenneLaperaux);
	free(tabDeMoyenneFemelle);
	free(tabDeMoyenneFemelleFertile);
	free(tabDeMoyenneFemelleInfertile);
	free(tabDeMoyenneMale);
	free(tabDeMoyenneMort);
	free(tabDeMoyenneNaissance);
	free(tabDeMoyenneMortMiseBas);
	free(popTabParMois);
	free(maleTabParMois);
	free(femelleTabParMois);
	free(femelleFertileTabParMois);
	free(femelleInfertileTabParMois);
	free(laperauxTabParMois);
	free(mortTabParMois);
	free(naissanceTabParMois);
	free(mortMiseBasParAn);
	LibereTab2D(tabAge, 2);
	
	return EXIT_SUCCESS;
}