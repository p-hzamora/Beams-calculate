#include "VEE.h"
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

void viga_emp_emp::get_solicitaciones() {
	cout << "\nCalculando esfuerzos...";
	cout << "\n\t[+] Reaccion A = " << suma_reaccionA + suma_reaccion_nudo_vol << " KN" << endl;
	cout << "\t[+] Reaccion B = " << suma_reaccionB + suma_reaccion_nudo_vol << " KN" << endl;
	cout << "\t[+] Flecha maxima= " << _flechaMaxima << " *(E*I)*e-1 mm" << endl;
}

void viga_emp_emp::Dos_momentos_invertidos_en_apoyos() {
	if (M != 0) {
		momento_inicial_izquierda= -M;
		momento_inicial_derecha =  -M;
		vector<double> CC;
		vector<double> CE;
		vector<double> CF;
		double x = 0;
		this->_reaccionA = (momento_inicial_izquierda - momento_inicial_derecha) / luz;
		this->_flechaMaxima = -(momento_inicial * pow(luz, 2)) / (9 * sqrt(3) * E * I);
		do {
			CC.push_back(this->_reaccionA);
			CE.push_back(((momento_inicial_izquierda * x) / (6 * E * I)) * (luz - x) * (1 + ((luz - x) / luz) + (momento_inicial_derecha / momento_inicial_izquierda) * (1 + x / luz)));
			CF.push_back(-(momento_inicial_izquierda / luz) * (luz - x) - (momento_inicial_derecha / luz) * x);
			x += incremento;
		} while (x <= luz + 0.0000000001);
		for (unsigned int x = 0; x < (int)1000 * luz + 1; x++) {
			_DiagCortante[x] -= CC[x];
			_DiagElastica[x] += CE[x];
			_Diagflectores[x] += CF[x];
		}
		this->_reaccionA = _DiagCortante[0];
		this->_reaccionB = abs(_DiagCortante.back());
		this->_momento_maximo = buscarMayor(_Diagflectores);
		this->_flechaMaxima = buscarMayor(_DiagElastica);
	}
	//Lo hago para que la ecuacion de la elastica cuadrase en el caso de cpuntual en los extremos del voladizo si no sirve QUITARLO
	invertirEjeX_eficiente(_DiagElastica);
	//suma_reaccion debe valor 0 en el primer calculo, cada vuelta suma su valor en la var global
	suma_reaccionA += _reaccionA;
	suma_reaccionB += _reaccionB;
}
void viga_emp_emp::continua_generica(double tramo, double inicial, double final) {
	viga::continua_generica(tramo, inicial, final);
	M = Mmax_vol != 0 ? Mmax_vol : M;
	Dos_momentos_invertidos_en_apoyos();
}
void viga_emp_emp::variable_generica(double tramo, double Qi, double Qf, double inicial, double final) {
	viga::variable_generica(tramo, Qi, Qf, inicial, final);
	M = Mmax_vol != 0 ? Mmax_vol : M;
	Dos_momentos_invertidos_en_apoyos();
}

//REVISR LAS FLECHAS