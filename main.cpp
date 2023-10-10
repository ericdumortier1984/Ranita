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
public:
	Personaje();
	void borrar();
};
Personaje::Personaje(){
	x = 0;
	y = 0;
}
void Personaje::borrar(){
	gotoxy(x, y);
	cout << " ";
}

class Rana : public Personaje{
private:
	int velocidad = 100;
protected:
	int vidas = 3;
public: 
	Rana();
	void dibujarVida();
	void perderVida();
	void mover();
	void dibujar();
};
Rana::Rana(){
	gotoxy(x, y);
	x = 40;
	y = 28;
}
void Rana::dibujarVida(){
	gotoxy(xMax - 10, yMin);
	textcolor(WHITE);
	cout << "Vidas " << vidas;
}
void Rana::perderVida(){
	vidas--;
}
void Rana::mover(){
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
void Rana::dibujar(){
	gotoxy(x, y);
	textcolor(GREEN);
	cout << "0";
}

class Automobil : public Personaje{
protected:
	int automobil = xMin;
	int velocidad = 50;
public:
	Automobil();
	void mover();
	void dibujar();
};
Automobil::Automobil(){
	gotoxy(automobil, 15);
	automobil = xMin;
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
class Camion : public Personaje {
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

class Juego : public Rana, public Camion, public Automobil {
public:
	Juego(){}
	void Iniciar();
	void marcarBordes();
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

void Juego::Iniciar(){
	marcarBordes();
	bool JuegoActivo = true;
	while(JuegoActivo){
		Rana Ranita;
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
