#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

#define VIVANT TRUE
#define MORT FALSE
#define _TAILLE_GRILLE 15
#define _PAUSE 1000

using std::this_thread::sleep_for;
using namespace std;

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

void CopierGrille(bool grilleAvant[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1], bool (&grilleApres)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    for(int ligne = 0; ligne < _TAILLE_GRILLE; ligne++) {
        for(int colonne = 0; colonne < _TAILLE_GRILLE; colonne++) {
            grilleApres[ligne][colonne] = grilleAvant[ligne][colonne];
        }
    }
}

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

int NombreDeVoisinsVivants(int ligne, int colonne, bool grille[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]) {
    int nombreDeVoisinsVivants = 0;

    for(int ligneCelluleVoisine = -1; ligneCelluleVoisine <= 1; ligneCelluleVoisine++){
        for(int colonneCelluleVoisine = -1; colonneCelluleVoisine <= 1; colonneCelluleVoisine++){
            if(!(ligneCelluleVoisine == 0 && colonneCelluleVoisine == 0)){
                if(grille[ligne+ligneCelluleVoisine][colonne+colonneCelluleVoisine] == VIVANT){
                    nombreDeVoisinsVivants++;
    }}}}
    return nombreDeVoisinsVivants;
}

void MajGrille(bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    int nombreDeVoisinsVivants;
    bool grilleTemp[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1] = {};
    CopierGrille(grille, grilleTemp);

    for(int ligne = 1; ligne < _TAILLE_GRILLE; ligne++) {
        for(int colonne = 1; colonne < _TAILLE_GRILLE; colonne++) {
            nombreDeVoisinsVivants = NombreDeVoisinsVivants(ligne, colonne, grille);
            grilleTemp[ligne][colonne] = ChangementEtat(nombreDeVoisinsVivants, grille[ligne][colonne]);
        }
    }
    CopierGrille(grilleTemp, grille);
}

void VerifCoordonnee(int numeroCellule, int &ligne, int &colonne){
    do{
        cout << "\nCellule numero : " << numeroCellule << endl;
        cout << "Coordonnee de la ligne : ";
        cin >> ligne;
        cout << "Coordonnee de la colonne : ";
        cin >> colonne;
    }while(ligne < 1 || ligne > _TAILLE_GRILLE || colonne < 1 || colonne > _TAILLE_GRILLE);
}

void Continuer(){
    sleep_for(chrono::milliseconds(_PAUSE));
    cout << "\n" << endl;
}

void Simulation(int nombreEtapes, bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    for(int Etape = 0; Etape < nombreEtapes; Etape++){
        MajGrille(grille);
        AfficherGrille(grille);
        Continuer();
    }
}

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

int NombreEtapes(){
    int nombreEtapes;
    do{
        cout << "Entrer le nombre d'etapes de la simulation : ";
        cin >> nombreEtapes;
    }while(nombreEtapes < 1);
    return nombreEtapes;
}

int NombreDeCellulesInitiales(){
    int nombreDeCellulesInitiales;
    do{
        cout << "Entrer le nombre de cellules vivantes au debut de la simulation : ";
        cin >> nombreDeCellulesInitiales;
    }while(nombreDeCellulesInitiales < 1 || nombreDeCellulesInitiales > _TAILLE_GRILLE*_TAILLE_GRILLE);
    return nombreDeCellulesInitiales;
}

void RemplirGrille(int nombreDeCellulesInitiales, bool (&grille)[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1]){
    int ligne, colonne;
    for(int cellule = 1; cellule <= nombreDeCellulesInitiales; cellule++){
        VerifCoordonnee(cellule, ligne, colonne);
        grille[ligne][colonne] = VIVANT;
        AfficherGrille(grille);
    }
}

void DebutSimulation(){
    char reponse;
    do{
        cout << "Commencer la simulation ? (O/N) ";
        cin >> reponse;
    }while(reponse != 'o' && reponse != 'O' && reponse != '0');
}

int main(){
    int nombreDeCellulesInitiales, nombreEtapes;
    bool grille[_TAILLE_GRILLE+1][_TAILLE_GRILLE+1] = {};

    AfficherRegles();
    nombreEtapes = NombreEtapes();
    nombreDeCellulesInitiales = NombreDeCellulesInitiales();
    RemplirGrille(nombreDeCellulesInitiales, grille);
    DebutSimulation();
    Simulation(nombreEtapes, grille);
    return 0;
}
