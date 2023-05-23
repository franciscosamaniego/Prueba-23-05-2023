#include <iostream>
#include <limits.h>

using namespace std;

//el objetivo de esta funcion es pedirle al usuario ingresar el valor en pesos de los premios de cada juego
//que luego se les entregara al mejor jugador de cada juego

void initialize(int premios[7]) {
	for(int i = 0; i < 7; i++) {
		cout << "Elija el premio (en pesos) del " << i+1 << " juego" << endl;
		cin >> premios[i];
		if(premios [i] <= 0) {
			cout << "Elija una cantidad existente" << endl;
			i--;
		}
	}
}

int main(void) {
	double juegos[7][30], jugadores[30] = {0};
	int idjuegos[7][30];
	int premios[7] = {0}, max_juego[7] = {0}, monto[30] = {0}, totaljugadosjuego[7] = {0};
	int total_sin_calif = 0,  idx = -1, total_jugados = 0;
	initialize(premios);
	cout << "Bienvenido a la competencia de 7 juegos" << endl;
	while(1) {
		double prom = 0.0;
		int jugado = 0;
		int juego, calif, jugador;
		int max = INT_MIN;
		//en esta parte del codigo, se le pide al usuario ingresar un numero entre el 1 y el 30 que representara
		//al jugador seleccionado, que luego sera verificada su existencia. Luego de eso, se le pide al usuario que
		//ingrese el juego en el que participara, que tambien sera verificado y luego revisa si el jugador ya habia
		//participado en el juego o no, en el caso de que si, le avisa y le pide ingresar otro jugador.
		cout << "Ingrese el numero del jugador (entre 1 y 30) o ingrese 0 para terminar" << endl;
		cin >> jugador;
		if(jugador > 0 && jugador < 31) {
		total_jugados++;
		cout << "Ingrese el numero del juego (entre 1 y 7)" << endl;
		cin >> juego;
		for(int i = 0; i < totaljugadosjuego[juego-1]; i++) {
			if(idjuegos[juego-1][i] == jugador) {
				cout << "Este jugador ya fue ingresado en este juego" << endl;
				jugado = 1;
				break;
			}
		}
		if(jugado) continue;
		double intentos = 0.0;
		int sincalif = 0;
		//En esta parte, se le pide al ususario ingresar las notas que quiera en el juego ingresado, que luego se hara un promedio
		//para despues ser utilizado. Si el ususario ingresa 0, significa que no fue calificado, por lo que se utiliza un contador
		//para luego calcular el porcentaje de jugadores totales sin calificacion.
		while(1) {
		cout << "Ingrese la calificacion(entre 1 y 10) o elija 0 si no fue calificado" << endl;
		cin >> calif;
		if(calif >= 0 && calif < 11) {
			if(calif == 0) {
			total_sin_calif++;
			sincalif = 1;
			break;
		}
		prom += calif;
		intentos++;
		char choice;
		cout << "Consiguio mas calificaciones? s/n" << endl;
		cin >> choice;
		if(choice == 'n' || choice == 'N') break;	
		 }
		}
		//En esta parte se busca el promedio maximo por juego que luego se le otorgara el premio correspondiente.
		//En esta parte tambien se almacena en una matriz los jugadores y sus promedios en cada juego que jugo.
		//Tambien, si el promedio que consigui es mayor a 8, se guarda en un array el premio que gano el jugador
		//maximo. Por ultimo, si el jugador en cuestion no fue calificado, el valor suyo pasa a ser 0 ya que
		//si no se hace eso el valor sera aleatorio
		jugadores[jugador-1] = prom / intentos;
		if(max < jugadores[jugador-1]) {
			max = jugadores[jugador-1];
			idx = jugador-1;
		}
		max_juego[juego-1] = max;
		juegos[juego-1][totaljugadosjuego[juego-1]] = jugadores[jugador-1];
		idjuegos[juego-1][totaljugadosjuego[juego-1]] = jugador;
		if(prom / intentos > 8) monto[idx] += premios[juego-1];
		if(sincalif) juegos[juego-1][totaljugadosjuego[juego-1]] = 0;
		totaljugadosjuego[juego-1]++;
		}
		else if(jugador == 0) break;
		else cout << "Elija un jugador existente" << endl;
	 }
	 //en esta ultima parte se imprime todo lo pedido en el ejercicio: el puntaje final de cada jugador, el porcentaje
	 //de jugadores sin calificacion (para esto use la regla de tres simples con todos los juagdores que participaron en
	 //todos los juegos y con la cantidad de jugadores sin calificacion) y tambien muestra cuanto gano cada jugador
	 //por los juegos que participo
	 for(int i = 0; i < 7; i++) {
	 	cout << "Juego " << i+1 << ":" << endl;
	 	for(int j = 0; j < totaljugadosjuego[i]; j++) {
	 		cout << "Jugador " << idjuegos[i][j] << ":";
	 		cout << juegos[i][j] << " ";
		 }
		 cout << endl;
	 }
	 for(int i = 0; i < 7; i++) {
	 	if(max_juego[i] > 8) {
	 		cout << "El jugador " << idx+1 << " se gano el premio de " << premios[i] << " pesos en el " << i+1 << " juego" << endl;
		 }
	 }
	 cout << "Jugadores que cobraran un monto" << endl;
	 for(int i = 0; i < 30; i++) {
	 	if(monto[i] > 0) cout << "Jugador " << i+1 << ": " << monto[i] << endl;
	 }
	 cout << endl;
	 cout << "Porcentaje de jugadores sin calificacion: " << (total_sin_calif * 100) / total_jugados << "%" << endl;
	return 0;
}
