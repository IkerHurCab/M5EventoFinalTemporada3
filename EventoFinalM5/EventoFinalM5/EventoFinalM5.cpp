#include "EnemigoFinal.h"
#include "Personaje.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
string name;
string mapa[15][15];
bool win = false;
bool enemigos[15][15];
bool collision[15][15];
bool bosses[15][15];
bool treasures[15][15];
bool exit_array[15][15];
char dir;
bool battle = false;
bool foundExit = false;
bool finalExit = false;
bool treasure = false;
bool boss = false;

bool correct = false;
bool map = false;
bool sword = false;
bool heal = false;
bool brujula = false;
bool llave = false;

int x;
int y;

EnemigoFinal enemigoFinal = EnemigoFinal("MAJORA",200, 20, 0, 0, 30, 50, true);
Personaje jugador = Personaje("", 100, 20, 0, 0, true);
Personaje enemigo[5];
int answer;

void generateEnemies() {
	
	for (int i = 0; i < 5; i++)
	{
		int ran = (rand() % 10);

		string nombres[] = {
			"Goblin",
			"Esqueleto",
			"Zombi",
			"Orco",
			"Limo",
			"Murcielago",
			"Rata",
			"Arana",
			"Bandido",
			"Lobo"
		};


		enemigo[i] = Personaje(nombres[ran], 50, 10, 0, 0, true);
	}

}

void inventory() {

	if (!sword && !map && !heal && !brujula && !llave)
	{
		cout << "No tienes nada en el inventario!\n";
	}

	else {
	
		if (sword)
		{
			cout << "Espada: infliges mas dano con ella.\n\n";
		}
		if (map)
		{
			cout << "Mapa: Revela la disposicion de la mazmorra.\n\n";
		}

		if (brujula) {
			cout << "Brujula: Revela los tesoros de la mazmorra.\n\n";
		}

		if (llave) {
			cout << "Llave: abre la puerta de la guarida del jefe.\n\n";
		}

		if (heal)
		{
			cout << "Cura: Te permite curarte hasta 220 puntos de vida.\n\n";
			cout << "Tienes " << jugador.getVida() << " puntos de vida. Quieres curarte? (Perderas un turno)\n1 - Si\n2 - No\n";
			cin >> answer;

			if (answer == 1)
			{
				jugador.setVida(jugador.getVida() * 1.3);

				if (jugador.getVida() > 220)
				{
					jugador.setVida(220);
				}
			}
		}
	}
}

void endGame() {
	if (finalExit)
	{
		win = true;
		cout << "Has encontado la salida! Has completado el juego!\n";
		system("pause");
		
	}

	else
	{
		cout << "Has encontrado la salida! Aunque esta bloqueada...\n";
		system("pause");
	}
	foundExit = false;
	system("cls");
}

