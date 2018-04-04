#include "ajout.h"

int main()
{
    int choix=0;
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC])
    {
        if(choix==0)
            choix=afficher_menu();

        if(choix==1)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            g.update();

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
        if(choix==2)
            reseau_2();

        if(choix==3)
            reseau_3();

        if(choix==4)
            break;

        if(mouse_y<25 && mouse_x<60 && mouse_b&1)
            choix=0;

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


