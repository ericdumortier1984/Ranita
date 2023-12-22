#include<iostream>
#include<conio2.h>
#include<windows.h>
#include<ctime>
using namespace std;

const int xMax = 80;
const int xMin = 1;
const int yMax = 30;
const int yMin = 1;	

class Personaje{
protected:
	clock_t tempo;
	clock_t paso; 
	int velocidad;
	int vidas = 3;
	int puntos = 0;
	void dibujar();
	void borrar();
public:
	Personaje(int vel);
	int x, y;
};

Personaje::Personaje(int vel){
	velocidad = vel;
	paso = CLOCKS_PER_SEC/velocidad; 
	tempo = clock();
}

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
	if (vidas>0 && tempo+paso<clock()) {
		if (_kbhit()) {
			borrar();
			char tecla = _getch();
			if (tecla == 'a' && x > xMin + 2) { x--; }
			if (tecla == 'd' && x < xMax - 2) { x++; }
			if (tecla == 'w' && y > yMin + 3) { y--; }
			if (tecla == 's' && y < yMax - 2) { y++; }
			tempo = clock();
		}
		dibujar();
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
	if(vidas > 0 && tempo+paso<clock() ){
		borrar();
		x++;
		if (x > xMax - 4){
			borrar();
			x = xMin + 2;
			tempo = clock();
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
	if(vidas > 0 && tempo+paso<clock()){
		borrar();
		x--;
		if (x < xMin + 2){
			borrar();
			x = xMax - 4;
			tempo = clock();
		}
		dibujar();
		Sleep(velocidad);
	}
}

class Camioneta : public Personaje {
public:
	Camioneta(int, int, int);
	void dibujar();
	void actualizar();
};

Camioneta::Camioneta(int _x, int _y, int vel) : Personaje (vel) {
	x = _x;
	y = _y;
}

void Camioneta::dibujar() {
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << "O";
}
void Camioneta::actualizar() {
	if(vidas > 0 && tempo+paso<clock() ){
		borrar();
		x++;
		if (x > xMax - 4){
			borrar();
			x = xMin + 2;
			tempo = clock();
		}
		dibujar();
		Sleep(velocidad);
	}
}

class Juego {
private:
	bool metaOcupada[3]; // Array para controlar las posiciones de meta ocupadas
	Rana* rana = new Rana(10);
	Automobil* automobil = new Automobil(2, 15 , 1);
	Automobil* automobilDos = new Automobil(2, 25, 8);
	Automobil* automobilTres = new Automobil(2, 17, 12);
	Automobil* automobilCuatro = new Automobil(2, 8, 23);
	Camion* camion = new Camion(78, 10, 9);
	Camion* camionDos = new Camion(78, 5, 13);
	Camion* camionTres = new Camion(78, 20, 25);
	Camion* camionCuatro = new Camion(78, 24, 7);
	Camioneta* camioneta = new Camioneta(2, 19, 3);
	Camioneta* camionetaDos = new Camioneta(2, 21, 11);
	Camioneta* camionetaTres = new Camioneta(2, 7, 19);
	Camioneta* camionetaCuatro = new Camioneta(2, 26, 16);
	
public:
	Juego();
	void iniciar();
	void marcarBordes();
	void ocultarCursor();
	void marcadorVidas();
	void marcadorPuntaje();
	void indicadorTeclas();
	void chequearColisiones();
	void llegarMeta();
	void finDelJuego();
	void ganaste();
	bool JuegoActivo = true;
};

Juego::Juego(){
	for (int i = 0; i < 2; i++) {
		metaOcupada[i] = false; // Inicializar todas las posiciones de meta como no ocupadas
	}
}

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
	for (int i = 1; i < 4; i++){
		gotoxy(i, 4);
		cout << "*";
	}
	for (int i = 5; i < 40; i++){
		gotoxy(i, 4);
		cout << "*";
	}
	for (int i = 41; i < 76; i++){
		gotoxy(i, 4);
		cout << "*";
	}
	for (int i = 77; i < 80; i++){
		gotoxy(i, 4);
		cout << "*";
	}
}

void Juego::marcadorVidas(){
	textcolor(YELLOW);
	gotoxy(20, 3);
	cout << "VIDAS: " << rana->obtenerVidas();
}

void Juego::marcadorPuntaje(){
	textcolor(YELLOW);
	gotoxy(50, 3);
	cout << "PUNTOS: " << rana->puntajeInicial(); 
}

void Juego::indicadorTeclas(){
	textcolor(YELLOW);
	gotoxy(10, 2);
	cout << "CONTROLES: A - IZQUIERDA, D - DERECHA, W - ARRIBA, S - ABAJO ";
}

void Juego::chequearColisiones(){
	if (rana->x == camion->x && rana->y == camion->y ||(rana->x == automobil->x && rana->y == automobil->y) || (rana->x == camioneta->x && rana->y == camioneta->y)){
		rana->perderVidas();
		marcadorVidas();
	}
}

void Juego::llegarMeta(){
	if ((rana->x == 4 && rana->y == 4) && !metaOcupada[0]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[0] = true; // Marcar la primera posición de meta como ocupada
	}else if ((rana->x == 4 && rana->y == 4) && metaOcupada[0]) {
		rana->reiniciarPosicion(); // Reiniciar la posición si la casilla de meta está ocupada
    }
	if ((rana->x == 40 && rana->y == 4) && !metaOcupada[1]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[1] = true; // Marcar la primera posición de meta como ocupada
	}else if ((rana->x == 40 && rana->y == 4) && metaOcupada[1]) {
		rana->reiniciarPosicion(); // Reiniciar la posición si la casilla de meta está ocupada
	}
	if ((rana->x == 76 && rana->y == 4) && !metaOcupada[2]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[2] = true; // Marcar la primera posición de meta como ocupada
	}else if ((rana->x == 76 && rana->y == 4) && metaOcupada[2]) {
		rana->reiniciarPosicion(); // Reiniciar la posición si la casilla de meta está ocupada
	}
}

void Juego::finDelJuego(){
	if (rana->obtenerVidas() <= 0){
		textcolor(WHITE);
		gotoxy(28, 15);
		cout << "P  E  R  D  I  S  T  E ";
		gotoxy(28, 16);
		cout << "I  N  T  E  N  T  A  R  ";
		gotoxy(25, 17);
		cout << "N  U  E  V  A  M  E  N  T  E  !";
		JuegoActivo = false;
	}
}

void Juego::ganaste(){
	if (rana->puntajeInicial() == 150){
		textcolor(WHITE);
		gotoxy(28, 15);
		cout << "G  A  N  A  S  T  E ";
		gotoxy(24, 16);
		cout << "B  I  E  N  H  E  C  H  O  !";
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
		automobilDos->actualizar();
		automobilTres->actualizar();
		automobilCuatro->actualizar();
		camion->actualizar();
		camionDos->actualizar();
		camionTres->actualizar();
		camionCuatro->actualizar();
		camioneta->actualizar();
		camionetaDos->actualizar();
		camionetaTres->actualizar();
		camionetaCuatro->actualizar();
		finDelJuego();
		ganaste();
	}
}

int main (int argc, char *argv[]) {
	
	Juego J;
	J.iniciar();
	
	return 0;
}


