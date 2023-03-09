//#include "Stdafx.h"
#include "funciones.h"
#include "variables.h"
#include "VAA.h"
#include "VAE.h"
#include "VEE.h"
#include "Vvol.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include<Windows.h>
#include <math.h>

using namespace std;
#define PRINT_VANO(x) cout<<"\t "; for(int i=1;i<=x;i++){ cout << "____________________";} cout<<endl; cout << "\t/\\";for (int i = 0; i < x; i++) {cout<<"                  /\\";} cout << "\n\tX ---------->|        " << endl; 


#if !defined(PROPIEDADES)
#define PROPIEDADES cout<<"\t\t";for (unsigned int fila = 0; fila < propiedades.size; fila++) {cout << propiedades[fila] << "\t";}
#endif
#define CPDescentrada cout <<	"\n1.Carga puntual descentrada." << "\t\t\t\t\t\tDisponible en VOLADIZO" << endl;
#define DosCP cout <<			"\n2.Dos Cargas puntuales simetricas." << "\t\t\t\t\t-" << endl;
#define CRCentrada cout <<		"\n3.Carga repartida centrada (Xo-Xf)." << "\t\t\t\t\tDisponible en VOLADIZO "<<  endl;
#define CRUniforme cout <<		"\n4.Carga repartida uniforme." << "\t\t\t\t\t\tDisponible en VOLADIZO "<<  endl;
#define CAscV cout <<			"\n5.Carga Ascendente desde apoyo izq." << "\t\t\t\t\tDisponible en VOLADIZO"<< endl;
#define CDesV cout <<			"\n6.CARGA descendente hasta centro de vano." << "\t\t\t\tDisponible en VOLADIZO"<< endl;
#define DosCDesCV cout <<		"\n7.DOS CARGAS descendentes hasta centro vano." << "\t\t\t\t-" << endl;
#define DosCAscD cout <<		"\n8.Dos Cargas Ascendentes." << "\t\t\t\t\t\t-" << endl;
#define CDscVC cout <<			"\n9.Carga Descendente amplia vano completo." << "\t\t\t\tDisponible en VOLADIZO" << endl;
#define DosCAscT cout <<		"\n10.Dos Cargas Ascendentes trapecio." << "\t\t\t\t\t-" << endl;
#define MAp cout <<				"\n11.Momento en el apoyo." << "\t\t\t\t\t\t\t-" << endl;
#define DosMIA cout <<			"\n12.Dos momentos invertidos en los apoyos." << "\t\t\t\t-" << endl;
#define DosMomMS cout <<		"\n13.Dos momentos en el mismo sentido en apoyos." << "\t\t\t\t-" << endl;
#define MCVano cout <<			"\n14.Momento centro vano." << "\t\t\t\t\t\t\tDisponible en VOLADIZO" << endl;
#define CAsc_CV_VAE  cout <<	"\n15.Carga ascendente desde el centro del vano hasta EMPOTRAMIENTO." << "\t\t\tDisponible en VOLADIZO"<< endl; 
#define CDesc_CV_VAE cout <<	"\n16.Carga descendente desde el centro del vano hasta EMPOTRAMIENTO (carga variable)." << "\tDisponible en VOLADIZO"<< endl; 

#define	Cgenerica 		cout << "\n20.Carga CONTINUA generica" << "\t\t\t\t\t\tDisponible en VOLADIZO" << endl;
#define Vgenerica 		cout << "\n21.Carga VARIABLE generica" << "\t\t\t\t\t\tDisponible en VOLADIZO" << endl;


