#include <SDL/SDL.h>
#include "Timer.h"
#include "Element.h"
#include "const.h"
#include "Force.h"
#include <vector>
#include <string>

//FORCE
Force::Force(int x, int y)
{
	velX = x;
	velY = y;
}
int Force::getVelX() {
	return velX ;             
}
int Force::getVelY() {
	return velY ;  
}
void Force::setVelX(int x) {
	velX = x ;
}
void Force::setVelY(int y) {
	velY = y ;   
}

//ELEMENT
Element::Element(int setX, int setY, int setWidth, int setHeight, SDL_Surface* setTronche)
{
	//Initialisation des coordonnees
	x = setX;
	y = setY;

	velX = 0 ;
	velY = 0 ;

	speed = 10 ;

	auSol = false ;
	surPlateforme = false ;

	tronche = setTronche ; 

	//Initialisation de la vitesse
	width = setWidth ;
	height = setHeight ;
}

void Element::handle_input(Uint8* keystates)
{
	if( keystates[ SDLK_UP ] ) { 
		//velY -= height / 8;
		velY = 0 - speed ; 
	}
	if( keystates[ SDLK_DOWN ] ) { 
		//velY += height / 8;
		velY = speed ;
	}
	if( keystates[ SDLK_LEFT ] ) { 
		//velX -= width / 8;
		velX = 0 - speed ;
	}
	if( keystates[ SDLK_RIGHT ] ) { 
		//velX += width / 8; 
		velX = speed ;
	}
	if( keystates[ SDLK_o ] ) { 
		//velX += width / 8; 
		y = 0 ;
	}
	if( keystates[ SDLK_SPACE ] && (auSol || surPlateforme) ) { 
		//y = y - 1  ;
		velY = -25 ;
	}
	if(keystates[ SDLK_LEFT ] == false && keystates[ SDLK_RIGHT ] == false && auSol) {                      
		velX = 0;             
	}
	if(keystates[ SDLK_UP ] == false && keystates[ SDLK_DOWN ] == false) {                      
		//velY = 0;             
	}

}

bool Element::checkCollision(Element &A) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calcul les cotes du rectangle A
	leftA = A.x;
	rightA = A.x + A.width;
	topA = A.y;
	bottomA = A.y + A.height;

	//Calcul les cotes du rectangle B
	leftB = x;
	rightB = x + width;
	topB = y;
	bottomB = y + height;
	//Tests de collision
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{ 
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//Si conditions collision detectee
	return true;
}

bool Element::getAuSol() {
	return auSol ;     
}

bool Element::getSurPlateforme() {
	return surPlateforme ;     
}

int Element::getX() {
	return x ;
}

int Element::getY() {
	return y ;
}

int Element::getWidth() {
	return width ;
}

int Element::getHeight() {
	return height ;
}

int Element::getVelX() {
	return velX ;
}

int Element::getVelY() {
	return velY ;
}

int Element::getSpeed() {
	return speed ;
}

void Element::setSpeed(int Speed) {
	speed = Speed ;
}

void Element::move() {
	x += velX;
	y += velY;
	if(x < 0) 
	{
		x = 0 ;
		//x = SCREEN_WIDTH - width ;
	}
	if(y < 0) 
	{
		//y = SCREEN_HEIGHT - height ;
		y = 0 ;
	}
	if(x >= (SCREEN_WIDTH - width)) 
	{
		x = SCREEN_WIDTH - width ;
	}
	//au sol
	if(y >= (SCREEN_HEIGHT - height)) 
	{
		y = SCREEN_HEIGHT - height ;
		velY = 0 ;
		auSol = true ;
	} else {
		auSol = false ;       
	}
}


SDL_Surface* Element::getTronche() {
	return tronche ;     
}

void Element::setTronche(SDL_Surface* setTronche) {
	tronche = setTronche ;     
}

void Element::addForce(Force force) {

	velX += force.getVelX();
	velY += force.getVelY();                         
}

//AVATAR
Avatar::Avatar(int setX, int setY, int setWidth, int setHeight, 
                   SDL_Surface* setTronche, int setTypeAnim) : 
                   Element(setX, setY, setWidth, setHeight, setTronche) {
    numSlide = 0 ;
    mort = false ;
    typeAnim = setTypeAnim ;
        switch(typeAnim) {   
            case 6 :
                for(int i = 0;i < 6;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 85 * i;
                      sprite.y = 0 ;
                      sprite.w = 85 ;
                      sprite.h = 50 ;
                      walk.push_back(sprite) ;
                }
                for(int i = 0;i < 6;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 85 * i ;
                      sprite.y = 55 ;
                      sprite.w = 85 ;
                      sprite.h = 50 ;
                      walk.push_back(sprite) ;
                }
                for(int i = 0;i < 6;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 85 * i ;
                      sprite.y = 110 ;
                      sprite.w = 85 ;
                      sprite.h = 50 ;
                      walk.push_back(sprite) ;
                }
                for(int i = 0;i < 6;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 85 * i ;
                      sprite.y = 165 ;
                      sprite.w = 85 ;
                      sprite.h = 50 ;
                      walk.push_back(sprite) ;
                }
                for(int i = 0;i < 4;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 85 * i ;
                      sprite.y = 220 ;
                      sprite.w = 85 ;
                      sprite.h = 60 ;
                      walk.push_back(sprite) ;
                }
                break ;
           case 4 :
                for(int i = 0;i < 4;++i) {
                      SDL_Rect sprite  ;
                      sprite.x = 38 * i + 1;
                      sprite.y = 130 ;
                      sprite.w = 31 ;
                      sprite.h = 30 ;
                      walk.push_back(sprite) ;
                }         
                break ;
           case 2 :
                  SDL_Rect sprite  ;
                  sprite.x = 0;
                  sprite.y = 0;
                  sprite.w = 43 ;
                  sprite.h = 44 ;
                  walk.push_back(sprite) ;
                  break ;
        
    }
    cycleWalk = 35 ;
    compteurAnim.start() ;
}



