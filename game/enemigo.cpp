// Class automatically generated by Dev-C++ New Class wizard

#include "enemigo.h" // class's header file

// class constructor
enemigo::enemigo()
{
    assert(false);   // don't use this constructor!
}

enemigo::enemigo(
    symbolTablePtr _symbolTable,
    fxHandler* _soundHandler,    
    int _id, 
    int type, 
    int initial_state, 
    int sentido, 
    int sentido_vert, 
    int x, 
    int y, 
    int despx, 
    int despy, 
    int velocidad, 
    const char *animationFile)
{           
    id                       = _id;
    ini_state                = initial_state;
    current_state            = initial_state;
    previous_state           = current_state;
    enemigo_sentido          = sentido;
    enemigo_sentido_vertical = sentido_vert;
    
    reset = false;
    
    contact_down = false;
    
    mseg_chk = 0;
    mseg_chk_anim = 0;
    
    // load animations
    sprintf(origFile, "%s", animationFile);  
    this->loadAnimations(animationFile);
    subAnimacion = 0;
    
    currentSprite = animacion[current_state].sprites.begin();

    current_x = x;
    current_y = y;
    
    ini_x = x;
    ini_y = y;
    ini_sentido = sentido;
    ini_sentido_vertical = sentido_vert;    
    enemyType = type;
    desp_x = despx;
    desp_y = despy;
    pixel_x_chk = x;
    pixel_y_chk = y;
    vel = velocidad;
    
    killed     = false;
    deadAtMseg = 0;
    
    enemigoEnRango = false;
    
    activated = true;
    
    symbTable = _symbolTable;
    soundHandler = _soundHandler;
    
    char enemy_activated[80];
    sprintf(enemy_activated, "enemy_activated_%d", id);
    symbTable->addVarToSymbolTable((char*)enemy_activated, (unsigned long*)&activated);    
    char enemy_reset[80];
    sprintf(enemy_reset, "enemy_reset_%d", id);
    symbTable->addVarToSymbolTable((char*)enemy_reset, (unsigned long*)&reset);        
}

void enemigo :: SetStateToInitial()
{
    reset  = false;
    
    killed = false; 

    current_x = ini_x;
    current_y = ini_y;
    pixel_x_chk = current_x;
    pixel_y_chk = current_y;
    
    previous_state = ini_state;
    current_state  = ini_state;
    
    enemigo_sentido = ini_sentido; 
    enemigo_sentido_vertical = ini_sentido_vertical;
    
    deadAtMseg = 0;
    
    subAnimacion = 0;
    currentSprite = animacion[current_state].sprites.begin();
    
    enemigoEnRango = false;
    activated = true;
}

// class destructor
enemigo::~enemigo()
{
    animacion.clear();
}

void enemigo :: computeNewPositionUsingCurrentState(mundo *world, int &x, int &y, unsigned int mseg)
{        
    // Calculamos la nueva posicion segun los inputs de teclado
    if( (current_state == ENEMIGO_CAMINANDO || current_state == ENEMIGO_SALTANDO || current_state == ENEMIGO_CAYENDO) && 
         enemigo_sentido == ENEMIGO_SENTIDO_DERECHA                                )    // RIGHT
    {
        if( x + 1 > world->GetScreenNewX() - world->GetTileSizeRatio()*(*currentSprite)->xSize ) 
            x = world->GetScreenNewX() - world->GetTileSizeRatio()*(*currentSprite)->xSize;
        else
            x += 1;
    }    
    if( (current_state == ENEMIGO_CAMINANDO || current_state == ENEMIGO_SALTANDO || current_state == ENEMIGO_CAYENDO) && 
        enemigo_sentido == ENEMIGO_SENTIDO_IZQUIERDA                              )   // LEFT
    {
        if( x - 1 < 0 )
            x = 0;
        else
            x -= 1;
    }
    if( current_state == ENEMIGO_SALTANDO )   // UP
    {
         if( y - 1 < 0 )
             y = 0;
         else
             y -= 1;
    }
    if( current_state == ENEMIGO_CAYENDO )   // DOWN
    {
         if( y + 1 > world->GetScreenNewY() - world->GetTileSizeRatio()*(*currentSprite)->xSize )
         {
             y = world->GetScreenNewY() - world->GetTileSizeRatio()*(*currentSprite)->xSize;
         }
         else
         {
             y += 1;
         }
    }
}

