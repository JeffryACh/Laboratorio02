// archivos_en_C.cpp : main project file VC2012


#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

struct cedula { // Estructura para guardar los datos de las personas
	int numero;
	char nombre[25];
	bool activo;
};

cedula arreglo[50];
int cont = 0;

void guardararchivo(cedula Arreglo[], int cont) {
	system("CLS");//limpia la pantalla
	cout << endl << endl;
	FILE* archcedulas; // primero se declara el puntero al archivo
	fopen_s(&archcedulas, "cedulas.txt", "w+"); // se abre el archivo en modo escritura, si no existe lo crea ya que es "w+"

	for (int y = 0; y < cont; y++) { // recorre el arreglo de cedulas
		if (Arreglo[y].activo == true) {//solo se guardaran aquellas personas que esten activas
			printf("Cedula: %i Nombre:  %s		-guardado- \n", arreglo[y].numero, arreglo[y].nombre); // imprime en pantalla los datos que se guardaran
			fprintf_s(archcedulas, "%s", Arreglo[y].nombre); // escribe el nombre en el archivo
			if (y == (cont - 1)) { fprintf_s(archcedulas, "\n%i", Arreglo[y].numero); }// se eliminan los enter al final del archivo de texto
			else fprintf_s(archcedulas, "\n%i\n\n", Arreglo[y].numero); // escribe el numero de cedula en el archivo
		}
	}
	fclose(archcedulas); // cierra el archivo
	cout << endl << " Presione una tecla para continuar..." << endl;
}

void cargararchivo(cedula arreglo[], int& cont) {//El arreglo no debe ingresar como referencia, pero el contador si para que su valor cambie respecto a lo que se hace en la funcion
	system("CLS");
	FILE* archcedulas;
	fopen_s(&archcedulas, "cedulas.txt", "r"); // abre el archivo en modo lectura
	if (archcedulas == NULL) { // si el archivo no existe o no se pudo abrir
		cout << "no se encontro el archivo" << endl;
	}
	else {
		while (!feof(archcedulas)) { // mientras no se llegue al final del archivo
			fscanf_s(archcedulas, "%s", arreglo[cont].nombre, 25);//cont al inicio esta en cero 
			fscanf_s(archcedulas, "%i", &arreglo[cont].numero); // lee el numero de cedula
			printf("\n\n  Cedula: %i Nombre:  %s		-cargado- \n", arreglo[cont].numero, arreglo[cont].nombre); // imprime en pantalla los datos que se cargan
			arreglo[cont].activo = true;// Activa de nuevo a la persona
			cont++;
		}
		fclose(archcedulas);
	}
	cout << endl << " Presione una tecla para continuar..." << endl;
}

void insertar(cedula arreglof[], int& cont) { // El arreglo no debe ingresar como referencia, pero el contador si para que su valor cambie respecto a lo que se hace en la funcion
	system("CLS");
	cout << endl << " ----------------  Ingresar persona  ----------------" << endl;
	cout << endl << " Digite el nombre de la persona: ";
	cin >> arreglof[cont].nombre;
	cout << endl << " Digite el numero de cedula: ";
	cin >> arreglof[cont].numero;
	arreglo[cont].activo = true;// activa a la persona
	cont++;
}

void buscar_nombre(cedula arreglo[], int cont) { // Esta funcion busca una persona por su nombre
	system("CLS");
	cout << endl << " ----------------  Buscar persona por nombre  ----------------" << endl << endl << endl;
	char cual[25]; // variable para guardar el nombre a buscar
	cout << " Digite el nombre que desea buscar: ";
	cin >> cual;
	cout << endl << endl;
	int i; // variable para recorrer el arreglo
	for (i = 0; i < cont; i++) { // recorre el arreglo de cedulas
		if ((strcmp(arreglo[i].nombre, cual) == 0) && (arreglo[i].activo == true)) {// compara el nombre y si esta activo
			cout << "El numero de cedula de " << cual << " es: " << arreglo[i].numero << endl;
			break; // si encuentra el nombre, imprime el numero de cedula y sale del ciclo
		}
	}
	if (i == cont) {// si no encuentra el nombre
		cout << " El nombre no ha sido ingresado o fue borrado" << endl; 
	}
}

