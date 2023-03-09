//Las flechas de este programa no se si estan bien, he de preguntar
#include "Vvol.h"
#include "variables.h"
#include "funciones.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include<Windows.h>
#include <math.h>

using namespace std;

viga_vol::viga_vol() :_luz(0) {};

void viga_vol::get_solicitaciones() {
	cout << "\nCalculando esfuerzos...";
	cout << "\n\t[+] Reaccion A = " << suma_reaccionA << " KN" << endl;
	cout << "\t[+] Reaccion B = " << suma_reaccionB + suma_reaccion_nudo_vol << " KN" << endl;
	cout << "\t[+] Cortante para x(" << numEcElast << ") = " << _cortante << " KN" << endl;
	cout << "\t[+] Momento maximo= " << _momento_maximo << " m*KN" << endl;	cout << "\t[+] Momento flector para x(" << numEcElast << ") = " << _mf_x << " m*KN" << endl;
	cout << "\t[+] Valor para x(" << numEcElast << ") de la ecuacion de la elastica = " << _ecuacion_elastica << " *(E*I)*e-1 mm" << endl;
	cout << "\t[+] Flecha maxima= " << _flechaMaxima << " *(E*I)*e-1 mm" << endl;
}
void viga_vol::carga_puntual_descentrada() {
		set_longitud_voladizo(longitud_voladizo);
		double a, b, x = 0, incremento = 0.001;
		cout << "Digite la distancia desde \"X\" de la carga puntual: "; cin >> a;
		b = _luz - a;
		this->_reaccionA = 0;
		this->_reaccionB = Q;
		do {
			if (x <= a) {
				this->_DiagCortante.push_back(0);
				this->_Diagflectores.push_back(0);
				this->_DiagElastica.push_back(Q * pow(b, 2) / 6 / E / I * (3 * (_luz - x) - b));
			}
			else {
				this->_DiagCortante.push_back(-Q);
				this->_Diagflectores.push_back(-Q * (x - a));
				this->_DiagElastica.push_back(Q / 6 / E / I * pow(_luz - x, 2) * (2 * b - a + x));
			}
			x += incremento;
		} while (x <= _luz + 0.0000000001);
		this->_momento_maximo = buscarMayor(_Diagflectores);
		this->_flechaMaxima = buscarMayor(_DiagElastica);
		this->_cortante = this->_DiagCortante[(int)(numEcElast / incremento)];
		this->_mf_x = this->_Diagflectores[(int)(numEcElast / incremento)];
		this->_ecuacion_elastica = this->_DiagElastica[(int)(numEcElast / incremento)];

		Mmax_vol = _momento_maximo;
}
void viga_vol::Carga_Repartida_uniforme() {
	double incremento = 0.001, x = 0;
	set_longitud_voladizo(longitud_voladizo);
	_reaccionA = 0;
	_reaccionB = Q * _luz;
	_flechaMaxima = (Q * pow(_luz, 4)) / (8 * E * I);

	do {
		_DiagCortante.push_back(-Q * x);
		_DiagElastica.push_back((Q / (24 * E * I)) * pow(_luz - x, 2) * ((3 * pow(_luz, 2)) + (2 * _luz * x) + pow(x, 2)));
		_Diagflectores.push_back(-Q * (pow(x, 2) / 2));
		x += incremento;
	} while (x <= _luz + 0.0000000001);
	_momento_maximo = buscarMayor(_Diagflectores);
	_cortante = _DiagCortante[(int)(numEcElast / incremento)];
	_mf_x = _Diagflectores[(int)(numEcElast / incremento)];
	_ecuacion_elastica = _DiagElastica[(int)(numEcElast / incremento)];
		
	Mmax_vol = _momento_maximo;
}
void viga_vol::Momento_centro_del_vano() {
	double incremento = 0.001;
	double a,b , x = 0;
	set_longitud_voladizo(longitud_voladizo);
	cout << "Valor del MOMENTO [m*KN]: "; cin >> M;
	cout << "Digite la distancia donde se aplica el MOMENTO: "; cin >> a;
	b = luz - a;
	do {
		if (x <= a) {
			_DiagCortante.push_back(0);
			_Diagflectores.push_back(0);
			_DiagElastica.push_back(M/2/E/I*b*(2*_luz-2*x-b));
		}
		else {
			_DiagCortante.push_back(0);
			_Diagflectores.push_back(-M);
			_DiagElastica.push_back(M/2/E/I*pow(_luz-x,2));
		}
		x += incremento;
	} while (x <= _luz + 0.0000000001);
	_momento_maximo = buscarMayor(_Diagflectores);
	_flechaMaxima = buscarMayor(_DiagElastica);
	Mmax_vol = _momento_maximo;
}