int main() {
	//VIGA para cargar las funciones de impresion de cargas
	viga viga;

	//VIGA APOYADA
	/*1*/  viga_ap_ap CPuntual_descentrada_VAA;
	/*2*/  viga_ap_ap Dos_CPuntuales_VAA ;
	/*4*/  viga_ap_ap CRepartida_uniforme_VAA ;
	/*7*/  viga_ap_ap Dos_CDescendentes_hasta_centro_vano_VAA ;
	/*8*/  viga_ap_ap Dos_CAscendentes_descentradas_VAA ;
	/*11*/ viga_ap_ap Momento_apoyo_VAA ;
	/*12*/ viga_ap_ap Dos_momentos_invertidos_apoyos_VAA ;
	/*13*/ viga_ap_ap Dos_momentos_iguales_en_apoyos_VAA ;
	/*14*/ viga_ap_ap Momento_centro_vano_VAA ;

	viga_ap_ap continua_generica_VAA;
	viga_ap_ap variable_generica_VAA;

	//VIGA APOYADA EMPOTRADA
	//Heredadas
	/*1*/	viga_ap_emp CPuntual_descentrada_VAE;
	/*2*/	viga_ap_emp Dos_CPuntuales_VAE ;
	/*4*/	viga_ap_emp CRepartida_uniforme_VAE ;
	/*7*/	viga_ap_emp Dos_CAscendentes_descentradas_VAE ;
	/*9*/	viga_ap_emp Momento_centro_vano_VAE ;

			viga_ap_emp continua_generica_VAE;
			viga_ap_emp variable_generica_VAE;

	//VIGA EMPOTRADA EMPOTRADA	
	/*1*/	viga_emp_emp CPuntual_descentrada_VEE;
	/*2*/	viga_emp_emp Dos_CPuntuales_VEE;
	/*4*/	viga_emp_emp CRepartida_uniforme_VEE;
	/*7*/	viga_emp_emp Dos_CDescendentes_hasta_centro_vano_VEE;
	/*8*/	viga_emp_emp Dos_CAscendentes_descentradas_VEE;
	/*11*/	viga_emp_emp Momento_centro_vano_VEE;

	viga_emp_emp continua_generica_VEE;
	viga_emp_emp variable_generica_VEE;

	//VIGA SIMPLE EN VOLADIZO
	/*1*/	viga_vol CPuntual_descentrada_vol;
	/*2*/	viga_vol CRepartida_centrada_vol ;
	/*3*/	viga_vol CRepartida_uniforme_vol ;
	/*4*/	viga_vol CAscendente_vol ;
	/*5*/	viga_vol CDescendente_vol ;
	/*6*/	viga_vol Dos_CAscendentes_descentradas_vol ;
	/*7*/	viga_vol Carga_Descendente_vano_completo ;
	/*8*/	viga_vol Momento_centro_vano_vol ;
	/*9*/	viga_vol CAscendente_CV_a_emp_vol ;
	/*10*/	viga_vol CDescendente_CV_a_emp_vol ;

	viga_vol continua_generica_vol;
	viga_vol variable_generica_vol;



	//carga general donde almacenaremos todas las cargas en los voladizos
	bool unaSolaCarga = true;
	int opcion_vano;
	int opcion_voladizo;
	

	//SEGUNDA PARTE
	double Qd = 1;
	double Mpl = 1;
	double Wpl = 1;
	double Wel = 1;
	double Mmaxd = 1;
	double flecha_mayorada = 1;
	double Vd = 1;
	double Mestat = 1;
	double fyd = 1;
	double fy = 1;
	double coefMayoracion = 1.05;
	bool vuelta = false;


	cout << "\t\t_________________________________________________________________" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t\t|\t\tDIMENSIONADO DE VIGAS EN VANO \t\t\t|" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t\t|\tCalculo de todas las solicitaciones en una viga \t|" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t\t|\tPablo Hernandez Zamora\t\t\t\t\t|" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t\t_________________________________________________________________" << endl;

	cout << "\n\n_____________________ESFUERZOS EN VIGAS APOYADAS O EMPOTRADAS_____________________________" << endl;
	cout << "\n0. NO AGREGA CARGAS\n" << endl;
	/*1 */	CPDescentrada
	/*4 */  CRUniforme
	/*8 */  DosCAscD
	/*11*/  MAp
	/*12*/  DosMIA
	/*13*/  DosMomMS
	/*14*/  MCVano
	cout << "\n";

	/*20*/  Cgenerica
	/*21*/  Vgenerica

	cout << "\n\n\n";
	cout << "***************************************  Calculo de diagramas  ***************************************" << endl;

	//vano = 's';
	//hay_voladizo = 1;
	//longitud_voladizo = 2;
	//opcion_voladizo = 4;
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	//cout << "\nLa viga dispone de voladizos? (s\\n): "; cin >> vano;
	if (vano == 's' || vano == 'S') {
	repetirVoladizo:
		cout << "\nNumero de voladizos?: "; cin >> hay_voladizo;
		if (!(hay_voladizo ==1 || hay_voladizo==2)) {
			cout << "\t[+] El numero de voladizos ha de ser 1 o 2" << endl;
			goto repetirVoladizo;
		}
		cout << "\nDistancia del voladizo: "; cin >> longitud_voladizo;
		cout << "\n\t_____________________" << endl;
		cout << "\t                    /\\" << endl;
		cout << "\tX ---------->|        "<< endl;
		cout << "\nTipo de esfuerzo sobre el voladizo: "; cin >> opcion_voladizo;
	aquivoladizo:
		//viga_vol copia;
		Mmax_vol = 0;
		viga_vol* datos = NULL;
		switch (opcion_voladizo) {
			case 20: {
				cout << "\nCargas en continuas en voladizo" << endl; viga.imprimir_CPCV();
				continua_generica_vol.continua_generica();
				anadir_voladizo_global(&continua_generica_vol);
				datos = &continua_generica_vol;
				sumar_voladizo++; break;
			}
			case 21: {
				cout << "\nCargas variables en voladizo" << endl;
				variable_generica_vol.variable_generica();
				anadir_voladizo_global(&variable_generica_vol);
				datos = &variable_generica_vol;
				sumar_voladizo++; break;
			}
		}
		if (opcion_voladizo != 0) { suma_reaccion_nudo_vol += abs(datos->get_ReaccionB()); }
	}
	unsigned short int numero_apoyos = 2;
	double Qi = 0, Qf = 0;
	if (vuelta == true) { goto aqui; }
	cout << "\n\t __________________________________________" << endl;
	cout << "\t/\\                   /\\                   /\\" << endl;
	cout << "\tX ---------->|        " << endl;
	cout << "\n\nDistancia total de la viga (sin voladizos) [m]: "; cin >> luz;
	//luz = 20;
	cout << "Introduce el numero total de apoyos [Uds]: "; cin >> numero_apoyos;
	PRINT_VANO(numero_apoyos - 1);
	//numero_apoyos = 7;
	posicion_apoyos.resize(numero_apoyos);
	//posicion_apoyos = { 0,5,7,10,13,15,20 };
	int posicion_int;
	for (unsigned int i = 0; i < numero_apoyos; i++) {
		cout << "Posicion del apoyo " << i + 1 << " [m] = "; cin >> posicion_apoyos[i];
	}
	distancia_vanos.resize(numero_apoyos - static_cast<int> (1));
	distancia_vanos[0] = posicion_apoyos[1];
	for (unsigned int i = 1; i <= distancia_vanos.size() - 1; i++) {
		distancia_vanos[i] = posicion_apoyos[i + 1] - posicion_apoyos[i];
	}
	suma_DiagCortante.resize ((int)(luz*1000+numero_apoyos));
	suma_Diagflectores.resize((int)(luz*1000+numero_apoyos));
	suma_DiagElastica.resize ((int)(luz*1000+numero_apoyos)); 
	cout << "\nTipo de esfuerzos en el vano: "; cin >> opcion_vano;
	//opcion_vano = 20;
	double inicial;
	double final;
	
	//viga.imprimir_cargas_variables(Qi, Qf);
aqui:
	switch (opcion_vano) {
 	case 20: {
		cout << "\nCarga CONTINUA generica" << endl;
		viga.imprimir_CPCV();	
		viga.imprimir_distancias(inicial, final);
		if (hay_voladizo == 0) {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				continua_generica_VAE.continua_generica(i,inicial,final);
				//copiar_datos_notepad(NULL, &continua_generica_VAE, NULL);
				//continua_generica_VAA.get_solicitaciones();
				posicion_int = (int)(posicion_apoyos[i] * 1000);
				sumarVanos(posicion_int, &continua_generica_VAE,NULL);
			}
		}
		else if (hay_voladizo == 1) {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				continua_generica_VAE.continua_generica(i, inicial, final);
				//copiar_datos_notepad(NULL, &continua_generica_VAE, NULL);
				//continua_generica_VAE.get_solicitaciones();
			}
		}
		else {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				continua_generica_VEE.continua_generica(i, inicial, final);
				copiar_datos_notepad(&continua_generica_VEE, NULL, NULL);
				//continua_generica_VEE.get_solicitaciones();
			}
		}
		//calcularSolicitacion(NULL, &CDescendente_centro_vano_a_empotramiento_VAE, NULL);
		sumar_diagramas(&continua_generica_VEE, &continua_generica_VAE, &continua_generica_VAA, &unaSolaCarga);
		break;
	}
	case 21: {
		cout << "\nCarga VARIABLE generica" << endl;
		if (hay_voladizo == 0) {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				variable_generica_VAA.variable_generica(i, Qi, Qf, inicial, final);
				copiar_datos_notepad(NULL, NULL, &variable_generica_VAA);
				variable_generica_VAA.get_solicitaciones();
			}
		}
		else if (hay_voladizo == 1) {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				variable_generica_VAE.variable_generica(i, Qi, Qf, inicial, final);
				copiar_datos_notepad(NULL, &variable_generica_VAE, NULL);
				variable_generica_VAE.get_solicitaciones();
			}
		}
		else {
			for (unsigned int i = 0; i < distancia_vanos.size(); i++) {
				variable_generica_VEE.variable_generica(i, Qi, Qf, inicial, final);
				copiar_datos_notepad(&variable_generica_VEE, NULL, NULL);
				variable_generica_VEE.get_solicitaciones();
			}
		}
		sumar_diagramas(&variable_generica_VEE, &variable_generica_VAE, &variable_generica_VAA, &unaSolaCarga);
