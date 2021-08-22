/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 12/04/2016
*/

#pragma once

#include "Core.h"
#include "Physics.h"
#include "Game_GUI.h"

enum GameScene {
	MENU, GAMEPLAY, GAMEOVER
};

extern int playerScore;
extern int gameLevel;
extern int chancesLeft;
extern int gameOverIndex;
extern GameScene gameState;
extern int highScore;


	void Game_Setup();
	void Game_Loop();
	


