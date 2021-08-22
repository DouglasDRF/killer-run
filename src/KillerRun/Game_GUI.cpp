/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 12/04/2016
*/

#include "Game_GUI.h"
#include "GUI.h"

Text scoreText;
Text scoreText_Value;
Text levelText;
Text levelText_Value;
Text chancesLeftText;
Text chancesLeftText_Value;

Text gameOverText;
Text playerScoreText;
Text playerScoreText_Value;
Text highScoreText;
Text highScoreText_Value;


// Este método está incluido no Game_Setup() no Game_Main.cpp
void Game_GUI_Setup() {
		
	// configuração do texto... Local do arquivo da fonte, COR RGB e tamanho e posição do Rect
	scoreText.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	scoreText.color = { 255, 255, 255 };
	scoreText.textPosition = SetRect(150, 30, 25, 20);

	scoreText_Value.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	scoreText_Value.color = { 255, 255, 255 };
	scoreText_Value.textPosition = SetRect(40, 30, 170, 20);

	levelText.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	levelText.color = { 255,255,255 };
	levelText.textPosition = SetRect(130, 30, 448, 25);

	levelText_Value.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	levelText_Value.color = { 255, 255, 255 };
	levelText_Value.textPosition = SetRect(40, 30, 492, 60);

	chancesLeftText.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	chancesLeftText.color = { 255, 255, 255 };
	chancesLeftText.textPosition = SetRect(180, 40, 820, 15);

	chancesLeftText_Value.font = TTF_OpenFont("Resources/Fonts/JUICE.ttf", 25);
	chancesLeftText_Value.color = { 255, 255 , 255 };
	chancesLeftText_Value.textPosition = SetRect(40, 30, 900, 60);

	gameOverText.font = TTF_OpenFont("Resources/Fonts/HATTEN.ttf", 50);
	gameOverText.color = { 255, 255, 255 };
	gameOverText.textPosition = SetRect(512, 45, 256, 125);

	highScoreText.font = TTF_OpenFont("Resources/Fonts/HATTEN.ttf", 30);
	highScoreText.color = { 255, 255 ,255 };
	highScoreText.textPosition = SetRect(256, 45, 412, 300);
	
	highScoreText_Value.font = TTF_OpenFont("Resources/Fonts/HATTEN.ttf", 30);
	highScoreText_Value.color = { 255, 255 ,255 };
	highScoreText_Value.textPosition = SetRect(40, 45, 512, 340);

	playerScoreText.font = TTF_OpenFont("Resources/Fonts/HATTEN.ttf", 30);
	playerScoreText.color = { 255, 255, 255 };
	playerScoreText.textPosition = SetRect(256, 45, 412, 192);

	playerScoreText_Value.font = TTF_OpenFont("Resources/Fonts/HATTEN.ttf", 30);
	playerScoreText_Value.color = { 255, 255, 255 };
	playerScoreText_Value.textPosition = SetRect(40, 45, 512, 230);

}

// Este método está incluido no Game_Loop() no Game_Main.cpp
void Game_GUI_Loop() {
	
	switch (gameState) {

	case GAMEPLAY:
		
		PutTextOnScreen(scoreText, "Pontos: ");
		PutTextOnScreen(levelText, "Level");
		PutTextOnScreen(chancesLeftText, "Chances Restantes");

		UpdateTextValue(scoreText_Value, playerScore);
		
		if (gameLevel < 5)
			UpdateTextValue(levelText_Value, gameLevel);
		else
			PutTextOnScreen(levelText_Value, "MAX");

		// Muda a cor conforme o jogador for perdendo chances restantes
		if (chancesLeft > 25)
			UpdateTextValue(chancesLeftText_Value, chancesLeft);
		if (chancesLeft > 10 && chancesLeft <= 25)
			// Amarelo meio escuro, e mais vísivel - Hex #FFD700 - RGB 255, 215, 0
			UpdateTextValue(chancesLeftText_Value, chancesLeft, 255, 215, 0);
		if (chancesLeft <= 10)
			UpdateTextValue(chancesLeftText_Value, chancesLeft, 255, 0, 0); // Vermelho, óbvio kkk 
		break;

	case GAMEOVER:
		
		switch (gameOverIndex) {
			
			case 1:
				PutTextOnScreen(gameOverText, "Você colidiu o seu avião!");
				PutTextOnScreen(playerScoreText, "Sua pontuação final ");
				PutTextOnScreen(highScoreText, "High Score");
				UpdateTextValue(highScoreText_Value, highScore);
				UpdateTextValue(playerScoreText_Value, playerScore);
			break;
			
			case 2:
				PutTextOnScreen(gameOverText, "Você deixou inimigos demais passarem");
				PutTextOnScreen(playerScoreText, "Sua pontuação final ");
				PutTextOnScreen(highScoreText, "High Score");
				UpdateTextValue(highScoreText_Value, highScore);
				UpdateTextValue(playerScoreText_Value, playerScore);
			break;
		}

		break;
	}

}




