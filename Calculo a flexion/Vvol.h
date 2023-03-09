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

class viga_vol : public viga {
public:
	//constructor heredado
	viga_vol();
	using viga::viga;

	void get_solicitaciones() override;

	//SETTERS
	inline void set_longitud_voladizo(double longitud) { _luz = longitud; }
	inline void add_diagramaCortante( const double &valor){_DiagCortante.push_back(valor);}
	inline void add_diagramaFlectores(const double &valor){_Diagflectores.push_back(valor);}
	inline void add_diagramaElastica( const double &valor) {_DiagElastica.push_back(valor);}

	inline void set_diagramaCortante( double valor, int posicion) { _DiagCortante [posicion] += valor; }
	inline void set_diagramaFlectores(double valor, int posicion) { _Diagflectores[posicion] += valor; }
	inline void set_diagramaElastica (double valor, int posicion) { _DiagElastica [posicion] += valor; }

	//GETTERs heredados
	inline double get_long_voladizo() { return _luz; }


	void carga_puntual_descentrada();			//1
	void Carga_Repartida_uniforme();			//3
	void Momento_centro_del_vano();			//8

	void carga_puntual_generica_vol(double a, double Q);
	void continua_generica();
	void variable_generica();

private:
	double _luz;
};
