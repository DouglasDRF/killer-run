/*
Douglas R. Ferreira

�ltima Atualiza��o
Rio de Janeiro, 21/04/2016
*/

#pragma once

#include "Core.h"
#include <stdio.h>



// Classe respons�vel por implementar m�todos de simula��o de f�sica, como colis�es, gravidade, for�a, impulso.
class Physics
{
public:
	

	static bool GetCollision(GameObject origin, GameObject target);
	
	// Aplique a gravidade diretamente no eixo Y incrementando um valor positivo
	static float ApplyGravity(GameObject &object, float gravityForce, float floorReference);
	// Aplique o pulo diretamente no exito Y incremendando um valor negativo
	static float ApplyJump(GameObject &object, float impulseForce, float jumpAcceleration, int duration, bool &trigger);


			
};



static enum ObjectState {
	STOPPED, ACCELERATING, ONGRAVITY
};

