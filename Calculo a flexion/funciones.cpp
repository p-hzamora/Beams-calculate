//meter en la funcion sumar diagrama la parte correspondiente a VEE la comprobacion de continuidad de los giros
#include "funciones.h"
#include "variables.h"
#include "Vvol.h"
#include "VAA.h"
#include "VAE.h"
#include "VEE.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include<Windows.h>
#include <math.h>

using namespace std;
short int sumar_voladizo = 0;
viga_vol carga_voladizo;


#if !defined(PROPIEDADES)
#define PROPIEDADES cout<<"\t\t";for (unsigned int fila = 0; fila < propiedades.size(); fila++) {cout << propiedades[fila] << "\t";}
#endif
void anadir_voladizo_global(viga_vol* voladizo) {
	unsigned int long_voladizo = (int)(longitud_voladizo *1000) + 1;
	for (unsigned int i = 0; i < long_voladizo; i++) {
		if (sumar_voladizo != 0) {
			//NO PODEMOS HACER UN PUSH_BACK 
			//SEGUNDA ITERACION PARA SUMA DE NUEVAS CARGAS
			carga_voladizo.set_diagramaCortante(voladizo->get_diagramaCortante()[i], i);
			carga_voladizo.set_diagramaFlectores(voladizo->get_diagramaFlectores()[i], i);
			carga_voladizo.set_diagramaElastica(voladizo->get_diagramaElastica()[i], i);
		}
		else if (sumar_voladizo ==0){
			//PRIMERA ITERACION
			carga_voladizo.add_diagramaCortante( voladizo->get_diagramaCortante()[i]);
			carga_voladizo.add_diagramaFlectores(voladizo->get_diagramaFlectores()[i]);
			carga_voladizo.add_diagramaElastica(voladizo->get_diagramaElastica()[i]);
		}
	}
		voladizo->reset_diagramaCortante();
		voladizo->reset_diagramaFlectores();
		voladizo->reset_diagramaElastica();	
}

bool comprobarSuma(vector<double> vec1, vector<double> vec2) {
	bool igualdad;
	igualdad= vec1 == vec2 ? true : false;
	return igualdad;
}
double buscarMayor(vector<double> vector) {
	double mayor,menor;
	mayor = vector[0];
	menor = mayor;
	for (unsigned int j = 1; j < vector.size(); j++) {
		mayor = mayor < vector[j] ? vector[j] : mayor;
		menor = menor > vector[j] ? vector[j]: menor;
	}
	mayor = mayor > abs(menor) ? mayor : menor;
	return mayor;
}

