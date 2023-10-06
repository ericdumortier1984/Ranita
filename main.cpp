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
	virtual void mover() = 0;
	virtual void borrar() = 0;
	virtual void dibujar() = 0;
public:
	Personaje();
};
Personaje::Personaje(){}

class Rana : public Personaje{
private:
	int vidas;
	int velocidad = 1000;
public: 
	Rana();
	void mover() override;
	void dibujar() override;
	void borrar() override;
};
Rana::Rana(){
	vidas = 3;
}
void Rana::mover(){
	if (_kbhit()) {
		borrar();
		char tecla = _getch();
		if (tecla == 'a' && x > xMin) { x--; }
		if (tecla == 'd' && x < xMax) { x++; }
		if (tecla == 'w' && y > yMin) { y--; }
		if (tecla == 's' && y < yMax) { y++; }
	}
	Sleep(velocidad);
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
class Autito :  public Personaje{
protected:
	int autito = xMin;
	const int velocidad = 100;
public:
	Autito();
	void mover() override;
	void dibujar() override;
	void borrar() override;
};
Autito::Autito(){
	autito = xMin;
}
void Autito::dibujar(){
	gotoxy(autito, 5);
	textcolor(BLUE);
	cout << "A";
}
void Autito::mover(){
	while(true){
	borrar();
	autito++;
	if (autito > xMax){
		autito = xMin;
	}
	dibujar();
	Sleep(velocidad);
	}
}
void Autito::borrar(){
	gotoxy(autito, y);
	cout << " ";
}
class Camion : public Personaje {
protected:
	int camion = xMax;
	const int velocidad = 100;
public:
	Camion();
	void mover() override;
	void dibujar() override;
	void borrar() override;
};
Camion::Camion(){
	camion = xMax;
}

void Camion::mover(){
	while(true){
	borrar();
	camion--;
	if (camion < xMin){
		borrar();
		camion = xMax;
	}
	dibujar();
	Sleep(velocidad);
	}
}
void Camion::dibujar(){
	gotoxy(camion, 10);
	textcolor(RED);
	cout << "C";
}
void Camion::borrar(){
	gotoxy(camion, y);
	cout << " ";
}

class Juego : public Rana, public Camion, public Autito {
public:
	Juego(){}
	void Jugar();
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

void Juego::Jugar(){
	bool juegoActivo = true;
	marcarBordes();
	Rana R;
	Camion C;
	Autito A;
	while (juegoActivo){
	R.dibujar();
	C.dibujar();
	R.mover();
	C.mover();
	A.mover();
	}
}
int main (int argc, char *argv[]) {
	Juego J;
	J.Jugar();
	return 0;
}
