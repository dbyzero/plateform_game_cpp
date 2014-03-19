#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_framerate.h>
#include "const.h"
#include "Timer.h"
#include "Element.h"
#include "Avatar.h"
#include "Force.h"
#include "Window.h"
#include <string>
#include <iostream>
#include <stdio.h>

//Event
SDL_Event event ; 
//Récupération du keystates 
Uint8* keystates = SDL_GetKeyState( NULL );
//Images
SDL_Surface* screen = NULL ;
//calcule fps
FPSmanager fps_manager;
//windowed ?
bool windowed = true ;
//image_null
SDL_Surface* image_null = NULL ;
//camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


//initialisation de l'application
int init() {
   // screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,  SDL_SWSURFACE | SDL_RESIZABLE );
     //création de la fenetre de base
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { 
		return EXIT_FAILURE; 
	}
	SDL_WM_SetCaption( "CPC le jeu", NULL );
	

    //Initialisation
    SDL_initFramerate(&fps_manager);
    SDL_setFramerate(&fps_manager,FRAMES_PER_SECOND);
}
//fonction d'asainissage des images
SDL_Surface *load_image( std::string filename ) { 
	SDL_Surface* loadedImage = NULL; 
	SDL_Surface* optimizedImage = NULL;
	loadedImage = SDL_LoadBMP( filename.c_str() );
	if( loadedImage != NULL ) { 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		SDL_FreeSurface( loadedImage ); 
	}
    if( optimizedImage != NULL )
    {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
           	//On met tous les pixels de couleur R 0, G 0xFF, B 0xFF transparent
	        SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
	        return optimizedImage; 
    }
}
//libération des variables
void free() {      
	SDL_FreeSurface( screen ); 
}
//ajouter un calque
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ) { 
	SDL_Rect offset; 
	offset.x = x; 
	offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );     
}

//creation des images du jeu
SDL_Surface* background = NULL; 
SDL_Surface* background_death = NULL; 
SDL_Surface* block = NULL; 


int main( int argc, char *argv[ ] )

