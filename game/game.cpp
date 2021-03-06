// Class automatically generated by Dev-C++ New Class wizard

#include "game.h" // class's header file

// class constructor
Game::Game()
{
    screen_x_orig = SCREEN_X_ORIG;
    screen_y_orig = SCREEN_Y_ORIG;
    screen_x_size = SCREEN_X;
    screen_y_size = SCREEN_Y;
    
    printScrollFront = true;    // remove this
    printScrollBack  = true;    // and this        
    
    current_phase = 0;
    lives = 5;
}

// class destructor
Game::~Game()
{
}

// Function to kill warrior by several events
void Game::FastKillWarrior(
     character* warrior, 
     EnemyHandler *enemyHandler, 
     checkpointHandler *checkHandler, 
     float &x, float &y)
{
    warrior->SetInitialState(); 
    enemyHandler->AllEnemiesToInitialState();             
    x = checkHandler->GetWarriorIniXCurrentCheck();
    y = checkHandler->GetWarriorIniYCurrentCheck();
    lives--;
}

void Game::ReadPhasesDescription()
{
    phase_info* phase;
    
    // Phase 1
    phase = new phase_info();
    phase->readPhaseInfo("./data/levels/phase1.txt");
    phases.push_back(phase);

    // Phase 2                                                                  // Ahora es fake
    phase = new phase_info();
    phase->readPhaseInfo("./data/levels/phase2.txt");
    phases.push_back(phase);
    
    // Phase 3
    phase = new phase_info();
    phase->readPhaseInfo("./data/levels/phase3.txt");
    phases.push_back(phase);

    // Phase 4
    phase = new phase_info();
    phase->readPhaseInfo("./data/levels/phase4.txt");
    phases.push_back(phase);    

}

void Game::basicScrollHandler(
     mundo *world, 
     int personaje_x, int personaje_y, 
     int &screen_x, int &screen_y, 
     int &pers_screen_x, int &pers_screen_y)
{     
    screen_x = personaje_x - (screen_x_orig/2);
    pers_screen_x = (screen_x_orig/2);
    if( screen_x <= 0 )
    {
        screen_x = 0;
        pers_screen_x = personaje_x;
    }
    else if( screen_x > (world->GetScreenNewX() - (screen_x_orig)) ) // FIXME
    {
        screen_x = world->GetScreenNewX() - (screen_x_orig);
        pers_screen_x += (screen_x_orig/2) - (world->GetScreenNewX() - personaje_x);
    }

    screen_y = personaje_y - (screen_y_orig/2);

    pers_screen_y = (screen_y_orig/2);
    if( screen_y <= 0 )
    {
        screen_y = 0;
        pers_screen_y = personaje_y;
    }
    else if( screen_y > (world->GetScreenNewY() - (screen_y_orig)) ) // FIXME
    {
        screen_y = world->GetScreenNewY() - (screen_y_orig);
        pers_screen_y += (screen_y_orig/2) - (world->GetScreenNewY() - personaje_y);
    } 
}

void Game::freeScrollHandler(
     mundo *world, 
     int teclado, 
     int personaje_x, int personaje_y, 
     int &screen_x, int &screen_y, 
     int &pers_screen_x, int &pers_screen_y)
{
    if( teclado & LEFT_SCROLL )
        screen_x -= 10;
    if( teclado & RIGHT_SCROLL )
        screen_x += 10;
    if( teclado & UP_SCROLL )
        screen_y -= 10;
    if( teclado & DOWN_SCROLL )
        screen_y += 10;        
    
    // Adjust limits 
    if( screen_x <= 0 )
        screen_x = 0;
    else if( screen_x > (world->GetScreenNewX() - (screen_x_orig)) ) // FIXME
        screen_x = world->GetScreenNewX() - (screen_x_orig);
    if( screen_y <= 0 )
        screen_y = 0;
    else if( screen_y > (world->GetScreenNewY() - (screen_y_orig)) ) // FIXME
        screen_y = world->GetScreenNewY() - (screen_y_orig);

    // Adjust warrior position if it is on to screen
    if( (personaje_x >= screen_x) && (personaje_x <= (screen_x + screen_x_orig)) &&
        (personaje_y >= screen_y) && (personaje_y <= (screen_y + screen_y_orig)) )
    {
        printf(" Warrior en pantalla!\n");
        pers_screen_x = personaje_x - screen_x;
        pers_screen_y = personaje_y - screen_y;    
    }
    else
    {
         pers_screen_x = world->GetScreenOrigX()*1000;
         pers_screen_y = world->GetScreenOrigY()*1000;
    }
}

