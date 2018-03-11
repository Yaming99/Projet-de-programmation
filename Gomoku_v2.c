#include <stdio.h>
#include <time.h> // pour la fonction rand
#ifdef __unix__ // pour la fonction sleep, compilation sous différentes plateformes
#include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x) // en millisecondes
#endif
#define N 19
//Équipe I : SKT et Batte de Base-ball




int menu()
{
    int choix;
    system("cls"); // efface ce qui est affiché afin d'éviter plusieurs affichages sur la console
    printf("Bienvenue !\n");
    printf("Instructions du jeu : \n\n");
    printf("1) Alignez cinq jetons ou plus verticalement, horizontalement ou en diagonale pour gagner la partie,\n");
    printf("   pendant que votre adversaire essaye de vous bloquer et de cr%cer sa propre rang%ce.\n\n", 130, 130);
    printf("2) Les coups interdits : jouer sur une case d%cj%c occup%ce ou jouer en dehors des limites\n", 130, 133, 130);
    printf("   de l'ar%cne ne vont pas vous disqualifier.\n\n", 138);
    printf("3) Entrez le num%cro de la ligne et de la colonne pour jouer sur la case choisie.\n\n", 130);
    printf("4) Entrez 1 pour affronter un autre joueur, 2 pour jouer contre une IA ou 3 pour voir deux IA s'affronter \n\n>> ");
    scanf("%d", &choix);
    return choix;
}




//affichage de la map
void ps5_afficher(char (*GAME)[N])
{
    int i, j;
    system("cls");
    printf("\n--------------------------------------- Gomoku ------------------------------------\n");
    printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #|\n");
    printf("#     ");
    for(i=0; i<N; i++)
    {
        printf("%02d  ",i); //affiche 0i pour i<10
    }
    printf("#|\n");
    for(i=0; i<N; i++)
    {
        printf("#  %02d ",i); //affiche 0i pour i<10
        for(j=0; j<N; j++)
        {
            printf("%-2c  ",GAME[i][j]); //affiche les espace entre les +
        }
        printf("#|\n");
    }
    printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # \n");
}




//initialisation des cellules
void ps5_init(char (*GAME)[N])
{
    int i,j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            GAME[i][j] = '+';
        }
    }
}




int check_win(char (*GAME)[N])
{
    int i,j;
    for(i=0; i<N; i++) // horizontal
    {
        for(j=0; j<N-4; j++)
        {
            if(GAME[i][j] != '+' && GAME[i][j]==GAME[i][j+1] && GAME[i][j]==GAME[i][j+2] && GAME[i][j] == GAME[i][j+3] && GAME[i][j]== GAME[i][j+4])
                return GAME[i][j];
        }
    }
    for(i=0; i<N-4; i++) // verticale
    {
        for(j=0; j<N; j++)
        {
            if(GAME[i][j] != '+' && GAME[i][j]== GAME[i+1][j] && GAME[i][j]== GAME[i+2][j] && GAME[i][j] == GAME[i+3][j] && GAME[i][j]== GAME[i+4][j])
                return GAME[i][j];
        }
    }
    for(i=0; i<N-4; i++) // diagonale principale
    {
        for(j=0; j<N-4; j++)
        {
            if(GAME[i][j] != '+' && GAME[i][j] == GAME[i+1][j+1] && GAME[i][j] == GAME[i+2][j+2] && GAME[i][j]== GAME[i+3][j+3] && GAME[i][j]== GAME[i+4][j+4])
                return GAME[i][j];
        }
    }
    for(i=0; i<N-4; i++) // autre diagonale
    {
        for(j=0; j<N-4; j++)
        {
            if(GAME[i][j] != '+' && GAME[i][j] == GAME[i+1][j-1] && GAME[i][j] == GAME[i+2][j-2] && GAME[i][j]== GAME[i+3][j-3] && GAME[i][j] == GAME[i+4][j-4])
                return GAME[i][j];
        }
    }
    return 0;
}



// demande où l'utilisateur veut jouer
int play(int joueur, char (*GAME)[N])
{
    int m, n;
    printf("Au tour de joueur %d !\nLigne : ", joueur);
    scanf("%d", &m);
    printf("Colonne : ");
    scanf("%d", &n);
    while(m < 0 || m > N-1 || n < 0 || n > N-1) //Saisie hors dimension
    {
        printf("Erreur : hors dimensions, veuillez recommencer.\nLigne : ");
        scanf("%d", &m);
        printf("Colonne : ");
        scanf("%d", &n);
    }
    while('+' != GAME[m][n]) //saisie sur une case non libre
    {
        printf("Erreur : la case est d%cj%c prise, veuillez recommencer.\nLigne : ", 130, 133);
        scanf("%d", &m);
        printf("Colonne : ");
        scanf("%d", &n);
    }
    if (joueur == 1)
    {
        GAME[m][n] = 'O';
    }
    else
    {
        GAME[m][n] = 'X';
    }
    return 0;
}



