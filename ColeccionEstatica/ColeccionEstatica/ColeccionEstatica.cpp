// EstructuraEstatica.cpp : Defines the entry point for the console application.
//

//importa las librerias
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
using namespace std;

/*esta es la estructura de los datos q poseen los Productos*/
typedef struct T_Producto { // Es una estructura que define un Producto
	int Codigo;
	char Descripcion[50];
	float Precio;
	int Disponible;
	bool Activo;
} X;

const int Max = 100; // Definimos el maximo de productos que se pueden almacenar 
// const int Max = 10000;  como maximp 10000, a partir de 10000 se genera un error de memoria
int Ultimo = 0; // Ultimo es un contador que nos indica el ultimo elemento insertado en el arreglo

void CargaAutomaticaDatosProducto(int NCodigo, int NDescripcion, float NPrecio, int NDisponible, T_Producto& Pieza)
{
	cout << "insertando ...";

	char descrip[50];
	char texto[20] = "Producto_";

	Pieza.Codigo = NCodigo;

	_itoa_s(NDescripcion, descrip, 50, 10); // Convierte el numero de descripcion a texto
	strcat_s(texto, descrip); // Concatena el texto "Producto_" con el numero de descripcion
	strcpy_s(Pieza.Descripcion, 50, texto); // Copia el texto concatenado a la descripcion del Producto

	Pieza.Precio = NPrecio;
	Pieza.Disponible = NDisponible;
	Pieza.Activo = true;

}

void Listar(T_Producto Inventario[Max]) { // Listar los Productos almacenados en el arreglo Inventario
	system("CLS");
	int conta = 0;
	cout << "Listado de  Productos" << endl;
	for (int i = 0; i < Ultimo; i++) { // Recorre el arreglo Inventario hasta el ultimo elemento insertado
		if (Inventario[i].Activo) { // Verifica si el Producto esta activo
			cout << Inventario[i].Codigo << " " << Inventario[i].Descripcion << " " << Inventario[i].Precio << " " // Imprime los datos del Producto
				<< Inventario[i].Disponible << " " << endl; // Imprime los datos del Producto
			conta++; // Incrementa el contador de Productos listados
			if (conta == 7) { // Si se han listado 7 Productos, pausa la pantalla
				cout << "-----------------------------------" << endl;
				cout << "Presione cualquier tecla para continuar..." << endl;
				system("pause");
				system("CLS");

				conta = 0; // Reinicia el contador de Productos listados
			}
		}
	}
	system("pause");
}



int BuscarElemento(T_Producto Inventario[Max], int Cual) // Busca un Producto en el arreglo Inventario por su Codigo
{
	bool Encontro = false; // Variable para indicar si se encontro el Producto
	int Cont = 0; // Contador para recorrer el arreglo Inventario

	while ((!Encontro) && (Cont < Ultimo)) // Recorre el arreglo Inventario hasta encontrar el Producto o llegar al final del arreglo
	{
		if ((Inventario[Cont].Activo == true) && (Inventario[Cont].Codigo == Cual)) // Verifica si el Producto esta activo y si su Codigo coincide con el buscado
			Encontro = true;
		else
			Cont++;
	}

	if (Encontro == true) // Si se encontro el Producto
		return Cont; // Retorna el indice del Producto encontrado
	else
		return -1;// Si no se encontro el Producto, retorna -1

}
void InsertarElemento(T_Producto Inventario[Max], T_Producto Unidad) // Inserta un Producto en el arreglo Inventario
{
	Inventario[Ultimo] = Unidad; // Asigna el Producto Unidad al ultimo indice del arreglo Inventario
	Ultimo++; // Incrementa el contador de Productos insertado
}

void BorrarElemento(T_Producto Inventario[Max], int Cual) // Borra un Producto del arreglo Inventario por su Codigo
{
	int PorBorrar; // Variable para almacenar el indice del Producto a borrar
	PorBorrar = BuscarElemento(Inventario, Cual); // Busca el Producto en el arreglo Inventario por su Codigo

	if (PorBorrar != -1) // Si se encontro el Producto
		Inventario[PorBorrar].Activo = false; // Marca el Producto como inactivo

}


