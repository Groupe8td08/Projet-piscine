#include "ajout.h"

int main()
{
    int choix=0;
    int fonction=0;
    int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0;

    BITMAP* pagina;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
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
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC])
    {
        if(choix==0)
            choix=afficher_menu(pagina);

        if(choix==1)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            fonction=g1.updatex(fonction,&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,choix);

            /// Mise à jour générale (clavier/souris/buffer etc...)
            //grman::mettre_a_jour();
            reseau_1(g1);
        }
        if(choix==2)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            fonction=g2.updatex(fonction,&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,choix);

            /// Mise à jour générale (clavier/souris/buffer etc...)
            //grman::mettre_a_jour();
            reseau_2(g2);
        }
        if(choix==3)
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            fonction=g3.updatex(fonction,&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,choix);

            /// Mise à jour générale (clavier/souris/buffer etc...)
            //grman::mettre_a_jour();
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
        {
            tempsur(choix, &g1, &g2, &g3);
        }

        if(mouse_y<35 && mouse_x<103 && mouse_x>25 && mouse_b&1)
        {
            choix=0;
        }
        grman::mettre_a_jour(fonction);
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