void Avatar::move(std::vector<Element> &Elements,std::vector<Missile> &Missiles ) {
	bool libre = true ;	
	x += velX ;	
	if(surPlateforme) {
         velX = 0 ;             
    }
	int i,size ;
	for(i = 0, size = Elements.size(); i < size; ++i) {
		if(checkCollision(Elements[i])) {
            velX = 0 ;             
			// collision droite
			if(x > Elements[i].getX()) {
                velX = 0 ;  
				x = Elements[i].getX() + Elements[i].getWidth();
			// collision gauche	
			} else {     
                x = Elements[i].getX() - width;
			}
		}
	}
	y += velY ;	
    surPlateforme = false ;
	for(i = 0, size = Elements.size(); i < size; ++i) {		
        if(checkCollision(Elements[i])) {
            velY = 0 ; 
			//collision haut
			if(y < Elements[i].getY()){
				y = Elements[i].getY() - height ;
				surPlateforme = true ;
			//collision bas
            } else {
				y = Elements[i].getY() + Elements[i].getHeight();
	     	}
		}
	}
	if(x < 0) 
	{
		x = 0 ;
		velX = 0 ;
	}
	if(y < 0) 
	{
		y = 0 ;
		velY = 0 ;
	}
	if(x >= (LEVEL_WIDTH - width)) 
	{
		x = LEVEL_WIDTH - width ;
	}
	if((y >= (LEVEL_HEIGHT - height))) 
	{
		y = LEVEL_HEIGHT - height ;
		velY = 0 ;
		mort = true ;
	}
	
	//COLLISIONS AVEC LES MISSILES
	for(i = 0, size = Missiles.size(); i < size; ++i) {
		if(checkCollision(Missiles[i])) {
			// collision droite
			if(x  > Missiles[i].getX() + Missiles[i].getWidth()) {
				mort = true ;
			}
			// collision gauche
			if(x + width < Missiles[i].getX()) {
				mort = true ;
			}
			//collision haut
			if(y < Missiles[i].getY()){
				mort = true ;
			}
			// collision bas
			if(y + height > Missiles[i].getY() + Missiles[i].getHeight()) {
				mort = true ;
			}
		}
	}
}

//changement de sprite
void Avatar::setSlide(Uint8* keystates) {
     if( compteurAnim.get_ticks() > cycleWalk ) {
         switch(typeAnim) {
            case 6 :
              if (keystates[ SDLK_RIGHT ]) {
                  if (numSlide >= 5) {
                      numSlide = 0 ;
                  } else {
                      numSlide++  ;
                  }
              }
              if (keystates[ SDLK_LEFT ]) {
                  if (numSlide >= 11 || numSlide < 6 ) {
                      numSlide = 6 ;
                  } else {
                      numSlide++ ;
                  }
              }
              if (!keystates[ SDLK_LEFT ] && !keystates[ SDLK_RIGHT ] && !keystates[ SDLK_UP ]) {
                  if ( numSlide < 6 ) {
                      numSlide = 12 ;
                  }
                  if ( 12 <= numSlide &&  numSlide < 18 ) {
                      numSlide ++ ;
                  }
                  if ( 18 == numSlide) {
                      numSlide = 12  ;
                  }
                  if ( 6 <= numSlide && numSlide < 12 ) {
                      numSlide = 19 ;
                  }
                  if ( 19 <= numSlide &&  numSlide < 23 ) {
                      numSlide ++ ;
                  }
                  if ( 23 <= numSlide) {
                      
                      if ( numSlide == 24) {
                         numSlide = 13  ;
                      } else {
                         numSlide = 19  ;    
                      }
                  }
              }
              if ((!getSurPlateforme()) && (!getAuSol())) {
                  if(getVelX() < 0 || 19 <= numSlide && numSlide < 23 ) {
                       numSlide = 26 ;
                  } else {
                       numSlide = 24  ; 
                  }
              }        
              compteurAnim.start();
              break ;
              
           case 4 :
              if( compteurAnim.get_ticks() > cycleWalk ) {
                
                    if (numSlide >= 3) {
                       numSlide = 0 ;
                   } else {
                       numSlide++  ;
                   }
                 }
              
              compteurAnim.start();
              break ;
        }           
    }
}

Missile::Missile(int setX, int setY, int setWidth, int setHeight, 
                   SDL_Surface* setTronche) : 
                   Element(setX, setY, setWidth, setHeight, setTronche) {
     destroy = false ;
}

void Missile::move() {
	x += velX;
	y += velY;
	if(y < 0) 
	{
		y = 0 ;
	}
	//au sol
	if(y >= (SCREEN_HEIGHT - height)) 
	{
		y = SCREEN_HEIGHT - height ;
		velY = 0 ;
		auSol = true ;
	} else {
		auSol = false ;       
	}
	if(x >= (SCREEN_WIDTH)) {
         destroy = true ;
    }
    if(x < (0 - height)) {
         destroy = true ;
    }
}
