#include "ajout.h"

int main()
{
    int choix=0;
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe


    Graph g1;
    Graph g2;
    Graph g3;
    g1.make_example("graphe1.txt");
    g2.make_example("graphe2.txt");
    g3.make_example("graphe3.txt");

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC])
    {
        if(choix==0)
            choix=afficher_menu();

        if(choix==1)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g1.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            if(key[KEY_SPACE])
            {
                g1.save("graphe1.txt");
            }
        }
        if(choix==2)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g2.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            if(key[KEY_SPACE])
            {
                g2.save("graphe2.txt");
            }
        }

        if(choix==3)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g3.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            if(key[KEY_SPACE])
            {
                g3.save("graphe3.txt");
            }
        }

        if(choix==4)
            break;

        if(mouse_y<25 && mouse_x<60 && mouse_b&1)
        {

            choix=0;

        }


    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


