/* 
    Douglas R. Ferreira
	
	Última Atualização
    Rio de Janeiro, 23/05/2016
*/

#include "Core.h"
#include "Game_Main.h"

bool Input::stillPressed = false;
SDL_Window* _window;    // Janela do programa
SDL_Renderer* renderer; // Renderizador que exibirá a imagem
SDL_Event _event, _inputEvent;

bool isRunning = true; // Variavel para o loop principal que verifica o jogo está ou não em execução
Uint32 globalTime; //Variável para controlar FPS.

int main(int argc, char* args[]) {

	// Inicializa todos os módulos do SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	// Inicializa o módulo de fontes 
	TTF_Init();
	// Cria a janela
	_window = SDL_CreateWindow("Killer Run", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	//Cria o Render
	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	//Inicializa o Modulo de áudio
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	
	Game_Setup(); // Inicializa configurações do jogo
		
	////////////////////////// Loop Principal ///////////////////////
	while (isRunning) {
			
		globalTime = SDL_GetTicks();
			
		SDL_RenderClear(renderer); // Limpa o render a cada frame
		Game_Loop(); // Loop principal do jogo
		
		SDL_RenderPresent(renderer); // Atualiza  render a cada frame
					
		// Captura evento caso ao clicar no botão para fechar janela
		while (SDL_PollEvent(&_event)) {
			
			if (_event.type == SDL_QUIT) {
				isRunning = false;
			}
					
		}
						
		//Limita o FPS a um valor definido no #define FPS Core.h
		if ((1000 / FPS) >= SDL_GetTicks() - globalTime) {
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - globalTime));
		
		}
	
	}
	///////////////////// Fim do Loop Principal ///////////////////////
	
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	Mix_CloseAudio();
	SDL_Quit();
	
	return 0;

} /////////////////// Fim do método Main ////////////////////

// Construtor e Destrutor
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
//Carrega um arquivo de imagem
void GameObject::LoadTexture(std::string filePath) {
	texture = IMG_LoadTexture(renderer, filePath.c_str());
}

// Método para criar um Rect no objeto de jogo (Game Object)
void GameObject::CreateRect(int width, int height, int position_x, int position_y) {
	transform.w = width;
	transform.h = height;
	transform.x = position_x;
	transform.y = position_y;
}

void GameObject::CreateTextureArea(int width, int height, int position_x, int position_y) {
	textureArea.w = width;
	textureArea.h = height;
	textureArea.x = position_x;
	textureArea.y = position_y;
}

SDL_Texture* GameObject::GetTexture(){
	return this->texture;
}

	// Executa um game object na cena
	void RunOnScene(GameObject object) {
		
		if (object.isActive) {
		
			SDL_RenderCopy(renderer, object.GetTexture(), NULL, &object.transform);

			if (object.GetTexture() == NULL)
			printf("\nCould not load the texture image!");
				
		}
		
	}

	// Método sobrecarregado para carregar somente um pedaço específico da textura
	void RunOnScene(GameObject object, SDL_Rect textureArea) {
		if (object.isActive) {
			SDL_RenderCopy(renderer, object.GetTexture(), &textureArea, &object.transform);

			if (object.GetTexture() == NULL)
				printf("\nCould not load the texture image!");
		}
	}
			
	SDL_Rect SetRect(int w, int h, int x, int y) {

		SDL_Rect _tempRect;

		_tempRect.w = w;
		_tempRect.h = h;
		_tempRect.x = x;
		_tempRect.y = y;

		return _tempRect;
	}
	
	// Detecta se determinada tecla está pressionada
	bool Input::KeyHold(SDL_Scancode keypressed) {
	
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);
		if (keyboard[keypressed]) {
			return true;
		} 
		return false;
	}
	// Só pode ser pode usar uma vez, precisa de melhorias
	bool Input::KeyPress(SDL_Scancode keypress)	{
		
		SDL_Event _inputEvent;
		bool check =  false;
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		
		if (SDL_PollEvent(&_inputEvent) == 1) {
			
			if (_inputEvent.type == SDL_KEYDOWN && keys[keypress] && !Input::stillPressed) {
				Input::stillPressed = true;
				check = true;
			}
			if (_inputEvent.type == SDL_KEYUP)
				Input::stillPressed = false;
		
		}
			
		if (check)
			return true;
		else 
			return false;
	}

