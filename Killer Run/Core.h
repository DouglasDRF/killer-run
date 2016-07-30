/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 23/05/2016
*/

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdarg.h>

#define FPS 60
#define WINDOW_WIDTH 1024 
#define WINDOW_HEIGHT 576

extern SDL_Renderer* renderer;
extern Uint32 globalTime;

// Essa é uma classe básica de um Objeto de Jogo (Game Object).
// Objetos de jogo são quaisquer elementos que estão carregados e são exibidos na tela.
// É recomendado que use para agilizar o desenvolvimento reunindo dados em uma estrutura só.
class GameObject {
public:
		GameObject();
		~GameObject();
		
	float speed;
	bool isActive = true;
	bool onAir = false;
	bool onTop = false;
	bool accelerating = false;
	Uint32 airTiming = 0;
	SDL_Rect transform; // É o tamanho e a posição da imagem.
	SDL_Rect textureArea;
	void LoadTexture(std::string filePath);
	void CreateRect(int width, int height, int position_x, int position_y);
	void CreateTextureArea(int width, int height, int position_x, int position_y);
	SDL_Texture* GetTexture();

private:
	SDL_Texture* texture;
			
};


//Classe com funções que tratam as entradas do teclado.
class Input {
public:
	static bool stillPressed;
	static bool	KeyHold(SDL_Scancode keypressed); 
	static bool KeyPress(SDL_Scancode keypress); 
	
};

	// Este método executa um objeto de jogo na cena
	void RunOnScene(GameObject object);
	void RunOnScene(GameObject object, SDL_Rect textureArea);
	

	//Método para agilizar a criação de SDL_Rects em um única linha
	SDL_Rect SetRect(int w, int h, int x, int y);
	



	


	
	






