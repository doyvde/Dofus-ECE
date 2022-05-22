/*
            int xOrigine,yOrigine,xFinal,yFinal;
                if ((i==0)&&(lattaque==1))
{
    xOrigine = acteur1->x; yOrigine = acteur1->y;
    xFinal = acteur2->x; yFinal = acteur2->y;
}
if ((i==0)&&(lattaque==2))
{
     xOrigine = acteur1->x; yOrigine = acteur1->y;
     xFinal = acteur3->x; yFinal = acteur3->y;
}
if ((i==0)&&(lattaque==3))
{
     xOrigine = acteur1->x; yOrigine = acteur1->y;
     xFinal = acteur4->x; yFinal = acteur4->y;
}
if ((i==1)&&(lattaque==0))
{
     xOrigine = acteur2->x; yOrigine = acteur2->y;
     xFinal = acteur1->x; yFinal = acteur1->y;
}
if ((i==1)&&(lattaque==2))
{
    xOrigine = acteur2->x; yOrigine = acteur2->y;
    xFinal = acteur3->x; yFinal = acteur3->y;
}
if ((i==1)&&(lattaque==3))
{
    xOrigine = acteur2->x; yOrigine = acteur2->y;
    xFinal = acteur4->x; yFinal = acteur4->y;
}
if ((i==2)&&(lattaque==1))
{
    xOrigine = acteur3->x; yOrigine = acteur3->y;
    xFinal = acteur2->x; yFinal = acteur2->y;
}
if ((i==2)&&(lattaque==0))
{
    xOrigine = acteur3->x; yOrigine = acteur3->y;
    xFinal = acteur1->x; yFinal = acteur1->y;
}
if ((i==2)&&(lattaque==3))
{
     xOrigine = acteur3->x; yOrigine = acteur3->y;
     xFinal = acteur4->x; yFinal = acteur4->y;
}
if ((i==3)&&(lattaque==1))
{
     xOrigine = acteur4->x; yOrigine = acteur4->y;
     xFinal = acteur2->x; yFinal = acteur2->y;
}
if ((i==3)&&(lattaque==2))
{
     xOrigine = acteur4->x; yOrigine = acteur4->y;
     xFinal = acteur3->x; yFinal = acteur3->y;
}
if ((i==3)&&(lattaque==0))
{
     xOrigine = acteur4->x; yOrigine = acteur4->y;
     xFinal = acteur1->x; yFinal = acteur1->y;
}


                int distanceX = xFinal - xOrigine;
                int directionX = 0;

                int xactuel = xOrigine;
                int yactuel = yOrigine;
                float a = 0;

                if(distanceX != 0){
                    directionX = distanceX / abs(distanceX);
                }

                if( (xFinal - xOrigine) != 0){
                    a =(float) (yFinal - yOrigine) / (xFinal - xOrigine) ;
                }

                int b = yOrigine - (a*xOrigine);

                while(xactuel != xFinal && yactuel != yFinal){

                    xactuel += directionX;   //j'incrémente mon x dans la bonne direction
                    yactuel = a*xactuel + b; //fonction affine

                    dessineTerrain(page, terrain);
                    //rajouter l'affichage des autres éléments
                    draw_sprite(page, bouledefeu->img, bouledefeu->x=xactuel , bouledefeu->y=yactuel);
        if (nJoueures==2)
        {
            // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);
        }

        if (nJoueures==3)
        {
            // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur3->img, acteur3->x - acteur3->img->w/2, acteur3->y - acteur3->img->h + 8);
        }

        if (nJoueures==4)
        {
            // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur3->img, acteur3->x - acteur3->img->w/2, acteur3->y - acteur3->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur4->img, acteur4->x - acteur4->img->w/2, acteur4->y - acteur4->img->h + 8);

        }
        // Infos ennemi 2
        if(nJoueures==2)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
        }

        // Infos ennemi 3
        if(nJoueures==3)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_right_ex(page,font,792,620,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
        }

        // Infos ennemi 4
        if(nJoueures==4)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_right_ex(page,font,792,620,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
            textprintf_right_ex(page,font,792,640,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[3].num,Joueures[3].pv);
        }


        // Bord console utilisateur
        rect(page,0,560,800,700,makecol(0,255,0 ));
        rect(page,1,561,799,699,makecol(0,255,0 ));
        rect(page,2,562,798,698,makecol(0,255,0 ));
        rect(page,3,563,797,697,makecol(0,255,0 ));

                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche à l'écran
                    rest(20);   //delai poour qu'on puisse voir l'animation
                }*/
