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
	int velocidad;
	int vidas = 1;
	int puntos = 0;
public:
	Personaje(int vel);
	int x, y;
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
	void reiniciarPosicion();
	bool haLlegadoMeta = false;
	bool haLlegado();
	int obtenerVidas();
	int puntajeInicial();
	int obtenerPuntos();
	int perderVidas();
};

Rana::Rana(int vel) : Personaje(vel) {
	x = 40;
	y = 28;
}

void Rana::dibujar() {
	gotoxy(x, y);
	textcolor(GREEN);
	cout << "R";
}

void Rana::actualizar() {
	if (vidas > 0) {
		if (_kbhit()) {
			borrar();
			char tecla = _getch();
			if (tecla == 'a' && x > xMin + 2) { x--; }
			if (tecla == 'd' && x < xMax - 2) { x++; }
			if (tecla == 'w' && y > yMin + 3) { y--; }
			if (tecla == 's' && y < yMax - 2) { y++; }
		}
		dibujar();
		Sleep(velocidad);
	}
}

int Rana::obtenerVidas(){
	return vidas;
}

int Rana::puntajeInicial(){
	return puntos;
}

int Rana::obtenerPuntos(){
	return puntos += 50;
}

int Rana::perderVidas(){
	return vidas--;
}

void Rana::reiniciarPosicion(){
	x = 40;
	y = 28;
}

bool Rana::haLlegado(){
	return haLlegadoMeta;
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
	if(vidas > 0){
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
	if(vidas > 0){
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
	void iniciar();
	void marcarBordes();
	void ocultarCursor();
	void marcadorVidas();
	void marcadorPuntaje();
	void indicadorTeclas();
	void chequearColisiones();
	void llegarMeta();
	void finDelJuego();
	bool JuegoActivo = true;
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

void Juego::marcadorVidas(){
	textcolor(YELLOW);
	gotoxy(2, 3);
	cout << "VIDAS: " << rana->obtenerVidas();
}

void Juego::marcadorPuntaje(){
	textcolor(YELLOW);
	gotoxy(65, 3);
	cout << "PUNTOS: " << rana->puntajeInicial(); 
}

void Juego::indicadorTeclas(){
	textcolor(YELLOW);
	gotoxy(2, 2);
	cout << "CONTROLES: A - IZQUIERDA, D - DERECHA, W - ARRIBA, S - ABAJO ";
}

void Juego::chequearColisiones(){
	if (rana->x == camion->x && rana->y == camion->y ||(rana->x == automobil->x && rana->y == automobil->y) ){
		rana->perderVidas();
		marcadorVidas();
	}
}

void Juego::llegarMeta(){
	if (rana->x == 4 && rana->y == 4){
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		rana->haLlegadoMeta = true;
	}
}

void Juego::finDelJuego(){
	if (rana->obtenerVidas() <= 0){
		textcolor(WHITE);
		gotoxy(28, 15);
		cout << "P  E  R  D  I  S  T  E";
		gotoxy(28, 16);
		cout << "I  N  T  E  N  T  A  R  ";
		gotoxy(25, 17);
		cout << "N  U  E  V  A  M  E  N  T  E  !";
		JuegoActivo = false;
	}
}

void Juego::ocultarCursor(){
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Juego::iniciar(){
	marcarBordes();
	ocultarCursor();
	marcadorVidas();
	marcadorPuntaje();
	indicadorTeclas();
	while(JuegoActivo){
		chequearColisiones();
		llegarMeta();
		rana->actualizar();
		automobil->actualizar();
		camion->actualizar();
		finDelJuego();
	}
}

int main (int argc, char *argv[]) {
	
	Juego J;
	J.iniciar();
	
	return 0;
}


