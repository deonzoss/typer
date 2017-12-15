#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
  this->renderer = renderer;
  textVector = makeTextVector();
  textGenerator = new TextGenerator(renderer);	
  scoreboard = new Scoreboard(renderer);
  mainMenu = new Menu(renderer);
  loadSounds();
  quit = false;
}

void Game::loadSounds()
{
  gameplayMusic = Mix_LoadMUS("sounds/music1.wav");
  if(!gameplayMusic){
    printf("%s\n", Mix_GetError());
  }
  pop1 = Mix_LoadWAV("sounds/pop1.wav");
  pop2 = Mix_LoadWAV("sounds/pop2.wav");
  pop3 = Mix_LoadWAV("sounds/pop3.wav");
  pop4 = Mix_LoadWAV("sounds/pop4.wav");
  pop5 = Mix_LoadWAV("sounds/pop5.wav");
  pop6 = Mix_LoadWAV("sounds/pop6.wav");
  hit1 = Mix_LoadWAV("sounds/hit1.wav");
  hit2 = Mix_LoadWAV("sounds/hit2.wav");
  hit3 = Mix_LoadWAV("sounds/hit3.wav");
  hit4 = Mix_LoadWAV("sounds/hit4.wav");
  hit5 = Mix_LoadWAV("sounds/hit5.wav");
  hit6 = Mix_LoadWAV("sounds/hit6.wav");
  hit7 = Mix_LoadWAV("sounds/hit7.wav");
  hit8 = Mix_LoadWAV("sounds/hit8.wav");
  hit9 = Mix_LoadWAV("sounds/hit9.wav");
  hit10 = Mix_LoadWAV("sounds/hit10.wav");
  startLetterSound = Mix_LoadWAV("sounds/startLetterSound.wav");
  backgroundPrinter = Mix_LoadWAV("sounds/backgroundPrinter.wav");
  backgroundRandom = Mix_LoadWAV("sounds/backgroundRandom.wav");
  flagSound = Mix_LoadWAV("sounds/flag.wav");
  pauseSound = Mix_LoadWAV("sounds/pause.wav");
  levelUpSound = Mix_LoadWAV("sounds/level.wav");
  trophySound = Mix_LoadWAV("sounds/trophy.wav");
  invalidSound = Mix_LoadWAV("sounds/invalid.wav");
  groundSound = Mix_LoadWAV("sounds/hit.wav");
  screenSound = Mix_LoadWAV("sounds/screenSlide2.wav");
  screenSoundReverse = Mix_LoadWAV("sounds/screenSlide2Reverse.wav");
  allLettersPop= Mix_LoadWAV("sounds/gameOverLetters.wav");

  if(pop1 == NULL || hit1 == NULL || startLetterSound == NULL || backgroundPrinter == NULL || backgroundRandom == NULL || flagSound == NULL || pauseSound == NULL || levelUpSound == NULL || trophySound == NULL || invalidSound == NULL){
    printf("Error loading sound\n");
  } 
}


	
std::vector<Texture*> Game::makeTextVector()
{
  textVector.resize(NUM_TEXT_ROWS);
  return textVector;
}


std::vector<Texture*> Game::populateTextVector()
{
  for(int i = 0; i < textVector.size(); i++){	
    Texture* texture = new Texture();
    texture->setRenderer(renderer);
    texture->loadText(textGenerator->create());	
    texture->setSpeed(currentLevel->getSpeed());
    textVector[i] = texture;	
  }

  return textVector;	
}


void Game::displayTextVector()
{	
  for(int j = 0; j < textVector.capacity(); j++){
    if(textVector[j]->getText().length() != 0){
      if(textVector[j]->offScreen()){
        textVector[j]->loadText(textGenerator->create());
        strikes++;
        Mix_PlayChannel(-1, flagSound, 0);
        screen->putFlagDown();
      }	
      textVector[j]->render(textVector[j]->getXPos(),SCREEN_END_YPOS+ TEXT_ROW_OFFSET +  j*TEXT_SIZE, NULL, NULL, NULL, SDL_FLIP_NONE);
      if(!pauseLevel){
        textVector[j]->move();	
      }
    }
  }
}

