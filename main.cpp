#include<iostream>
#include<conio2.h>
#include<windows.h>
using namespace std;

class Rana{
protected:
	int x, y;
	
};

class Juego : public Rana {
public:
	Juego();
	void Jugar();
	void posicion(){
		gotoxy(x, y);
		cout << "0";
	} 
};
Juego::Juego(){
	x = 0;
	y = 0;
}
void Juego::Jugar(){
	bool juegoActivo = true;
	int velocidad = 100; // Velocidad del juego en milisegundos
	int direccion = 0; // Dirección de la rana (0: arriba, 1: derecha, 2: abajo, 3: izquierda)
	// Inicializar posición de la rana
	x = 10;
	y = 10;
	while (juegoActivo){
		if (_kbhit()) {
			char tecla = _getch();
			if (tecla == 'a') { x--; }
			if (tecla == 'd') { x++; }
			if (tecla == 'w') { y--; }
			if (tecla == 's') { y++; }
		}
		posicion();
		// Verificar condición de finalización del juego
		if(x < 0 || x >= 80 || y < 0 || y >= 25){ // Si la rana sale de los límites de la pantalla
			juegoActivo = false; // Finalizar el juego
		}
		Sleep(velocidad);
	}
	
}

int main (int argc, char *argv[]) {
	Juego J;
	J.Jugar();
	return 0;
}