void enemigo :: handleStateEnemyDespX(unsigned int mseg_global)
{
    assert( current_state == ENEMIGO_CAMINANDO || current_state == ENEMIGO_PARADO );
    if( current_state == ENEMIGO_CAMINANDO )
    {        
        if( abs((int)(pixel_x_chk - current_x)) > abs(desp_x) )
        {
            if( enemigo_sentido == ENEMIGO_SENTIDO_IZQUIERDA )
            {
                enemigo_sentido = ENEMIGO_SENTIDO_DERECHA;
                pixel_x_chk = current_x;
            }
            else
            {
                enemigo_sentido = ENEMIGO_SENTIDO_IZQUIERDA;
                pixel_x_chk = current_x;
            }
        }
    }
   // else enemigo parado     
}

void enemigo :: handleStateEnemyDespXAndY(unsigned int mseg_global)
{
    if( current_state == ENEMIGO_SALTANDO )
    {        
        previous_state = current_state;             
        if( abs((int)(pixel_x_chk - current_x)) > abs(desp_x) )
        {
            if( enemigo_sentido == ENEMIGO_SENTIDO_IZQUIERDA )
            {
                enemigo_sentido = ENEMIGO_SENTIDO_DERECHA;
                pixel_x_chk = current_x;
            }
            else
            {
                enemigo_sentido = ENEMIGO_SENTIDO_IZQUIERDA;
                pixel_x_chk = current_x;
            }
        }
        if( abs((int)(pixel_y_chk - current_y)) > abs(desp_y) )
        {
            current_state = ENEMIGO_CAYENDO; 
            pixel_y_chk = current_y;
        }
    }
    else if( current_state == ENEMIGO_CAYENDO )
    {    
        previous_state = current_state;             
        if( abs((int)(pixel_x_chk - current_x)) > abs(desp_x) )
        {
            if( enemigo_sentido == ENEMIGO_SENTIDO_IZQUIERDA )
            {
                enemigo_sentido = ENEMIGO_SENTIDO_DERECHA;
                pixel_x_chk = current_x;
            }
            else
            {
                enemigo_sentido = ENEMIGO_SENTIDO_IZQUIERDA;
                pixel_x_chk = current_x;
            }
        }
        if( abs((int)(pixel_y_chk - current_y)) > abs(desp_y) )
        {         
            current_state = ENEMIGO_SALTANDO;
            pixel_y_chk = current_y; 
        }
    }

}

void enemigo :: handleStateEnemyDespYNoLoop(unsigned int mseg_global)
{
    assert( current_state == ENEMIGO_SALTANDO );
    if( abs((int)(pixel_y_chk - current_y)) > abs(desp_y) )
    {
        killed = true;
    }
}


// BIG FIXME!!!
void enemigo :: handleStateEnemyDragon(character* warrior, unsigned int mseg_global)
{
     if( current_state == ENEMIGO_PARADO )
     {
         if( warrior->GetCurrentX() > (this->GetCurrentX() - SCREEN_X) )
         {
             if( enemigoEnRango == false )
             {
                 mseg_chk = mseg_global;
                 enemigoEnRango = true;
             }
         }
         else
         {
             enemigoEnRango = false;
         }
         if( enemigoEnRango && (mseg_global - mseg_chk > 5000) )
         {
             previous_state = current_state;
             current_state = ENEMIGO_CAMINANDO;
             if( !soundHandler->getEnabled(7) )
             {
                 soundHandler->setEnabled(7, true);     
                 soundHandler->playSound(7);
             }             
         }
         else
                 soundHandler->setEnabled(7, false);     
     }
     else if( current_state == ENEMIGO_CAMINANDO )
     {
         if( warrior->GetCurrentX() < (this->GetCurrentX() - SCREEN_X) )
         {
             enemigoEnRango = false;
             previous_state = current_state;
             current_state = ENEMIGO_PARADO;
         }
         else
         {
             previous_state = current_state;
             current_state = ENEMIGO_CAMINANDO;
         }
     }
}