void Game::explodeTextVector()
{
  for(int i = 0; i < textVector.capacity(); i++){
    while(textVector[i]->getText().length() != 0){
      Letter* letter = new Letter();
      letter->loadLetter(textVector[i]->getText().front(), renderer);
      letter->setX(textVector[i]->getXPos());
      letter->setY(SCREEN_END_YPOS + TEXT_ROW_OFFSET + i*TEXT_SIZE);
      if(slowTime){
        letter->setSpeed(LETTER_SLOW_SPEED);
      } 
      letterVector.push_back(letter);
      textVector[i]->popFront();
    }
  }
}

void Game::displayLetterVector()
{
  for(int j = 0;j < letterVector.size(); j++){
    int dynamic = letterVector[j]->getDynamic(); 
    if(dynamic != 2){ 
      letterVector[j]->render(letterVector[j]->getX(), letterVector[j]->getY(), renderer);
    } 
    if(!pauseLevel){
      if(letterVector[j]->getOnGround()){ 
        if(dynamic == 1){
          if(boss->getWalking()){
            double speed = 1; 
            if(slowTime){
              speed = LETTER_SLOW_SPEED;
            }
            if(boss->getFacingRight())
              letterVector[j]->setX(letterVector[j]->getX()+WALKING_SPEED/speed);
            else
              letterVector[j]->setX(letterVector[j]->getX()-WALKING_SPEED/speed);
            if(boss->getFrameIndex()%2==0)
              letterVector[j]->setY(BOSS_SPAWN_Y-9*SCALESIZE);
            else
              letterVector[j]->setY(BOSS_SPAWN_Y-8*SCALESIZE);
               
          }
        }
        if(letterVector[j]->getLifetime() > LETTER_LIFETIME){
          letterVector[j]->fade();
          if(letterVector[j]->getAlpha()<=0){	
            Letter* temp = letterVector[j];	
            letterVector.erase(letterVector.begin()+j);
            delete(temp);
          }
        }
      }
      else{
        letterVector[j]->move();
        if(letterVector[j]->getOnGround()){
          if(SDL_GetTicks() - soundTime >= 20){
            //Mix_PlayChannel(-1, groundSound, 0);
            soundTime = SDL_GetTicks();
          }
        }
      }
    }
  }
}

void Game::displayDynamicLetters(){
  for(int j = 0; j < letterVector.size(); j++){
    int dynamic = letterVector[j]->getDynamic();
    if(dynamic == 2){
      letterVector[j]->render(letterVector[j]->getX(), letterVector[j]->getY(), renderer);
    }
  }
}

void Game::displayScoreVector()
{
  for(int j = 0;j < scoreVector.size(); j++){
    scoreVector[j]->render();
    if(!pauseLevel){
      scoreVector[j]->move();
      if(scoreVector[j]->getOnGround() && scoreVector[j]->getLifetime() > LETTER_LIFETIME){
        scoreVector[j]->fade();
        if(scoreVector[j]->getAlpha()<=0){	
          Scorer* temp = scoreVector[j];	
          scoreVector.erase(scoreVector.begin()+j);
          delete(temp);
        }
      }
    }
  }
}


