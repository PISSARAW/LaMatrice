#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Matrice{
	int c;
	int l;
	double  *grille;
	double  *second;
};

typedef struct Matrice matrice;

void Initmatrice(matrice *m, int ligne, int colonne)
	{
		int i=0;
		(*m).c=colonne;
		(*m).l=ligne;
		(*m).grille= ( double *)malloc((colonne*ligne)*sizeof( double));
		(*m).nbCasesLibres=ligne*colonne;
		if((*m).grille==NULL)
		{
		    printf("Erreur allocation!\n");
		    exit(-1);
		}
		for(i=0;i<colonne*ligne;i++)
		{
			(*m).grille[i]=0;
		}
		(*m).second= (double*)malloc((ligne)*sizeof( double));
		if((*m).second==NULL)
		{
		    printf("Erreur allocation!\n");
		    exit(-1);
		}
		for(i=0;i<ligne;i++)
		{
			(*m).second[i]=0;
		}
	}

void libereMemoire(matrice *m)
{
    free((*m).grille);
    free((*m).second);
}




void afficher(matrice *m)
{
    int i;int j=0;
	for(i=0;i<((*m).l*(*m).c);i++)
	{
		printf("%0.7gx%d \t",(*m).grille[i],i%(*m).l);
        if((i%((*m).c))==(*m).c-1)
		{
			printf("|%0.7g\t",(*m).second[j]);
			printf("\n");
			j++;
		}
	}
}

int indiceValide(matrice *p, int i, int j)
	{
		if (i>=(*p).l || i<0)
			{
				return 0;
			}
		else
		{
			if (j>=0 && j<(*p).c)
			{
				return 1;
			}
		}

		return 0;
	}



 
/**
 * Fonction modifiant la valeur de la case (ligne, colonne) de la matrice p avec la valeur val
 *
 * \param p: pointeur sur la matrice
 * \param val: entier à mettre dans la case (i,j) si elle existe
 * \param ligne: entier correspondant au numéro de ligne
 * \param colonne: entier correspondant au numéro de colonne
 * \return 1 : si la valeur a été correctement modifiée
 * \return 0 : si la valeur n'a pas été modifiée
 */
 
int setVal(matrice  *p,int ligne,int colonne,double val)
{
    int i;
	if(indiceValide(p,ligne,colonne)==1)
	{
		for(i=0;i<ligne;i++)
		{
			colonne=colonne+(*p).c;
		}
		if ((*p).grille[colonne]==0) // Cas où la valeur à modifier est null
		{
			(*p).grille[colonne]=val;
			return 1;
		}
		else{ // Cas où la valeur à modifier est différent de 0
			(*p).grille[colonne]=val;
			return 1;
		}
		
	}
	else if(indiceValide(p, ligne, colonne)!=1 && indiceValide(p, ligne, colonne-1))
	{
		(*p).second[ligne]=val;
		return 1;
	}
	else
	{
	    return 0;
	}
 
}	
	
	
	
	
 
/**
 * Fonction récupérant la valeur de la case (ligne, colonne) de la matrice
 *
 * \param p: pointeur sur la matrice
 * \param val: entier à mettre dans la case (i,j) si elle existe
 * \param ligne: entier correspondant au numéro de ligne
 * \param colonne: entier correspondant au numéro de colonne
 * \return : la valeur de la case
 */
double getVal(matrice  *p,int ligne,int colonne) //Penser à utiliser modulo n de la colonne
{
    int i;
	if(indiceValide(p,ligne,colonne)==0)
	{
		return (*p).second[ligne]; //Faux retourne -1
	}
	
	else
	{
		for(i=0;i<ligne;i++)
		{
			colonne=colonne+(*p).c;
		}

		return (*p).grille[colonne]; //Vrai retourne la valeur
	}
}

 
/**
 * Fonction qui détermine le pivot
 *
 * \param m: pointeur sur la matrice
 * \return : la position du pivot
 */
int pivot(matrice *m, int n)
{
	int i;int j;
	for(i=0;i<(*m).l;i++)
	{
		if(getVal(m,i,n)!=0)
		{
			return i;
		}
	}
}

void viderBuffer(void)
{
  int c;
  while((c=getchar()) != EOF && c != '\n');

}

 
/**
 * Fonction qui échange deux lignes entrées en paramètre
 *
 * \param m: pointeur sur la matrice
 * \param l1: entier correspondant au numéro de la première ligne choisie 
 * \param l2: entier correspondant au numéro de la deuxième ligne choisie
 */