void finalBoss(int x, int y) {

	if (!llave)
	{
		cout << "Has encontrado la guarida del jefe de la mazmorra! Sin embargo, no tienes la llave que abre la puerta.\n";
		system("pause");
	}
	
	else {
		cout << "Has encontrado la guarida del jefe de la mazmorra! Quieres entrar?\n1 - Si\n2 - No";
		cin >> answer;
		
		if (answer == 1) {
			system("cls");
			while (enemigoFinal.getStatus() && jugador.getStatus())
			{
				cout << "\t\t\t" << enemigoFinal.getNombre() << "(" << enemigoFinal.getVida() << " puntos de vida)";
				cout << "\n--------------------------------------------------------------------\n\t\t   1 - ATAQUE\t2 - INVENTARIO\n";
				cin >> answer;

				if (answer == 1)
				{

					enemigoFinal.setVida(enemigoFinal.getVida() - jugador.getAtaque());

					if (enemigoFinal.getVida() <= 0)
					{
						enemigoFinal.setVida(0);
						enemigoFinal.setStatus(false);
					}
					cout << "Has quitado un total de " << jugador.getAtaque() << " puntos a Majora! Le quedan " << enemigoFinal.getVida() << "\n\n";
					system("pause");

				}

				else if (answer == 2) {
					inventory();
					system("pause");
				}

				if (enemigoFinal.getStatus())
				{

					if (enemigoFinal.getVida() < 30 && enemigoFinal.getAtaqueEspecial() == 30)
					{
						jugador.setVida(jugador.getVida() - enemigoFinal.getAtaqueFinal());

						cout << "Majora ha utilizado toda la fuerza que le quedaba y te ha quitado 50 puntos de vida! Te quedan " << jugador.getVida() << "\n\n";

						if (jugador.getVida() <= 0)
						{
							jugador.setVida(0);
							jugador.setStatus(false);
						}

						enemigoFinal.setAtaqueEspecial(10);
					}

					else {
						jugador.setVida(jugador.getVida() - enemigoFinal.getAtaqueEspecial());

						if (jugador.getVida() <= 0)
						{
							jugador.setVida(0);
							jugador.setStatus(false);
						}

						cout << enemigoFinal.getNombre() << " te ha golpeado y te ha quitado " << enemigoFinal.getAtaqueEspecial() << " puntos de vida! Te quedan " << jugador.getVida() << "\n\n";
					}

					system("pause");
				}

				else {
					cout << "Has vencido a " << enemigoFinal.getNombre() << "!\nLa salida de la mazmorra se ha abierto!\n";
					finalExit = true;

					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (exit_array[i][j])
							{
								mapa[i][j] = "\033[32mEXIT\033[0m";
							}
						}
					}
					mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";
					jugador.setPosicionX(x);
					jugador.setPosicionY(y);
					bosses[x][y] = false;
					mapa[jugador.getPosicionX()][jugador.getPosicionY()] = "\033[32mO\033[0m";
					system("pause");
				}

				
				system("cls");

			}
		}

	}

	boss = false;
	system("cls");
}

void treasureFound(int x, int y) {
	treasure = false;
	treasures[x][y] = false;
	
	while (!correct)
	{
		int ran = (rand() % 5) + 1;
		switch (ran) {
		case 1:

			if (!map)
			{
				correct = true;
				map = true;
				cout << "Has encontrado el mapa de la mazmorra! Ahora podras ver la disposicion de esta.\n";
				system("pause");


				for (int i = 0; i < 15; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						if (collision[i][j])
						{
							mapa[i][j] = "-";
						}
					}
				}

			}
			break;
		case 2:

			if (!brujula)
			{
				correct = true;
				brujula = true;
				cout << "Has encontrado una brujula! Se revelaran los secretos de la mazmorra.\n";
				system("pause");


				for (int i = 0; i < 15; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						if (treasures[i][j])
						{
							mapa[i][j] = "\033[33m?\033[0m";
						}

						else if (bosses[i][j])
						{
							mapa[i][j] = "\033[31mX\033[0m";
						}
					}
				}
			}

			break;
		case 3:

			if (!sword)
			{
				correct = true;
				sword = true;
				cout << "Has encontrado una espada! Tu dano aumenta de forma significante!\n";
				system("pause");
				jugador.setAtaque(jugador.getAtaque() * 1.5);
			}
			break;
		case 4:

			if (!heal)
			{
				correct = true;
				heal = true;
				cout << "Has encontrado una cura! Ahora podras curarte hasta los 220 puntos de vida en combate.\n";
				system("pause");
			}
			break;
		case 5:

			if (!llave)
			{
				correct = true;
				llave = true;
				cout << "Has encontrado la llave para la sala del jefe!";
				system("pause");

			}
			
		}

	}

	system("cls");

	correct = false;

	mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";

	jugador.setPosicionX(x);
	jugador.setPosicionY(y);
	mapa[jugador.getPosicionX()][jugador.getPosicionY()] = "\033[32mO\033[0m";

}