//Declarar funciones 
void calcularSolicitacion(viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA) {
	char solicitacion = 'n';
	double nuevaPosicion;
	int total;
	double cortante, flectores, elastica;
	for(;;){
		cout << "\n\nDesea calcular alguna otra solicitacion de la misma viga? (s\\n): "; cin >> solicitacion;
		if (solicitacion == 's' || solicitacion == 'S') {
			cout << "\nPosicion X del nuevo punto de solicitaciones [m]: "; cin >> nuevaPosicion;
			switch (hay_voladizo) {
			case 0:
				total = (int)(nuevaPosicion * 1000);
				cortante = VAA->get_diagramaElastica()[total];
				flectores = VAA->get_diagramaFlectores()[total];
				elastica = VAA->get_diagramaElastica()[total];
			case 1:
				total = (int)(nuevaPosicion * 1000);
				cortante = VAE->get_diagramaElastica()[total];
				flectores = VAE->get_diagramaFlectores()[total];
				elastica = VAE->get_diagramaElastica()[total];
			case 2:
				total = (int)(nuevaPosicion * 1000);
				cortante = VEE->get_diagramaElastica()[total];
				flectores = VEE->get_diagramaFlectores()[total];
				elastica = VEE->get_diagramaElastica()[total];
			}
			if (cortante >= 0 && cortante <= 0.0000001) {
				cortante = 0;
			}
			if (flectores >= 0 && flectores <= 0.0000001) {
				flectores = 0;
			}
			if (elastica >= 0 && elastica <= 0.0000001) {
				elastica = 0;
			}
			cout << endl;
			cout << "\t[+] Cortante en x(" << nuevaPosicion << ") = " << cortante << " KN" << endl;
			cout << "\t[+] Flector en x(" << nuevaPosicion << ") = " << flectores << " m*KN" << endl;
			cout << "\t[+] Flecha en x(" << nuevaPosicion << ") = " << elastica << "  *(E*I)*e-1 mm" << endl;
		}
		break;
	}
}
bool sumar_diagramas( viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA, bool*unaSolaCarga){
	//solo para unir los vanos con los voladizos
	unsigned int long_vano = (int) (luz * 1000) + 1;
	unsigned int long_voladizo = (int)(longitud_voladizo*1000) + 1;
	unsigned int viga_total = 0;
	auxCortante.resize((int)(luz * 1000 + 1));
	auxFlector.resize((int)(luz * 1000 + 1 ));
	auxElastica.resize((int)(luz * 1000 + 1));
	
	vector<double> auxVolCortante;
	vector<double> auxVolFlector ;
	vector<double> auxVolElastica;

	auxVolCortante = carga_voladizo.get_diagramaCortante();
	auxVolFlector  = carga_voladizo.get_diagramaFlectores();
	auxVolElastica = carga_voladizo.get_diagramaElastica();

	if (hay_voladizo == 0) {						//no tiene voladizo
		suma_DiagCortante.resize( long_vano);
		suma_Diagflectores.resize(long_vano);
		suma_DiagElastica.resize( long_vano);

		for (unsigned int i = 0; i < long_vano; i++) {
			suma_DiagCortante[i] += VAA->get_diagramaCortante()[i];
			suma_Diagflectores[i] += VAA->get_diagramaFlectores()[i];
			suma_DiagElastica[i] += VAA->get_diagramaElastica()[i];
		}

		*unaSolaCarga = suma_DiagCortante == VAA->get_diagramaCortante() ? true : false;
		//Redimensionamos todas las variables originales para que no guarden registros de usos anteriores, los registros anteriores se sumaran en el vector suma_....
		VAA->get_diagramaCortante().resize(0);
		VAA->get_diagramaFlectores().resize(0);
		VAA->get_diagramaElastica().resize(0);
		return *unaSolaCarga;
	}
	else if (hay_voladizo == 1) {
		viga_total = long_vano + long_voladizo;

		//Forma de almacenar los valores a la hora de sumar diagramas
		for (unsigned int i = 0; i < long_vano; i++) {
			VAE->get_diagramaCortante()[i] += auxCortante[i];
			VAE->get_diagramaFlectores()[i] += auxFlector[i];
			VAE->get_diagramaElastica()[i] += auxElastica[i];

			auxCortante[i] += VAE->get_diagramaCortante()[i];
			auxFlector[i]  += VAE->get_diagramaFlectores()[i];
			auxElastica[i] += VAE->get_diagramaElastica()[i];
		}

		for (unsigned int i = 0; i < long_voladizo; i++) {
			VAE->get_diagramaCortante().push_back(auxVolCortante[i]);
			VAE->get_diagramaFlectores().push_back(auxVolFlector[i]);
			VAE->get_diagramaElastica().push_back(auxVolElastica[i]);
		}
		//redimensionamos el vector suma con la distancia del voladizo y del vano
		suma_DiagCortante.resize( viga_total);
		suma_Diagflectores.resize(viga_total);
		suma_DiagElastica.resize( viga_total);

		//vector de voladizos con sus respectivos giros para cuadrar en el diagrama
		int apoyo = (int)(luz * 1000);
		vector <double> IZQUIERDAinvertirCortante = invertirEjeY(invertirEjeX((carga_voladizo.get_diagramaCortante())));
		vector <double> IZQUIERDAinvertirFlector = invertirEjeY(carga_voladizo.get_diagramaFlectores());
		vector <double> IZQUIERDAinvertirElastica = invertirEjeY(carga_voladizo.get_diagramaElastica());
		// Forma de comprobar la continuidad de los giros entre las 2 vigas.
		if (VAE->get_diagramaElastica()[apoyo - 1] > 0) { IZQUIERDAinvertirElastica = invertirEjeY(invertirEjeX(carga_voladizo.get_diagramaElastica())); }
		for (unsigned int i = 0; i < viga_total; i++) {
			if (i < long_vano) {
				suma_DiagCortante[i] += VAE->get_diagramaCortante()[i];
				suma_Diagflectores[i] += VAE->get_diagramaFlectores()[i];
				suma_DiagElastica[i] += VAE->get_diagramaElastica()[i];
			}
			else {
				suma_DiagCortante[i] = IZQUIERDAinvertirCortante[i - long_vano];
				suma_Diagflectores[i] = IZQUIERDAinvertirFlector[i - long_vano];
				suma_DiagElastica[i] = IZQUIERDAinvertirElastica[i - long_vano];
			}
		}
		VAE->reset_diagramaCortante();
		VAE->reset_diagramaFlectores();
		VAE->reset_diagramaElastica();
		return 0;
	}
	else {
		viga_total = long_vano + 2 * long_voladizo;
		suma_DiagCortante.resize( viga_total);
		suma_Diagflectores.resize(viga_total);
		suma_DiagElastica.resize( viga_total);

		//No  invertimos los voladizo de la izquierda porque estan calculado suponiendo esa posicion
		vector <double> IZQUIERDAinvertirCortante = auxVolCortante;
		vector <double> IZQUIERDAinvertirFlector =  auxVolFlector;
		vector <double> IZQUIERDAinvertirElastica = auxVolElastica;

		vector <double> DERECHAinvertirCortante =invertirEjeY(invertirEjeX(auxVolCortante));
		vector <double> DERECHAinvertirFlector = invertirEjeY(auxVolFlector);
		vector <double> DERECHAinvertirElastica = invertirEjeY(auxVolElastica);

		//Forma de almacenar los valores a la hora de sumar diagramas
		for (unsigned int i = 0; i < long_vano; i++) {
			VEE->get_diagramaCortante()[i] += auxCortante[i];
			VEE->get_diagramaFlectores()[i] += auxFlector[i];
			VEE->get_diagramaElastica()[i] += auxElastica[i];

			auxCortante[i] += VEE->get_diagramaCortante()[i];
			auxFlector[i] += VEE->get_diagramaFlectores()[i];
			auxElastica[i] += VEE->get_diagramaElastica()[i];
		}

		for(unsigned int i = 0; i < viga_total; i++) {
			if ( i < long_voladizo) {
				//Invertimos los ejes para voladizo izquierda
				suma_DiagCortante[i] = IZQUIERDAinvertirCortante[i];
				suma_Diagflectores[i]= IZQUIERDAinvertirFlector[i];
				suma_DiagElastica[i] =  IZQUIERDAinvertirElastica[i];
			}
			else if (i >= long_voladizo && i< long_vano+long_voladizo ) {
				suma_DiagCortante[i] += VEE->get_diagramaCortante()[i-long_voladizo];
				suma_Diagflectores[i] += VEE->get_diagramaFlectores()[i - long_voladizo];
				suma_DiagElastica[i] += VEE->get_diagramaElastica()[i - long_voladizo];
			}
			else {
				suma_DiagCortante[i]   = DERECHAinvertirCortante[i - long_vano - long_voladizo];
				suma_Diagflectores[i]  =DERECHAinvertirFlector[i - long_vano - long_voladizo];
				suma_DiagElastica[i]   = DERECHAinvertirElastica[i - long_vano - long_voladizo];
			}
		}
		VEE->reset_diagramaCortante();
		VEE->reset_diagramaFlectores();
		VEE->reset_diagramaElastica();
 		return 0;
	}
	long_vano = 0;
	long_voladizo = 0;
	viga_total = 0;
}
void print_suma_diagramas(bool unaSolaCarga) {
	if ((unaSolaCarga != true && hay_voladizo ==0) || (hay_voladizo != 0)) {
		cout << "\n\n*******************Impresion de diagramas con todas las cargas***********************" << endl;
		ofstream cortante;
		cortante.open("C:\\Diagramas\\Diagrama de cortantes.txt");

		ofstream flector;
		flector.open("C:\\Diagramas\\Diagrama de momentos.txt");

		ofstream elastica;
		elastica.open("C:\\Diagramas\\Diagrama de flechas.txt");
		for (unsigned int i = 0; i < suma_DiagCortante.size(); i++) {
			cortante << i << "|" << suma_DiagCortante[i] << endl;
			flector << i << "|" << suma_Diagflectores[i] << endl;
			elastica << i << "|" << suma_DiagElastica[i] << endl;
		}
		cortante << hay_voladizo << "|" << longitud_voladizo; cortante.close();
		flector << hay_voladizo << "|" << longitud_voladizo; flector.close();
		elastica << hay_voladizo << "|" << longitud_voladizo; elastica.close();

		system("start \"\" \"C:\\Diagramas\\Diagrama de cortantes.py\"");
		system("start \"\" \"C:\\Diagramas\\Diagrama de momentos.py\"");
		system("start \"\" \"C:\\Diagramas\\Diagrama de flechas.py\"");
	}
}
void copiar_datos_notepad(viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA) {		//Solo afecta al bloc de notas no al vector del eje X e Y de la viga.
	ofstream cortante;
	cortante.open("C:\\Diagramas\\Diagrama de cortantes.txt");
	ofstream flector;
	flector.open("C:\\Diagramas\\Diagrama de momentos.txt");
	ofstream elastica;
	elastica.open("C:\\Diagramas\\Diagrama de flechas.txt");
	if (hay_voladizo == 0 /*|| copia_de_datos == true*/) {
		unsigned int tamanio = VAA->get_diagramaCortante().size();
		for (unsigned int i = 0; i < tamanio; i++) {
			cortante << i << "|" << VAA->get_diagramaCortante()[i] << endl;
			flector << i << "|" << VAA->get_diagramaFlectores()[i] << endl;
			elastica << i << "|" << VAA->get_diagramaElastica()[i] << endl;
		}
	}
	else if (hay_voladizo == 1) {
		for (unsigned int i = 0; i < VAE->get_diagramaElastica().size(); i++) {
			cortante << i << "|" << VAE->get_diagramaCortante()[i] << endl;
			flector << i << "|" << VAE->get_diagramaFlectores()[i] << endl;
			elastica << i << "|" << VAE->get_diagramaElastica()[i] << endl;
		}
	}
	else {
		for (unsigned int i = 0; i < VEE->get_diagramaElastica().size(); i++) {
			cortante << i << "|" << VEE->get_diagramaCortante()[i] << endl;
			flector << i << "|" << VEE->get_diagramaFlectores()[i] << endl;
			elastica << i << "|" << VEE->get_diagramaElastica()[i] << endl;
		}
	}
	cortante << hay_voladizo << "|" << longitud_voladizo; cortante.close();
	flector << hay_voladizo << "|" << longitud_voladizo; flector.close();
	elastica << hay_voladizo << "|" << longitud_voladizo; elastica.close();

	if (hay_voladizo == 0) {
		cout << "\nImprimiendo diagramas..." << endl;
		cout << "\t[1] Cortante." << endl;
		cout << "\t[2] Momentos." << endl;
		cout << "\t[3] Elastica." << endl;
		system("start \"\" \"C:\\Diagramas\\Diagrama de cortantes.py\"");
		system("start \"\" \"C:\\Diagramas\\Diagrama de momentos.py\"");
		system("start \"\" \"C:\\Diagramas\\Diagrama de flechas.py\"");
	}
	//copia_de_datos++;
}

