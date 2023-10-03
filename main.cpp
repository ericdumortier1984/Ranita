#include<iostream>
#include<conio2.h>
#include<windows.h>
using namespace std;

const int xMax = 79;
const int xMin = 3;
const int yMax = 24;
const int yMin = 2;	
	
class Rana{
protected:
	int x, y;
	void borrar();
private:
	int velocidadRana = 1000;
public:
	Rana();
	void dibujar();
	void moverRana();
};
Rana::Rana(){
	
}
void Rana::moverRana(){
	if (_kbhit()) {
		borrar();
		char tecla = _getch();
		if (tecla == 'a' && x > xMin) { x--; }
		if (tecla == 'd' && x < xMax) { x++; }
		if (tecla == 'w' && y > yMin) { y--; }
		if (tecla == 's' && y < yMax) { y++; }
	}
	Sleep(velocidadRana);
}
void Rana::dibujar(){
	gotoxy(x, y);
	x = 40;
	y = 24;
	textcolor(GREEN);
	cout << "0";
}
void Rana::borrar(){
	gotoxy(x, y);
	cout << " ";
}
class Autito : virtual public Rana{
protected:
	int autito = xMin;
	const int velocidad = 100;
	void dibujarAutito();
	void borrarAutito();
public:
	Autito();
	void moverAutito();
};
Autito::Autito(){
	autito = xMin;
}
void Autito::dibujarAutito(){
	gotoxy(autito, 5);
	textcolor(BLUE);
	cout << "A";
}
void Autito::moverAutito(){
	while(true){
	borrarAutito();
	autito++;
	if (autito > xMax){
		autito = xMin;
	}
	dibujarAutito();
	Sleep(velocidad);
	}
}
void Autito::borrarAutito(){
	gotoxy(autito, y);
	cout << " ";
}
class Camion : virtual public Rana {
protected:
	int camion = xMax;
	const int velocidad = 100;
	void borrarCamion();
public:
	Camion();
	void moverCamion();
	void dibujarCamion();
};
Camion::Camion(){
	camion = xMax;
}

void Camion::moverCamion(){
	while(true){
	borrarCamion();
	camion--;
	if (camion < xMin){
		borrarCamion();
		camion = xMax;
	}
	dibujarCamion();
	Sleep(velocidad);
	}
}
void Camion::dibujarCamion(){
	gotoxy(camion, 10);
	textcolor(RED);
	cout << "C";
}
void Camion::borrarCamion(){
	gotoxy(camion, y);
	cout << " ";
}

class Juego : virtual public Rana, public Camion, public Autito {
public:
	Juego() : Rana(), Camion(){}
	virtual~Juego(){}
	void Jugar();
	void marcarBordes();
};
void Juego::marcarBordes(){
	for (int i = 1; i < 81; i++){
		gotoxy(i, 1);
		cout << "-";
	}
	for (int i = 1; i < 81; i++){
		gotoxy (i, 25);
		cout << "-";
	}
	for (int i = 1; i < 25; i++){
		gotoxy(1, i);
		cout << "-";
	}
	for (int i = 1; i < 25; i++){
		gotoxy(80, i);
		cout << "-";
	}
}

void Juego::Jugar(){
	bool juegoActivo = true;
	marcarBordes();
	Rana *R;
	Camion C;
	Autito A;
	R = &A;
	R->dibujar();
	C.dibujarCamion();
	while (juegoActivo){
	R->moverRana();
	C.moverCamion();
	A.moverAutito();
	}
}
int main (int argc, char *argv[]) {
	Juego J;
	J.Jugar();
	return 0;
}
