#include "ajout.h"

int afficher_menu()
{
    int choi=0;
    if(!choi)
    {
        clear_bitmap(grman::page);
        grman::page=load_bitmap("accueil.bmp",NULL);
        rect(grman::page,200,100,600,160,makecol(0,0,0));
        rect(grman::page,200,200,600,260,makecol(0,0,0));
        rect(grman::page,200,300,600,360,makecol(0,0,0));
        rect(grman::page,250,450,550,510,makecol(0,0,0));
        textprintf_ex(grman::page,font,370,125,makecol(255,255,255),-1,"RESEAU 1");
        textprintf_ex(grman::page,font,370,225,makecol(255,255,255),-1,"RESEAU 2");
        textprintf_ex(grman::page,font,370,325,makecol(150,150,150),-1,"RESEAU 3");
        textprintf_ex(grman::page,font,370,475,makecol(0,0,0),-1,"QUITTER");
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
