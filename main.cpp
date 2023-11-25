#include<iostream>
#include<conio2.h>
#include<windows.h>
using namespace std;

const int xMax = 80;
const int xMin = 1;
const int yMax = 30;
const int yMin = 1;	

class Personaje{
protected:
	int x, y;
	int velocidad;
	int vidas = 3;
public:
	Personaje(int vel);
	void dibujar();
	void borrar();
};

Personaje::Personaje(int vel){
	velocidad = vel;
}

void Personaje::dibujar(){}

void Personaje::borrar(){
	gotoxy(x, y);
	cout << " ";
}

class Rana : public Personaje {
public:
	Rana(int vel);
	void dibujar();
	void actualizar();
};

Rana::Rana(int vel) : Personaje(vel) {
	x = 40;
	y = 28;
}

void Rana::dibujar() {
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << "R";
}

void Rana::actualizar() {
	while (vidas > 0) {
		if (_kbhit()) {
			borrar();
			char tecla = _getch();
			if (tecla == 'a' && x > xMin + 2) { x--; }
			if (tecla == 'd' && x < xMax - 2) { x++; }
			if (tecla == 'w' && y > yMin + 2) { y--; }
			if (tecla == 's' && y < yMax - 2) { y++; }
		}
		dibujar();
		Sleep(velocidad);
	}
}

class Automobil : public Personaje {
public:
	Automobil(int, int, int);
	void dibujar();
	void actualizar();
};

Automobil::Automobil(int _x, int _y, int vel) : Personaje (vel) {
	x = _x;
	y = _y;
}

void Automobil::dibujar() {
	gotoxy(x, y);
	textcolor(BLUE);
	cout << "A";
}
void Automobil::actualizar() {
	while(vidas > 0){
		borrar();
		x++;
		if (x > xMax - 4){
			borrar();
			x = xMin + 2;
		}
		dibujar();
		Sleep(velocidad);
	}
}

class Camion : public Personaje {
public:
	Camion(int, int, int);
	void dibujar();
	void actualizar();
};

Camion::Camion(int _x, int _y, int vel) : Personaje (vel) {
	x = _x;
	y = _y;
}

void Camion::dibujar() {
	gotoxy(x, y);
	textcolor(RED);
	cout << "C";
}

void Camion::actualizar() {
	while(vidas > 0){
		borrar();
		x--;
		if (x < xMin + 2){
			borrar();
			x = xMax - 4;
		}
		dibujar();
		Sleep(velocidad);
	}
}

class Juego {
	
	Rana* rana = new Rana(100);
	Automobil* automobil = new Automobil(2, 15 ,50);
	Camion* camion = new Camion(78, 10, 80);
	
public:
	Juego(){}
	void Iniciar();
	void marcarBordes();
	void ocultarCursor();
};

void Juego::marcarBordes(){
	for (int i = 1; i < 80; i++){
		gotoxy(i, 1);
		cout << "*";
	}
	for (int i = 1; i < 80; i++){
		gotoxy (i, 30);
		cout << "*";
	}
	for (int i = 1; i < 30; i++){
		gotoxy(1, i);
		cout << "*";
	}
	for (int i = 1; i < 30; i++){
		gotoxy(80, i);
		cout << "*";
	}
}

void Juego::ocultarCursor(){
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Juego::Iniciar(){
	marcarBordes();
	ocultarCursor();
	bool JuegoActivo = true;
	while(JuegoActivo){
		rana->actualizar();
		automobil->actualizar();
		camion->actualizar();
	}
}

int main (int argc, char *argv[]) {
	
	Juego J;
	J.Iniciar();
	
	return 0;
}


