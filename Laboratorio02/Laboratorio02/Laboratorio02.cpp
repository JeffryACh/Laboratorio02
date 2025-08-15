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
* Modified: 14/08/2025 22:05
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
typedef struct T_Producto {
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
* Esta funcion carga automaticamente los datos de un Producto en la estructura T_Producto.
* Utiliza valores predefinidos para el Codigo, Descripcion, Precio y Cantidad Disponible.
* 
* @param:
*	- int NCodigo: Codigo del Producto a cargar.
*	- int NDescripcion: Descripcion del Producto a cargar.
*	- float NPrecio: Precio del Producto a cargar.
*	- int NDisponible: Cantidad Disponible del Producto a cargar.
*	- T_Producto &Pieza: Referencia a la estructura donde se almacenaran los datos del Producto.
* 
* @return:
*	+ void: No retorna ningun valor, los datos se almacenan directamente en la estructura pasada por referencia.
*/
void CreadorAutomaticoDatosProducto(int NCodigo, int NDescripcion, float NPrecio, int NDisponible, T_Producto &Pieza)
{
	cout << "insertando ... ";
	char descrip[50];
	char texto[20] = "Producto_";

	Pieza.Codigo = NCodigo;

	_itoa_s(NDescripcion, descrip, 50, 10); // Convierte el entero NDescripcion a cadena
	strcat_s(texto, descrip); // Concatena "Producto_" con el numero convertido
	strcpy_s(Pieza.Descripcion, 50, texto); // Copia el resultado a la descripcion del Producto

	Pieza.Precio = NPrecio;
	Pieza.Disponible = NDisponible;
	Pieza.Activo = true;
	cout << "Listo, elemento insertado" << endl;
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

	T_Producto PiezasFerreteria[Max];
	T_Producto Elemento;

	int opcion = 0;

	while (opcion < 4)
	{

		system("cls");//limpia la pantalla
		cout << "******Menu principal******" << endl;
		cout << "1. Capturar productos de prueba" << endl;
		cout << "2. Listar Piezas " << endl;
		cout << "3. Borrar Piezas " << endl;
		cout << "4. Salir " << endl;
		cin >> opcion;//captura el numero introducido

		/*
		* Se va a utilizar un switch sencillo para las opciones del menu
		* 
		* Por ahora solo acepta opciones del 1 al 4
		* 
		* Se espera que el usuario no ingrese letras o caracteres especiales
		*/
		switch (opcion)
		{
		case 1:
			system("cls"); // limpia la pantalla
			Ultimo = 0;
			for (int contador = 0; contador < Max; contador++)
			{
				CreadorAutomaticoDatosProducto(contador, contador, contador, contador, Elemento);
				InsertarElemento(PiezasFerreteria, Elemento);
			}
			system("PAUSE"); // Pausa para que el usuario vea el mensaje antes de continuar
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
		case 4:
			cout << "Saliendo del programa..." << endl;
			break;
		}
	}
}

// Resultado:

/*
	******Menu principal******
	1. Capturar productos de prueba
	2. Listar Piezas
	3. Borrar Piezas
	4. Salir
	1
	...
	insertando ... Listo, elemento insertado
	insertando ... Listo, elemento insertado
	insertando ... Listo, elemento insertado
	insertando ... Listo, elemento insertado
	Presione una tecla para continuar . . .

	******Menu principal******
	1. Capturar productos de prueba
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
	...
	98 Producto_98 98 98
	99 Producto_99 99 99
	Presione una tecla para continuar . . .

	******Menu principal******
	1. Capturar productos de prueba
	2. Listar Piezas
	3. Borrar Piezas
	4. Salir
	3

	Digite el codigo del Producto a Borrar

	CodigoProducto:
	0

	******Menu principal******
	1. Capturar productos de prueba
	2. Listar Piezas
	3. Borrar Piezas
	4. Salir
	2

	Listado de  Productos
	1 Producto_1 1 1
	2 Producto_2 2 2
	3 Producto_3 3 3
	4 Producto_4 4 4
	5 Producto_5 5 5
	6 Producto_6 6 6
	7 Producto_7 7 7
	-----------------------------------
	Presione cualquier tecla para continuar...
	Presione una tecla para continuar . . .

	******Menu principal******
	1. Capturar productos de prueba
	2. Listar Piezas
	3. Borrar Piezas
	4. Salir
	4
	Saliendo del programa...
	C:\Users\jeffr\OneDrive - Estudiantes ITCR\Documentos\Computacion\Semestre 08\ED\Semana02\Labs\Proyecto\Laboratorio02\Laboratorio02\Debug\Laboratorio02.exe (proceso 24896) se cerró con el código 0 (0x0).
	Presione cualquier tecla para cerrar esta ventana. . .	
*/