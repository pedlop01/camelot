// Class automatically generated by Dev-C++ New Class wizard

#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include <math.h>
#include "entradasortida.h"

#include "symboltable.h"
#include "fxhandler.h"

#include "defines.h"

#include "mundo.h"
#include "static_image.h"
#include "animation.h"
#include "characterstatehandler.h"

#define abs(x) (x > 0 ? x : -(x))

/*
 * Personaje del juego. Actualmente es el personaje principal pero despu�s
 * se especializar� en personaje principal, ayudante o enemigo
 */
class character
{
    private:            
        int am_i_a_frog;
            
        int current_state;
        int previous_state;
        int warrior_sentido;    
        
        int carrying_object;
        int offered_object;
                    
        
        bool contact_down;         // Actualmente hay colisi�n por debajo
        bool contact_up;           // Actualmente hay colisi�n por arriba
        unsigned int mseg_chk ;    // Checkpoint del tiempo. �til para las animaciones
        float pixel_y_chk;  // Checkpoint de la posicion del personaje en un
        float pixel_x_chk;  // momento determinado
        
        float current_x_ant;         // Last last valid position
        float current_y_ant;  
        float current_x;             // Last valid position
        float current_y;
        float jumpTime;
       
        // animations
        string                     animationFile;
        entradaSortida             fitxerAnimacio;        
        static_image               animationBitmap;
        map<int, animation>        animacion;
        int                        subAnimacion;
        list<sprite_ptr>::iterator currentSprite;
        unsigned int               mseg_chk_anim;
        
        // drawing
        BITMAP* buffer;            // buffer actual (pantalla de juego)
        
        symbolTablePtr symbTable;
        fxHandler* soundHandler;
        
        characterStateHandler stateHandler;
        
        bool en_escaleras_left;
        bool en_escaleras_right;        
        
        unsigned int forceStateUpdate;
        unsigned int keepMoving;       
        
        bool state_change_fx;     

	public:
		character(symbolTablePtr _symbolTable, fxHandler* _soundHandler);               // class constructor
		~character();      		   // class destructor
		
		void SetInitialState();	
		void SetInitialState(int currentState, int prevState);			
		
        void SetWarriorForm(int var)      { am_i_a_frog = var;     }
        void SetWarriorState(int var)     { current_state = var;   }
        void SetWarriorPrevState(int var) { previous_state = var;  }
		void SetWarriorSentido(int var)   { warrior_sentido = var; stateHandler.SetDirection(var); }
		
		void ClearImportantVars();
		
		void handleState(int entrada_teclado, unsigned int mseg_global);
		void computeNewPositionUsingCurrentState(mundo *world, int entrada_teclado, float &x, float &y);
		void computeNewPositionUsingCollisionDetection(mundo *world, int entrada_teclado, float &x, float &y, unsigned int mseg_global);
		void computeNextAnimationSprite(unsigned int mseg_global);
		
		// animations
		void   SetAnimationFile(string n) { animationFile = n;    }
		string GetAnimationFile()         { return animationFile; }
		void   loadAnimations(char* file);
		
		// drawing
		void drawCharacterInWorld(mundo* world, BITMAP* world_bmp, int posX, int posY);

		void SetCurrentState(int s)   { current_state = s; }
		void SetCurrentX(float x)     { current_x = x;     }
		void SetCurrentY(float y)     { current_y = y;     }

		int GetCurrentState()   { return current_state; }
		float GetCurrentX()     { return current_x;     }
		float GetCurrentY()     { return current_y;     }
		
		inline int GetCurrentSizeX() { return (*currentSprite)->xSize;   }		
		inline int GetCurrentSizeY() { return (*currentSprite)->ySize;   }				


		int GetSentido()      { return warrior_sentido; }
		
		bool SwordCollision(mundo* world, int x, int y, int xSize, int ySize);
		bool EnemyCollision(BITMAP* buffer, mundo* world, int x, int y, int xSize, int ySize, int x_, int y_);		
		
		void AddInternalVarsToSymbTable();
};

#endif // CHARACTER_H
