/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 12/04/2016
*/

#include "Game_Main.h"
#include "Sounds.h"

// váriavel que indica a posição do chão
const int floorPositionY = 440;
const int topPositionY = 50;

// elementos da que compõe a cena
GameObject menuBackground;
GameObject gameOverBackground;
GameObject background;
GameObject character;
GameObject enemyA, enemyB, enemyC, enemyD;
GameObject missile, enemyMissile;
GameObject explosion;

// Faixas de audio em WAV
Mix_Chunk* shot;


//Obs: O SDL usa valores do tipo int no SDL_Rect e nos seus eixos x, y na tela
// O C++ permite "misturar" variáveis do tipo int e float em operações matemáticas
// Porém, no caso do SDL a variável final que recebe o valor é int então esse valor será arredondado
const float perSecond = 0.016; // 1 / 60 Frames

// Velocidade de cada elemento na cena - Em Pixels Por Segundo
const int scenarioSpeed = 400;
const int playerSpeed = 700 ;
int enemySpeed = 1000;
const int shotSpeed = 4200;

int _tempX, _tempXB, _tempXC, _tempXD; // Várivael que armazena temporariamente e atualiza a posição de X explosão ser exibida na tela
int _tempY, _tempYB, _tempYC, _tempYD;// Várivael que armazena temporariamente e atualiza a posição de Y do avião para passa pro míssel
Uint32 killTime = 0, killTimeB = 0, killTimeC = 0, killTimeD = 0;

bool exploded, explodedB, explodedC, explodedD; // variável indica quando a imagem da explosão deve ser exibida

int highScore;
int playerScore; // váriavel que armazena e
int chancesLeft;
int gameLevel;
int gameOverIndex; // Variavel que determina qual tela de gameover será exeibida

GameScene gameState = MENU; // Este enum está no arquivo de cabeçalho Game_Main.h