break;
	}
	}

	//quitar cuando acabemos de depurar el codigo
	//print_suma_diagramas(unaSolaCarga);

	char nuevaSolicitacion = 'n';
	cout << "\nDesea recalcular otro esfuerzo diferente? (s\\n): "; cin >> nuevaSolicitacion;
	contador++;
	if (nuevaSolicitacion == 's' || nuevaSolicitacion == 'S') {
		//resetear los esfuerzos que ya hayamos utilizado 
		vuelta = true;
		opcion_voladizo = 0;
		if (vano != 'n') {
			cout << "\n[+] Elija otro esfuerzo sobre el voladizo: "; cin >> opcion_voladizo;
		}
		cout << "[+] Elija otro esfuerzo sobre la viga: "; cin >> opcion_vano;
		goto aquivoladizo;

	}
	print_suma_diagramas(unaSolaCarga);

	//double usuario;
	//cout << "Donde quiere calcular la comprobacion de la flecha en X: "; cin >> usuario;
	//usuario *= 1000;
	Vd = abs(buscarMayor(suma_DiagCortante));
	Mmaxd = abs(buscarMayor(suma_Diagflectores));
	flecha_mayorada = abs(buscarMayor(suma_DiagElastica));
	string nombre = "vano";
	if (hay_voladizo != 0) {
		unsigned int dist_apoyoB = (int)(luz * 1000);
		bool mayor = abs(suma_DiagCortante[dist_apoyoB]) > suma_DiagCortante[dist_apoyoB + 1] ? true : false;

		switch (mayor) {
		case true: nombre = "vano"; break;
		case false: nombre = "voladizo"; break;
		}
	}
	double Ra;
	double Rb = suma_reaccionB + suma_reaccion_nudo_vol;
	if (hay_voladizo == 0 || hay_voladizo == 1) { Ra = suma_reaccionA; }
	else { Ra = suma_reaccionA + suma_reaccion_nudo_vol; };

	cout << "\nCalculando esfuerzos ultimos totales..." << endl;
	cout << "\t[+] Reaccion A = " << Ra << " KN" << endl;
	cout << "\t[+] Reaccion B = " << Rb << " KN" << endl;
	cout << "\t[+] Cortante maximo es de " << Vd << " KN perteneciente al " << nombre << endl;
	cout << "\t[+] Momento maximo= " << Mmaxd << " m*KN" << endl;
	cout << "\t[+] Flecha maxima= " << flecha_mayorada << " *(E*I)*e-1 mm\n" << endl;

	cout << "\t[+] Carga total soportada= " << Ra + Rb << " KN" << endl;
	cout << "\n\n";

	vector<float> cortantef, momentof, elasticaf;
	cortantef = valor0(suma_DiagCortante);
	momentof = valor0(suma_Diagflectores);
	elasticaf = valor0(suma_DiagElastica);
	cout << "\t[+] Posicion donde el cortante es 0:";	for (const auto& item : cortantef) { printf("	%.3f m", item); }
	cout << "\n\t[+] Posicion donde el momento  es 0:";	for (const auto& item : momentof) { printf("	%.3f m", item); }
	cout << "\n\t[+] Posicion donde la elastica es 0:";	for (const auto& item : elasticaf) { printf("	%.3f m", item); }

	double numEcElast;
	nuevaSolicitacion = 'n';
	double cortante, momento, elastica;
	for (;;) {
		cout << "\n\nDesea conocer alguna posicion en \"X\" de las solicitaciones? (s\\n): "; cin >> nuevaSolicitacion;
		if (nuevaSolicitacion == 's' || nuevaSolicitacion == 'S') {
		numEcElastMAYOR:
			cout << "\nPosicion en X [m]: "; cin >> numEcElast;
			if (numEcElast > luz) {
				cout << "\tEl numero introducido es mayor a la luz de la viga." << endl;
				goto numEcElastMAYOR;
			}

			cortante = suma_DiagCortante[(int)(numEcElast * 1000)];
			momento = suma_Diagflectores[(int)(numEcElast * 1000)];
			elastica = suma_DiagElastica[(int)(numEcElast * 1000)];

			if (cortante > 0 && cortante < 0.0000000001) { cortante = 0; }

			cout << "El cortante en (" << numEcElast << ") es = " << cortante << " KN" << endl;
			cout << "El momento en (" << numEcElast << ") es = " << momento << " m*KN" << endl;
			cout << "La elastica en (" << numEcElast << ") es = " << elastica << " *(E*I)*e-1 mm" << endl;
		}
		else { break; }
	}
	char momento_elegir;
	double momento_valor = 0.0;
	for (;;) {
		cout << "\n\nDesea conocer la posicion del Md en \"X\" del vano ? (s\\n): "; cin >> momento_elegir;
		if ((momento_elegir == 's' || momento_elegir == 'S')) {
			vector<double> copia;
			cout << "\nValor del Md [m*KN]: "; cin >> momento_valor;
			if (momento_valor > Mmaxd) { cout << "El momento es superior al M.max"<<endl; break; }
			double itera;
			for (unsigned int i = 0; i < suma_Diagflectores.size(); i++) {
				if (momento_valor <= suma_Diagflectores[i]) {
					itera = i;
					cout << "El momento de " << momento_valor << " m*KN por la izq en el vano se encuentra en " << itera/1000 << " m" << endl;
					break;
				}
			}
			copia = invertirEjeY(suma_Diagflectores);
			short int num;
			enum numero { caso1=1, caso2, caso3 };
			if (hay_voladizo == 0) { num= caso1;}
			else if(hay_voladizo == 1) { num= caso2;}
			else { num= caso3; }

			for (unsigned int i = 0; i < copia.size(); i++) {
				if (momento_valor <= copia[i]) {
					itera = i;
					cout << "El momento de " << momento_valor << " m*KN por la decha en el vano se encuentra en " << (double)((suma_Diagflectores.size()- num)/1000) - (itera / 1000) << " m" << endl;
					break;
				}
			}
		}
		else { break; }
	}
	int diagramas;
	char bucle2='n';
	for (;;) {
		cout << "\nDesea volver a mostrar un diagrama? (s/n): "; cin >> bucle2;
		if (bucle2 == 's') {
			cout << "\nElija el diagrama: "; cin >> diagramas;

			switch (diagramas) {
			case 1:system("start \"\" \"C:\\Diagramas\\Diagrama de cortantes.py\""); break;
			case 2:system("start \"\" \"C:\\Diagramas\\Diagrama de momentos.py\""); break;
			case 3:system("start \"\" \"C:\\Diagramas\\Diagrama de flechas.py\"");  break;
			}
		}
		else {
			break;
		}
	}

	//==============================================================================================================================
	
	cout << "\n*************************** Calculo de ELU y agotamiento de las secciones ***************************\n" << endl;
	string tipoPerfil;
	int seleccion=1;
	cout << "Indique el tipo de perfil (IPE,UPE,HE,IPN,UPN) del que se trata: "; cin >> tipoPerfil;
	mayuscula(tipoPerfil);
	if (tipoPerfil == "IPE") { seleccion = 1; }
	else if (tipoPerfil == "IPN") { seleccion = 2; }
	else if (tipoPerfil == "HE" ) { seleccion = 3; }
	else if (tipoPerfil == "UPE") { seleccion = 4; }
	else if (tipoPerfil == "UPN") { seleccion = 5; }
	printf("\n\n********************** COMPROBACION EN ELU ************************\n");
	cout << "Introduce el valor numerico del tipo de acero de la viga: "; cin >> fy;

	//si las cargas son desfavorables... Tabla 4.1b Coeficientes parciales de seguridad de las acciones para ELU 

	double coeficiente = pow(10, 6);
	int iteracionPerfiles=0;
	double h = 0;
	double tw = 0;
	double Vpl_Rd =0;
	double flechaAdmisible = 0;

	Qd = viga.get_cargaTotal();			// NO ESTA BIEN LA FUNCION, HA DE ACTUALIZAR  TODOS LOS CAMBIOS.
	fyd = fy / coefMayoracion;
	double comprobar_Wpl = Mmaxd / fyd * 1000; //1000 para pasar a cm3 y commpararlos con las tablas

	printf("\n\n********************** TIPOS DE COMPROBACION ************************\n"); \
	cout << "\n1.PREDIMENSION DEL PERFIL A FLEXION." << endl;
	cout << "2.COMPROBACION A CORTANTE." << endl;
	cout << "3.COMPROBACION POSIBLES SECCION Md + Vd." << endl;
	cout << "4.COMPROBACION DE FLECHAS." << endl;
	printf("\nPulse 5 para salir.\n\n");
	for (;;) {
		printf("\nElija una opcion: "); cin >> opc;
		switch (opc) {
		case 1:
			switch (seleccion) {
			case 1:	iteracionPerfiles = comprobacionCortante(tipoPerfil, comprobar_Wpl, IPE, caracMecanicasIPE); break;
			case 2:	iteracionPerfiles = comprobacionCortante(tipoPerfil, comprobar_Wpl, IPN, caracMecanicasIPN); break;
			case 3: iteracionPerfiles = comprobacionCortante(tipoPerfil, comprobar_Wpl, HE, caracMecanicasHE); break;
			case 4: iteracionPerfiles = comprobacionCortanteUPE(tipoPerfil, comprobar_Wpl, UPE, caracMecanicasUPE); break;
			case 5: iteracionPerfiles = comprobacionCortanteUPE(tipoPerfil, comprobar_Wpl, UPN, caracMecanicasUPN); break;
			}
			break;
		case 2:
			h = caracFisicasIPE[iteracionPerfiles][1];	// 1 hace referencia a la posicion en la matriz de datoFisicosIPE
			tw = caracFisicasIPE[iteracionPerfiles][3]; // 3 hace referencia a la posicion en la matriz de datoFisicosIPE
			Vpl_Rd = incremento * h * tw * (fyd / sqrt(3)); // 0.001 para pasar de N a KN		lo que soporta el perfil
			if (Vd <= Vpl_Rd) {
				cout << "El perfil elegido es valido." << endl;
				if (Vpl_Rd / 2 > Vd) {
					cout << "No debemos realizar el punto 3.\"COMPROBACION POSIBLES SECCION Md + Vd\" ya que el _cortante mayorado es menor al que soporta el perfil." << endl;
				}
			}
			else {
				cout << "\nEl perfil no cumple la normativa." << endl;
				//iteracionPerfiles++;
			}
			break;
		case 3:
			cout << "en vigas apoyadas es muy raro este caso" << endl;
			//en vigas apoyadas es muy raro su comprobacion pero si en los casos que la viga tenga un voladizo
			break;
		case 4:
			cout << "1.Integridad." << endl;
			cout << "2.Apariencia" << endl;
			cout << "3.Confort." << endl;
			cout << "\nElija el tipo de fleha que desea estudiar: "; cin >> opc2;
			switch (opc2) {
			case 1:
				E = 210'000; //MPa = 1N/mm^2
				double CV;
				cout << "Ingrese la CV: "; cin >> CV;
				printf("integridad\n");
				flechaAdmisible = (double)(luz * 1000) / 400;
				flecha_mayorada *= coeficienteElasticidad(tipoPerfil, iteracionPerfiles)/Q*CV;	//usamos *= porque en la funcion lo calculamos como 1/E*I
				cout << "La flecha myorada " << flecha_mayorada << " es menor a " << flechaAdmisible << endl;
				break;
			case 2:
				printf("Apariencia\n");
				break;
			case 3:
				printf("confort\n");
				break;
			};
			//case 5:
			//	break;
		};
		if (opc == 5) {
			cout << "Saliendo...";
			break;
		}
	}
	char mostrar = 'n';
	cout << "\nDesea mostrar las tablas de perfiles?: "; cin >> mostrar;
	if (mostrar == 's') {
		mostrar_tabla();
	}
	char verifica = 'n';
	cout << "\nDesea buscar un perfil (s\\n): "; cin >> verifica;
	if (verifica == 's') {
		cin.ignore();
		buscador_de_valores();
	}
	system("pause");
	return 0;
}