void buscar_cedula(cedula arreglo[], int cont, int cual) { //misma logica que la funcion anterior pero ahora busca por cedula
	int i;
	for (i = 0; i < cont; i++) {
		if ((arreglo[i].numero == cual) && (arreglo[i].activo == true)) {
			cout << "El numero de cedula: " << cual << " corresponde a: " << arreglo[i].nombre << endl;
			break;
		}
	}
	if (i == cont) {
		cout << " El numero de cedula no ha sido ingresado o fue borrado" << endl;
	}
}

void listarcedulas(cedula arreglo[], int cont) { // Esta funcion lista todas las personas que estan activas
	system("CLS");
	cout << endl << " ----------------  Lista de personas  ----------------" << endl << endl;
	int numerador = 1;
	cout << "		# Cedula		Nombre" << endl << endl;
	if (cont == 0) { cout << endl << "		La lista esta vacia." << endl; } //si no hay personas en el arreglo
	else {
		for (int i = 0; i < cont; i++) { // recorre el arreglo de cedulas
			if (arreglo[i].activo == true) {
				cout << "	" << numerador << "	" << arreglo[i].numero << "		" << arreglo[i].nombre << endl;
				numerador++;
			}
		}
	}
	cout << endl << endl << " ************** Fin de la lista  ***************" << endl;
}

int buscarparaborrar(cedula arreglo[], int& cont) { // Esta funcion busca una persona por su nombre para borrarla
	system("CLS");
	cout << endl << " ----------------  Buscar persona para borrar  ----------------" << endl << endl;
	char cual[25];
	cout << " Digite el nombre que desea buscar para eliminar: ";
	cin >> cual;
	cout << endl << endl;
	int i; // variable para recorrer el arreglo
	for (i = 0; i < cont; i++) {
		if ((strcmp(arreglo[i].nombre, cual) == 0) && (arreglo[i].activo == true)) { // compara el nombre y si esta activo
			cout << endl << " Persona borrada con exito" << endl << endl;
			cont--;//decrementa el contador para que la cuenta de personas sea precisa
			return i;//retorna el numero de lugar en el que esta el nombre en el arreglo
		}
	}
	if (i == cont) {
		cout << " El nombre no ha sido ingresado o ya fue borrado" << endl;
		return -1;//retorna -1 ya q la funcion es tipo entero, y al ser llamada se esper un valor de regreso
	}
	else return -2;//Se escribe para evitar warning
}