void enemigo :: handleState(character* warrior, unsigned int mseg_global)
{             
    if( killed )
    {
        deadAtMseg = mseg_global;
        previous_state = current_state;
        current_state = ENEMIGO_MUERTO;
    }
    // Ojo, cada vez que se cambia de estado se debe poner subAnimacion a 0
    if( current_state != previous_state )
    {
        subAnimacion = 0;
    }             
    
    if( current_state == ENEMIGO_MUERTO )
        return;
         
    if( enemyType >= 1 && enemyType <= 5 )   // FIXME
    {
         handleStateEnemyDespX(mseg_global);    // and wait states
    }
    else if( enemyType == 6 )
    {
        this->handleStateEnemyDespXAndY(mseg_global);
    }
    else if( enemyType == 7 )
    {
        this->handleStateEnemyDespYNoLoop(mseg_global);
    }
    else if( enemyType == 8 )
    {
        this->handleStateEnemyDragon(warrior, mseg_global);
    }        
}

void enemigo :: computeNewPositionUsingCollisionDetection(mundo *world, unsigned int mseg_global)
{
    int x_ant = current_x;
    int y_ant = current_y;    
    current_x_ant = current_x;
    current_y_ant = current_y;

    this->computeNewPositionUsingCurrentState(world, current_x, current_y, mseg_global);
    this->computeNextAnimationSprite(mseg_global);
    
    if( current_state == ENEMIGO_MUERTO )
        return;
          
    // Deteccion de colisiones con la nueva posicion y computo de una posicion segura
    // en caso de colision
    bool col_right = false;
    bool col_left  = false;
    bool col_up    = false;
    bool col_down  = false;

    if( current_x != x_ant )
    {
        if( current_x > x_ant )
        {
             for( int i = current_y + 1 ; (i < current_y + world->GetTileSizeRatio()*(*currentSprite)->ySize - 1) && !col_right ; i++ )    
             {
                 col_right = world->GetTileByCoord(current_x + world->GetTileSizeRatio()*(*currentSprite)->xSize, i)->GetCollisionable();
             }
        }
        else
        {
             for( int i = current_y + 1 ; (i < current_y + world->GetTileSizeRatio()*(*currentSprite)->ySize - 1) && !col_left ; i++ )     
             {
                 col_left = world->GetTileByCoord(current_x, i)->GetCollisionable();
             }
        }
    }
    if( current_y != y_ant )
    {
        if( current_y > y_ant )
        {
             for( int i = current_x + 1 ; (i < current_x + world->GetTileSizeRatio()*(*currentSprite)->xSize - 1) && !col_down ; i++ )     
             {
                 col_down = world->GetTileByCoord(i, current_y + world->GetTileSizeRatio()*(*currentSprite)->ySize - 1)->GetCollisionable();
             }
        }
        else
        {
             for( int i = current_x + 1 ; (i < current_x + world->GetTileSizeRatio()*(*currentSprite)->xSize - 1) && !col_up ; i++ )       
             {
                 col_up = world->GetTileByCoord(i, current_y)->GetCollisionable();
             }
        }
    }

    if( col_left || col_right )
    {
        current_x = x_ant;
    }
    if( col_up || col_down )
    {
        current_y = y_ant;
    }

    // Queremos saber si estamos en contacto con el suelo
    contact_down = false;
    for( int i = current_x ; (i < current_x + world->GetTileSizeRatio()*(*currentSprite)->xSize) && !contact_down ; i++ )    
    {
        contact_down = world->GetTileByCoord(i, current_y + world->GetTileSizeRatio()*(*currentSprite)->ySize)->GetCollisionable();   
    }
    // Queremos saber si golpeamos con la cabeza algo
    contact_up = false;
    for( int i = current_x ; (i < current_x + world->GetTileSizeRatio()*(*currentSprite)->xSize) && !contact_up ; i++ )    
    {
        contact_up = world->GetTileByCoord(i, current_y - 1)->GetCollisionable();   // FIXME: asegurar limites superiores de pantalla!
    }    
}

