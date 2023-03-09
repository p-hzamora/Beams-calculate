#include "VAE.h"
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

void viga_ap_emp::get_solicitaciones() {
	cout << "\nCalculando esfuerzos...";
	cout << "\n\t[+] Reaccion A = " << suma_reaccionA << " KN" << endl;
	cout << "\t[+] Reaccion B = " << suma_reaccionB + suma_reaccion_nudo_vol << " KN" << endl;
	cout << "\t[+] Flecha maxima= " << _flechaMaxima << " *(E*I)*e-1 mm" << endl;
}
void viga_ap_emp::Momento_en_el_apoyo() {
	if (M != 0) {
		M *= -1;
		vector<double> CC((int)(luz * 1000 + 1));
		vector<double> CE((int)(luz * 1000 + 1));
		vector<double> CF((int)(luz * 1000 + 1));
		double incremento = 0.001, x = 0;

		_DiagCortante.resize((int)(luz * 1000 + 1));
		_Diagflectores.resize((int)(luz * 1000 + 1));
		_DiagElastica.resize((int)(luz * 1000 + 1));
		for (unsigned int x = 0; x < (int)1000 * luz + 1; x++) {
			CC[x] = M / luz;
			CE[x] = (-(M * luz) / (6 * E * I)) * (luz - (x * incremento)) * (1 - pow(((luz - (x * incremento)) / luz), 2));
			CF[x] = -M * (1 - (x * incremento) / luz);
		}
		CC = invertirEjeY(CC);
		CE = invertirEjeY(CE);
		CF = invertirEjeY(CF);
		for (unsigned int x = 0; x < (int)1000 * luz + 1; x++) {
			_DiagCortante[x] -= CC[x];
			_DiagElastica[x] += CE[x];
			_Diagflectores[x] += CF[x];
		}
		//ESTAS REACCIONES SALEN DEL VECTOR DE DIAGRAMAS DONDE ESTAN SUMADAS TANTO LA CARGA COMO EL GIRO
		this->_reaccionA = _DiagCortante[0];
		this->_reaccionB = abs(_DiagCortante.back());
		this->_momento_maximo = buscarMayor(_Diagflectores);
		this->_flechaMaxima = buscarMayor(_DiagElastica);
	}
		//suma_reaccion debe valer 0 en el primer calculo, cada vuelta suma su valor en la var global
		suma_reaccionA += _reaccionA;
		suma_reaccionB += _reaccionB;
}
void viga_ap_emp::continua_generica(double tramo, double inicial, double final) {
	_suma_giroA =0;
	_suma_giroB =0;
	 viga::continua_generica(tramo, inicial, final);
	 M = Mmax_vol != 0 ? Mmax_vol : 1; 
	 Momento_en_el_apoyo(); }
void viga_ap_emp::variable_generica(double tramo, double Qi, double Qf, double inicial, double final) {
	 viga::variable_generica(tramo, Qi, Qf, inicial, final);
	 M = Mmax_vol != 0 ? Mmax_vol : 1; 
	 Momento_en_el_apoyo(); }

	