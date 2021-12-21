#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

//Projet reproduction du Jeu de la Vie pour M3301 avec Mr Marhic
//S3 du DUT Informatique année 2021-2022
//Développeurs : Claire Cardona, Théo Fée et Yannick Lonjarret

///Redéfinition des valeurs booléennes en VIVANT et MORT au lien de TRUE et FALSE
#define VIVANT TRUE
#define MORT FALSE
///Constante _TAILLE_GRILLE = 15 pour la taille de la grille de jeu 
#define _TAILLE_GRILLE 15
///Définition d'une constante pour la _PAUSE d'une durée de 1000
#define _PAUSE 1000

using std::this_thread::sleep_for;
using namespace std;

/// <summary>
/// Fonction Principale 4 AfficherGrille
/// Fonction permettant d'afficher la grille du jeu
/// Yannick Lonjarret
/// état : Terminer
/// </summary>
/// <param name="grille">Tableau de booléen à deux dimensions de la grille de jeu</param>
void AfficherGrille(bool grille[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    for(int ligne = 1; ligne <= _TAILLE_GRILLE; ligne++){
        for(int colonne = 1; colonne <= _TAILLE_GRILLE; colonne++){
            if(grille[ligne][colonne] == VIVANT){
                cout << " O ";
            } else {
                cout << " x ";
            }
            if(colonne == _TAILLE_GRILLE) {
                cout << endl;
            }
        }
    }
}

/// <summary>
/// Fonction Secondaire 3.2.1 CopierGrille
/// Permet de copier la grille de jeu pour préparer le nouveau tour
/// Claire Cardona
/// état : Terminer
/// </summary>
/// <param name="grilleAvant">Tableau de Booléen correspondant à la grille de jeu au tour précédent </param>
/// <param name="grilleApres">Préparation du tableau de booléen (grille de jeu) pour le tour en cours</param>
void CopierGrille(bool grilleAvant[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1], bool (&grilleApres)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    for(int ligne = 0; ligne < _TAILLE_GRILLE; ligne++) {
        for(int colonne = 0; colonne < _TAILLE_GRILLE; colonne++) {
            grilleApres[ligne][colonne] = grilleAvant[ligne][colonne];
        }
    }
}

/// <summary>
/// Fonction Secondaire 3.2.3 ChangementEtat
/// Change l'état de la cellule en fonction du nombre de voisin et de l'état au tour précédent
/// Yannick Lonjarret
/// état : Terminer 
/// </summary>
/// <param name="nombreDeVoisinsVivants">Nombre de voisin de la cellule à modifier au tour précédent</param>
/// <param name="EtatAvant">état de la cellule au tour précédent </param>
/// <returns>état de la cellule au tour en cours</returns>
bool ChangementEtat(int nombreDeVoisinsVivants, bool EtatAvant) {
    bool EtatApres = MORT;
    if(EtatAvant == VIVANT) {
        if(nombreDeVoisinsVivants > 1 && nombreDeVoisinsVivants < 4) EtatApres = VIVANT;
    }
    if(EtatAvant == MORT) {
        if(nombreDeVoisinsVivants == 3) EtatApres = VIVANT;
    }
    return EtatApres;
}

/// <summary>
/// Fonction Secondaire 3.2.2 NombreVoisinVivant
/// Trouve le nombre de voisin vivant autour de la cellule
/// Yannick Lonjarret
/// état : Terminer 
/// </summary>
/// <param name="ligne">indice de la grille correspondant à la ligne de la cellule</param>
/// <param name="colonne">indice de la grille correspondant à la colonne de la cellule</param>
/// <param name="grille">tableau de booléen représentant la grille de jeu</param>
/// <returns></returns>
int NombreVoisinVivant(int ligne, int colonne, bool grille[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]) {
    int nombreDeVoisinsVivants = 0;

    for(int ligneCelluleVoisine = -1; ligneCelluleVoisine <= 1; ligneCelluleVoisine++)
    {
        for(int colonneCelluleVoisine = -1; colonneCelluleVoisine <= 1; colonneCelluleVoisine++)
        {
            if(!(ligneCelluleVoisine == 0 && colonneCelluleVoisine == 0))
            {
                if(grille[ligne+ligneCelluleVoisine][colonne+colonneCelluleVoisine] == VIVANT)
                {
                    nombreDeVoisinsVivants++;
                }
            }
        }
    }
    return nombreDeVoisinsVivants;
}

/// <summary>
/// Fonction Secondaire 3.1 MAJGrille 
/// Met à joural grille de jeu pour le nouveau tour 
/// Claire Cardona
/// état : Terminer 
/// </summary>
/// <param name="grille">Tablea à 2 dimensions, grille du jeu correspondant au tour précédent</param>
void MajGrille(bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    int nombreDeVoisinsVivants;
    bool grilleTemp[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1] = {};
    CopierGrille(grille, grilleTemp);

    for(int ligne = 1; ligne < _TAILLE_GRILLE; ligne++) {
        for(int colonne = 1; colonne < _TAILLE_GRILLE; colonne++) {
            nombreDeVoisinsVivants = NombreVoisinVivant(ligne, colonne, grille);
            grilleTemp[ligne][colonne] = ChangementEtat(nombreDeVoisinsVivants, grille[ligne][colonne]);
        }
    }
    CopierGrille(grilleTemp, grille);
}

/// <summary>
/// Fonction Secondaire 2.3.1 VerifCoordonnees
/// Vérification de la saisie de l'utilisateur pour les coordonnées des cellules 
/// Théo Fée
/// état : Terminer
/// </summary>
/// <param name="numeroCellule">Numéro de la cellule par rapport au nombre total de cellules vivantes dans la grille</param>
/// <param name="ligne">Passé par paramètre, numéro de la ligne de la cellule dans la grille</param>
/// <param name="colonne">Passé par paramètre, numéro de la colonne de la cellule dans la grille de jeu</param>
void VerifCoordonnee(int numeroCellule, int &ligne, int &colonne){
    do{
        cout << "\nCellule numero : " << numeroCellule << endl;
        cout << "Coordonnee de la ligne : ";
        cin >> ligne;
        cout << "Coordonnee de la colonne : ";
        cin >> colonne;
    }while(ligne < 1 || ligne > _TAILLE_GRILLE || colonne < 1 || colonne > _TAILLE_GRILLE);
}

/// <summary>
/// Fonction Secondaire 3.2 Continuer 
/// Mise en place d'un délai pour laisser le temps à l'utilisateur de lire la grille 
/// Yannick Lonjarret
/// état : Terminer 
/// </summary>
void Continuer(){
    sleep_for(chrono::milliseconds(_PAUSE));
    cout << "\n" << endl;
}

/// <summary>
/// Fonction Principale 3 Simulation 
/// Fais tourner le Jeu de la vie selon les paramètres entrés par l'utilisateur 
/// Claire Cardona 
/// état : Terminer 
/// </summary>
/// <param name="nombreEtapes">Nombre de tour dans le jeu => combien de fois le programme doit tourner</param>
/// <param name="grille">Grille de jeu avec les cellules vivantes et mortes</param>
void Simulation(int nombreEtapes, bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    for(int Etape = 0; Etape < nombreEtapes; Etape++){
        MajGrille(grille);
        AfficherGrille(grille);
        Continuer();
    }
}

/// <summary>
/// Fonction Principale 1 AfficherRegles 
/// Affichage des règles du jeu pour que l'utilisateur sache comment fonctionne le jeu
/// Yannick Lonjarret
/// état : Terminer 
/// </summary>
void AfficherRegles(){
    cout << "################################# LE JEU DE LA VIE #################################\n" << endl;
    cout << "Regles : " << endl;
    cout << "Le jeu de la vie se deroule dans un tableau a 2 dimensions ou chaque" << endl;
    cout << "case represente une cellule ayant 2 etats possibles : vivant ou mort." << endl;
    cout << "Une cellule interagit avec ses 8 voisins et va changer d'etat (ou non)" << endl;
    cout << "a chaque tour en suivant quelques regles : " << endl;
    cout << "   1) Sous-population : Une cellule vivante va mourir a la prochaine etape si elle a moins de 2 voisins vivants" << endl;
    cout << "   2) Sur-population : Une cellule vivante va mourir a la prochaine etape si elle a plus de 3 voisins vivants" << endl;
    cout << "   3) Etat stable : Une cellule vivante va survivre a la prochaine etape si elle a entre 2 et 3 voisins vivants" << endl;
    cout << "   4) Naissance : Une cellule morte va naitre a la prochaine etape si elle a 3 voisins vivants\n" << endl;
    cout << "Une cellule vivante est representee par un ' O '\n" << endl;
    cout << "################################# LE JEU DE LA VIE #################################\n" << endl;
}

/// <summary>
/// Fonction Secondaire 2.1 NombreEtape
/// Saisie par l'utilisateur du nombre de tour souhaité pour cette partie du jeu de la vie
/// Théo Fée
/// état : Terminer 
/// </summary>
/// <returns>nombre saisie par l'utilisateur correspondant au nombre d'étape dans le jeu</returns>
int NombreEtapes(){
    int nombreEtapes;
    do{
        cout << "Entrer le nombre d'etapes de la simulation : ";
        cin >> nombreEtapes;
    }while(nombreEtapes < 1);
    return nombreEtapes;
}

/// <summary>
/// Fonction Secondaire 2.2 NombreDeCellulesInitiales
/// Saisie par l'utilisateur du nombre initial de cellules vivantes dans le grille de jeu
/// Claire Cardona
/// état : Terminer 
/// </summary>
/// <returns>nombre de cellules vivantes au début de la partie</returns>
int NombreDeCellulesInitiales(){
    int nombreDeCellulesInitiales;
    do{
        cout << "Entrer le nombre de cellules vivantes au debut de la simulation : ";
        cin >> nombreDeCellulesInitiales;
    }while(nombreDeCellulesInitiales < 1 || nombreDeCellulesInitiales > _TAILLE_GRILLE*_TAILLE_GRILLE);
    return nombreDeCellulesInitiales;
}

/// <summary>
/// Fonction Secondaire 2.3 RemplirGrille
/// Remplit la grille avec les cellules vivantes, modification en VIVANT les cellules souhaitées par l'utilisateur
/// Yannick Lonjarret
/// état : Terminer 
/// </summary>
/// <param name="nombreDeCellulesInitiales">Nombre de cellules vivantes souhaitées par l'utilisateur</param>
/// <param name="grille">tableau 2 dimensions correspondant à la grille de jeu</param>
void RemplirGrille(int nombreDeCellulesInitiales, bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    int ligne, colonne;
    for(int cellule = 1; cellule <= nombreDeCellulesInitiales; cellule++){
        VerifCoordonnee(cellule, ligne, colonne);
        grille[ligne][colonne] = VIVANT;
        AfficherGrille(grille);
    }
}

/// <summary>
/// Fonction Secondaire 2.4 Confirmation
/// Demande de confirmation à l'utilisateur pour commencer la simulation du jeu de la vie avec les paramètres entrées par l'utilisateur
/// Théo Fée
/// état : Terminer
/// </summary>
void ConfirmationSimulation(){
    char reponse;
    do{
        cout << "Commencer la simulation ? (O/N) ";
        cin >> reponse;
    }while(reponse != 'o' && reponse != 'O' && reponse != '0');
}

/// <summary>
/// Fonction Principale 2 InitialisationGrille 
/// Initialise la grille de jeu et les paramètres de la partie en cours
/// Théo Fée
/// état : Terminer 
/// </summary>
/// <param name="nombreEtapes">nombre de tour pour la partie du jeu de la vie en cours </param>
/// <param name="grille">tableau à 2 dimensions correspondant à la grille de jeu </param>
void InitialisationGrille(int &nombreEtapes, bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    int nombreDeCellulesInitiales;

    nombreEtapes = NombreEtapes();
    nombreDeCellulesInitiales = NombreDeCellulesInitiales();
    RemplirGrille(nombreDeCellulesInitiales, grille);
    ConfirmationSimulation();
}

/// <summary>
/// Fonction Principale 0 main
/// Déroulement de la partie du jeu de la vie 
/// état : Terminer 
/// </summary>
int main(){
    int nombreEtapes;
    bool grille[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1] = {};

    AfficherRegles();
    InitialisationGrille(nombreEtapes, grille);
    Simulation(nombreEtapes, grille);

    return 0;
}