void main() {

	T_Producto PiezasFerreteria[Max]; // Arreglo de Productos de tipo T_Producto con un maximo de Max elementos
	T_Producto Elemento;
	int opcion = 0;

	while (opcion < 4) {

		system("CLS");//limpia la pantalla 
		//genera el menu de opciones
		cout << "******Menu principal******" << endl;
		cout << "1. Cargar Productos de Prueba" << endl;
		cout << "2. Listar Piezas " << endl;
		cout << "3. Borrar Piezas " << endl;
		cout << "4. Salir " << endl;
		cin >> opcion;//captura el numero introducido

		switch (opcion) { // evalua la opcion introducida

		case 1: // Opcion para insertar un Producto
			system("CLS");
			Ultimo = 0; // Reinicia el contador de Productos insertados
			for (int contador = 0; contador < 51; contador++) {
				CargaAutomaticaDatosProducto(contador, contador, contador, contador, Elemento);
				InsertarElemento(PiezasFerreteria, Elemento);
			}
			
			system("pause");
			break;

		case 2: // Opcion para listar los Productos
			system("CLS");
			Listar(PiezasFerreteria);
			break;
		case 3: // Opcion para borrar un Producto
			system("CLS");
			int CodigoEscogido;
			cout << "Digite el codigo del Producto a Borrar" << endl;
			cout << "" << endl;
			cout << "CodigoProducto:" << endl;
			cin >> CodigoEscogido;
			BorrarElemento(PiezasFerreteria, CodigoEscogido);
			break;

		}
	}
}

/*
******Menu principal******
1. Cargar Productos de Prueba
2. Listar Piezas
3. Borrar Piezas
4. Salir
1
insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...insertando ...Presione una tecla para continuar . . .
******Menu principal******
1. Cargar Productos de Prueba
2. Listar Piezas
3. Borrar Piezas
4. Salir
2
Listado de  Productos
0 Producto_0 0 0
1 Producto_1 1 1
2 Producto_2 2 2
3 Producto_3 3 3
4 Producto_4 4 4
5 Producto_5 5 5
6 Producto_6 6 6
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
7 Producto_7 7 7
8 Producto_8 8 8
9 Producto_9 9 9
10 Producto_10 10 10
11 Producto_11 11 11
12 Producto_12 12 12
13 Producto_13 13 13
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
14 Producto_14 14 14
15 Producto_15 15 15
16 Producto_16 16 16
17 Producto_17 17 17
18 Producto_18 18 18
19 Producto_19 19 19
20 Producto_20 20 20
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
21 Producto_21 21 21
22 Producto_22 22 22
23 Producto_23 23 23
24 Producto_24 24 24
25 Producto_25 25 25
26 Producto_26 26 26
27 Producto_27 27 27
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
28 Producto_28 28 28
29 Producto_29 29 29
30 Producto_30 30 30
31 Producto_31 31 31
32 Producto_32 32 32
33 Producto_33 33 33
34 Producto_34 34 34
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
35 Producto_35 35 35
36 Producto_36 36 36
37 Producto_37 37 37
38 Producto_38 38 38
39 Producto_39 39 39
40 Producto_40 40 40
41 Producto_41 41 41
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
42 Producto_42 42 42
43 Producto_43 43 43
44 Producto_44 44 44
45 Producto_45 45 45
46 Producto_46 46 46
47 Producto_47 47 47
48 Producto_48 48 48
-----------------------------------
Presione cualquier tecla para continuar...
Presione una tecla para continuar . . .
49 Producto_49 49 49
50 Producto_50 50 50
Presione una tecla para continuar . . .
******Menu principal******
1. Cargar Productos de Prueba
2. Listar Piezas
3. Borrar Piezas
4. Salir
3
Digite el codigo del Producto a Borrar

CodigoProducto:
1
******Menu principal******
1. Cargar Productos de Prueba
2. Listar Piezas
3. Borrar Piezas
4. Salir
4
*/

