#ifndef Fonction_Lapin_H
#define Fonction_Lapin_H
 
	int fibonacci(int n);
	double uniform(double min, double max);
	void generatorByTabPercent(double *pourcenTab, int inTaille, int inNbreEssais, long long int *Echantillon);
	void intervalDeConfiance(double *moyennePopulationTab, int inNbEssais);
	long long int naissance(long long int inPortee, long long int inFemelle, long long int **tabAge);
	long long int infertile(long long int inFemelle);
	void ageLapin(long long int **tabAge, int tailleTabAge);
	double setIntervalleDeMort(int inNbMois);
	long long int mortLapin(long long int **tabAge, int tailleTabAge, long long int *cmptMort);
	void verifNbrLapin(long long int *inFemelle, long long int *inMale, long long int *laperaux, long long int **tabAge, int tailleTabAge);
	long long int **creatabLL2D(int ligne, int colonne);
	void LibereTab2D(long long int **T, int n);
	void afficheTabLLInt2D(long long int **T, int n, int colonne);
	void afficheTabLLInt(long long int *T, int n);
	void afficheTabDouble(double *T, int n);
	void initTabLLInt(long long int * tab, int inTaille);
	void initTab2DLLInt(long long int ** tab, int inTailleX, int inTailleY);
 
#endif