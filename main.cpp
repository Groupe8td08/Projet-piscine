#include "ajout.h"

int main()
{
    int choix=0;
    BITMAP* pagina;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe

    pagina=load_bitmap("accueil.bmp",NULL);
    Graph g1;
    Graph g2;
    Graph g3;
    g1.make_example("graphe1.txt");
    g2.make_example("graphe2.txt");
    g3.make_example("graphe3.txt");

    ///Tests connexit� graph::connexe() ( pb de lecture ex:graphe1 manque 3 liens)
    g1.connexe();
//    g2.connexe();
//    g3.connexe();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC])
    {
        if(choix==0)
            choix=afficher_menu(pagina);

        if(choix==1)
        {
            reseau_1(g1);
        }
        if(choix==2)
        {
            reseau_2(g2);
        }
        if(choix==3)
        {
            reseau_3(g3);
        }
        if(choix==4)
            break;

        if(mouse_y<35 && mouse_x<103 && mouse_x>25 && mouse_b&1)
        {
            choix=0;
        }
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