SDL_Texture* Game::loadBackground()
{
  SDL_Surface* loadedSurface = IMG_Load("images/typer.png");
  //SDL_Surface* scaledSurface;
  SDL_Rect scaleRect;
  scaleRect.x = 0;
  scaleRect.y = 0;
  scaleRect.w = SCREEN_WIDTH;
  scaleRect.h = SCREEN_HEIGHT;
 
  //if(!SDL_BlitScaled(loadedSurface, NULL, scaledSurface, &scaleRect))
    //printf("%s\n", SDL_GetError());

  if(loadedSurface == NULL){
    printf("Error loading surface. SDL_image Error: %s\n", IMG_GetError());
  }
  else{
    background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(background == NULL){
      printf("Unable to create texture from surface. SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
    //SDL_FreeSurface(scaledSurface);
  }
  return background;
}

SDL_Texture* Game::loadAnimationSheet()
{
  SDL_Surface* loadedSurface = IMG_Load("images/typer_objects.png");
  if(loadedSurface == NULL){
    printf("Error loading surface. SDL_image Error: %s\n", IMG_GetError());
  }
  else{
    animationSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(animationSheet == NULL){
      printf("Unable to create texture from surface. SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  scoreboard->setObjectTexture(animationSheet);
  return animationSheet;
}

void Game::slowDown(){
    
  double newSpeed = textVector[0]->getSpeed() / 3; 
  for(int i = 0; i < textVector.size(); i++){
    textVector[i]->setSpeed(newSpeed);
  }
  for(int i = 0; i < letterVector.size(); i++){
    letterVector[i]->setSpeed((double)10);
  }
  for(int i = 0; i < scoreVector.size(); i++){
    scoreVector[i]->setSpeed((double)10);
  }
  mainCharacter->setSpeed((double)10);
  boss->setSpeed((double)10);
  clock->setSpeed((double)10); 
  door->setSpeed((double)10);
  worker->setSpeed((double)10);

  return;
}

void Game::speedUp(){
  double newSpeed = textVector[0]->getSpeed() * 3; 
  for(int i = 0; i < textVector.size(); i++){
    textVector[i]->setSpeed(newSpeed);
  } 
  for(int i = 0; i < letterVector.size(); i++){
    letterVector[i]->setSpeed((double)1);
  } 
  for(int i = 0; i < scoreVector.size(); i++){
    scoreVector[i]->setSpeed((double)1);
  }
  mainCharacter->setSpeed((double)1); 
  boss->setSpeed((double)1);
  clock->setSpeed((double)1); 
  door->setSpeed((double)1); 
  worker->setSpeed((double)1);
  return;
}

void Game::newLevel(){
  clock->setMinuteHandAngle(0);
  levelTime = SDL_GetTicks();
  levelNum++;
  currentLevel->setLevelNum(levelNum);
  if(currentLevel->getRand()){
    double newSpeed = textVector[0]->getSpeed() + LEVEL_SPEED_INCREASE; 
    for(int i = 0; i < textVector.size(); i++){
      textVector[i]->setSpeed(newSpeed);
    } 
  }
  else{
    double newSpeed = textVector[0]->getSpeed() + .02*SCALESIZE; 
    for(int i = 0; i < textVector.size(); i++){
      textVector[i]->setSpeed(newSpeed);
    }
  }
}

void Game::eventHandler()
{
  while(SDL_PollEvent(&event) != 0){
    if(event.type == SDL_QUIT){
      quit = true;
    }
    else if(startLevel && event.key.keysym.sym==SDLK_ESCAPE && event.type == SDL_KEYUP){
      explodeTextVector(); 
      Mix_PlayChannel(-1, screenSoundReverse, 0);
      Mix_PlayChannel(-1, allLettersPop, 0);
      Mix_PauseMusic();
      quitLevel = true;
      mainMenu->reset();
      screen->setEndGame(true);
    }
    else if(startLevel && event.key.keysym.sym==SDLK_RETURN && event.type == SDL_KEYUP){
      slowTime = !slowTime;
      if(slowTime)
        slowDown();
      else
        speedUp();
    }
    else if(!startLevel && event.type == SDL_MOUSEBUTTONDOWN){
      int x,y;
      SDL_GetMouseState(&x, &y);
      collisionHandler(x,y-2*SCALESIZE);
       
    } 
    else if(event.type == SDL_TEXTINPUT){
      mainCharacter->setTyping(true);	
      processInput(event.text.text[0]);
    }
  }
}


void Game::processInput(char input)
{
  bool match = false;	
  if(input == SDLK_SPACE && startLevel){
    pauseLevel = !pauseLevel;	
    if(pauseLevel==false){
      mainCharacter->unfreeze();
      worker->unfreeze(); 
      boss->unfreeze(); 
      mainMenu->setMenuDisplay(0); 
    }
    else{
      mainMenu->setMenuDisplay(6); 
    } 
    return;
  }
  if(startLevel && !pauseLevel){	
	  for(int i = 0; i < textVector.capacity(); i++){
		  if(textVector[i]->hasText() && textVector[i]->getText().front() == input){
        match = true;	

        //Play Sound
          int randInt = rand()%6 + 1;
          if(randInt == 1){
            Mix_PlayChannel(-1, pop1, 0);
          }
          else if(randInt == 2){
            Mix_PlayChannel(-1, pop2, 0);
          }
          else if(randInt == 3){
            Mix_PlayChannel(-1, pop3, 0);
          }
          else if(randInt == 4){
            Mix_PlayChannel(-1, pop4, 0);
          }
          else if(randInt == 5){
            Mix_PlayChannel(-1, pop5, 0);
          }
          else if(randInt == 6){
            Mix_PlayChannel(-1, pop6, 0);
          }

        Letter* letter = new Letter();
        letter->loadLetter(input, renderer);
        letter->setX(textVector[i]->getXPos());
        letter->setY(SCREEN_END_YPOS + TEXT_ROW_OFFSET + i*TEXT_SIZE);
        if(slowTime){
          letter->setSpeed(LETTER_SLOW_SPEED);
        } 
        letterVector.push_back(letter);
        int letterScore = scoreboard->updateScore(LETTER_TYPED_SCORE, 1);
        mainCharacter->setScoring(letterScore, 1);
        if(textVector[i]->getText().length() > 1){
          textVector[i]->popFront();
        }
        else if(textVector[i]->getText().length() == 1){
          int wordScore = scoreboard->calculateAndAddWordScore(textVector[i]->getOriginalText());	
          mainCharacter->setScoring(wordScore, 2);
          textVector[i]->loadText(textGenerator->create());	
        }
      }
    }

    if(!match){
        if(SDL_GetTicks() - soundTime >= 20){
          Mix_PlayChannel(-1, invalidSound, 0);
          soundTime = SDL_GetTicks();
        }
      scoreboard->setMultiplier(0);
    }
    else{
      scoreboard->setMultiplier(scoreboard->getMultiplier()+1);
      match = false;
    }	
  }
  else if(toupper(input) == startWord.front()){
    Mix_PlayChannel(-1, startLetterSound, 0);
    soundTime = SDL_GetTicks();
    mainMenu->setMenuDisplay(1);
    startWord.erase(startWord.begin()); 
    screen->raiseLetter(); 
    if(startWord.length() == 0){
      scoreboard->reset();
      startLevel = true;
      Mix_PlayChannel(-1, screenSound, 0);
      quitLevel = false; 
	  }
  }
	else if(input == 'c'){
		mainMenu->setMenuDisplay(2);
	}
  else if(input == 't'){
    mainMenu->setMenuDisplay(1);
  } 
  else if(input == 'l'){
    mainMenu->setMenuDisplay(3);
  } 
  else if(input == 'h'){
    mainMenu->setMenuDisplay(4);
  }
  else if(input == 'o'){
    mainMenu->setMenuDisplay(5);
  } 
}

void Game::setupTrophies()
{
  trophyList.resize(25);
  for(int i = 0; i < 25; i++){
    trophyList[i] = trophyFactory->makeTrophy(NULL); 
    trophyList[i]->setObjectTexture(animationSheet);
  }

}

void Game::dropTrophy()
{
  if(trophyDropIndex < trophyList.size()){
    trophyList[trophyDropIndex]->setDrop(true);
    trophyDropIndex++;
  }
}

void Game::collisionHandler(double x, double y)
{
  int scoreValue = NULL;
  char scoreString[5];
  if(!startLevel && x && y){
      if(boss->collisionCheck(x,y)){
        scoreValue = 100; 
        strcpy(scoreString, "+100");
        boss->setHeavyHead(true);
      } 
      else if(worker->collisionCheck(x,y)){
        scoreValue = 100; 
        strcpy(scoreString, "+100");
        worker->setHeavyHead(true);
      }
      else if(mainCharacter->collisionCheck(x,y)){
        scoreValue = 100;
        strcpy(scoreString, "+100");
        mainCharacter->setHeavyHead(true);
      }
      else if(door->collisionCheck(x,y)){
        scoreValue = 100;
        strcpy(scoreString, "+100");
        door->setAnimate(true);
      }
      else if(fountain->collisionCheck(x,y)){
        scoreValue = 100;
        strcpy(scoreString, "+100");
      }
      else if(trashcan->collisionCheck(x,y)){
        scoreValue = 100; 
        strcpy(scoreString, "+100");
        trashcan->animate();
      }
      else if(clock->collisionCheck(x,y)){
        scoreValue = 100; 
        strcpy(scoreString, "+100");
      }
      else if(worker->computerCollisionCheck(x,y)){
        worker->updateComputer();
        scoreValue = 100; 
        strcpy(scoreString, "+100");
      }
      else if(boss->coffeeCollisionCheck(x,y)){
        scoreValue = 500;
        strcpy(scoreString, "+500");
      }
      if(scoreValue){ 
        
        Mix_PlayChannel(-1, hit1, 0);
       
        Scorer* score = new Scorer(scoreString, renderer, x,y);
        scoreboard->updateScore(scoreValue,2); 
        if(slowTime){
          score->setSpeed(LETTER_SLOW_SPEED);
        }
        scoreVector.push_back(score); 
      }
  }
  else if (startLevel && !x && !y){ 
   for(int i = 0; i < letterVector.size(); i++){
      if(letterVector[i]->getOnGround() == false){
        int scoreValue = NULL;
        bool deleteLetter = false;
        if(boss->collisionCheck(letterVector[i]->getX(),letterVector[i]->getY())){
          scoreValue = 100; 
          letterVector[i]->setY(BOSS_SPAWN_Y-90);
          letterVector[i]->setOnGround(true);
          letterVector[i]->setDynamic(1); 
          boss->setHeavyHead(true);
        } 
        else if(worker->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100; 
          letterVector[i]->setY(COWORKER_SPAWN_Y-40);
          letterVector[i]->setOnGround(true);
          worker->setHeavyHead(true);
        }
        else if(mainCharacter->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100;
          letterVector[i]->setY(76*SCALESIZE);
          letterVector[i]->setOnGround(true);
          mainCharacter->setHeavyHead(true);
        }
        else if(door->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100;
          letterVector[i]->setDynamic(2);
          letterVector[i]->setY(77*SCALESIZE);
          letterVector[i]->setOnGround(true);
          door->setAnimate(true);
        }
        else if(fountain->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100;
          letterVector[i]->setDynamic(2);
          letterVector[i]->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y - 20);
          letterVector[i]->setOnGround(true);
        }
        else if(trashcan->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100; 
          deleteLetter = true;
          trashcan->animate();
        }
        else if(clock->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          scoreValue = 100; 
          deleteLetter = true; 
        }
        else if(worker->computerCollisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
          worker->updateComputer();
          scoreValue = 100; 
          deleteLetter = true;
        }
        if(scoreValue){ 
        
          int multValue = scoreboard->getMultValue();
          if(multValue == 1){
            Mix_PlayChannel(-1, hit1, 0);
          }
          else if(multValue == 2){
            Mix_PlayChannel(-1, hit2, 0);
          }
          else if(multValue == 3){
            Mix_PlayChannel(-1, hit3, 0);
          }
          else if(multValue == 4){
            Mix_PlayChannel(-1, hit4, 0);
          }
          else if(multValue == 5){
            Mix_PlayChannel(-1, hit5, 0);
          }
          else if(multValue == 6){
            Mix_PlayChannel(-1, hit6, 0);
          }
          else if(multValue == 7){
            Mix_PlayChannel(-1, hit7, 0);
          }
          else if(multValue == 8){
            Mix_PlayChannel(-1, hit8, 0);
          }
          else if(multValue == 9){
            Mix_PlayChannel(-1, hit9, 0);
          }
          else if(multValue == 10){
            Mix_PlayChannel(-1, hit10, 0);
          }
          Scorer* score = new Scorer("+100", renderer, letterVector[i]->getX(), letterVector[i]->getY());
          scoreboard->updateScore(scoreValue,2); 
          if(slowTime){
            score->setSpeed(LETTER_SLOW_SPEED);
          }
          scoreVector.push_back(score); 
          if(deleteLetter){ 
            Letter* temp = letterVector[i];	
            letterVector.erase(letterVector.begin()+i);
            delete(temp);
          }
        }
      }
    }
  }
}


void Game::start()
{	
  currentLevel = new Level(1,LEVEL_ONE_SPEED, levelNum, renderer);
  loadBackground();		
  loadAnimationSheet();	
  mainCharacter = new Character(renderer);
  mainCharacter->setObjectTexture(animationSheet);
  mainMenu->loadFromRenderedText(); 
  mainMenu->setObjectTexture(animationSheet); 
  screen = new GameScreen(renderer);
  screenRaised = true; 
  screen->setObjectTexture(animationSheet);
  worker = new Coworker(renderer);
  worker->setObjectTexture(animationSheet); 
  boss = new Boss(renderer);
  boss->setObjectTexture(animationSheet);
  trophyFactory = new TrophyFactory(renderer);
  setupTrophies();
  desk = new Object(80, 82, 27, 16, MAIN_CHARACTER_DESK_SPAWN_X, MAIN_CHARACTER_DESK_SPAWN_Y, renderer);
  desk->setObjectTexture(animationSheet);
 
  trashcan = new Trashcan(renderer);
  trashcan->setObjectTexture(animationSheet);

  fountain = new Fountain(renderer);
  fountain->setObjectTexture(animationSheet);  
  
  clock = new Clock(renderer);
  clock->setObjectTexture(animationSheet); 
  
  door = new Door(renderer);
  door->setObjectTexture(animationSheet); 

  Object* mouse = new Object(149, 68, 6, 6, 0, 0, renderer);
  mouse->setObjectTexture(animationSheet);
  int mouseY;
  int mouseX;
 
  //Mix_PlayChannel(-1, backgroundPrinter, 0);
  Mix_PlayChannel(-1, pauseSound, 0);
  
  while(!quit){
    SDL_RenderClear(renderer);
    SDL_Rect dest = {.x = 0, .y = 0, .w = SCREEN_WIDTH, .h = SCREEN_HEIGHT}; 
    SDL_RenderCopy(renderer, background, NULL, &dest);	


    

    door->render();  
    clock->render(); 
    trashcan->render(); 
    fountain->render(); 
    if(startLevel && !quitLevel && screenDropped){ 
      displayDynamicLetters(); 
    } 
    boss->render(); 
    desk->render(); 
    worker->render();

   
    if(startLevel && !quitLevel){
      if(Mix_PlayingMusic() == 0){
        if(Mix_PlayMusic(gameplayMusic, -1) == -1){
         // printf("music error\n");
        }
      }
      else if(Mix_PausedMusic() == 1){
        Mix_ResumeMusic();
      }
      if(!levelTime){
        levelTime = SDL_GetTicks();
      }
      if((SDL_GetTicks() - levelTime) > currentLevel->getLifetime()){
        //Mix_PlayChannel(-1, levelUpSound, 0);
        newLevel();
      }
      else{
        double newAngle = ((SDL_GetTicks()- levelTime)/(double)currentLevel->getLifetime()) * 360;
        clock->setMinuteHandAngle(newAngle);
      }
      screen->renderScreen(); 
      if(screenDropped){
        if(textVector[0] == NULL || textVector[0]->getText().length() == 0){
          textVector = populateTextVector();
        }
        displayTextVector();	
        scoreboard->render();
        screen->renderFrame();	
        collisionHandler(NULL, NULL); 
      } 
      else if (screen->getLettersRaised()){
        mainMenu->setRaiseMenu(true);
        mainMenu->render();
        screenDropped = screen->dropScreen();
        screenRaised = !screenDropped; 
        screen->renderScreen(); 
        if(screenDropped){
          mainMenu->reset();
        }
      }
      else{
        mainMenu->render();
      }
      if(pauseLevel){
        mainMenu->render(); 
        mainCharacter->freeze();
        worker->freeze(); 
        boss->freeze(); 
      }   
      //currentLevel->render();
    }
    
    else if(quitLevel){
      screen->renderScreen(); 
      if(!screenRaised){
        screenRaised = screen->liftScreen();
        screenDropped = !screenRaised; 
      }
      else if(!screen->getLettersDropped()){
        screen->dropLetter();
      } 
      else{
        startWord = "START"; 
        startLevel = false;	
        quitLevel = false;
      }	
    }
    else{
      mainMenu->render();
      screen->renderScreen(); 
    }
    if(trophyDropIndex < trophyList.size() && SDL_GetTicks() - trophyTime > 50){ 
      dropTrophy();
      trophyTime = SDL_GetTicks();
    }
    for(int i = 0; i < trophyList.size(); i++){
      trophyList[i]->render();
    }
    mainCharacter->render();	
    displayLetterVector();	
    displayScoreVector(); 
    
    eventHandler();	//for typing	

    if(slowTime){
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 191, 220, 245, slowRectAlpha);
      SDL_RenderFillRect(renderer, &slowRect);
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); 
      if(slowRectAlpha < 0x30){
        slowRectAlpha+=5;
      } 
    }
    else if(slowRectAlpha > 0){
      slowRectAlpha-=5;
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 191, 220, 245, slowRectAlpha);
      SDL_RenderFillRect(renderer, &slowRect);
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); 
      if(slowRectAlpha < 0){
        slowRectAlpha=0;
      }
    } 
    if(renderLevelDisplay)
      currentLevel->render();
    
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_ShowCursor(0);
    mouse->setX(mouseX);
    mouse->setY(mouseY);
    mouse->render();
    SDL_RenderPresent(renderer);
    /*if(strikes == 3){
      quitLevel = true;
      screen->setEndGame(true); 
      strikes = 0; 
    }*/ 

    
  }
}