void  echangerLigne(matrice *m, int l1, int l2)
{
	int i; double s; double c;
	for(i=0;i<(*m).c;i++)
	{
		c=getVal(m, l1, i);
		s=getVal(m, l2, i);
		//printf("c:%d s:%d ", c, s);
		setVal(m, l1, i, s);
		setVal(m, l2, i, c);
		if(i==(*m).c-1)
		{
			c=(*m).second[l1];
			
			(*m).second[l1]=(*m).second[l2];
			
			(*m).second[l2]=c;
			
			//printf("\n");
			
			//printf("c:%d s:%d ", c, s);
		}
	}
}

/**
 * Fonction qui multiplie une ligne par un nombre donné en parmètre
 *
 * \param m: pointeur sur la matrice
 * \param l: entier correspondant au numéro de la ligne choisie 
 * \param n: double correspondant à la valeur qui multiplie
 */
void  multiLigne(matrice *m, int l, double  n)
{
	if(n!=0)
	{
		int i; double c;
		for(i=0;i<(*m).c;i++)
		{
			c=getVal(m, l, i);
			setVal(m, l, i, n*c);
		}
	}
}

/**
 * Fonction qui détermine si une matrice est homogène
 *
 * \param m: pointeur sur la matrice
 * \return 1 : si la matrice est homogène
 */
int homogene(matrice *m)
{
	int i; double somme=0;
	for(i=0;i<(*m).l;i++)
	{
		somme+=(*m).second[i];
	}
	if(somme==pow(1, -10000000000000000000))
	{
		return 1;
	}
	return 0;
}

/**
 * Fonction qui retourne le résultat d'une équation du premier degré
 *
 * \param a: double correspondant 
 * \param b: double correspondant 
 * \return 
 */
double axb(double a,double b)
{
	double x;
	if (b == 0.0)
    {
        return NULL;
    }
        x = -a/b;
   return x;
 

}


void operation(matrice *m, int i, int c)
{
	if(i<(*m).l && c<(*m).c /*&& i==pivot(m, c)*/)
	{
		int j;
		double vc; //valeur de la case de la ligne en cours de modification
		int k;
		double vp; //valeur de la case de la loge du pivot qui se fait multiplier
		double vx; //valeur de la première case du pivot
		double vs; //valeur du second membre modifie
		double vb;
		for(j=i+1;j<(*m).l;j++)
		{
			vx=getVal(m, j, c);
			for(k=c;k<(*m).c+1;k++)
			{
				vp=getVal(m, i, k);
				vc=getVal(m, j, k);
				vb=getVal(m,i,c);
				//printf("\n vc = %g\n", vc);
				//printf("\n coeff = %g\n", axb(vx, vb));
				//printf("\nvc %g + (%g * vp %g) = %g\n", vc,axb(vx, vb), vp, (axb(vx, vb))*vp );
				setVal(m, j, k, (vc+(axb(vx, vb))*vp));
				
			}
			//vs=getVal(m, j, (*m).c+1);
			//(*m).second[j]=vs+axb(vx, vb)*vb;
		}
		
	}
}

int compatible(matrice *m){
	double suite=0;
	suite=(*m).grille[((*m).l*(*m).c)-1];
	printf("%0.13g",suite);
	if(suite != pow(0, 10000000000000000000) && (*m).second[(*m).l-1]!=0)
	{
		return 1;
	}
	return 0;
}

int variables(matrice *m){
	int i; int var=0;
	for(i=0;i<(*m).l;i++)
	{
		if(getVal(m, i, i)!= 0)
		{
			var++;
		}
	}
	return var;
}

void echelonneM(matrice *m){
	int i; int j=0;
	afficher(m);
	printf("\n");
	
	for(i=0;i<(*m).l;i++)
	{
		if(getVal(m, i, i)==pow(0, 10000000000000000000))
		{
			echangerLigne(m, i, i+1);
			afficher(m);
			printf("\n");
		}
		operation(m, i, i);
		afficher(m);
		printf("\n");
	}
	if(compatible(m)==1)
	{
		printf("\nle systeme associé à la matrice echelonnée M est compatible.\n");
		if(variables(m)<(*m).l)
		{
			printf("\nle systeme admet une infinite de solutions\n");
			j=(*m).c-variables(m);
			printf("\nLe systeme admet %d variable(s) lie(s) et %d variable(s) libre(s)\n", variables(m), j);
		}
		printf("\nle systeme admet une unique solution\n");
		printf("\nLe systeme admet %d variable(s) lie(s)\n", variables(m));
	}
	else
	{
		printf("\nle systeme associé à la matrice echelonnée M est incompatible. Il y a une ligne de la forme 0|b\n");
	}
	
}

void remplirM(matrice *m){
	int i;
	for(i=0;i<(*m).l*(*m).c;i++)
	{
		scanf("%g", (*m).grille[i]);
		viderBuffer();
	}
	for(i=0;(*m).l;i++)
	{
		scanf("%g", (*m).second[i]);
		viderBuffer();
	}
}