void Game::scrollHandler(
     mundo *world, 
     int teclado, 
     int personaje_x, int personaje_y, 
     int &screen_x, int &screen_y, 
     int &pers_screen_x, int &pers_screen_y, 
     bool free_scroll)
{
    if( free_scroll == false )
    {
        basicScrollHandler(world, personaje_x, personaje_y, screen_x, screen_y, pers_screen_x, pers_screen_y);
    }
    else
    {
        freeScrollHandler(world, teclado, personaje_x, personaje_y, screen_x, screen_y, pers_screen_x, pers_screen_y);  
    }
}

void Game::drawScrollsBack(
     mundo *world, 
     BITMAP *buffer, 
     int screenIniX, int screenIniY)
{
     if( printScrollBack == false )
     {
         return;
     }
     // Scrolls trasero
     for( int i = world->GetNumScrollPlanes() - 1 ; i >= 0 ; i-- )
     {
            int tiles_scroll_i_x   = (screen_x_orig / world->GetScrollSizeX(i)) + 1;
            int tiles_scroll_i_y   = (screen_y_orig / world->GetScrollSizeY(i)) + 1;
            int correct_scroll_i_x = (screenIniX / (world->GetScrollVelX(i))) % world->GetScrollSizeX(i);
            int correct_scroll_i_y = (screenIniY / (world->GetScrollVelY(i))) % world->GetScrollSizeY(i);

            for( int r = 0 ; r < tiles_scroll_i_x ; r++ )
            {
                //for( int s = 0 ; s < tiles_scroll_i_y ; s++ )                
                int s = 0;
                {
                    masked_blit(world->GetScrollImage(i), buffer,
                                0, 0,
                                r * world->GetScrollSizeX(i) - correct_scroll_i_x, s * world->GetScrollSizeY(i) /*- correct_scroll_i_y*/,
                                world->GetScrollSizeX(i), world->GetScrollSizeY(i));
                }
            }
     }
}

void Game::drawScrollsFront(
     mundo *world, 
     BITMAP *buffer, 
     int screenIniX, int screenIniY)
{
     if( printScrollFront == false )
     {
          return;
     }
     // Scrolls delantero
     for( int i = 0 ; i < world->GetNumScrollPlanesFront() ; i++ )
     {
            int tiles_scroll_x   = (screen_x_orig / world->GetScrollSizeXFront(i));
            int tiles_scroll_y   = (screen_y_orig / world->GetScrollSizeYFront(i));
            int x = (screenIniX * (world->GetScrollVelFrontX(i))) % world->GetScrollSizeXFront(i);
            int y_ini = (screenIniY * (world->GetScrollVelFrontY(i))) % world->GetScrollSizeYFront(i);
            int y = y_ini;
            int size_x = 0;
            int size_y = 0;
            int screen_x = size_x;
            int screen_y = size_y;

            for( int r = 0 ; r < tiles_scroll_x + 2; r++ ) // FIXME
            {
                screen_x += size_x; 
                size_x = world->GetScrollSizeXFront(i) - x;
                size_y = 0;
                screen_y = 0;
                for( int s = 0 ; s < tiles_scroll_y + 1; s++ )
                {
                    screen_y += size_y;
                    size_y = world->GetScrollSizeYFront(i) - y;
                    
                    masked_blit(world->GetScrollImageFront(i), buffer,
                                x, y,
                                screen_x, screen_y,
                                size_x, size_y);
                    
                    y += (world->GetScrollSizeYFront(i) - y);
                    y %= world->GetScrollSizeYFront(i);
                }
                x += (world->GetScrollSizeXFront(i) - x);
                x %= world->GetScrollSizeXFront(i);
                y = y_ini;
            }
     }
}