vector <double> invertirEjeX(vector<double> vec) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		vec[i] = vec[i] * -1;
	}
	return vec;
}
vector <double> invertirEjeY(vector<double> vec) {
	double aux;
	unsigned int cantidad = vec.size();
	for (unsigned int i = 0; i < cantidad/2; i++) {
		aux = vec[i];
		vec[i] = vec[cantidad - 1 - i];
		vec[cantidad - 1 - i] = aux;
	}
	return vec;
}
void invertirEjeX_eficiente(vector<double>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		vec[i] = vec[i] * -1;
	}
}
void invertirEjeY_eficiente(vector<double>& vec) {
	double aux;
	unsigned int cantidad = vec.size();
	for (unsigned int i = 0; i < cantidad / 2; i++) {
		aux = vec[i];
		vec[i] = vec[cantidad - 1 - i];
		vec[cantidad - 1 - i] = aux;
	}
}
vector <float> valor0(const vector<double>& vec) {
	vector<float> position;
	for (unsigned int i = 0; i < vec.size()-1; i++) {
		if (vec[i] != vec[i + (unsigned int)1]) {
			if (!((vec[i] < 0 && vec[i + (unsigned int)1] < 0) || (vec[i] > 0 && vec[i + (unsigned int)1] > 0))) {
				position.push_back((float)i/(float)1000);
			}
		}
	}
	return position;
}

