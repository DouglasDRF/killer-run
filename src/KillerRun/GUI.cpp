/*
Douglas R. Ferreira

�ltima Atualiza��o
Rio de Janeiro, 16/05/2016
*/

#include "GUI.h"

// Fun��o para colocar um texto est�tico na tela
void PutTextOnScreen(Text text, std::string message) {

	text.tempTextSurface = TTF_RenderText_Solid(text.font, message.c_str(), text.color);
	text.textTexture = SDL_CreateTextureFromSurface(renderer, text.tempTextSurface);
	SDL_RenderCopy(renderer, text.textTexture, NULL, &text.textPosition);

	SDL_FreeSurface(text.tempTextSurface);
	SDL_DestroyTexture(text.textTexture);

}

// m�todo que atualiza a cada frame uma vari�vel do tipo int e converte para string e exibe em texto
void UpdateTextValue(Text text, int value) {

	std::string _tempString = std::to_string(value);
	text.tempTextSurface = TTF_RenderText_Solid(text.font, _tempString.c_str(), text.color);
	text.textTexture = SDL_CreateTextureFromSurface(renderer, text.tempTextSurface);
	SDL_RenderCopy(renderer, text.textTexture, NULL, &text.textPosition);

	SDL_FreeSurface(text.tempTextSurface);
	SDL_DestroyTexture(text.textTexture);

}

// M�todo sobrecarregado que atualiza a variavel e a cor do texto
void UpdateTextValue(Text text, int value, Uint8 red, Uint8 green, Uint8 blue) {

	SDL_Color color = { red, green, blue };
	text.color = color;
	std::string _tempString = std::to_string(value);
	text.tempTextSurface = TTF_RenderText_Solid(text.font, _tempString.c_str(), text.color);
	text.textTexture = SDL_CreateTextureFromSurface(renderer, text.tempTextSurface);
	SDL_RenderCopy(renderer, text.textTexture, NULL, &text.textPosition);

	SDL_FreeSurface(text.tempTextSurface);
	SDL_DestroyTexture(text.textTexture);

}