void Game::drawWorld(
     mundo *world, 
     character* warrior, 
     BITMAP *buffer, 
     int screenIniX, int screenIniY)
{
     int     i2, j2;
     int     tiles_in_screen_x;
     int     tiles_in_screen_y;
     int     tiles_in_tiles_image_x;
     int     first_tile_screen_x;
     int     first_tile_screen_y;

     tiles_in_tiles_image_x = world->GetScreenTilesX() / world->GetTilesSizeX();
     tiles_in_screen_x = (screen_x_orig / world->GetTilesSizeX()) + (screenIniX < world->GetScreenNewX() - screen_x_orig);
     tiles_in_screen_y = (screen_y_orig / world->GetTilesSizeY()) + (screenIniY < world->GetScreenNewY() - screen_y_orig);
     if( tiles_in_screen_x > world->GetTilesWorldX() )
     {
         tiles_in_screen_x = world->GetTilesWorldX();
     }
     if( tiles_in_screen_y > world->GetTilesWorldY() )
     {
         tiles_in_screen_y = world->GetTilesWorldY();
     }

     first_tile_screen_x = screenIniX / world->GetTilesSizeX();
     first_tile_screen_y = screenIniY / world->GetTilesSizeY();
     correct_scroll_x    = screenIniX % world->GetTilesSizeX();
     correct_scroll_y    = screenIniY % world->GetTilesSizeY();

     tilesFirstPlane.clear();

     // Tiles
     i2 = 0;
     for( int i = first_tile_screen_y ; i < first_tile_screen_y + tiles_in_screen_y ; i++ )
     {
         j2 = 0;
         for( int j = first_tile_screen_x ; j < first_tile_screen_x + tiles_in_screen_x ; j++ )
         {
                int x = (world->GetTileValue(j, i)- 1) % tiles_in_tiles_image_x;
                int y = (world->GetTileValue(j, i) - 1)/ tiles_in_tiles_image_x;

                if( world->GetTileValue(j, i) != 0 ) 
                {
                     // First check for tiles that appear in front of main character
                     if( ((world->GetTile(j, i)->GetPintado() == TILE_PINTADO_ESCALERAS) && 
                         (warrior->GetCurrentState() >= WARRIOR_EN_ESCALERAS_LEFT_PARADO && warrior->GetCurrentState() <= WARRIOR_EN_ESCALERAS_RIGHT_CAMINANDO)) ||
                         (world->GetTile(j, i)->GetPintado() == TILE_PINTADO_DELANTE) ) // FIXME
                     {
                         Coord4D coordenadas;
                         coordenadas.x = j;
                         coordenadas.y = i;
                         coordenadas.z = j2;
                         coordenadas.t = i2;
                         tilesFirstPlane.push_back(coordenadas);
                     }
                     else
                     {
                         blit(world->GetWorldImage(), sprite_image, x * world->GetTilesSizeX(), y * world->GetTilesSizeY(), 0, 0, world->GetTilesSizeX(), world->GetTilesSizeY());
                         masked_blit(sprite_image, buffer,
                                     0, 0,
                                     j2 * world->GetTilesSizeX() - correct_scroll_x, i2 * world->GetTilesSizeY() - correct_scroll_y,
                                     world->GetTilesSizeX(), world->GetTilesSizeY());
                     }
                }
                j2++;
         }
         i2++;
     }

}

void Game::drawWorldTilesFirstPlane(mundo *world, BITMAP *buffer)
{
     int tiles_in_tiles_image_x = world->GetScreenTilesX() / world->GetTilesSizeX();
     
     for(list<Coord4D>::iterator it = tilesFirstPlane.begin() ; it != tilesFirstPlane.end() ; it++ )
     {
         int x = (world->GetTileValue(it->x, it->y)- 1) % tiles_in_tiles_image_x;
         int y = (world->GetTileValue(it->x, it->y) - 1)/ tiles_in_tiles_image_x;                                 
         
         blit(world->GetWorldImage(), sprite_image, x * world->GetTilesSizeX(), y * world->GetTilesSizeY(), 0, 0, world->GetTilesSizeX(), world->GetTilesSizeY());
         masked_blit(sprite_image, buffer,
                     0, 0,
                     it->z * world->GetTilesSizeX() - correct_scroll_x, it->t * world->GetTilesSizeY() - correct_scroll_y,
                     world->GetTilesSizeX(), world->GetTilesSizeY());         
         
     }
}

