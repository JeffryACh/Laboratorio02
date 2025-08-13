/*
* Laboratorio02
*
* @Authors: 
*   - Jeffry Araya Ch.
*   - Federick Fernadez C.
*   - Juan J. Rojas
*
* Created: 12/08/2025 13:25
*
* Modified: 12/08/2025 14:55
*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>


using namespace std;

/*esta es la estructura de los datos q poseen los Productos*/
/*
* struct T_Producto
* - int Codigo: Codigo del Producto
* - char Descripcion[50]: Descripcion del Producto
* - float Precio: Precio del Producto
* - int Disponible: Cantidad Disponible del Producto
* - bool Activo: Indica si el Producto esta activo o no
*/
typedef struct T_Producto 
{
	int Codigo;
	char Descripcion[50];
	float Precio;
	int Disponible;
	bool Activo;
} X; // El alias X es opcional, se puede usar directamente T_Producto


// Definicion de constantes
const int Max = 100; 
int Ultimo = 0;

/*
* Esta funcion captura los datos de un Producto y los almacena en la estructura T_Producto.
* Solicita al usuario que ingrese el Codigo, Descripcion, Precio y Cantidad Disponible del Producto.
* @param:
*	- T_Producto& Pieza: Referencia a la estructura donde se almacenaran los datos del Producto.
* 
* @return:
*	+ void: No retorna ningun valor, los datos se almacenan directamente en la estructura pasada por referencia.
*/
void CapturarElemento(T_Producto& Pieza)
{
	system("CLS");
	cout << "Captura de una Pieza" << endl;
	cout << "" << endl;

	system("CLS");
	cout << "Captura de una Pieza" << endl;
	cout << "" << endl;
	cout << "CodigoProducto:";
	cin >> Pieza.Codigo;  cout << "" << endl;
	cout << "DescripcionProducto:";
	cin >> Pieza.Descripcion;
	cout << "" << endl;
	cout << "PrecioProducto:";
	cin >> Pieza.Precio;
	cout << "" << endl;
	cout << "DisponibleProducto:";
	cin >> Pieza.Disponible;  cout << "" << endl;
	Pieza.Activo = true;

}

/*
* Esta funcion lista todos los Productos activos en el Inventario.
* Recorre el arreglo de Productos y muestra los datos de cada Producto activo.
* @param:
* 	- T_Producto Inventario[Max]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 
* @return:
* 	+ void: No retorna ningun valor, solo muestra los datos en la consola.
*/
void Listar(T_Producto Inventario[Max]) 
{
	system("CLS");
	int conta = 0;
	cout << "Listado de  Productos" << endl;
	for (int i = 0; i < Ultimo; i++) 
	{
		if (Inventario[i].Activo) 
		{
			cout << Inventario[i].Codigo << " " << Inventario[i].Descripcion << " " << Inventario[i].Precio << " "
				<< Inventario[i].Disponible << " " << endl;
			conta++;
			if (conta == 7) 
			{
				cout << "-----------------------------------" << endl;
				cout << "Presione cualquier tecla para continuar..." << endl;
				system("pause");
				system("CLS");

				conta = 0;
			}
		}
	}
	system("pause");
}


/*
* Esta funcion busca un Producto en el Inventario por su Codigo.
* Revisa cada Producto activo en el arreglo y devuelve el indice del Producto encontrado.
* @param:
* 	- T_Producto Inventario[Max]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- int Cual: Codigo del Producto a buscar.
* 
* @return:
* 	+ int: Retorna el indice del Producto encontrado si esta activo, o -1 si no se encuentra.
*/
int BuscarElemento(T_Producto Inventario[Max], int Cual)
{
	bool Encontro = false;
	int Cont = 0;

	while ((!Encontro) && (Cont < Ultimo))
	{
		if ((Inventario[Cont].Activo == true) && (Inventario[Cont].Codigo == Cual))
			Encontro = true;
		else
			Cont++;
	}

	if (Encontro == true)
		return Cont;
	else
		return -1;

}

/*
* Esta funcion inserta un nuevo Producto en el Inventario.
* Agrega el Producto al final del arreglo y aumenta el contador de Productos.
* @param:
* 	- T_Producto Inventario[Max]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- T_Producto Unidad: Estructura del Producto a insertar.
* 
* @return:
* 	+ void: No retorna ningun valor, el Producto se agrega directamente al arreglo.
*/
void InsertarElemento(T_Producto Inventario[Max], T_Producto Unidad)
{
	Inventario[Ultimo] = Unidad;
	Ultimo++;
}

/*
* Esta funcion borra un Producto del Inventario marcandolo como inactivo.
* Busca el Producto por su Codigo y cambia su estado a inactivo.
* @param:
*	- T_Producto Inventario[Max]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- int Cual: Codigo del Producto a borrar.
* 
* @return:
* 	+ void: No retorna ningun valor, el Producto se marca como inactivo en el arreglo.
*/
void BorrarElemento(T_Producto Inventario[Max], int Cual)
{
	int PorBorrar;
	PorBorrar = BuscarElemento(Inventario, Cual);

	if (PorBorrar != -1)
		Inventario[PorBorrar].Activo = false;

}


void main() {

	T_Producto PiezasFerreteria[Max]; // Arreglo para almacenar los Productos
	T_Producto Elemento; // Estructura temporal para capturar un Producto
	int opcion = 0; // Variable para el menu de opciones

	while (opcion < 4) 
	{

		system("cls");//limpia la pantalla
		cout << "******Menu principal******" << endl;
		cout << "1. Insertar Pieza" << endl;
		cout << "2. Listar Piezas " << endl;
		cout << "3. Borrar Piezas " << endl;
		cout << "4. Salir " << endl;
		cin >> opcion;//captura el numero introducido

		switch (opcion) 
		{

		case 1:
			system("cls");
			CapturarElemento(Elemento);
			InsertarElemento(PiezasFerreteria, Elemento);
			break;

		case 2:
			system("cls");
			Listar(PiezasFerreteria);
			break;
		case 3:
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

