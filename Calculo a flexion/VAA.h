#pragma once
#include "variables.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include<Windows.h>
#include <math.h>

using namespace std;

class viga_ap_ap: public viga{
public:
	//constructor heredado
	using viga::viga;

	void get_solicitaciones() override;

	//DECLARACION DE FORMULAS DE PRONTUARIOS

	void continua_generica(double tramo, double inicial, double final);
	void variable_generica(double tramo, double Qi, double Qf, double inicial, double final);


};

