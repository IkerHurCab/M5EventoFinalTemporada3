#include "Personaje.h"
#include <iostream>
using namespace std;

//getters

string Personaje::getNombre() {
	return nombre;
}

int Personaje::getVida() {
	return vida;
}

int Personaje::getAtaque() {
	return ataque;
}

int Personaje::getPosicionX() {
	return posicionX;
}

int Personaje::getPosicionY() {
	return posicionY;
}

bool Personaje::getStatus() {
	return status;
}

//setters 

void Personaje::setNombre(string pNombre) {
	nombre = pNombre;
}

void Personaje::setVida(int pVida) {
	vida = pVida;
}

void Personaje::setAtaque(int pAtaque) {
	ataque = pAtaque;
}

void Personaje::setPosicionX(int pPosicionX) {
	posicionX = pPosicionX;
}

void Personaje::setPosicionY(int pPosicionY) {
	posicionY = pPosicionY;
}

void Personaje::setStatus(bool pStatus) {
	status = pStatus;
}

//constructores

Personaje::Personaje() {

}

Personaje::Personaje(std::string pNombre, int pVida, int pAtaque, int pPosicionX, int pPosicionY, bool pStatus) {
	nombre = pNombre;
	vida = pVida;
	ataque = pAtaque;
	posicionX = pPosicionX;
	posicionY = pPosicionY;
	status = pStatus;
}