void enemigo :: loadAnimations(const char *file)
{
     char   buffer[200], bitmapFile[200], auxfile[200];
     int    bitmapSizeX, bitmapSizeY;
     int    numAnimaciones;     
     int    velocidad;     
     int    numSprites;
 
     sprintf(auxfile, "%s", file);

     // leer fichero animaciones del personaje
     fitxerAnimacio.obrirFitxer(auxfile, LECTURA);

     string directory = chopToDirectory(auxfile);

     printf("\t Reading enemy animation info from file %s\n", auxfile);

     // cabecera
     fitxerAnimacio.llegirLinea(buffer);
     fitxerAnimacio.llegirLinea(buffer);
     fitxerAnimacio.llegirLinea(buffer);
     fitxerAnimacio.llegirLinea(buffer);         // Linea blanco
     // bitmap
     fitxerAnimacio.llegirParaula(buffer);
     fitxerAnimacio.llegirParaula(bitmapFile);
     fitxerAnimacio.llegirParaula(buffer);
     fitxerAnimacio.llegirEnter(&bitmapSizeX);
     fitxerAnimacio.llegirParaula(buffer);
     fitxerAnimacio.llegirEnter(&bitmapSizeY);
     fitxerAnimacio.llegirLinea(buffer);         // Linea blanco

     string aux(bitmapFile);
     animationFile = aux;
     string completeBitmapFile = directory + animationFile;
     animationBitmap.openImage(completeBitmapFile.c_str(), bitmapSizeX, bitmapSizeY);

     // animaciones
     fitxerAnimacio.llegirParaula(buffer);
     fitxerAnimacio.llegirEnter(&numAnimaciones);
     fitxerAnimacio.llegirLinea(buffer);         // Linea blanco

     for( int i = 0 ; i < numAnimaciones ; i++ )
     {
         int numFrames;
         fitxerAnimacio.llegirParaula(buffer);
         fitxerAnimacio.llegirParaula(buffer);   // nombre animacion

         fitxerAnimacio.llegirParaula(buffer);
         fitxerAnimacio.llegirEnter(&numFrames);

         fitxerAnimacio.llegirParaula(buffer);
         fitxerAnimacio.llegirEnter(&velocidad);

         animacion[i].numSprites = 0;
         animacion[i].velocidad  = velocidad;
         for( int j = 0; j < numFrames ; j++ )
         {
             int xUpLeft, yUpLeft, xDownRight, yDownRight;
             int estado;
             fitxerAnimacio.llegirParaula(buffer);
             fitxerAnimacio.llegirEnter(&xUpLeft);
             fitxerAnimacio.llegirEnter(&yUpLeft);
             fitxerAnimacio.llegirEnter(&xDownRight);
             fitxerAnimacio.llegirEnter(&yDownRight);
             fitxerAnimacio.llegirEnter(&estado);
             fitxerAnimacio.llegirEnter(&numSprites);
             sprite *spriteAux = new sprite();
             spriteAux->newSprite(&animationBitmap,
                                  xUpLeft, yUpLeft,
                                  xDownRight, yDownRight,
                                  estado, numSprites);    
             animacion[i].numSprites++;
             animacion[i].sprites.push_back(spriteAux);
                                               
             for( int k = 0 ; k < numSprites ; k++ )   // composed sprite
             {
                 fitxerAnimacio.llegirParaula(buffer);
                 fitxerAnimacio.llegirEnter(&xUpLeft);
                 fitxerAnimacio.llegirEnter(&yUpLeft);
                 fitxerAnimacio.llegirEnter(&xDownRight);
                 fitxerAnimacio.llegirEnter(&yDownRight);
                 
                 spriteAux->AddInternalSprite(&animationBitmap, xUpLeft, yUpLeft, xDownRight, yDownRight);
             }
         }
     }
}


void enemigo :: computeNextAnimationSprite(unsigned int mseg)
{
    bool trobat = false;
    
    if( !activated )
        return;
    
    // gesti�n del tiempo para controlar el cambio de animacion (sprite)
    if( mseg - mseg_chk_anim > animacion[current_state].velocidad )
    {
         subAnimacion++;
         if( subAnimacion == animacion[current_state].sprites.size() )
         {
                if( current_state == ENEMIGO_MUERTO )
                    activated = false;
                subAnimacion = 0;
         }
         mseg_chk_anim = mseg;
    }
        
    // Seleccion del sprite de la animacion
    int i = 0;
    for( currentSprite = animacion[current_state].sprites.begin() ;
         currentSprite != animacion[current_state].sprites.end() && !trobat; 
       )
    {
         if( i == subAnimacion )
         {
             trobat = true;       
         }       
         else
         {
             i++;    
             currentSprite++;
         }
    }
    ASSERT( trobat == true );
}

