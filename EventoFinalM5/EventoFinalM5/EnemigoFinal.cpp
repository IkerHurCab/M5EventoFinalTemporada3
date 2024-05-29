#include "EnemigoFinal.h"
#include <iostream>
using namespace std;

//constructores
EnemigoFinal::EnemigoFinal() : Personaje() {

}

EnemigoFinal::EnemigoFinal(string pNombre,
						   int pVida,
						   int pAtaque,
						   int pPosicionX, 
						   int pPosicionY,
						   int pAtaqueEspecial,
	                       int pAtaqueFinal,
						   bool pStatus) : Personaje(pNombre,
													     pVida, 
														 pAtaque, 
														 pPosicionX,
													     pPosicionY,
														 pStatus)
																   	{
																		ataqueEspecial = pAtaqueEspecial;
																		ataqueFinal = pAtaqueFinal;															
																     }

//getters
int EnemigoFinal::getAtaqueEspecial() {
	return ataqueEspecial;
}

int EnemigoFinal::getAtaqueFinal() {
	return ataqueFinal;
}

//setters

void EnemigoFinal::setAtaqueEspecial(int pAtaqueEspecial) {
	ataqueEspecial = pAtaqueEspecial;
}

void EnemigoFinal::setAtaqueFinal(int pAtaqueFinal) {
	ataqueEspecial = pAtaqueFinal;
}