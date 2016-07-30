/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 16/05/2016
*/

#pragma once

#include "Core.h"


// Estrutura para criar um Texto e exibir na tela
struct Text {
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* tempTextSurface;

	SDL_Rect textPosition;
	SDL_Texture* textTexture = NULL;

};

void Game_GUI_Setup();
void Game_GUI_Loop();

void PutTextOnScreen(Text text, std::string message);
void UpdateTextValue(Text text, int value);
void UpdateTextValue(Text text, int value, Uint8 red, Uint8 green, Uint8 blue);
