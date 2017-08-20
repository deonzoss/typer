#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
  this->renderer = renderer;
  textVector = makeTextVector();
  textGenerator = new TextGenerator(renderer);	
  scoreboard = new Scoreboard(renderer);
  mainMenu = new Menu(renderer);
  quit = false;
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
  for(int j = 0; j < textVector.size(); j++){
    if(textVector[j]->offScreen()){
      textVector[j]->loadText(textGenerator->create());
      strikes++;
      printf("X\n"); 
    }	
    textVector[j]->render(textVector[j]->getXPos(),TEXT_ROW_OFFSET +  j*TEXT_SIZE);
    if(!pauseLevel){
      textVector[j]->move();	
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
      letterVector[j]->move();
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
              letterVector[j]->setY(BOSS_SPAWN_Y-90);
            else
              letterVector[j]->setY(BOSS_SPAWN_Y-80);
               
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
  if(loadedSurface == NULL){
    printf("Error loading surface. SDL_image Error: %s\n", IMG_GetError());
  }
  else{
    background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(background == NULL){
      printf("Unable to create texture from surface. SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
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
    letterVector[i]->setSpeed(10);
  }
  for(int i = 0; i < scoreVector.size(); i++){
    scoreVector[i]->setSpeed(10);
  }
  mainCharacter->setSpeed(10);
  boss->setSpeed(10);
  clock->setSpeed(10); 
  door->setSpeed(10);

  return;
}

void Game::speedUp(){
  double newSpeed = textVector[0]->getSpeed() * 3; 
  for(int i = 0; i < textVector.size(); i++){
    textVector[i]->setSpeed(newSpeed);
  } 
  for(int i = 0; i < letterVector.size(); i++){
    letterVector[i]->setSpeed(1);
  } 
  for(int i = 0; i < scoreVector.size(); i++){
    scoreVector[i]->setSpeed(1);
  }
  mainCharacter->setSpeed(1); 
  boss->setSpeed(1);
  clock->setSpeed(1); 
  door->setSpeed(1); 
  return;
}

void Game::eventHandler()
{
  while(SDL_PollEvent(&event) != 0){
    if(event.type == SDL_QUIT){
      quit = true;
    }
    else if(startLevel && event.key.keysym.sym==SDLK_ESCAPE && event.type == SDL_KEYUP){
      quitLevel = true;
      screen->setEndGame(true);
    }
    else if(startLevel && event.key.keysym.sym==SDLK_RETURN && event.type == SDL_KEYUP){
      slowTime = !slowTime;
      if(slowTime)
        slowDown();
      else
        speedUp();
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN){
      int x,y;
      SDL_GetMouseState(&x, &y);
      Letter* letter = new Letter();
      letter->loadLetter('a', renderer);
      letter->setX(x);
      letter->setY(y);
      if(slowTime){
        letter->setSpeed(LETTER_SLOW_SPEED);
      } 
      letterVector.push_back(letter);
       
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
      mainMenu->setMenuDisplay(1); 
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
        Letter* letter = new Letter();
        letter->loadLetter(input, renderer);
        letter->setX(textVector[i]->getXPos());
        letter->setY(TEXT_ROW_OFFSET + i*TEXT_SIZE);
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
      scoreboard->setMultiplier(0);
    }
    else{
      scoreboard->setMultiplier(scoreboard->getMultiplier()+1);
      match = false;
    }	
  }
  else if(toupper(input) == startWord.front()){
    startWord.erase(startWord.begin()); 
    screen->raiseLetter(); 
    if(startWord.length() == 0){
      startLevel = true;
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

Level* Game::newLevel(int levelNum){	
  if(levelNum == 1){
    Level* level = new Level();
    level->setMaxWords(10);
    level->setWordRate(1);
    level->setSpeed(LEVEL_ONE_SPEED);	
    return level;	
  }
  return NULL;
}

void Game::collisionHandler()
{
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
        letterVector[i]->setY(700);
        letterVector[i]->setOnGround(true);
        mainCharacter->setHeavyHead(true);
      }
      else if(door->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
        scoreValue = 100;
        letterVector[i]->setDynamic(2);
        letterVector[i]->setY(710);
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
      }
      else if(clock->collisionCheck(letterVector[i]->getX(), letterVector[i]->getY())){
        scoreValue = 100; 
        deleteLetter = true; 
      }
      if(scoreValue){ 
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
void Game::start()
{	
  currentLevel = newLevel(1);
  textVector = populateTextVector();
  loadBackground();		
  loadAnimationSheet();	
  mainCharacter = new Character(renderer);
  mainCharacter->setObjectTexture(animationSheet);
  mainMenu->loadFromRenderedText(); 
  mainMenu->setObjectTexture(animationSheet); 
  screen = new Screen(renderer);
  screenRaised = true; 
  screen->setObjectTexture(animationSheet);
  worker = new Coworker(renderer);
  worker->setObjectTexture(animationSheet); 
  boss = new Boss(renderer);
  boss->setObjectTexture(animationSheet);
  
  desk = new Object(800, 820, 270, 160, 0, 760, renderer);
  desk->setObjectTexture(animationSheet);
 
  trashcan = new Trashcan(renderer);
  trashcan->setObjectTexture(animationSheet);

  fountain = new Fountain(renderer);
  fountain->setObjectTexture(animationSheet);  
  
  clock = new Clock(renderer);
  clock->setObjectTexture(animationSheet); 
  
  door = new Door(renderer);
  door->setObjectTexture(animationSheet); 
  
  while(!quit){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);	

    screen->renderScreen(); 
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
    mainCharacter->render();	

   
    if(startLevel && !quitLevel){
      if(screenDropped){
        displayTextVector();	
        scoreboard->render();
        screen->renderFrame();	
        displayLetterVector();	
        displayScoreVector(); 
        collisionHandler(); 
      } 
      else if (screen->getLettersRaised()){
        screenDropped = screen->dropScreen();
        screenRaised = !screenDropped; 
      }
      if(pauseLevel){
        mainMenu->render(); 
        mainCharacter->freeze();
        worker->freeze(); 
        boss->freeze(); 
      }   
    }
    
    else if(quitLevel){
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
    }
    
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
    SDL_RenderPresent(renderer);
    /*if(strikes == 3){
      quitLevel = true;
      screen->setEndGame(true); 
      strikes = 0; 
    }*/ 
    
  }
}
