// El programa funciona segun lo esperado. Hemos de mirar los momentos centrados ya que la grafica sale al reves, pero todos los valores son correctos

#include "VAA.h"
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

void viga_ap_ap::get_solicitaciones() {
	cout << "\nCalculando esfuerzos...";
	cout << "\n\t[+] Reaccion A = " << suma_reaccionA << " KN" << endl;
	cout << "\t[+] Reaccion B = " << suma_reaccionB  << " KN" << endl;
	cout << "\t[+] Flecha maxima= " << _flechaMaxima << " *(E*I)*e-1 mm" << endl;
}
void viga_ap_ap::continua_generica(double tramo, double inicial, double final) {
	viga::continua_generica(tramo,inicial,final);
	for (unsigned int i = 0; i < vano; i++) {
		suma_DiagCortante[i] += _DiagCortante[i];
		suma_Diagflectores[i] += _Diagflectores[i];
		suma_DiagElastica[i] += _DiagElastica[i];
	}
	suma_reaccionA += _reaccionA;
	suma_reaccionB += _reaccionB;

}
void viga_ap_ap::variable_generica(double tramo, double Qi, double Qf, double inicial, double final) {
	viga::variable_generica(tramo, Qi, Qf, inicial, final);
	suma_reaccionA += _reaccionA;
	suma_reaccionB += _reaccionB;

}