// demande si l'utilisateur souhaite rejouer 
int replay(int joueur, int n, char (*GAME)[N])
{
    int choix;
    system("cls");
    ps5_afficher(GAME);
    if (n != 0) printf("Fin de la partie. Joueur %d a gagn%c !\n",joueur, 130);
    else printf("%cgalit%c !\n", 144, 130);
    printf("Voulez vous rejouer ? (Oui : 1, Non : 0)\n");
    scanf("%d", &choix);
    switch(choix)
    {
    case 0:
        break;
    case 1:
        return 1;
    }
    return 0;
}



// IA mouvements aléatoire
int basic_ai(char (*GAME)[N], int n, int a)
{
    return(rand() % n);
}




int main()
{
    int a = menu(); // mode choisi
    char GAME[N][N];
    int count = 0;  // nombre de jetons joués
    int m, n;       // longueur et largeur
    int x, y;       // longueur et largeur
    int nombre, c, b;
    char tab[nombre];
    ps5_init(GAME);
    ps5_afficher(GAME);
    if (a == 3) // IA VS IA
    {
        printf("Combien de joueurs ? (Au moins 2)\n");
        scanf("%d", &nombre);
        for (c = 1; c <= nombre; c++)
        {
            printf("Caract%cre repr%csantant le joueur %d :\n", 138, 130, c);
            scanf("%s", &tab[c-1]);
        }
    }
    while(1)
    {
        if (a == 1) // humain VS humain
        {
            if(120 == count) //nombre maximum de jetons au total
            {
                if (replay(0, 0, GAME) == 0) return 0;
                else main();
            }
            if(0 == count%2)
            {
                play (1, GAME);
                if(check_win(GAME) == 'O') //Rond gagne
                {
                    if (replay(1, 1, GAME) == 0) return 0;
                    else main();
                }
            }
            else
            {
                play(2, GAME);
                if (replay(2, 1, GAME) == 0) return 0;
                else main();
            }
            count++;
            system("cls");
            ps5_afficher(GAME);
        }
        if (a == 2) // humain VS IA
        {
            if(120 == count) // nombre maximum de jetons au total
            {
                if (replay(0, 1, GAME) == 0) return 0;
                else main();
            }
            if(0 == count%2)
            {
                play(1, GAME);
                if(check_win(GAME) == 'O') // Rond gagne
                {
                    if (replay(1, 1, GAME) == 0) return 0;
                    else main();
                }
            }
            else
            {
                x = basic_ai(GAME, N, N); // ligne
                y = basic_ai(GAME, N, N); // colonne
                while(x < 0 || x > N-1 || y < 0 || y > N-1) // joue hors dimension
                {
                    x = basic_ai(GAME, N, N);
                    y = basic_ai(GAME, N, N);
                }
                while('+' != GAME[x][y]) // joue sur une case déjà occupée
                {
                    x = basic_ai(GAME, N, N);
                    y = basic_ai(GAME, N, N);
                }
                GAME[x][y] = 'X';
                if(check_win(GAME) == 'X') //Croix gagne
                {
                    if (replay(2, 1, GAME) == 0) return 0;
                    else main();
                }
            }
            count++;
            system("cls");
            ps5_afficher(GAME);
            sleep(1); // attend 1 seconde
        }
        if (a == 3) // IA VS IA
        {
            if(120 == count) //nombre maximum de jetons au total
            {
                if(replay(0, 0, GAME)==0) return 0;
                else main();
            }
            if(0 == count%2)
            {
                for(b = 0; b < nombre; b++)
                {
                    m = basic_ai(GAME, N, N);
                    n = basic_ai(GAME, N, N);
                    while('+' != GAME[m][n]) // joue sur une case non libre
                    {
                        m = basic_ai(GAME, N, N);
                        n = basic_ai(GAME, N, N);
                    }
                    GAME[m][n] = tab[b];
                    ps5_afficher(GAME);
                    if(check_win(GAME) == tab[b])
                    {
                        if(replay(b+1, 1, GAME) == 0) return 0;
                        else main();
                    }
                    sleep(1);
                }
            }
            count += nombre;
            system("cls");
            ps5_afficher(GAME);
            sleep(1);
        }
    }
}