{ 
    
    //initialisation du moteur
    init() ;
    
    //Creation de la fenetre
    background = load_image( "ressource/nivo1.bmp" ) ;
    background_death = load_image( "ressource/nivo1_dead.bmp" ) ;
    block = load_image( "ressource/block.bmp" ) ;
    
    //creation du tableau des colision
    std::vector<Element> Elements;
    Element sol(0,400, 2208,100, image_null) ;
    Elements.push_back(sol);
    Element sol2(2272,400, 482,100, image_null) ;
    Elements.push_back(sol2);
    Element sol3(2849,400, 2047,100, image_null) ;
    Elements.push_back(sol3);
    Element sol4(4960,400, 2000,100, image_null) ;
    Elements.push_back(sol4);    
    Element block1(512,273, 30,30, image_null) ;
    Elements.push_back(block1);
    Element block2(705,144, 30,30, image_null) ;
    Elements.push_back(block2);
    Element block3(660,272, 160,30, image_null) ;
    Elements.push_back(block3);
    Element block4(896,336, 64,64, image_null) ;
    Elements.push_back(block4);
    Element block5(1216,305, 64,96, image_null) ;
    Elements.push_back(block5);
    Element block6(1473,272, 62,128, image_null) ;
    Elements.push_back(block6);
    Element block7(1825,272, 62,128, image_null) ;
    Elements.push_back(block7);
    Element block8(2464,272, 96, 32, image_null) ;
    Elements.push_back(block8);
    Element block9(2560,144, 256,32, image_null) ;
    Elements.push_back(block9);
    Element block10(2913,144, 127,32, image_null) ;
    Elements.push_back(block10);
    Element block11(3008,272, 32,32, image_null) ;
    Elements.push_back(block11);
    Element block12(3200,272, 64,32, image_null) ;
    Elements.push_back(block12);
    Element block13(3392,272, 32,32, image_null) ;
    Elements.push_back(block13);
    Element block14(3488,272, 32,32, image_null) ;
    Elements.push_back(block14);
    Element block15(3584,272, 32,32, image_null) ;
    Elements.push_back(block15);
    Element block16(3488,145, 32,32, image_null) ;
    Elements.push_back(block16);
    Element block17(3776,272, 32,32, image_null) ;
    Elements.push_back(block17);
    Element block18(3871,144, 96,32, image_null) ;
    Elements.push_back(block18);
    Element block19(4096,144, 128,32, image_null) ;
    Elements.push_back(block19);
    Element block20(4129,272, 64,32, image_null) ;
    Elements.push_back(block20);    
    Element block21(4289,368, 128,32, image_null) ;
    Elements.push_back(block21);
    Element block22(4319,336, 96,32, image_null) ;
    Elements.push_back(block22);
    Element block23(4351,304, 64,32, image_null) ;
    Elements.push_back(block23);
    Element block24(4384,272, 32,32, image_null) ;
    Elements.push_back(block24);        
    Element block25(4479,272, 32,32, image_null) ;
    Elements.push_back(block25);
    Element block26(4479,304, 64,32, image_null) ;
    Elements.push_back(block26);
    Element block27(4479,336, 96,32, image_null) ;
    Elements.push_back(block27);
    Element block28(4479,368, 128,32, image_null) ;
    Elements.push_back(block28);    
    Element block29(4735,369, 128,32, image_null) ;
    Elements.push_back(block29);
    Element block31(4768,336, 92,32, image_null) ;
    Elements.push_back(block31);
    Element block32(4800,304, 64,32, image_null) ;
    Elements.push_back(block32);
    Element block33(4832,272, 32,32, image_null) ;
    Elements.push_back(block33);    
    Element block34(4960,272, 32,32, image_null) ;
    Elements.push_back(block34);
    Element block35(4960,304, 64,32, image_null) ;
    Elements.push_back(block35);
    Element block36(4960,336, 96,32, image_null) ;
    Elements.push_back(block36);
    Element block37(4960,368, 128,32, image_null) ;
    Elements.push_back(block37);  
    Element block38(5216,336, 64,64, image_null) ;
    Elements.push_back(block38);
    Element block39(5376,272, 128,32, image_null) ;
    Elements.push_back(block39);
    Element block40(5728,336, 64,64, image_null) ;
    Elements.push_back(block40);   
    Element block41(5792,369, 288,32, image_null) ;
    Elements.push_back(block41);
    Element block42(5824,336, 256,32, image_null) ;
    Elements.push_back(block42);
    Element block43(5856,304, 224,32, image_null) ;
    Elements.push_back(block43);
    Element block44(5888,272, 196,32, image_null) ;
    Elements.push_back(block44);
    Element block45(5920,240, 160,32, image_null) ;
    Elements.push_back(block45);
    Element block46(5952,208, 128,32, image_null) ;
    Elements.push_back(block46);
    Element block47(5984,176, 96,32, image_null) ;
    Elements.push_back(block47);
    Element block48(6016,144, 64,32, image_null) ;
    Elements.push_back(block48);
    Element block49(6336,368, 32,32, image_null) ;
    Elements.push_back(block49);
    
    //création du tableau des missiles
    std::vector<Missile> Missiles;
    
    //Création du tabkeau des gens
    Avatar avatar(100,350,50,50,load_image( "ressource/joueur1.bmp"),6) ;
    Avatar slipman(250,370,31,30,load_image( "ressource/slipman.bmp" ),4) ;
    Avatar chat(600,358,42,43,load_image( "ressource/chat2.bmp" ),2) ;
    avatar.setSpeed(10) ;
    slipman.setSpeed(15) ;
    chat.setSpeed(20) ;
    slipman.cycleWalk = 100 ;
    std::vector<Avatar> Avatars;
    std::vector<Avatar>::iterator itAvatars;
    Avatars.push_back(slipman);
    Avatars.push_back(chat);
    Avatars.push_back(avatar);
    
    

    //initialisation des variable de calcule du FPS   
    int frame = 0  ;
    Timer fps;
    Timer update;
    
    //demarage des compteurs
    update.start();
    fps.start();
    
    //forces
    Force Gravite(0,2) ;
    Force missile_droite(1,0) ;
    Force missile_gauche(-1,0) ;

    //ajout du background
    apply_surface( 0, 0, background, screen , &camera);
    
    //ajout de l'avatar
    apply_surface( 100, 400, avatar.getTronche(), screen );

    //Mise à jour de l'écran 
	if( SDL_Flip( screen ) == -1 ) { 
		return EXIT_FAILURE; 
	}
 
    //variable de sortie
	bool quit = false;
	int clignotage = 0;
	
	//*******************************
    /*     BOUCLE DU PROGRAMME     */
    //*******************************
    
	while( quit == false ) {
           if(SCREEN_WIDTH + camera.x >= LEVEL_WIDTH && (Avatars[2].getX() > LEVEL_WIDTH - (SCREEN_WIDTH / 2))) {
                camera.x = LEVEL_WIDTH - SCREEN_WIDTH ;
           } else if(camera.x <= 0 && (Avatars[2].getX() < (SCREEN_WIDTH / 2))) {
                camera.x = 0 ;
           } else {
                camera.x =  Avatars[2].getX() - (SCREEN_WIDTH / 2)  ;    
           }
           Uint8 *keystates = SDL_GetKeyState( NULL );
           
           //dessinage du niveau
           
           if(!Avatars[0].mort) {
                  apply_surface( 0, 0, background, screen, &camera );
           } else {
                  clignotage++ ;
                  if((clignotage % 2) == 0) {
                       apply_surface( 0, 0, background_death, screen, &camera );
                  } else {
                       apply_surface( 0, 0, background, screen, &camera );       
                  }
           }
           
           //récuperation des evenements clavier
           while( SDL_PollEvent( &event ) ) {              
                  //Si l'utilisateur a cliqué sur le X de la fenêtre
			      switch(event.type) {
                      case SDL_QUIT: 
                           quit = true ; 
                           break;
                      default: break;
                  }
                  if( keystates[ SDLK_ESCAPE ] ) { 
                      quit = true ;
                  }
                  if( keystates[ SDLK_a ] ) { 
                      Avatars[0].cycleWalk += 5 ;
                  }
                  if( keystates[ SDLK_q ] ) { 
                      Avatars[0].cycleWalk -= 5 ;
                  }
                  if( keystates[ SDLK_e ] ) { 
                      Avatars[0].cycleWalk = 175 ;
                      Avatars[0].setSpeed(2) ;
                  }
                  if( keystates[ SDLK_r ] ) { 
                      Avatars[0].cycleWalk = 35 ;
                      Avatars[0] .setSpeed(10) ;
                  }
                  if( keystates[ SDLK_x ] &&  !Avatars[0].mort) { 
                      Missile teub(Avatars[0].getX() + 32,Avatars[0].getY() + 19, 15,5, load_image( "ressource/teub.bmp" )) ;
                      teub.setSpeed(2) ;
                      Missiles.push_back(teub);
                  }
                  if( keystates[ SDLK_c ] ) { 
                      Avatars[0].mort = false ;
                  }
                  if( keystates[ SDLK_f ] ) { 
                      if(windowed) {
                             screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
                             windowed = false ;
                      } else {
                             screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,  SDL_SWSURFACE | SDL_RESIZABLE ); 
                             windowed = true ;
                      }
                  }
                  if( keystates[ SDLK_k ] ) { 
                      camera.x -= 5 ;
                  }
                  if( keystates[ SDLK_l ] ) { 
                      camera.x += 5 ;
                  }
           }
          
          //traitements des avatars 
          int i = 0 ;
          for (itAvatars = Avatars.begin(); itAvatars != Avatars.end(); itAvatars++)
          {
                if((*itAvatars).mort) {
                        continue;
                }
                //Recuperation du slide des avatars
                (*itAvatars).setSlide(keystates) ;
                //application des forces
                (*itAvatars).addForce(Gravite) ;
                //reaction des claviers
                (*itAvatars).handle_input(keystates) ;
                //deplacement des elements
                (*itAvatars).move(Elements,Missiles) ;    
                //dessinage des images
                apply_surface( (*itAvatars).getX() - camera.x,(*itAvatars).getY() - camera.y, (*itAvatars).getTronche(), screen, &(*itAvatars).walk[(*itAvatars).numSlide] );
                i++ ;

          }

          //traitements des elements
          for ( int i = 0, size = Elements.size(); i < size; ++i )
          {
              apply_surface( Elements[i].getX() - camera.x, Elements[i].getY() - camera.y, Elements[i].getTronche(), screen);
          }
          
          //traitements des missiles
          for ( int i = 0, size = Missiles.size(); i < size; ++i )
          {
              if(Missiles[i].destroy) {
                        continue;
              }
              Missiles[i].addForce(missile_droite) ;
              Missiles[i].move() ;
              apply_surface( (Missiles[i].getX() - camera.x),(Missiles[i].getY() - camera.y), Missiles[i].getTronche(), screen);
          }
               
          //calcule du FPS
          if( update.get_ticks() > 1 )
          {
                char caption[ 64 ];
                sprintf( caption, "CPC le jeu : %.0f FPS velY:%i slide:%i haut:%i <= %i, bas:%i >= %i, gauche:%i <= %i, droite:%i >= %i, C : %i", 
                         (float)frame / ( fps.get_ticks() / 1000.f ),Avatars[0].getVelY(),Avatars[0].numSlide,
                         Elements[0].getY() + Elements[0].getHeight(), Avatars[0].getY(),
                         Elements[0].getY() , Avatars[0].getY() + Avatars[0].getHeight(),
                         Elements[0].getX() + Elements[0].getWidth(), Avatars[0].getX(),
                         Elements[0].getX(), Avatars[0].getX() + Avatars[0].getWidth(),
                         Avatars[0].checkCollision(Elements[0]));
                SDL_WM_SetCaption( caption, NULL );
                update.start();
          }
          
          //apres avoir dessiner dans le dos de l'ecran on le retourne
          if( SDL_Flip( screen ) == -1 ) { 
		      return EXIT_FAILURE;
          }
          
          //attente passive pour le framerate
          SDL_framerateDelay(&fps_manager);
          frame++;
          if(Avatars[2].mort) {
             quit = true ;                
          }
	}          
             
    free() ;
	SDL_Quit();

	return EXIT_SUCCESS;

}