void enemigo :: drawCharacterInWorld(mundo* world, BITMAP* buffer, int posXWorld, int posYWorld)
{
    BITMAP* sprite;
    BITMAP* internal_sprite;

    if( !activated )
        return;       
       
    // Informacion para pintar el sprite en el mundo
    int xUpLeft    = (*currentSprite)->xUpLeft;    
    int yUpLeft    = (*currentSprite)->yUpLeft;
    int xDownRight = (*currentSprite)->xDownRight;
    int yDownRight = (*currentSprite)->yDownRight;
    int xSize      = (*currentSprite)->xSize;
    int ySize      = (*currentSprite)->ySize;
    int nComp      = (*currentSprite)->numComponents;

    // Procedemos a pintar
    sprite = create_bitmap(world->GetTileSizeRatio()*xSize, world->GetTileSizeRatio()*ySize); 

    stretch_blit(animationBitmap.getImage(), sprite, xUpLeft, yUpLeft,
                   xSize, ySize,
                   0, 0, world->GetTileSizeRatio()*xSize, world->GetTileSizeRatio()*ySize);   


    if( enemigo_sentido == ENEMIGO_SENTIDO_DERECHA )
    {
        draw_sprite(buffer, sprite, posXWorld, posYWorld);        // DERECHA
    }
    else
    {
        draw_sprite_h_flip(buffer, sprite, posXWorld, posYWorld); // IZQUIERDA
    }
    
    // Composed sprite to draw
    for( int i = 0 ; i < nComp ; i++ )
    {
         xSize      = (*currentSprite)->internalSprites[i]->xSize;
         ySize      = (*currentSprite)->internalSprites[i]->ySize;
         xUpLeft    = (*currentSprite)->internalSprites[i]->xUpLeft;    
         yUpLeft    = (*currentSprite)->internalSprites[i]->yUpLeft;

         internal_sprite = create_bitmap(world->GetTileSizeRatio()*xSize, world->GetTileSizeRatio()*ySize);    
         stretch_blit(animationBitmap.getImage(), internal_sprite, xUpLeft, yUpLeft,
                      xSize, ySize,
                      0, 0, world->GetTileSizeRatio()*xSize, world->GetTileSizeRatio()*ySize);   
         
         if( enemigo_sentido == ENEMIGO_SENTIDO_DERECHA )
         {
             draw_sprite(buffer, internal_sprite, posXWorld + (i + 1)*world->GetTileSizeRatio()*xSize, posYWorld);        // DERECHA
         }
         else
         {
             draw_sprite_h_flip(buffer, internal_sprite, posXWorld - (i + 1)*world->GetTileSizeRatio()*xSize, posYWorld); // IZQUIERDA
         }         
         destroy_bitmap(internal_sprite);
    }
    
    destroy_bitmap(sprite);       
}

int enemigo :: GetCurrentXCompleteSprite()     
{ 
    int nComp = (*currentSprite)->numComponents;
    
    if( nComp == 0 || enemigo_sentido == ENEMIGO_SENTIDO_DERECHA )
    {
        return current_x; 
    }
    
    // nComp != 0 & enemigo_sentido == ENEMIGO_SENTIDO_IZQUIERDA
    return current_x - (nComp + 1)*4*(*currentSprite)->internalSprites[nComp - 1]->xSize; // FIXME: 32 por GetTileSizeRatio!
    
}

int enemigo :: GetCurrentSizeX() 
{ 
    int nComp = (*currentSprite)->numComponents;
    int xSize = (*currentSprite)->xSize;
    
    if( nComp == 0 )
    {
        return xSize;
    }
    
    for( int i = 0 ; i < nComp ; i++ )
    {
         xSize += (*currentSprite)->internalSprites[i]->xSize;
    }
    
    return xSize;   
}

int enemigo :: GetCurrentSizeY() 
{ 
    int nComp = (*currentSprite)->numComponents;
    int ySize = (*currentSprite)->ySize;
    
    if( nComp == 0 )
    {
        return ySize;
    }
    
    for( int i = 0 ; i < nComp ; i++ )
    {
         ySize += (*currentSprite)->internalSprites[i]->ySize;
    }
    
    return ySize;     
}		