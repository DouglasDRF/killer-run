/*
Douglas R. Ferreira

�ltima Atualiza��o
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

// Essa � uma classe b�sica de um Objeto de Jogo (Game Object).
// Objetos de jogo s�o quaisquer elementos que est�o carregados e s�o exibidos na tela.
// � recomendado que use para agilizar o desenvolvimento reunindo dados em uma estrutura s�.
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
	SDL_Rect transform; // � o tamanho e a posi��o da imagem.
	SDL_Rect textureArea;
	void LoadTexture(std::string filePath);
	void CreateRect(int width, int height, int position_x, int position_y);
	void CreateTextureArea(int width, int height, int position_x, int position_y);
	SDL_Texture* GetTexture();

private:
	SDL_Texture* texture;
			
};


//Classe com fun��es que tratam as entradas do teclado.
class Input {
public:
	static bool stillPressed;
	static bool	KeyHold(SDL_Scancode keypressed); 
	static bool KeyPress(SDL_Scancode keypress); 
	
};

	// Este m�todo executa um objeto de jogo na cena
	void RunOnScene(GameObject object);
	void RunOnScene(GameObject object, SDL_Rect textureArea);
	

	//M�todo para agilizar a cria��o de SDL_Rects em um �nica linha
	SDL_Rect SetRect(int w, int h, int x, int y);
	



	


	
	






