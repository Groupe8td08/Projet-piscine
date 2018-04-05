#include "ajout.h"

int main()
{
    int choix=0;
    int fonction=0;
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

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC])
    {
        if(choix==0)
            choix=afficher_menu(pagina);

        if(choix==1)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            fonction=g1.updatex(fonction);

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            reseau_1(g1);
        }
        if(choix==2)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            fonction=g2.updatex(fonction);

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            reseau_2(g2);
        }
        if(choix==3)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            fonction=g3.updatex(fonction);

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
            reseau_3(g3);
        }
        if(choix==4)
            break;

        if(fonction==1)
            std::cout<<"1"<<std::endl;

        if(fonction==2)
            std::cout<<"2"<<std::endl;

        if(fonction==3)
            std::cout<<"3"<<std::endl;

        if(fonction==4)
            std::cout<<"4"<<std::endl;

        if(mouse_y<35 && mouse_x<103 && mouse_x>25 && mouse_b&1)
        {
            choix=0;
        }
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


