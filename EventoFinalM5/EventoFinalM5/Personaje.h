#pragma once
#include <iostream>

class Personaje
{
private:

	std::string nombre;
	int vida;
	int ataque;
	int posicionX;
	int posicionY;
	bool status;
	
public:

	//getters

	std::string getNombre();
	int getVida();
	int getAtaque();
	int getPosicionX();
	int getPosicionY();
	bool getStatus();

	//setters

	void setNombre(std::string pNombre);
	void setVida(int pVida);
	void setAtaque(int pAtaque);
	void setPosicionX(int pPosicionX);
	void setPosicionY(int pPosicionY);
	void setStatus(bool pStatus);

	//constructores
	
	Personaje();
	Personaje(std::string pNombre, int pVida, int pAtaque, int pPosicionX, int pPosicionY, bool pStatus);

};