void main() {
	bool menu = true;
	while (menu) {
		system("CLS");
		cout << endl << endl << "	-----------------	Menu Principal   -----------------" << endl << endl;
		cout << "		1. Agregar persona" << endl;
		cout << "		2. Buscar por nombre" << endl;
		cout << "		3. Buscar por cedula" << endl;
		cout << "		4. Listar todos" << endl;
		cout << "		5. Borrar una persona" << endl;
		cout << "		6. Guardar Arreglo a archivo" << endl;
		cout << "		7. Cargar Arreglo desde archivo " << endl;
		cout << "		8. Salir" << endl << endl;
		cout << "		Digite una opcion: ";
		int opcion = 0;
		cin >> opcion;
		switch (opcion) { // se usa un switch para seleccionar la opcion del menu
		case 1: {
			insertar(arreglo, cont); // llama a la funcion insertar para agregar una persona
			cout << endl << endl << " La persona fue ingresada correctamente." << endl << endl;
			cout << " Presione una tecla para continuar..." << endl;
			_getch(); // espera a que se presione una tecla para continuar
			break;
		}
		case 2: {
			buscar_nombre(arreglo, cont); // llama a la funcion buscar_nombre para buscar una persona por su nombre
			cout << endl << " Presione una tecla para continuar..." << endl;
			_getch();
			break;
		}
		case 3: {
			system("CLS");
			cout << endl << " ----------------  Buscar persona por #cedula  ----------------" << endl << endl << endl;
			int cual;
			cout << " Digite el numero de cedula que desea buscar: ";
			cin >> cual;
			cout << endl << endl;
			buscar_cedula(arreglo, cont, cual); // llama a la funcion buscar_cedula para buscar una persona por su cedula
			cout << endl << " Presione una tecla para continuar..." << endl;
			_getch();
			break;
		}
		case 4: {
			listarcedulas(arreglo, cont); // llama a la funcion listarcedulas para listar todas las personas que estan activas
			cout << endl << " Presione una tecla para continuar..." << endl;
			_getch();
			break;
		}
		case 5: {
			arreglo[buscarparaborrar(arreglo, cont)].activo = false;// desactiva persona
			cout << endl << " Presione una tecla para continuar..." << endl;
			_getch();
			break;
		}
		case 6: {
			guardararchivo(arreglo, cont); // llama a la funcion guardararchivo para guardar el arreglo en un archivo
			_getch();
			break;
		}
		case 7: { // opcion para cargar el arreglo desde un archivo
			if (cont != 0) {
				cout << endl << endl << "  Se perderan los cambios realizados en esta sesion," << endl; // advierte al usuario que se perderan los cambios si carga el archivo
				cout << "  desea continuar(S/N): ";
				char sino[2];
				cin >> sino;
				if ((strcmp(sino, "S") == 0) || (strcmp(sino, "s") == 0)) {
					cont = 0; // reinicia el contador para que se carguen los datos desde el archivo
					cargararchivo(arreglo, cont);
				}
				else cout << " No se cargaran datos guardados. " << endl; // si el usuario no quiere cargar el archivo, no hace nada
			}
			else cargararchivo(arreglo, cont); // si el contador es cero, no hay datos que perder, por lo que se carga el archivo directamente
			_getch();
			break;
		}

		case 8: { // opcion para salir del programa
			menu = false;
			system("CLS");
			cout << endl << endl << endl << endl << "			***********************************" << endl;
			cout << "			*                                 *" << endl;
			cout << "			*   *******  *******   *******    *" << endl;
			cout << "			*      *     *         *          *" << endl;
			cout << "			*      *     *****     *          *" << endl;
			cout << "			*      *     *         *          *" << endl;
			cout << "			*      *     *******   *******    *" << endl;
			cout << "			*                                 *" << endl;
			cout << "			***********************************" << endl << endl << endl;
			cout << " Presione una tecla para salir..." << endl;
			_getch();
			break;
		}
		default: { // si la opcion no es valida o no existe
			cout << endl << "La opcion digitada no exite" << endl << endl;
			cout << " Presione una tecla para continuar..." << endl;
			_getch();
		}
		}
	}
}

/*
Resultados:



		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 1

 ----------------  Ingresar persona  ----------------

 Digite el nombre de la persona: 1

 Digite el numero de cedula: 1


 La persona fue ingresada correctamente.

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion:
1

 ----------------  Ingresar persona  ----------------

 Digite el nombre de la persona: 2

 Digite el numero de cedula: 2


 La persona fue ingresada correctamente.

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 2

 ----------------  Buscar persona por nombre  ----------------


 Digite el nombre que desea buscar: 1


El numero de cedula de 1 es: 1

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 3

 ----------------  Buscar persona por #cedula  ----------------


 Digite el numero de cedula que desea buscar: 2


El numero de cedula: 2 corresponde a: 2

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 6


Cedula: 1 Nombre:  1            -guardado-
Cedula: 2 Nombre:  2            -guardado-

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 5

 ----------------  Buscar persona para borrar  ----------------

 Digite el nombre que desea buscar para eliminar: 2



 Persona borrada con exito


 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 4

 ----------------  Lista de personas  ----------------

				# Cedula                Nombre

		1       1               1


 ************** Fin de la lista  ***************

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 7


  Se perderan los cambios realizados en esta sesion,
  desea continuar(S/N): S


  Cedula: 1 Nombre:  1          -cargado-


  Cedula: 2 Nombre:  2          -cargado-

 Presione una tecla para continuar...


		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion:
4

 ----------------  Lista de personas  ----------------

				# Cedula                Nombre

		1       1               1
		2       2               2


 ************** Fin de la lista  ***************

 Presione una tecla para continuar...



		-----------------       Menu Principal   -----------------

				1. Agregar persona
				2. Buscar por nombre
				3. Buscar por cedula
				4. Listar todos
				5. Borrar una persona
				6. Guardar Arreglo a archivo
				7. Cargar Arreglo desde archivo
				8. Salir

				Digite una opcion: 8




						***********************************
						*                                 *
						*   *******  *******   *******    *
						*      *     *         *          *
						*      *     *****     *          *
						*      *     *         *          *
						*      *     *******   *******    *
						*                                 *
						***********************************


 Presione una tecla para salir...

*/