void Game::drawScreen(
    mundo *world,
    character* warrior,    
    BITMAP *buffer,
    int screen_x,
    int screen_y,
    int screen_x_orig,
    int screen_y_orig,
    int pers_screen_x,
    int pers_screen_y,    
    bool rect,
    unsigned int mseg,
    bool checkpointImage)
{
    drawScrollsBack(world, buffer, screen_x, screen_y);   // scrolls traseros    
    drawWorld(world, warrior, buffer, screen_x, screen_y);         // tiles del mundo
    warrior->drawCharacterInWorld(world, buffer, pers_screen_x, pers_screen_y);   // pintamos al personaje
    enemyHandler->DrawEnemiesInScreen(buffer, world, screen_x, screen_y, screen_x_orig, screen_y_orig);         // y a los enemigos
    drawWorldTilesFirstPlane(world, buffer);
    objHandler->DrawObjectsInScreen(buffer, world, screen_x, screen_y, screen_x_orig, screen_y_orig, rect, mseg);
    drawScrollsFront(world, buffer, screen_x, screen_y);   //  scrolls delanteros    
    
    if( checkpointImage )
        blit(buffer, screenChk, 0, 0, 0, 0, screen_x_orig, screen_y_orig);
}

void Game::prepareMsgBox(
    character* warrior, 
    float &x, float &y, 
    bool killed, 
    unsigned int mseg, 
    messageBoxHandler *msgBox,
    EnemyHandler      *enemyHand,
    checkpointHandler *checkHand,
    bool pause, 
    bool esc)
{
    char texto[100];
    
    if( killed )
    {
        sprintf(texto, "Lives x %d ", lives);     
    }
    else if( current_phase == 0 )
    {
        sprintf(texto, "El fuego que no quema");              
    }
    else if( current_phase == 1 )
    {
        sprintf(texto, "El espejo de la sabiduria");     
    }
    else if( current_phase == 2 )
    {
        sprintf(texto, "El elixir de la vida");              
    }
    else if( current_phase == 3 )
    {
        sprintf(texto, "La voz del otro mundo");              
    }            
    
    msgBox->setReason(0);
        
    if( pause )
    {
        sprintf(texto, "GAME PAUSED");
        msgBox->setReason(1);
    }
    else if( esc )
    {
        sprintf(texto, "Press ESCAPE to quit");         
        msgBox->setReason(2);
    }
    
    
    
    // Prepare message box
    msgBox->setActivated(true);
    msgBox->setTimeChk(mseg);
    msgBox->setText(texto);
    msgBox->setWakeUpByKey(pause || esc);

    if( killed )                        // Prepare for restart
        this->FastKillWarrior(warrior, enemyHand, checkHand, x, y);                 
    else
    {
        soundHandler->setEnabled(9, true);
        soundHandler->playSound(9);        
    }

        
}

int Game::readKeyboard()
{
    int entrada_teclado = NO_KEY;

    if( key[KEY_O] )
    {
        entrada_teclado |= LEFT;
    }
    if( key[KEY_P] )
    {
        entrada_teclado |= RIGHT;
    }
    if( key[KEY_Q] )
    {
        entrada_teclado |= UP;
    }
    if( key[KEY_A] )
    {
        entrada_teclado |= DOWN;
    }
    if( key[KEY_SPACE] )
    {
        entrada_teclado |= FIRE;
    }
    if( key[KEY_H] )
    {
        entrada_teclado |= PAUSE;
    }
    if( key[KEY_ESC] )
    {
        entrada_teclado |= ESC;
    }
    
    if( key[KEY_F] )
    {
         while( !key[KEY_F] );
         printScrollFront = !printScrollFront;
    }
    if( key[KEY_B] )
    {
         while( !key[KEY_B] );
         printScrollBack = !printScrollBack;
    }
    
    //
    if( key[KEY_LEFT] )
    {
        entrada_teclado |= LEFT_SCROLL;
    }
    if( key[KEY_RIGHT] )
    {
        entrada_teclado |= RIGHT_SCROLL;
    }
    if( key[KEY_UP] )
    {
        entrada_teclado |= UP_SCROLL;
    }
    if( key[KEY_DOWN] )
    {
        entrada_teclado |= DOWN_SCROLL;
    }
    
    // FIXME
    if( key[KEY_PLUS_PAD] )
    {
        screen_x_orig++;
        screen_y_orig++;
    }
    if( key[KEY_MINUS_PAD] )
    {
        screen_x_orig--;
        screen_y_orig--;
    }
    return entrada_teclado;
}

