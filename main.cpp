#include<iostream>
#include<conio2.h>
#include<windows.h>
using namespace std;

const int xMax = 80;
const int xMin = 1;
const int yMax = 30;
const int yMin = 1;	
	
class Personaje{
private:
	int velocidad = 100;
	int x, y;
	int vidas = 3;
public:
	Personaje();
	void dibujarVida();
	void perderVida();
	void mover();
	void dibujar();
	void borrar();
};
Personaje::Personaje(){
	gotoxy(x, y);
	x = 40;
	y = 28;
}

void Personaje::dibujarVida(){
	gotoxy(xMax - 10, yMin);
	textcolor(WHITE);
	cout << "Vidas " << vidas;
}

void Personaje::perderVida(){
	vidas--;
}

void Personaje::mover(){
	while(vidas > 0){
		if (_kbhit()) {
			borrar();
			char tecla = _getch();
			if (tecla == 'a' && x > xMin + 2) { x--; }
			if (tecla == 'd' && x < xMax - 2) { x++; }
			if (tecla == 'w' && y > yMin + 2) { y--; }
			if (tecla == 's' && y < yMax - 2) { y++; }
			dibujar();
		}
		Sleep(velocidad);
	}
}

void Personaje::borrar(){
	gotoxy(x, y);
	cout << " ";
}

void Personaje::dibujar(){
	gotoxy(x, y);
	textcolor(GREEN);
	cout << "0";
}

class Obstaculos {
protected:
	int x, y;
	int velocidad;
public:
	Obstaculos(){
		int velocidad;
	}
	void dibujar();
	void borrar();
};


class Automobil : public Obstaculos {
protected:
	int automobil = xMin;
public:
	Automobil();
	bool update();
};
Automobil::Automobil(){
	gotoxy(automobil, 15);
	automobil = xMin;
}

void Automobil::borrar(){
	gotoxy(x, y);
	cout << " ";
}

void Automobil::dibujar(){
	gotoxy(automobil + 2, 15);
	textcolor(BLUE);
	cout << "A";
}
void Automobil::mover(){
	while(automobil){
	borrar();
	automobil++;
	if (automobil > xMax){
		automobil = xMin;
	}
	dibujar();
	Sleep(velocidad);
	}
}
class Camion : public Automobil {
protected:
	int camion = xMax;
	int velocidad = 50;
public:
	Camion();
	void mover();
	void dibujar();
};
Camion::Camion(){
	gotoxy(camion, 10);
	camion = xMax;
}
void Camion::dibujar(){
	gotoxy(camion - 2, 10);
	textcolor(RED);
	cout << "C";
}
void Camion::mover(){
	while(camion){
	borrar();
	camion--;
	if (camion < xMin + 3){
		borrar();
		camion = xMax;
	}
	dibujar();
	Sleep(velocidad);
	}
}

class Juego : public Personaje, public Camion, public Automobil {
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
		Personaje Ranita;
		Camion Camioncito;
		Automobil Autito;
		
		Ranita.dibujar();
		Ranita.mover();
		Ranita.dibujarVida();
		
		Camioncito.dibujar();
		Camioncito.mover();
		
		Autito.dibujar();
		Autito.mover();
	}
}
int main (int argc, char *argv[]) {
	
	Juego J;
	J.Iniciar();
	
	return 0;
}
