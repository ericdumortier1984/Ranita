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
	clock_t tiempoActual;
	clock_t paso; 
	int velocidad;
	int vidas = 1;
	int puntos = 0;
	void dibujar();
	void borrar();
public:
	Personaje(int vel);
	int x, y;
};

Personaje::Personaje(int vel){
	velocidad = vel;
	paso = CLOCKS_PER_SEC/velocidad;//Cada cuanto se mueven los objetos
	tiempoActual = clock();//Inicia tiempo actual con el reloj
	tempo = clock();//Inicia tempo con el reloj
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
	cout << "^";
}

void Rana::actualizar() {
	tiempoActual = clock();
	if(vidas > 0){
		if (tempo + paso < clock()){
		if (_kbhit()) {
			borrar();
			char tecla = _getch();
			if (tecla == 'a' && x > xMin + 2) { x--; }
			if (tecla == 'd' && x < xMax - 2) { x++; }
			if (tecla == 'w' && y > yMin + 3) { y--; }
			if (tecla == 's' && y < yMax - 2) { y++; }
		}
		dibujar();
		tempo = tiempoActual;//Actualiza el tiempo
		}
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
	textcolor(LIGHTRED);
	cout << ">";
}
void Automobil::actualizar() {
	tiempoActual = clock();
	if(vidas > 0){
		if (tempo + paso < clock()){
		borrar();
		x++;
		if (x > xMax - 4){
			borrar();
			x = xMin + 2;
		}
		dibujar();
		tempo = tiempoActual;
		}
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
	textcolor(LIGHTBLUE);
	cout << "{";
}

void Camion::actualizar() {
	tiempoActual = clock();
	if(vidas > 0){
		if (tempo + paso < clock()){
		borrar();
		x--;
		if (x < xMin + 2){
			borrar();
			x = xMax - 4;
		}
		dibujar();
		tempo = tiempoActual;
		}
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
	textcolor(LIGHTCYAN);
	cout << ">";
}
void Camioneta::actualizar() {
	tiempoActual = clock();
	if(vidas > 0){
		if (tempo + paso < clock()){
		borrar();
		x++;
		if (x > xMax - 4){
			borrar();
			x = xMin + 2;
		}
		dibujar();
		tempo = tiempoActual;
		}
	}
}

class Juego {
private:
	bool metaOcupada[3];
	Rana* rana = new Rana(5);
	Automobil* automobil = new Automobil(2, 13 , 27);
	Automobil* automobilDos = new Automobil(2, 25, 45);
	Automobil* automobilTres = new Automobil(2, 17, 38);
	Automobil* automobilCuatro = new Automobil(2, 8, 23);
	Automobil* automobilCinco = new Automobil(2, 22, 28);
	Camion* camion = new Camion(78, 10, 35);
	Camion* camionDos = new Camion(78, 6, 52);
	Camion* camionTres = new Camion(78, 20, 25);
	Camion* camionCuatro = new Camion(78, 24, 18);
	Camion* camionCinco = new Camion(78, 9, 16);
	Camioneta* camioneta = new Camioneta(2, 19, 40);
	Camioneta* camionetaDos = new Camioneta(2, 21, 21);
	Camioneta* camionetaTres = new Camioneta(2, 7, 19);
	Camioneta* camionetaCuatro = new Camioneta(2, 26, 43);
	Camioneta* camionetaCinco = new Camioneta(2, 14, 33);
	
public:
	Juego();
	void iniciar();
	void marcarBordes();
	void pintarAutopista();
	void ocultarCursor();
	void marcadorVidas();
	void tituloDelJuego();
	void marcadorPuntaje();
	void indicadorTeclas();
	void chequearColisiones();
	void llegarMeta();
	void finDelJuego();
	void ganaste();
	bool JuegoActivo = true;
};

Juego::Juego(){
	//Arreglo para determinar si la casilla de meta está ocupada o no
	for (int i = 0; i < 2; i++) {
		metaOcupada[i] = false; 
	}
}

void Juego::marcarBordes(){
	//Bordes de la pantalla de juego
	for (int i = 1; i < 80; i++){
		textcolor(LIGHTGRAY);
		gotoxy(i, 1);
		cout << "-";
	}
	for (int i = 1; i < 80; i++){
		gotoxy (i, 30);
		cout << "-";
	}
	for (int i = 1; i < 30; i++){
		gotoxy(1, i);
		cout << "-";
	}
	for (int i = 1; i < 30; i++){
		gotoxy(80, i);
		cout << "-";
	}
	
	//Texto de ayuda
	gotoxy(3, 4);
	textcolor(LIGHTCYAN);
	cout << "META 1";
	gotoxy(38, 4);
	textcolor(LIGHTCYAN);
	cout << "META 2";
	gotoxy(74, 4);
	textcolor(LIGHTCYAN);
	cout << "META 3";
	
	//Bordes de las casillas de meta
	for (int i = 1; i < 4; i++){
		textcolor(LIGHTGREEN);
		gotoxy(i, 5);
		cout << "*";
	}
	for (int i = 5; i < 40; i++){
		gotoxy(i, 5);
		cout << "*";
	}
	for (int i = 41; i < 76; i++){
		gotoxy(i, 5);
		cout << "*";
	}
	for (int i = 77; i < 80; i++){
		gotoxy(i, 5);
		cout << "*";
	}
}

//zona de descanso
void Juego::pintarAutopista(){	
	textbackground(WHITE);
	for (int i = xMin; i <= xMax; i++) {
		gotoxy(i, 15);
		cout << " ";
	}
	textbackground(BLACK);
}

//Menu de indicaciones y titulo del juego
void Juego::tituloDelJuego(){
	textcolor(LIGHTGREEN);
	gotoxy(36, 3);
	cout << "-RANITA-";
}

void Juego::marcadorVidas(){
	textcolor(LIGHTGRAY);
	gotoxy(20, 3);
	cout << "VIDAS: " << rana->obtenerVidas();
}

void Juego::marcadorPuntaje(){
	textcolor(LIGHTGRAY);
	gotoxy(50, 3);
	cout << "PUNTOS: " << rana->puntajeInicial(); 
}

void Juego::indicadorTeclas(){
	textcolor(LIGHTGRAY);
	gotoxy(10, 2);
	cout << "CONTROLES: A - IZQUIERDA, D - DERECHA, W - ARRIBA, S - ABAJO ";
}

void Juego::chequearColisiones(){
	switch (JuegoActivo) {
	case 1: if (rana->x == camion->x && rana->y == camion->y) {rana->perderVidas();marcadorVidas();break;}
	case 2: if (rana->x == camionDos->x && rana->y == camionDos->y) {rana->perderVidas();marcadorVidas();break;}
	case 3: if (rana->x == camionTres->x && rana->y == camionTres->y) {rana->perderVidas();marcadorVidas();break;}
	case 4: if (rana->x == camionCuatro->x && rana->y == camionCuatro->y) {rana->perderVidas();marcadorVidas();break;}
	case 5: if (rana->x == automobil->x && rana->y == automobil->y) {rana->perderVidas();marcadorVidas();break;}
	case 6: if (rana->x == automobilDos->x && rana->y == automobilDos->y) {rana->perderVidas();marcadorVidas();break;}
	case 7: if (rana->x == automobilTres->x && rana->y == automobilTres->y) {rana->perderVidas();marcadorVidas();break;}
	case 8: if (rana->x == automobilCuatro->x && rana->y == automobilCuatro->y) {rana->perderVidas();marcadorVidas();break;}
	case 9: if (rana->x == camioneta->x && rana->y == camioneta->y) {rana->perderVidas();marcadorVidas();break;}
	case 10: if (rana->x == camionetaDos->x && rana->y == camionetaDos->y) {rana->perderVidas();marcadorVidas();break;}
	case 11: if (rana->x == camionetaTres->x && rana->y == camionetaTres->y) {rana->perderVidas();marcadorVidas();break;}
	case 12: if (rana->x == camionetaCuatro->x && rana->y == camionetaCuatro->y) {rana->perderVidas();marcadorVidas();break;}
	case 13: if (rana->x == camionetaCinco->x && rana->y == camionetaCinco->y) {rana->perderVidas();marcadorVidas();break;}
	case 14: if (rana->x == camionCinco->x && rana->y == camionCinco->y) {rana->perderVidas();marcadorVidas();break;}
	case 15: if (rana->x == automobilCinco->x && rana->y == automobilCinco->y) {rana->perderVidas();marcadorVidas();break;}
	}
}

void Juego::llegarMeta(){
	//llegamos a la casilla, si la misma está ocupada se reinicia la posición pero sin sumar puntos
	if ((rana->x == 4 && rana->y == 5) && !metaOcupada[0]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[0] = true; 
	}else if ((rana->x == 4 && rana->y == 5) && metaOcupada[0]) {
		rana->reiniciarPosicion(); 
    }
	if ((rana->x == 40 && rana->y == 5) && !metaOcupada[1]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[1] = true;
	}else if ((rana->x == 40 && rana->y == 5) && metaOcupada[1]) {
		rana->reiniciarPosicion();
	}
	if ((rana->x == 76 && rana->y == 5) && !metaOcupada[2]) {
		rana->obtenerPuntos();
		marcadorPuntaje();
		rana->reiniciarPosicion();
		metaOcupada[2] = true; 
	}else if ((rana->x == 76 && rana->y == 5) && metaOcupada[2]) {
		rana->reiniciarPosicion();
	}
}

void Juego::finDelJuego(){
	//Si vidas igual o menor a cero termina el juego de manera negativa
	if (rana->obtenerVidas() <= 0){
		textcolor(LIGHTRED);
		gotoxy(28, 16);
		cout << "P  E  R  D  I  S  T  E ";
		gotoxy(28, 18);
		cout << "I  N  T  E  N  T  A  R  ";
		gotoxy(25, 20);
		cout << "N  U  E  V  A  M  E  N  T  E  !";
		JuegoActivo = false;
	}
}

void Juego::ganaste(){
	//Si obtenemos 150 puntos (casillas de meta completas)termina el juego de manera positiva
	if (rana->puntajeInicial() == 150){
		textcolor(LIGHTGREEN);
		gotoxy(28, 16);
		cout << "G  A  N  A  S  T  E ";
		gotoxy(24, 118);
		cout << "B  I  E  N    H  E  C  H  O  !";
		JuegoActivo = false;
	}
}

void Juego::ocultarCursor(){
	//Ocultamos el cursor
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Juego::iniciar(){
	marcarBordes();
	pintarAutopista();
	ocultarCursor();
	tituloDelJuego();
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
		automobilCinco->actualizar();
		camion->actualizar();
		camionDos->actualizar();
		camionTres->actualizar();
		camionCuatro->actualizar();
		camionCinco->actualizar();
		camioneta->actualizar();
		camionetaDos->actualizar();
		camionetaTres->actualizar();
		camionetaCuatro->actualizar();
		camionetaCinco->actualizar();
		ganaste();
		finDelJuego();
	}
}

int main (int argc, char *argv[]) {
	Juego J;
	J.iniciar();
	
	return 0;
}


