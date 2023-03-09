#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <math.h>

using namespace std;

//PARTE PRIMERA
extern vector<double> posicion_apoyos;
extern vector<double> distancia_vanos;
extern const double incremento;
extern double luz; //esta variable ira cambiando en funcion del tramo en el que nos encontremos
extern double numEcElast;
extern double E;
extern double I;
extern double Q;
extern double M;
extern double momento_inicial;
extern double momento_inicial_izquierda;
extern double momento_inicial_derecha;
extern short int contador;

extern double Mmax_vol;

extern double longitud_voladizo;

extern double suma_reaccionA;
extern double suma_reaccionB;
extern double suma_reaccion_nudo_vol;
extern vector <double> suma_DiagCortante;
extern vector <double> suma_Diagflectores;
extern vector <double> suma_DiagElastica;


extern vector<double> auxCortante;
extern vector<double> auxFlector;
extern vector<double> auxElastica;



//ESTRUCTURA DE LAS VARIABLES QUE PODEMOS CALCULAR DE LOS PRONTUARIOS.
class viga {
public:
	//constructor
	viga();
	~viga();

	//Setters
	virtual void	imprimir_momento_unico();
	virtual void	imprimir_momentos();
	virtual double  imprimir_CPCV();
	virtual double  imprimir_Cpuntual();
	virtual void	imprimir_distancias(double& inicial, double& final);



	//GETTERS
	virtual void get_solicitaciones();

	inline virtual double get_ReaccionA() { return _reaccionA; }
	inline virtual double get_ReaccionB() { return _reaccionB; }
	inline virtual double get_Cortante() { return _cortante; }
	inline virtual double get_MomentoMaximo() { return _momento_maximo; }
	inline virtual double get_FlechaMaxima() { return _flechaMaxima; }
	inline virtual double get_mf_x() { return _mf_x; }
	inline virtual double get_ecuacion_elastica() { return _ecuacion_elastica; }
	inline virtual vector<double> get_diagramaCortante() { return this->_DiagCortante; }
	inline virtual vector<double> get_diagramaFlectores(){ return this->_Diagflectores; }
	inline virtual vector<double> get_diagramaElastica() { return this->_DiagElastica; }
	inline virtual double get_cargaTotal() { return _CP + _CV; }
	inline virtual double get_giroA() { return _giroA; }
	inline virtual double get_giroB() { return _giroB; }


	//SETTERS
	inline virtual void reset_diagramaCortante()  {_DiagCortante.resize(0); }
	inline virtual void reset_diagramaFlectores() {_Diagflectores.resize(0); }
	inline virtual void reset_diagramaElastica()  {_DiagElastica.resize(0);}

	//PRONTUARIOS
	virtual void carga_puntual_generica(double a, double Q);
	virtual void continua_generica(short int tramo, double inicial, double final);
	virtual void variable_generica(short int tramo, double Qi,double Qf,double inicial, double final);


protected:
	double _reaccionA;
	double _reaccionB;
	double _cortante;
	double _momento_maximo;
	double _flechaMaxima;
	double _mf_x;
	double _ecuacion_elastica;
	vector<double> _DiagCortante;
	vector<double> _Diagflectores;
	vector<double> _DiagElastica;
	double _CP;
	double _CV;
	double _giroA;
	double _giroB;
	double _suma_giroA;
	double _suma_giroB;
};




//PARTE SEGUNDA
extern string buscarPerfil, buscarValor;
extern int posicionfila, posicioncolumna;
extern int opc, opc2;

 
//densidad del acero: 7850 kg/m3
extern int hay_voladizo; //Usamos esta variable para saber el numero de voladizos que hay
extern bool copia_de_datos;
extern bool rep;
extern char opcVigaSimetrica, vano;


//TABLAS PARA CALCULO A FLEXION
extern double caracMecanicasIPE[18][13];
extern double caracFisicasIPE[18][7];
extern vector <string> IPE;

extern double caracMecanicasIPN[21][13];
extern double caracFisicasIPN[21][7];
extern vector <string> IPN;

extern double caracMecanicasHE[38][13];
extern double caracFisicasHE[38][7];
extern vector <string> HE;

extern double caracMecanicasUPE[14][15];
extern double caracFisicasUPE[14][7];
extern vector <string> UPE;

extern double caracMecanicasUPN[18][15];
extern double caracFisicasUPN[18][8];
extern vector <string> UPN;

extern vector <string> propiedades;