void sumarVanos(int posicion,viga_ap_emp* VAE, viga_emp_emp* VEE){
	if (posicion == 0) {
		posicion *= 1000;
		for (unsigned int i = posicion; i < VAE->get_diagramaCortante().size() + posicion; i++) {
			suma_DiagCortante[i] += VAE->get_diagramaCortante()[i];
			suma_Diagflectores[i] += VAE->get_diagramaFlectores()[i];
			suma_DiagElastica[i] += VAE->get_diagramaElastica()[i];
		}
	}
	else if (posicion > 0 && posicion < posicion_apoyos.back()) {
		posicion *= 1000;
		for (unsigned int i = posicion; i < VEE->get_diagramaCortante().size() + posicion; i++) {
			suma_DiagCortante[i] += VEE->get_diagramaCortante()[i];
			suma_Diagflectores[i] +=VEE->get_diagramaFlectores()[i];
			suma_DiagElastica[i] += VEE->get_diagramaElastica()[i];
		}
	}
	else if (posicion > 0 && posicion == posicion_apoyos.back()) {
		posicion *= 1000;
		vector<double> CC = invertirEjeY(VAE->get_diagramaCortante());
		vector<double> CF = invertirEjeY(VAE->get_diagramaFlectores());
		vector<double> CE = invertirEjeY(VAE->get_diagramaElastica());
		for (unsigned int i = posicion; i < VAE->get_diagramaCortante().size() + posicion; i++) {
			suma_DiagCortante[i] += CC[i];
			suma_Diagflectores[i] += CF[i];
			suma_DiagElastica[i] += CE[i];
		}
	}
}