int Game::gameMain()
{
    char text[50];
    float x_ini;
    float y_ini;
    float x;       // posicion de un personaje cuadrado
    float y;
    int screen_x = 0;
    int screen_y = 0;
    int pers_screen_x = 0;
    int pers_screen_y = 0;
    int entrada_teclado = 0x0000;
    int toNextLevel  = 0;
    int externalKill = 0;
    bool warriorKilled = false;
    bool quit = false;
    unsigned int buffer_num = 0;
          
    character* warrior = new character(&globalSymbolTable, soundHandler);   
    
    if( current_phase == 0 )
        lives = 9;

    // load level info and start level handling
    x_ini = phases[current_phase]->GetXIni();
    y_ini = phases[current_phase]->GetYIni();
    x = x_ini;       // posicion de un personaje cuadrado
    y = y_ini;
    MIDI *music_phase1 = load_midi(phases[current_phase]->GetSongFile()); 
    if (!music_phase1)
        printf("Couldn't load sample!\n");

    printf("Current phase %d with name %s\n", current_phase, phases[current_phase]->GetWorldDescriptionFile());
        
    // Ini Warrior variables
    warrior->ClearImportantVars();
    warrior->AddInternalVarsToSymbTable();                                              // Important for script handling
    warrior->SetInitialState(phases[current_phase]->GetWarriorIniState(), phases[current_phase]->GetWarriorPrevState());
    warrior->SetWarriorSentido(phases[current_phase]->GetWarriorDir());
    warrior->SetWarriorForm(phases[current_phase]->GetWarriorForm());
    // Golbal var
    globalSymbolTable.addVarToSymbolTable("to_next_level", (unsigned long*)&toNextLevel);
    globalSymbolTable.addVarToSymbolTable("external_kill", (unsigned long*)&externalKill);
    // Phase initialization
    mundo *world = new mundo(phases[current_phase]->GetWorldDescriptionFile(), false);         // World info
    // Handler initialization
    enemyHandler = new EnemyHandler(&globalSymbolTable, soundHandler);                        // Enemies info
    enemyHandler->ReadEnemiesFile(phases[current_phase]->GetEnemiesDescriptionFile());      
    checkHandler = new checkpointHandler();                          // Checkpoints info
    checkHandler->loadCheckpointFile(phases[current_phase]->GetChkDescriptionFile());              
    scriptHandler *scrptHandler = new scriptHandler(&globalSymbolTable);                // Scripts info
    scrptHandler->ReadScriptsFile(phases[current_phase]->GetScriptsFile());
    objHandler = new objectHandler(&globalSymbolTable);                  // Objects info
    objHandler->ReadObjectsFromFile(phases[current_phase]->GetObjectsFile());
    machinimiaHandler *machinHandler = new machinimiaHandler(&globalSymbolTable, objHandler);
    scrHandler.init(phases[current_phase]->GetScrollsFile(), screen_x_size, screen_y_size, 
        (int)warrior->GetCurrentX(), (int)warrior->GetCurrentY(), warrior->GetSentido(), 16, 16);        
    machinHandler->loadAnimations(phases[current_phase]->GetAnimsFile());
    globalSymbolTable.DumpSymbolTable();                                                // Symbol Table Dump    
    messageBoxHandler *msgBoxHandler = new messageBoxHandler(&globalSymbolTable, "./data/objects/pergamino.txt");
    
    play_midi(music_phase1, 1); 
        
   	while( (!quit && !key[KEY_N] && !toNextLevel && (lives >= 0)) || (msgBoxHandler->getActivated()) ) // Aqu� va la condici�n de pasar de nivel
    {
        ///////////////////////////////////////////////////////////////////////
        // ENTRADA
        timer->setMseg(0);                  // sincronizacion del bucle principal
        warriorKilled = false;
        acquire_bitmap(buffer[buffer_num]);
        clear_bitmap(buffer[buffer_num]);
        acquire_bitmap(screen_buffer[buffer_num]);
        clear_bitmap(screen_buffer[buffer_num]);
            
        entrada_teclado = readKeyboard();   // input del teclado                

        ///////////////////////////////////////////////////////////////////////
        // PROCESAMIENTO
        if( !machinHandler->getRunning() && !msgBoxHandler->getActivated() )
        {   
            for( int i = 0 ; (i < 4) && (!warriorKilled) ; i++ )
            { 
                warrior->handleState(entrada_teclado, timer->getMsegGlobal());
                warrior->computeNewPositionUsingCollisionDetection(world, entrada_teclado, x, y, timer->getMsegGlobal());
                if( key[KEY_K] || externalKill == 1 || enemyHandler->EnemyKillWarrior(buffer[buffer_num], world, warrior, screen_x, screen_y) )
                {
                    externalKill = 0;        
                    while( key[KEY_K] );
                    warriorKilled = true;                 
                }                                 
                
            }
            
            // Scripts and checkpoints have to bigger than the MAX CONSTANT of the for above
            scrptHandler->AnalyzeScripts((int)warrior->GetCurrentX(), (int)warrior->GetCurrentY(), (int)warrior->GetCurrentSizeX(), (int)warrior->GetCurrentSizeY());
            checkHandler->PositionedOnNextCheckpoint((int)warrior->GetCurrentX(), (int)warrior->GetCurrentY(), (int)warrior->GetCurrentX(), (int)warrior->GetCurrentY());                                                    
            enemyHandler->HandleEnemiesState(buffer[buffer_num], world, warrior, timer->getMsegGlobal(), screen_x, screen_y);                
            
            //scrollHandler(world, entrada_teclado, (int)x, (int)y, screen_x, screen_y, pers_screen_x, pers_screen_y, true);
            scrHandler.supervisor((unsigned int)x, (unsigned int)y, (unsigned int)warrior->GetCurrentSizeX(), warrior->GetSentido(), screen_x, screen_y, pers_screen_x, pers_screen_y);
            //scrHandler.handler((unsigned int)x, (unsigned int)y, warrior->GetSentido(), screen_x, screen_y, pers_screen_x, pers_screen_y);                                 

            if( (entrada_teclado & PAUSE) || (entrada_teclado & ESC) ||
                warriorKilled || msgBoxHandler->getActivated() )  // Warrior killed or script enable msgBox
            {
                 // Do checkpoint of image
                 this->drawScreen(world, warrior, buffer[buffer_num], screen_x, screen_y,
                    screen_x_orig, screen_y_orig, pers_screen_x, pers_screen_y,    
                    false, timer->getMsegGlobal(), true);
                 this->prepareMsgBox(warrior, x, y, warriorKilled, timer->getMsegGlobal(), 
                     msgBoxHandler, enemyHandler, checkHandler, 
                     (entrada_teclado & PAUSE), (entrada_teclado & ESC));
            }                        
        }
        else if( machinHandler->getRunning() )
        {
            if( !soundHandler->getEnabled(6) )
            {
                soundHandler->setEnabled(6, true);                
                soundHandler->playSound(6);
            }
            machinHandler->processAnimation(machinHandler->getNumActiveAnimation());
        }  
        else   // msgBoxHandler is activated
        {
            if( (msgBoxHandler->getReason() == 2) && !msgBoxHandler->getCounting() ) // GAME paused for ESC
                if( entrada_teclado & ESC )
                    quit = true;
        }      
        
        ///////////////////////////////////////////////////////////////////////
        // SALIDA 
        if( !msgBoxHandler->getActivated() )
        {
            this->drawScreen(world, warrior, buffer[buffer_num], screen_x, screen_y,
                screen_x_orig, screen_y_orig, pers_screen_x, pers_screen_y,    
                false, timer->getMsegGlobal(), false);
        }
        else
        {
            blit(screenChk, buffer[buffer_num], 0, 0, 0, 0, screen_x_orig, screen_y_orig);
            msgBoxHandler->drawMessageBox(buffer[buffer_num], world, timer->getMsegGlobal(), entrada_teclado);
        }            
        
        stretch_blit(buffer[buffer_num], screen_buffer[buffer_num], 0, 0, screen_x_orig,  screen_y_orig, 0, 0, screen_x_size, screen_y_size);   // adaptamos la pantalla
        // Aplicamos los efectos de post-procesado si estan presentes
        if( current_phase == 1 )        // FIXME
          waterFx.handler(buffer[buffer_num], screen_buffer[buffer_num], screen_x_size, screen_y_size, timer->getMsegGlobal());
        release_bitmap(buffer[buffer_num]);
        release_bitmap(screen_buffer[buffer_num]);
        show_video_bitmap(buffer[buffer_num]);
        show_video_bitmap(screen_buffer[buffer_num]);
        buffer_num = 1 - buffer_num;        
        ///////////////////////////////////////////////////////////////////////
        // SINCRONIZACI�N
        while( timer->getMseg() < 10 );
        vsync();                
        
        //sprintf(text, "%f", (float)1000/(timer->getMseg()));
        //textout_ex(screen_buffer[buffer_num], font, text, 8, 24, 0xABCDE, -1);  
            
        ///////////////////////////////////////////////////////////////////////
        // Pintado final en pantalla
        blit(screen_buffer[buffer_num], screen, 0, 0, 0, 0, screen_x_size, screen_y_size);                               
   	}
    
    // Destroy all
    stop_midi();
    delete world;
    delete enemyHandler;
    delete checkHandler;
    delete scrptHandler;
    delete objHandler;
    delete machinHandler;
    globalSymbolTable.ClearSymbolTable();
    	   
    // if hemos pasado de fase entonces current_phase++    
    if( toNextLevel || key[KEY_N] )
    {
        current_phase = (current_phase + 1) /*% phases.size()*/;
        return TO_NEXT_LEVEL;
    }
    
    toNextLevel = 0;
    externalKill = 0;
    
	return ESC_FROM_LEVEL;
}