void enemyBattle(int x, int y) {

	if (battle = true)
	{
		int id_enemigo;
		enemigos[x][y] = false;
		battle = false;

		for (int i = 0; i < 5; i++)
		{
			if (enemigo[i].getPosicionX() == x && enemigo[i].getPosicionY() == y) {
				id_enemigo = i;
			}
		}

		if (enemigo[id_enemigo].getNombre()._Equal("Rata") || enemigo[id_enemigo].getNombre()._Equal("Arana"))
		{
			cout << "Has encontrado a una " << enemigo[id_enemigo].getNombre() << "!\t";
		}
		else cout << "Has encontrado a un " << enemigo[id_enemigo].getNombre() << "!\t";

		system("pause");
		system("cls");

		while (enemigo[id_enemigo].getStatus() && jugador.getStatus())
		{
			cout << "\t\t\t" << enemigo[id_enemigo].getNombre() << "(" << enemigo[id_enemigo].getVida() << " puntos de vida)";
			cout << "\n--------------------------------------------------------------------\n\t\t   1 - ATAQUE\t2 - INVENTARIO\n";
			cin >> answer;

			if (answer == 1)
			{
				enemigo[id_enemigo].setVida(enemigo[id_enemigo].getVida() - jugador.getAtaque());

				if (enemigo[id_enemigo].getVida() <= 0)
				{
					enemigo[id_enemigo].setVida(0);
					enemigo[id_enemigo].setStatus(false);
				}
				cout << "Has quitado un total de " << jugador.getAtaque() << " puntos a tu enemigo! Le quedan " << enemigo[id_enemigo].getVida() << "\n\n";
				system("pause");	
				
			}

			else if (answer == 2) {
				inventory();
				system("pause");
			}

			if (enemigo[id_enemigo].getStatus())
			{
				jugador.setVida(jugador.getVida() - enemigo[id_enemigo].getAtaque());

				if (jugador.getVida() <= 0)
				{
					jugador.setVida(0);
					jugador.setStatus(false);
				}

				cout << enemigo[id_enemigo].getNombre() << " te ha golpeado y te ha quitado " << enemigo[id_enemigo].getAtaque() << " puntos de vida! Te quedan " << jugador.getVida() << "\n\n";
				system("pause");
			}

			else {
				cout << "Has vencido a " << enemigo[id_enemigo].getNombre() << "!\n";

				mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";

				jugador.setPosicionX(x);
				jugador.setPosicionY(y);

				mapa[jugador.getPosicionX()][jugador.getPosicionY()] = "\033[32mO\033[0m";
				system("pause");
			}

			system("cls");

		}
	}


}

void generateTerrain () {

	int random = 0;
	int playerCount = 0;
	int bossCount = 0;
	int enemyCount = 0;
	int exitCount = 0;
	int treasureCount = 0;

	for (int i = 0; i < 15; i++) {

		for (int j = 0; j < 15; j++)
		{
			collision[i][j] = false;
			enemigos[i][j] = false;
			exit_array[i][j] = false;
			treasures[i][j] = false;
			bosses[i][j] = false;

		}
		
	}

	for (int i = 0; i < 15; i++)
	{
		
		for (int j = 0; j < 15; j++)
		{
			
			random = (rand() % 7) + 1;

			if (i == 0 || j == 0 || i == 14 || j == 14)
			{
				mapa[i][j] = "-";
				collision[i][j] = true;

			}

			else {
				switch (random)
				{

				case 1:
					mapa[i][j] = " ";
					collision[i][j] = true;
					break;
				case 2:
					mapa[i][j] = " ";
					break;
				case 3:

					if (playerCount == 0)
					{
						mapa[i][j] = "\033[32mO\033[0m";
						jugador.setPosicionX(i);
						jugador.setPosicionY(j);
						playerCount++;
					}

					else {
						mapa[i][j] = " ";
					}

					break;
				case 4:
					if (enemyCount < 5)
					{
						mapa[i][j] = " ";
						enemigos[i][j] = true;
						enemigo[enemyCount].setPosicionX(i);
						enemigo[enemyCount].setPosicionY(j);
						enemyCount++;
					}

					else {
						mapa[i][j] = " ";
					}

					break;
				case 5:
					if (bossCount == 0)
					{
						mapa[i][j] = " ";
						bosses[i][j] = true;
						bossCount++;
					}

					else {
						mapa[i][j] = " ";
					}

					break;
				case 6:
					if (exitCount == 0)
					{
						mapa[i][j] = " ";
						exit_array[i][j] = true;
						exitCount++;
					}

					else {
						mapa[i][j] = " ";
					}
					break;

				case 7:
					if (treasureCount < 5)
					{
						mapa[i][j] = " ";
						treasures[i][j] = true;
						treasureCount++;
					}
					break;

				}

			}

		}

	}


}

