#pragma once
#include "Personaje.h"
#include <iostream>

class EnemigoFinal: public Personaje
{
private:
	int ataqueFinal;
	int ataqueEspecial;

public:
	
	//getters
	int getAtaqueFinal();
	int getAtaqueEspecial();

	//setters
	void setAtaqueFinal(int pAtaqueFinal);
	void setAtaqueEspecial(int pAtaqueEspecial);

	//constructores
	EnemigoFinal();
	EnemigoFinal(std::string pNombre, int pVida, int pAtaque, int pPosicionX, int pPosicionY, int pAtaqueEspecial, int pAtaqueFinal, bool pStatus);
};