void viga_vol::carga_puntual_generica_vol(double a, double Q) {
	//set_longitud_voladizo(longitud_voladizo);
	double  b, y;
	b = _luz - a;
	_reaccionA = 0;
	_reaccionB = Q;
	for (unsigned int x = 0; x < (int)1000 * _luz + 1; x++) {
		y = x * incremento;
		if (y <= a) {
			_DiagCortante[x] += 0;
			_Diagflectores[x] += 0;
			_DiagElastica[x] += Q * pow(b, 2) / 6 / E / I * (3 * (_luz - y) - b);
		}
		else {
			_DiagCortante[x] += -Q;
			_Diagflectores[x] += -Q * (y - a);
			_DiagElastica[x] += Q / 6 / E / I * pow(_luz - y, 2) * (2 * b - a + y);
		}
	}
}
void viga_vol::continua_generica() {
	set_longitud_voladizo(longitud_voladizo);
	_DiagCortante.resize((int)_luz * 1000 + 1);
	_Diagflectores.resize((int)_luz * 1000 + 1);
	_DiagElastica.resize((int)_luz * 1000 + 1);
	double a, c;
repetir_peticion:
	cout << "Digite la distancia de INICIO en \"X\" de la CARGA REPARTIDA [m]: "; cin >> a;
	cout << "Digite la distancia FINAL de la CARGA REPARTIDA [m]: "; cin >> c;
	if (a > c) {
		cout << "\n\t[+] La distancia INICIAL debe ser menor a la FINAL\n" << endl;
		goto repetir_peticion;
	}
	const double distCarga = c - a;
	double distancia, carga;
	double incremento = 0.001;
	// El num de rep. ha de ser igual que el incremento para que el tramo a calcular sea el correcto
	for (unsigned int i = 0; i < 1001; i++) {
		if (i == 0) { distancia = a; }
		else { distancia = a + distCarga * incremento; }
		a += distCarga * incremento;
		carga = Q;
		carga_puntual_generica_vol(distancia, carga);
	}
	for (unsigned int x = 0; x < _DiagCortante.size(); x++) {
		_DiagCortante[x] *= distCarga * incremento;
		_Diagflectores[x] *= distCarga * incremento;
		_DiagElastica[x] *= distCarga * incremento;
	}
	this->_reaccionA = _DiagCortante[0];
	this->_reaccionB = abs(_DiagCortante.back());
	this->_momento_maximo = buscarMayor(_Diagflectores);
	this->_flechaMaxima = buscarMayor(_DiagElastica);

	//Obligatorio en todas
	Mmax_vol = _momento_maximo;
}
void viga_vol::variable_generica() {
	set_longitud_voladizo(longitud_voladizo);
	_DiagCortante.resize((int)_luz * 1000 + 1);
	_Diagflectores.resize((int)_luz * 1000 + 1);
	_DiagElastica.resize((int)_luz * 1000 + 1);
	double a, c, co, cf;

	cout << "\n*****************Distancia en m ********************" << endl;
	repetir_peticion:
	cout << "Digite la distancia de INICIO en \"X\" de la CARGA VARIABLE [m]: "; cin >> a;
	cout << "Digite la distancia FINAL de la CARGA VARIABLE [m]: "; cin >> c;
	if (a > c) {
		cout << "\n\t[+] La distancia INICIAL debe ser menor a la FINAL\n" << endl;
		goto repetir_peticion;
	}
	cout << "\n*****************Cargas en KN ********************" << endl;
	cout << "Digite la carga INICIAL [KN]: "; cin >> co;
	cout << "Digite la carga FINAL [KN]: "; cin >> cf;

	const double distCarga = c - a;
	const double cargaIncremento = abs(cf - co);
	double distancia, carga;
	double incremento = 0.001;

	for (unsigned int i = 0; i < 1001; i++) {
		if (i == 0) {
			distancia = a;
			carga = co;
		}
		else { //Estos  bucles se encargan de aumentar proporcionalmente tanto la distancia como la carga
			distancia = a + distCarga * incremento;
			carga = co;
		}
		a += distCarga * incremento;
		// Dependiendo de si la carga variable es ascendente o descendente
		if (co < cf) { co += cargaIncremento * incremento; }
		else if (co > cf) { co -= cargaIncremento * incremento; }
		else { carga = cf; }
		carga_puntual_generica_vol(distancia, carga);
	}
	for (unsigned int x = 0; x < _DiagCortante.size(); x++) {
		_DiagCortante[x] *= distCarga * incremento;
		_Diagflectores[x] *= distCarga * incremento;
		_DiagElastica[x] *= distCarga * incremento;
	}
	this->_reaccionA = _DiagCortante[0];
	this->_reaccionB = abs(_DiagCortante.back());
	this->_momento_maximo = buscarMayor(_Diagflectores);
	this->_flechaMaxima = buscarMayor(_DiagElastica);
	Mmax_vol = _momento_maximo;
}