void Game_Setup() {

	Game_GUI_Setup();

	// preparando a função padrão do C/C++ rand() para não gerar o mesmo valor repetido de compilação
	srand((unsigned)time(NULL));

	// Inicializando todos os objetos, carregando a imagem e criando um retângulo
	menuBackground.LoadTexture("Resources/Images/MainMenu.png");
	menuBackground.CreateRect(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	background.LoadTexture("Resources/Images/Scenario_Extended.png");
	background.CreateRect(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
	background.CreateTextureArea(530, 330, 0, 0);

	character.LoadTexture("Resources/Images/Plane.png");
	character.CreateRect(104, 40, 50, 100);

	enemyA.LoadTexture("Resources/Images/Enemy.png");
	enemyA.CreateRect(104, 40, 1280, rand() % floorPositionY);
	enemyB.LoadTexture("Resources/Images/Enemy2.png");
	enemyB.CreateRect(104, 40, 2048, rand() % floorPositionY);
	enemyC.LoadTexture("Resources/Images/Enemy3.png");
	enemyC.CreateRect(104, 40, 3064, rand() % floorPositionY);
	enemyD.LoadTexture("Resources/Images/Enemy4.png");
	enemyD.CreateRect(104, 40, 4096, rand() % floorPositionY);

	missile.LoadTexture("Resources/Images/Missile.png");
	missile.CreateRect(80, 20, (character.transform.x + 15), (character.transform.y + 20));
	missile.isActive = false;

	enemyMissile.LoadTexture("Resources/Images/MissileInverted.png");
	enemyMissile.CreateRect(80, 20, (character.transform.x + 15), (character.transform.y + 20));
	enemyMissile.isActive = false;

	explosion.LoadTexture("Resources/Images/Explosion.png");
	explosion.CreateRect(80, 80, NULL, NULL);

	gameOverBackground.LoadTexture("Resources/Images/GameOver_Base.png");
	gameOverBackground.CreateRect(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	shot = Mix_LoadWAV("Resources/Sounds/SFX_Shot.wav");
	
	

}

void Game_Loop() {

	// Alterna as telas e os estados de jogo
	switch (gameState) {

	case MENU:
		playerScore = 0;
		gameLevel = 1;
		chancesLeft = 50;
		RunOnScene(menuBackground);
		if (Input::KeyHold(SDL_SCANCODE_RETURN)) {
			gameState = GAMEPLAY;
		}
		break;

	case GAMEPLAY:

		//Carregando e atualizando os elementos na tela
		//Obs: Os elementos devem em ordem, do fundo para o elemento mais a frente
		RunOnScene(background, background.textureArea); // fundo do cenário
		RunOnScene(character); //  sobreposto o fundo do cenário
		RunOnScene(enemyA); // sucessivamente ...

		if(gameLevel >= 2)
			RunOnScene(enemyB);

		if (gameLevel >= 3)
			RunOnScene(enemyC);

		if (gameLevel >= 4)
			RunOnScene(enemyD);

		RunOnScene(missile);
		Game_GUI_Loop(); // Interface grafica por último

		//Faz a textura do cenário correr para dar sensação de movimento.
		background.textureArea.x += scenarioSpeed *perSecond;
		if (background.textureArea.x >= 1060) {
			background.textureArea.x = 0;
		}

		///////////////////////////// Explosão dos inimigos /////////////////////
		if (exploded) {
			explosion.transform.x = _tempX;
			explosion.transform.y = _tempY;
			RunOnScene(explosion);
			if ((SDL_GetTicks() - killTime) > 250) {
				exploded = false;
			}
		}

		if (explodedB) {
			explosion.transform.x = _tempXB;
			explosion.transform.y = _tempYB;
			RunOnScene(explosion);
			if ((SDL_GetTicks() - killTimeB) > 350) {
				explodedB = false;
			}
		}

		if (explodedC) {
			explosion.transform.x = _tempXC;
			explosion.transform.y = _tempYC;
			RunOnScene(explosion);
			if ((SDL_GetTicks() - killTimeC) > 350) {
				explodedC = false;
			}
		}

		if (explodedD) {
			explosion.transform.x = _tempXD;
			explosion.transform.y = _tempYD;
			RunOnScene(explosion);
			if ((SDL_GetTicks() - killTimeD) > 350) {
				explodedD = false;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////

		////////////////////////////// Programação dos inimigos //////////////////////////////

			// Faz o inimigo A ir em direção ao personagem,
			enemyA.transform.x -= enemySpeed * perSecond; // V = S * T

			if (enemyA.transform.x <= -5) {
				enemyA.isActive = true;
				chancesLeft--;
				enemyA.transform.x = rand() % 1100 + WINDOW_WIDTH;
				enemyA.transform.y = rand() % (floorPositionY - 50) + topPositionY;

			}

			if (gameLevel >= 2) {
				enemyB.isActive = true;
				// Faz o inimigo B ir em direção ao personagem somente a partir do level 2
				enemyB.transform.x -= enemySpeed * perSecond; // V = S * T

				if (enemyB.transform.x <= -5) {
					enemyB.isActive = true;
					chancesLeft--;
					enemyB.transform.x = rand() % 2048 + WINDOW_WIDTH;
					enemyB.transform.y = rand() % (floorPositionY - 50) + topPositionY;

				}
			}

			if (gameLevel >= 3) {
				enemyC.isActive = true;
				// Faz o inimigo C ir em direção ao personagem somente a partir do level 2
				enemyC.transform.x -= enemySpeed * perSecond; // V = S * T

				if (enemyC.transform.x <= -5) {
					enemyC.isActive = true;
					chancesLeft--;
					enemyC.transform.x = rand() % 3064 + WINDOW_WIDTH;
					enemyC.transform.y = rand() % (floorPositionY - 50) + topPositionY;
				}
			}

			if (gameLevel >= 3) {
				enemyD.isActive = true;
				// Faz o inimigo C ir em direção ao personagem somente a partir do level 2
				enemyD.transform.x -= enemySpeed * perSecond; // V = S * T

				if (enemyD.transform.x <= -5) {
					enemyD.isActive = true;
					chancesLeft--;
					enemyD.transform.x = rand() % 4096 + WINDOW_WIDTH;
					enemyD.transform.y = rand() % (floorPositionY - 50) + topPositionY;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////// Programação dos misseis /////////////////////////////////////////

		//Mantém a posição de saída do míssel em relação ao avião atualizada
		if (!missile.isActive)
			missile.transform.y = character.transform.y + 25;

		//Movimentação do míssel ao ser disparado
		if (missile.isActive) {
			missile.transform.x += shotSpeed * perSecond; // V = S * T
			if (missile.transform.x > WINDOW_WIDTH) {
				missile.transform.x = character.transform.x + 15;
				missile.transform.y = character.transform.y + 25;
				missile.isActive = false;
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////



		// Aumenta o nível de dificuldade do jogo
		// OBS é invertido para aumentar a precisão da detecção e evitar bugs eviando usar o operador ==
		// já que o jogador pode fazer mais de um ponto de uma vez
		if (playerScore > 200) {
			gameLevel = 5;
			enemySpeed = 1350;
		
		}
		if (playerScore > 100) {
			gameLevel = 4;
			enemySpeed = 1275;
		
		}
		if (playerScore > 30) {
			gameLevel = 3;
			enemySpeed = 1200;
		
		}
		if (playerScore > 10) {
			gameLevel = 2;
			enemySpeed = 1100;
			
		}

		// Game over se todas as chances de errar do jogador acabar
		if (chancesLeft <= 0) {
			gameState = GAMEOVER;
			gameOverIndex = 2;
		}

		///////////////////////////////////// Colisões //////////////////////////////////////

		// Colisões do personagem
		if (Physics::GetCollision(character, enemyA) && character.isActive && enemyA.isActive) {
			character.isActive = false;
			missile.isActive = false;
			enemyA.isActive = false;
			enemyB.isActive = false;
			enemyC.isActive = false;
			enemyD.isActive = false;
			missile.isActive = false;
			gameState = GAMEOVER;
			gameOverIndex = 1;

		}

		if (Physics::GetCollision(character, enemyB) && character.isActive && enemyB.isActive) {
			character.isActive = false;
			missile.isActive = false;
			enemyA.isActive = false;
			enemyB.isActive = false;
			enemyC.isActive = false;
			enemyD.isActive = false;
			missile.isActive = false;
			gameState = GAMEOVER;
			gameOverIndex = 1;
		}

		if (Physics::GetCollision(character, enemyC) && character.isActive && enemyC.isActive) {
			character.isActive = false;
			missile.isActive = false;
			enemyA.isActive = false;
			enemyB.isActive = false;
			enemyC.isActive = false;
			enemyD.isActive = false;
			missile.isActive = false;
			gameState = GAMEOVER;
			gameOverIndex = 1;
		}
		if (Physics::GetCollision(character, enemyD) && character.isActive && enemyD.isActive) {
			character.isActive = false;
			missile.isActive = false;
			enemyA.isActive = false;
			enemyB.isActive = false;
			enemyC.isActive = false;
			enemyD.isActive = false;
			missile.isActive = false;
			gameState = GAMEOVER;
			gameOverIndex = 1;
		}


		// Colisão dos misseis e inimigos
		if (Physics::GetCollision(missile, enemyA) && missile.isActive) {
			_tempX = enemyA.transform.x;
			_tempY = enemyA.transform.y;
			enemyA.transform.x = rand() % 1280 + WINDOW_WIDTH;
			enemyA.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			killTime = SDL_GetTicks();
			playerScore++;
			exploded = true;
		}

		if (Physics::GetCollision(missile, enemyB) && missile.isActive) {
			_tempXB = enemyB.transform.x;
			_tempYB = enemyB.transform.y;
			enemyB.transform.x = rand() % 2048 + WINDOW_WIDTH;
			enemyB.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			killTimeB = SDL_GetTicks();
			playerScore++;
			explodedB = true;
		}

		if (Physics::GetCollision(missile, enemyC) && missile.isActive) {
			_tempXC = enemyC.transform.x;
			_tempYC = enemyC.transform.y;
			enemyC.transform.x = rand() % 3064 + WINDOW_WIDTH;
			enemyC.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			killTimeC = SDL_GetTicks();
			playerScore++;
			explodedC = true;
		}

		if (Physics::GetCollision(missile, enemyD) && missile.isActive) {
			_tempXD = enemyD.transform.x;
			_tempYD = enemyD.transform.y;
			enemyD.transform.x = rand() % 4096 + WINDOW_WIDTH;
			enemyD.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			killTimeD = SDL_GetTicks();
			playerScore++;
			explodedD = true;
		}
		////////////////////////////////////////////////////////////////////////


		/////////////////// Entradas do teclado //////////////////
		if (Input::KeyHold(SDL_SCANCODE_DOWN) && character.transform.y <= floorPositionY) {

			character.transform.y += playerSpeed * perSecond; // V = S * T
		}

		if (Input::KeyHold(SDL_SCANCODE_UP) && character.transform.y >= topPositionY) {

			character.transform.y -= playerSpeed * perSecond; // V = S * T
		}

		if (Input::KeyHold(SDL_SCANCODE_SPACE)) {
			missile.isActive = true;
			Sound::PlayAudio(shot, 1, 0);
		}

		///////////////////////////////////////////////////////
		break;

	case GAMEOVER:

		////// As instruções abaixo são para salvar a maior pontuação do jogador no arquivo ////////


		int loadHighScore; // uma variável temporária que carrega o valor salvo

		// OBS: Não mexa no arquivo de texto!
		// Caso o altere, esses comandos não irão reconhecer corretamente os dados e irá bugar.
		// Para "desbugar" somente criando um novo arquivo e fazendo um save forçado
		// compile, execute e de gameover uma vez, depois retire o comando forçado e recompile
		// Não mexer no Data.txt para alterar o recorde

		/*FILE* save = fopen("Data.txt", "w");
		fprintf(save, "%d", highScore);
		fclose(save);
		highScore = playerScore;*/

		// Carrega o arquivo com a maior pontuação salva
		FILE* load = fopen("Data.txt", "r");
		highScore = fscanf(load, "%d", &loadHighScore);
		fclose(load);

		//Verifica se a pontuação do jogador é maior que a pontuação salva
		if (playerScore > loadHighScore) {

			FILE* save = fopen("Data.txt", "w");
			highScore = playerScore;
			fprintf(save, "%d", highScore);
			fclose(save);


		}
		else {
			highScore = loadHighScore;
		}

		/////////////////////////////////////////////////////////////////////////////////


		RunOnScene(gameOverBackground);
		Game_GUI_Loop();

		if (Input::KeyHold(SDL_SCANCODE_R)) {

			gameState = GAMEPLAY;

			character.transform.y = 100;

			enemyA.transform.x = rand() % 1100 + WINDOW_WIDTH; // Reseta a posição dos inimigos para fora da tela
			enemyA.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			enemyB.transform.x = rand() % 1100 + WINDOW_WIDTH; // Reseta a posição dos inimigos para fora da tela
			enemyB.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			enemyC.transform.x = rand() % 1100 + WINDOW_WIDTH; // Reseta a posição dos inimigos para fora da tela
			enemyC.transform.y = rand() % (floorPositionY - 50) + topPositionY;
			enemyD.transform.x = rand() % 1100 + WINDOW_WIDTH; // Reseta a posição dos inimigos para fora da tela
			enemyD.transform.y = rand() % (floorPositionY - 50) + topPositionY;

			character.isActive = true;
			enemyA.isActive = true;
			enemySpeed = 1000;
			playerScore = 0;
			gameLevel = 1;
			chancesLeft = 50;
		}
		break;

	}

}

