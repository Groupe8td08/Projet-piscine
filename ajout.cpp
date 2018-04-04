#include "ajout.h"

int afficher_menu()
{
    int choi=0;
    if(!choi)
    {
        clear_bitmap(grman::page);
        grman::page=load_bitmap("accueil.bmp",NULL);
        rect(grman::page,300,120,700,180,makecol(0,0,0));
        rect(grman::page,300,220,700,280,makecol(0,0,0));
        rect(grman::page,300,320,700,380,makecol(0,0,0));
        rect(grman::page,350,470,650,530,makecol(0,0,0));
        textprintf_ex(grman::page,font,470,145,makecol(0,0,0),-1,"RESEAU 1");
        textprintf_ex(grman::page,font,470,245,makecol(0,0,0),-1,"RESEAU 2");
        textprintf_ex(grman::page,font,470,345,makecol(0,0,0),-1,"RESEAU 3");
        textprintf_ex(grman::page,font,470,495,makecol(0,0,0),-1,"QUITTER");
        blit(grman::page, screen, 0,0,0,0,1024,768);
        if(mouse_x>300 && mouse_x<700)
        {
            if(mouse_y>120 && mouse_y<180 && mouse_b&1)
            {
                //reseau 1
                choi=1;
            }
            if(mouse_y>220 && mouse_y<280 && mouse_b&1)
            {
                //reseau 2
                choi=2;
            }
            if(mouse_y>320 && mouse_y<380 && mouse_b&1)
            {
                //reseau 3
                choi=3;
            }
            if(mouse_y>470 && mouse_y<530 && mouse_b&1)
            {
                choi=4;
            }
        }
    }

    return choi;
}

void reseau_1(Graph g1)
{
    /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
    g1.update();

    /// Mise à jour générale (clavier/souris/buffer etc...)
    grman::mettre_a_jour();
    if(mouse_y>37 && mouse_y<70 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        g1.save("graphe1.txt");
        std::cout<<"sauver"<<std::endl;
    }
    if(mouse_y>72 && mouse_y<104 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"connexe"<<std::endl;
    }
    if(mouse_y>106 && mouse_y<138 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_connexe"<<std::endl;
    }
    if(mouse_y>140 && mouse_y<172 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_sommet_connexe"<<std::endl;
    }


}

void reseau_2(Graph g1)
{
    /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
    g1.update();

    /// Mise à jour générale (clavier/souris/buffer etc...)
    grman::mettre_a_jour();
    if(mouse_y>37 && mouse_y<70 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        g1.save("graphe2.txt");
        std::cout<<"sauver"<<std::endl;
    }
    if(mouse_y>72 && mouse_y<104 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"connexe"<<std::endl;
    }
    if(mouse_y>106 && mouse_y<138 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_connexe"<<std::endl;
    }
    if(mouse_y>140 && mouse_y<172 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_sommet_connexe"<<std::endl;
    }
}

void reseau_3(Graph g1)
{
    /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
    g1.update();

    /// Mise à jour générale (clavier/souris/buffer etc...)
    grman::mettre_a_jour();
    if(mouse_y>37 && mouse_y<70 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        g1.save("graphe3.txt");
        std::cout<<"sauver"<<std::endl;
    }
    if(mouse_y>72 && mouse_y<104 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"connexe"<<std::endl;
    }
    if(mouse_y>106 && mouse_y<138 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_connexe"<<std::endl;
    }
    if(mouse_y>140 && mouse_y<172 && mouse_x<103 && mouse_x>25 && mouse_b&1)
    {
        std::cout<<"k_sommet_connexe"<<std::endl;
    }
}