//Segunda parte
void mayuscula(string& palabra) {
	for (unsigned int i = 0; i < palabra.length(); i++) {
		palabra[i] = toupper(palabra[i]);
	}
}
void mostrar_tabla() {
	//imprimir la columna vector de perfil IPE
	PROPIEDADES;
	printf("\n\n");
	for (unsigned int fila = 0; fila < IPE.size(); fila++) {
		cout << IPE[fila] << "\t\t";					//	Imprimir el vector de cabecera de los datos
		for (unsigned int columna = 0; columna < propiedades.size(); columna++) {
			cout << caracMecanicasIPE[fila][columna] << "\t";		//Imprimir la matriz de datos
		}printf("\n");
	}
	printf("\n\n\n");
	//imprimir la columna vector de perfil UPE
	PROPIEDADES; printf("ys\tym");
	printf("\n\n");
	for (unsigned int fila = 0; fila < UPE.size(); fila++) {
		cout << UPE[fila] << "\t\t";
		for (unsigned int columna = 0; columna < propiedades.size() + 2; columna++) {
			cout << caracMecanicasUPE[fila][columna] << "\t";
		}printf("\n");
	}
	printf("\n\n\n");
	//imprimir la columna vector de perfil HE
	PROPIEDADES;
	printf("\n\n");
	for (unsigned int fila = 0; fila < HE.size(); fila++) {
		if (HE[fila][3] == 'A') {
			cout << HE[fila] << "\t";
		}
		else {
			cout << HE[fila] << "\t\t";
		}
		for (unsigned int columna = 0; columna < propiedades.size(); columna++) {
			cout << caracMecanicasHE[fila][columna] << "\t";
		}printf("\n");
	}
}
void buscador_de_valores() {
	//Buscador de palabras
	printf("\nQue perfil desea buscar: "); getline(cin, buscarPerfil);
	//If para tabla IPE
	mayuscula(buscarPerfil);
	if (buscarPerfil[0] == 'I') {
		for (unsigned int i = 0; i < IPE.size(); i++) {
			if (buscarPerfil == IPE[i]) {
				posicionfila = i;
				break;
			}
		};
	}
	else  if (buscarPerfil[0] == 'U') { //else if para tabla UPE
		for (unsigned int i = 0; i < UPE.size(); i++) {
			if (buscarPerfil == UPE[i]) {
				posicionfila = i;
				break;
			}
		};
	}
	else if (buscarPerfil[0] == 'H') {
		for (unsigned int i = 0; i < HE.size(); i++) {
			if (buscarPerfil == HE[i]) {
				posicionfila = i;
				break;
			}
		};
	}

	printf("\nQue propiedad desea buscar: "); getline(cin, buscarValor);

	for (unsigned int j = 0; j < propiedades.size(); j++) {
		if (buscarValor == propiedades[j]) {
			posicioncolumna = j;
			break;
		}
	};
	if (buscarPerfil[0] == 'I') { //Cuidado con el IPE y el IPN esta forma no las distingue
		cout << "\nEl valor buscado es: " << caracMecanicasIPE[posicionfila][posicioncolumna] << endl;
	}
	else  if ((buscarPerfil[0] == 'U')) {
		cout << "\nEl valor buscado es: " << caracMecanicasUPE[posicionfila][posicioncolumna] << endl;
	}
	else if ((buscarPerfil[0] == 'H')) {
		cout << "\nEl valor buscado es: " << caracMecanicasHE[posicionfila][posicioncolumna] << endl;
	}
	char verifica2;
	cout << "Desea volver a buscar un perfil (s\\n): "; cin >> verifica2;
	cin.ignore();
	if (verifica2 == 's' || verifica2 == 'S') {
		system("cls");
		mostrar_tabla();
		buscador_de_valores();
	}
}
int comprobacionCortante(string tipoPerfil,double comprobar_Wpl, vector<string> perfil, double caracMecanicas[][13]) {
	unsigned short int iteracionPerfiles = 0;
	unsigned short int tipoWpl = 3;
	do { iteracionPerfiles++; } while (caracMecanicas[iteracionPerfiles][tipoWpl] <= comprobar_Wpl); //el 3 hace alusion a la posicion del Wpl.y y no el elastico porque se trata de un material de clase 1
	if (iteracionPerfiles <= perfil.size()) {
		cout << "EL " << tipoPerfil << " necesario para las cargas introducidas es un	 " << perfil[iteracionPerfiles] << endl;
		//El codigo siguiente solo es para visualizar las propiedades del IPE que necesitamos
		PROPIEDADES;
		cout << "\n\n\t\t";
		for (unsigned int columna = 0; columna < 13; columna++) {
			cout << caracMecanicas[iteracionPerfiles][columna] << "\t";
		};
		cout << endl;
	}
	else {
		cout << "Ningun perfil "<< tipoPerfil <<" sin ninguna modificacion puede soportar las cargas sobre el." << endl;
	}
	return iteracionPerfiles;
}
int comprobacionCortanteUPE(string tipoPerfil, double comprobar_Wpl, vector<string> perfil, double caracMecanicas[][15]) {
	unsigned short int iteracionPerfiles = 0;
	unsigned short int tipoWpl = 3; // debemos saber cuando poner Wel.y [2] o el que esta puesto Wpl.y
	do { iteracionPerfiles++; } while (caracMecanicas[iteracionPerfiles][tipoWpl] <= comprobar_Wpl); //el 3 hace alusion a la posicion del Wpl.y y no el elastico porque se trata de un material de clase 1
	if (iteracionPerfiles <= perfil.size()) {
		cout << "EL " << tipoPerfil << " necesario para las cargas introducidas es un	 " << perfil[iteracionPerfiles] << endl;
		//El codigo siguiente solo es para visualizar las propiedades del IPE que necesitamos
		PROPIEDADES;
		cout << "\n\n\t\t";
		for (unsigned int columna = 0; columna < 13; columna++) {
			cout << caracMecanicas[iteracionPerfiles][columna] << "\t";
		};
		cout << endl;
	}
	else {
		cout << "Ningun perfil "<< tipoPerfil << " sin ninguna modificacion puede soportar las cargas sobre el.";
	}
	return iteracionPerfiles;
}
double coeficienteElasticidad(string tipoPerfil, int iteracionPerfiles) {
	double coeficienteElasticidad = 1.0;
	//no multiplicamos por 10^4 como en los prontuarios porque queremos introducir el valor como cm^4 no mm
	if (tipoPerfil == "IPE") {
		coeficienteElasticidad /= E / caracMecanicasIPE[iteracionPerfiles][1] ; 
		// 1 hace referencia al valor de Iy en la matriz
	}
	else if (tipoPerfil == "IPN"){coeficienteElasticidad /= E /caracMecanicasIPN[iteracionPerfiles][1];}
	else if (tipoPerfil == "HE") {coeficienteElasticidad /= E /caracMecanicasHE [iteracionPerfiles][1];}
	else if (tipoPerfil == "UPE"){coeficienteElasticidad /= E /caracMecanicasUPE[iteracionPerfiles][1];}
	else if (tipoPerfil == "UPN"){coeficienteElasticidad /= E /caracMecanicasUPN[iteracionPerfiles][1];}
	return coeficienteElasticidad * pow(10,-5); //10^-5 coef para pasar a KN/m^2
}


