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
    textprintf_ex(grman::page,font,5,10,makecol(0,0,0),-1,"quitter");
    blit(grman::page, screen, 0,0,0,0,1024,768);
}
