/*
Douglas R. Ferreira

Última Atualização
Rio de Janeiro, 21/04/2016
*/

#include "Physics.h"



//Aplica gravidade sobre qualquer objeto na cena. Precisa ter um chão de referencia.
float Physics::ApplyGravity(GameObject &object, float gravityForce, float floorReference) {
	
	float gravity = 0;
	float startSpeed = 0;
	Uint32 &startTimeRef = object.airTiming;
		
	
	if ((!object.accelerating && object.onAir && object.onTop)) {
	
		startTimeRef = SDL_GetTicks();
		object.accelerating = true;
		object.onTop = false;

	}

	if ((object.transform.y) >= floorReference) {

		object.accelerating = false;
		object.onAir = false;
		startTimeRef = 0;
		gravity = 0;
		
		
		if (object.transform.y > floorReference)
			object.transform.y = floorReference;
						

	} else if (object.onAir) {
		
		// Vf = Vo + (A * T) 
		std::cout << "Gravity: " << (gravityForce * (globalTime - startTimeRef) / 100) << "\n";
		gravity = startSpeed + (gravityForce * ((globalTime - startTimeRef) / 100));
	}
		
	return gravity;
		
}

float Physics::ApplyJump(GameObject &object, float impulseForce, float jumpAcceleration, int duration, bool &trigger){
	
	float &velocity = object.speed;
	Uint32 &startTimeRef = object.airTiming;
	
	if (trigger) {

		if (!object.onAir) {
			
			startTimeRef = 0;
			velocity += 0;
			startTimeRef = SDL_GetTicks();
			object.onAir = true;
			
		}

		if ( ((globalTime - startTimeRef) / 100) > duration ) {
			object.onTop = true;
			trigger = false;
			

		} else {
			// Vf = Vo + (A * T) 
			velocity = impulseForce + (jumpAcceleration * ((globalTime - startTimeRef) / 100));
			std::cout << "Impulse: " << velocity << " ";
		}

	} else {
		// Desaceleração do pulo
		if (velocity > 0)
			velocity -= 0.16; // Delta Time = FPS / 1000ms = 16 ms
		else if (velocity < 0)
			velocity = 0;
	}
			
	return velocity;
	
}


bool Physics::GetCollision(GameObject origin, GameObject target) {
	// Declarando e calculando as bordas do primeiro retangulo a ser colidido
	int left1 = origin.transform.x;
	int right1 = origin.transform.x + origin.transform.w;
	int top1 = origin.transform.y;
	int bottom1 = origin.transform.y + origin.transform.h;

	// Declarando e calculando as bordas do segundo retangulo a ser colidido
	int left2 = target.transform.x;
	int right2 = target.transform.x + target.transform.w;
	int top2 = target.transform.y;
	int bottom2 = target.transform.y + target.transform.h;

	// Verificando Colisão
	// Todas as verificações abaixo estão interligadas e devem ser verdadeiras indicando que não há colisão
	// Retornando false
	if (left1 > right2)
		return false; 

	if (right1 < left2)
		return false;

	if (top1 > bottom2)
		return false; 

	if (bottom1 < top2)
		return false; 
	
	// Caso sejam falsas o método irá retornar verdadeiro
	return true;
}



