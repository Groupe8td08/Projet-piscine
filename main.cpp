#include "grman/grman.h"
#include <iostream>

#include "graph.h"
int afficher_menu()
{
    int choi=0;
    while(!choi)
    {
        clear_bitmap(grman::page);
        grman::page=load_bitmap("accueil.bmp",NULL);
        rectfill(grman::page,200,100,600,160,makecol(0,0,0));
        rectfill(grman::page,200,200,600,260,makecol(0,0,0));
        rectfill(grman::page,200,300,600,360,makecol(0,0,0));
        rectfill(grman::page,250,450,550,510,makecol(0,0,0));
        textprintf_ex(grman::page,font,370,125,makecol(255,255,255),-1,"RESEAU 1");
        textprintf_ex(grman::page,font,370,225,makecol(255,255,255),-1,"RESEAU 2");
        textprintf_ex(grman::page,font,370,325,makecol(255,255,255),-1,"RESEAU 3");
        textprintf_ex(grman::page,font,370,475,makecol(255,255,255),-1,"QUITTER");
        blit(grman::page, screen, 0,0,0,0,1024,768);
        if(mouse_x>200 && mouse_x<600)
        {
            if(mouse_y>100 && mouse_y<160 && mouse_b&1)
            {
                //reseau 1
                choi=1;
            }
            if(mouse_y>200 && mouse_y<260 && mouse_b&1)
            {
                //reseau 2
                choi=2;
            }
            if(mouse_y>300 && mouse_y<360 && mouse_b&1)
            {
                //reseau 3
                choi=3;
            }
            if(mouse_y>450 && mouse_y<510 && mouse_b&1)
            {
                choi=4;
            }
        }
    }

    return choi;
}

void reseau_1()
{

}

void reseau_2()
{
    clear_bitmap(grman::page);
    textprintf_ex(grman::page,font,370,125,makecol(0,255,0),-1,"RESEAU 2");
    rectfill(grman::page,3,3,60,25,makecol(255,255,255));
    textprintf_ex(grman::page,font,5,10,makecol(0,0,0),-1,"quitter");
    blit(grman::page, screen, 0,0,0,0,1024,768);
}

void reseau_3()
{
    clear_bitmap(grman::page);
    textprintf_ex(grman::page,font,370,125,makecol(0,0,255),-1,"RESEAU 3");
    rectfill(grman::page,3,3,60,25,makecol(255,255,255));
    textprintf_ex(grman::page,font,5,5,makecol(0,0,0),-1,"quitter");
    blit(grman::page, screen, 0,0,0,0,1024,768);
}

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
        {
            choix=afficher_menu();
        }
        if(choix==1)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            g.update();

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }

        if(choix==2)
        {
            reseau_2();
        }
        if(choix==3)
        {
            reseau_3();
        }

        if(choix==4)
        {
            break;
        }
        if(mouse_y<25 && mouse_x<60 && mouse_b&1)
        {
            choix=0;
        }

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


