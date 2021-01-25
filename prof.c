#include <stdio.h>
#include <stdlib.h>
typedef struct noeud
{
    int val ;
    struct noeud * Gauche ;
    struct noeud * Droite;
}Sommet;
typedef Sommet * Arbre ;
// Cette fonction permet de créer un noeud
Arbre Creer_sommet(int x, Arbre G, Arbre D)
{
    Arbre Nouveau;
    Nouveau= (Arbre) malloc(sizeof(Sommet));
    Nouveau ->Gauche = G;
    Nouveau->Droite = D;
    Nouveau->val = x ;
    return Nouveau;
}
//Cette fonction permet de créer une feuille
Arbre CreerFeuille(int x)
{
    return Creer_sommet(x, NULL, NULL);
}
// Parcours Préordre Racine Gauche Droite
void Prefixe(Arbre Racine)  
{ 
    if(Racine!=NULL)
    {
        printf("%d\t",Racine->val);
        Prefixe (Racine->Gauche);
        Prefixe (Racine->Droite);
    }
}

// Parcours Inordre Gauche Racine Droite
void Infixe(Arbre Racine)  
{ 
    if(Racine!=NULL)
    {
        Infixe (Racine->Gauche);
        printf("%d\t",Racine->val);
        Infixe (Racine->Droite);
    }
}
// Parcours Postordre Gauche Droite Racine
void Postfixe(Arbre Racine)  
{ 
    if(Racine!=NULL)
    {
        Postfixe (Racine->Gauche);
        Postfixe (Racine->Droite);
        printf("%d\t",Racine->val);
    }
}

//Retourne le nombre de sommet dans l'arbre
int Nombre(Arbre Racine)
{
    if(Racine)
        return 1+Nombre(Racine->Droite)+Nombre(Racine->Gauche);
    return 0; 
}
// Nombre d'arêtes dans l'arbre
int Taille(Arbre Racine)
{
    //return Nombre(Racine)-1 ; démotré mathétiquement tout le temps coorect pas seulement pour les arbres binaires
    if (Racine==NULL) return 0 ;
    if(Racine->Droite==NULL && Racine->Gauche==NULL)
        return 0 ;
    if( Racine->Droite!=NULL && Racine->Gauche==NULL)
        return 1+Taille(Racine->Droite);
    if(Racine->Droite==NULL && Racine->Gauche!=NULL)
        return 1+Taille(Racine->Gauche);
    //Racine->Droite et Racine->Gauche non NULL
    return 2+Taille(Racine->Droite)+Taille(Racine->Gauche);
}
// Ajout d'une valeur en respectant le principe suivant (Arbre binaire de recherche)
//tout ce qui est à gauche est < à la racine
// tout ce qui est à droite est >= à la racine
// Par conséquent :le parcours infixé gauche la liste crée est triée croissant
Arbre Inserer_Croissant(Arbre Racine ,Arbre Nouveau)
{
    if(Racine==NULL) return Nouveau ;
    if(Racine->val > Nouveau->val)
    {
        Racine->Gauche= Inserer_Croissant(Racine->Gauche, Nouveau);
    }
    else
    {
        if(Racine->val <= Nouveau->val)
        {
            Racine->Droite= Inserer_Croissant(Racine->Droite, Nouveau);
        }
       
    }
    return Racine;
}

int main()
{
    system("cls");
    Arbre Rac=NULL, Nv;
    int x ;    
    do
    {
        printf(" Saisir une valeur (0 arret): ");
        scanf("%d",&x);
        if(x)
        {
            Nv=CreerFeuille(x);
            Rac=Inserer_Croissant(Rac, Nv);
        }
    }while(x!=0);
    printf("PARCOURS INFIXE DE L'ARBRE LES VALEURS SERONT TRIEES \n");
    Infixe(Rac);

    // Arbre T1 = CreerFeuille(12);
    // Arbre T2 = CreerFeuille(14);
    // Arbre T3 = Creer_sommet(10, T1, T2);
    // Arbre T4 = Creer_sommet(15, T3, T3);
    // Prefixe(T4);
    // printf("\n====================\n");
    // Infixe(T4);
    // printf("\n====================\n");
    // Postfixe(T4);
    // printf(" \n NOMBRE DE SOMMETS EST :%d\n",Nombre(T4));
    // printf(" NOMBRE D'ARETES  EST :%d\n",Taille(T4));
    // return 0;
}


