#include <vector>

//FORCE
class Force
{
	private :
		int  velX, velY ;
	public:
		Force(int,int);
		int getVelX();
		int getVelY();
		void setVelX(int velX) ;
		void setVelY(int velY) ;
};

//ELEMENT
class Element
{
	protected :
		int x, y, width, height, velX, velY, speed;
		bool auSol ;
		bool surPlateforme ;

		SDL_Surface* tronche ;
	public:
		Element(int x ,int y,int w ,int h, SDL_Surface* tronche);
		void handle_input(Uint8* keystates) ;
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		int getVelX();
		int getVelY();
		int getVelWidth();
		int getVelHeight();
		int getSpeed();
		bool getAuSol();
		bool getSurPlateforme();
		void setSpeed(int Speed) ;
		void move() ;
		void setTronche(SDL_Surface* tronche) ;
		bool checkCollision(Element &A) ;
		SDL_Surface* getTronche() ;
		void addForce(Force force) ;
};

//Missile
class Missile : public Element {             
	public :
		Missile(int x , int y, int width, int height, SDL_Surface* tronche);
		void move() ;
		bool destroy ;
		
};

//AVATAR
class Avatar : public Element {             
	public :
		Avatar(int x , int y, int width, int height, SDL_Surface* tronche, int typeAnim);
		void move(std::vector <Element> &Decord,std::vector<Missile> &Missiles) ;
		void setSlide(Uint8* keystates) ;
		
		int cycleWalk ;
		int numSlide ;
		int typeAnim ;
		
		bool mort ;
		
		Timer compteurAnim ;;
		std::vector<SDL_Rect> walk ;
};