void moveCharacter(char dir) {

	if (dir == 'd')
	{
		if (!collision[jugador.getPosicionX()][jugador.getPosicionY() + 1] && !enemigos[jugador.getPosicionX()][jugador.getPosicionY() + 1] && !bosses[jugador.getPosicionX()][jugador.getPosicionY() + 1] && !exit_array[jugador.getPosicionX()][jugador.getPosicionY() + 1] && !treasures[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";
			mapa[jugador.getPosicionX()][jugador.getPosicionY() + 1] = "\033[32mO\033[0m";
			jugador.setPosicionY(jugador.getPosicionY() + 1);
		}

		else if (enemigos[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{			
			battle = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() + 1;
			mapa[x][y] = "\033[31m!\033[0m";
		}

		else if (treasures[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{
			treasure = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() + 1;
			mapa[x][y] = "\033[33m?\033[0m";
		}

		else if (bosses[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{
			boss = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() + 1;
			mapa[x][y] = "\033[31mX\033[0m";
		}

		else if (exit_array[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{
			foundExit = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() + 1;

			if (finalExit)
			{
				mapa[x][y] = "\033[32mEXIT\033[0m";
			}

			else mapa[x][y] = "\033[31mEXIT\033[0m";
			
		}

		if (collision[jugador.getPosicionX()][jugador.getPosicionY() + 1])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY() + 1] = "-";
		}

		

	}
	else if (dir == 'a')
	{
		if (!collision[jugador.getPosicionX()][jugador.getPosicionY() - 1] && !enemigos[jugador.getPosicionX()][jugador.getPosicionY() - 1] && !bosses[jugador.getPosicionX()][jugador.getPosicionY() - 1] && !exit_array[jugador.getPosicionX()][jugador.getPosicionY() - 1] && !treasures[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";
			mapa[jugador.getPosicionX()][jugador.getPosicionY() - 1] = "\033[32mO\033[0m";
			jugador.setPosicionY(jugador.getPosicionY() - 1);
		}

		else if (enemigos[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			battle = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() - 1;
			mapa[x][y] = "\033[31m!\033[0m";
		}

		else if (treasures[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			treasure = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() - 1;
			mapa[x][y] = "\033[33m?\033[0m";
		}

		else if (bosses[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			boss = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() - 1;
			mapa[x][y] = "\033[31mX\033[0m";
		}

		else if (exit_array[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			foundExit = true;
			x = jugador.getPosicionX();
			y = jugador.getPosicionY() - 1;

			if (finalExit)
			{
				mapa[x][y] = "\033[32mEXIT\033[0m";
			}

			else mapa[x][y] = "\033[31mEXIT\033[0m";

		}

		if (collision[jugador.getPosicionX()][jugador.getPosicionY() - 1])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY() - 1] = "-";
		}
	}

	else if (dir == 'w')
	{
		if (!collision[jugador.getPosicionX() - 1][jugador.getPosicionY()] && !enemigos[jugador.getPosicionX() - 1][jugador.getPosicionY()] && !bosses[jugador.getPosicionX() - 1][jugador.getPosicionY()] && !exit_array[jugador.getPosicionX() - 1][jugador.getPosicionY()] && !treasures[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";
			mapa[jugador.getPosicionX() - 1][jugador.getPosicionY()] = "\033[32mO\033[0m";
			jugador.setPosicionX(jugador.getPosicionX() - 1);
		}

		else if (enemigos[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			battle = true;
			x = jugador.getPosicionX() - 1;
			y = jugador.getPosicionY();		
			mapa[x][y] = "\033[31m!\033[0m";
		}

		else if (treasures[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			treasure = true;
			x = jugador.getPosicionX() - 1;
			y = jugador.getPosicionY();
			mapa[x][y] = "\033[33m?\033[0m";
		}

		else if (bosses[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			boss = true;
			x = jugador.getPosicionX() - 1;
			y = jugador.getPosicionY();
			mapa[x][y] = "\033[31mX\033[0m";
		}

		else if (exit_array[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			foundExit = true;
			x = jugador.getPosicionX() - 1;
			y = jugador.getPosicionY();

			if (finalExit)
			{
				mapa[x][y] = "\033[32mEXIT\033[0m";
			}

			else mapa[x][y] = "\033[31mEXIT\033[0m";

		}
		if (collision[jugador.getPosicionX() - 1][jugador.getPosicionY()])
		{
			mapa[jugador.getPosicionX() - 1][jugador.getPosicionY()] = "-";
		}
	}

	else if (dir == 's')
	{
		if (!collision[jugador.getPosicionX() + 1][jugador.getPosicionY()] && !enemigos[jugador.getPosicionX() + 1][jugador.getPosicionY()] && !bosses[jugador.getPosicionX() + 1][jugador.getPosicionY()] && !exit_array[jugador.getPosicionX() + 1][jugador.getPosicionY()] && !treasures[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			mapa[jugador.getPosicionX()][jugador.getPosicionY()] = " ";
			mapa[jugador.getPosicionX() + 1][jugador.getPosicionY()] = "\033[32mO\033[0m";
			jugador.setPosicionX(jugador.getPosicionX() + 1);
		}

		else if (enemigos[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			battle = true;
			x = jugador.getPosicionX() + 1;
			y = jugador.getPosicionY();
			mapa[x][y] = "\033[31m!\033[0m";

		}

		else if (treasures[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			treasure = true;
			x = jugador.getPosicionX() + 1;
			y = jugador.getPosicionY();
			mapa[x][y] = "\033[33m?\033[0m";
		}
		else if (bosses[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			boss = true;
			x = jugador.getPosicionX() + 1;
			y = jugador.getPosicionY();
			mapa[x][y] = "\033[31mX\033[0m";
		}

		else if (exit_array[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			foundExit = true;
			x = jugador.getPosicionX() + 1;
			y = jugador.getPosicionY();

			if (finalExit)
			{
				mapa[x][y] = "\033[32mEXIT\033[0m";
			}

			else mapa[x][y] = "\033[31mEXIT\033[0m";

		}



		if (collision[jugador.getPosicionX() + 1][jugador.getPosicionY()])
		{
			mapa[jugador.getPosicionX() + 1][jugador.getPosicionY()] = "-";
		}
	}

}

void updateTerrain() {

	while (jugador.getStatus() && !win)
	{
		
		if (_kbhit()) {
			char dir = tolower(_getch());
			moveCharacter(dir);
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				cout << mapa[i][j];
				cout << "\t";

			}
			cout << "\n\n";
		}

		if (battle)	enemyBattle(x, y);
		else if (treasure) treasureFound(x, y);
		else if (boss) finalBoss(x, y);
		else if (foundExit) endGame();

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		
	}

	if (!jugador.getStatus())
	{
		cout << "\nHas muerto.\n";
	}
	
}

int main()
{
	cout << "Introduce tu nombre: ";
	cin >> name;
	system("cls");
	jugador.setNombre(name);
	srand(time(0));
	generateEnemies();
	generateTerrain();
	updateTerrain();
}

