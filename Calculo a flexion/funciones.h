#pragma once
#include "variables.h"
#include "Vvol.h"
#include "VAA.h"
#include "VAE.h"
#include "VEE.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <math.h>

using namespace std;
extern short int sumar_voladizo; // Usada en la funcion anadir_voladizo_global
extern viga_vol carga_voladizo;

void anadir_voladizo_global(viga_vol* voladizo);

bool comprobarSuma(vector<double> vec1, vector<double> vec2);
double buscarMayor(vector<double> vector);


//Declarar funciones 
void calcularSolicitacion(viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA);
bool sumar_diagramas( viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA, bool* _unaSolaCarga);
void print_suma_diagramas(bool _unaSolaCarga);
void copiar_datos_notepad(viga_emp_emp* VEE, viga_ap_emp* VAE, viga_ap_ap* VAA);
vector <double> invertirEjeX(vector<double> vec);
vector <double> invertirEjeY(vector<double> vec);

void invertirEjeX_eficiente(vector<double>& vec);
void invertirEjeY_eficiente(vector<double>& vec);
vector<float> valor0(const vector<double>& vec);

void sumarVanos(int posicion, viga_ap_emp* VAE, viga_emp_emp* VEE);



//Segunda parte
void mayuscula(string& palabra);
void mostrar_tabla();
void buscador_de_valores();
int comprobacionCortante(string tipoPerfil,double comprobar_Wpl, vector<string> perfil, double caracMecanicas[][13]);
int comprobacionCortanteUPE(string tipoPerfil, double comprobar_Wpl, vector<string> perfil, double caracMecanicas[][15]);
double coeficienteElasticidad(string tipoPerfil, int iteracionPerfiles);