void Game::init()
{
    int depth, res;
          
    depth = 16;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
	if (res != 0)
    {
		allegro_message(allegro_error);
		exit(-1);
	}
    
    soundHandler = new fxHandler(); // Init fx sounds
    soundHandler->addSound("./data/fx/hit.wav", false);            // 0
    soundHandler->addSound("./data/fx/sword.wav", false);          // 1
    soundHandler->addSound("./data/fx/player_walk.wav", true);     // 2
    soundHandler->addSound("./data/fx/rockfall.wav", false);       // 3
    soundHandler->addSound("./data/fx/skeleton_dead.wav", false);  // 4    
    soundHandler->addSound("./data/fx/mort.wav", false);           // 5 
    soundHandler->addSound("./data/fx/caldero.wav", false);        // 6     
    soundHandler->addSound("./data/fx/fire.wav", false);           // 7      
    soundHandler->addSound("./data/fx/granota.wav", false);        // 8   
    soundHandler->addSound("./data/fx/item_appear.wav", false);    // 9      

    waterFx.initialize(FRAMES_AGUA, DIST_DESP_AGUA, 25);     
    
    screenChk = create_bitmap(screen_x_orig, screen_y_orig);
	buffer[0] = create_bitmap(screen_x_orig, screen_y_orig);
    buffer[1] = create_bitmap(screen_x_orig, screen_y_orig);
    screen_buffer[0] = create_bitmap(screen_x_size, screen_y_size);
    screen_buffer[1] = create_bitmap(screen_x_size, screen_y_size);
    buffer_num = 0;
    sprite_image = create_bitmap_ex(depth, 32, 32);//world->GetTilesSizeX(), world->GetTilesSizeY());  // FIXME    
    
    ReadPhasesDescription();    
    
    timer = new Timer();  
    timer->init(1);
}

void Game::deinit() 
{
	clear_keybuf();
	/* add other deinitializations here */
}
