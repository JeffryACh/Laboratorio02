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
* Modified: 17/08/2025 15:55
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
const int Max = 100; // Maximo de Productos que se pueden almacenar
const T_Producto Arreglo[Max];
int cont = 0; // Contador de Productos, indica cuántos Productos hay en el arreglo

/*
* Esta funcion guarda los Productos activos en un archivo de texto.
* Recorre el arreglo de Productos y escribe los datos de cada Producto activo en el archivo "ferreteria.txt".
* 
* @param:
*	- T_Producto Arreglo[]: Arreglo de Productos donde se almacenan los datos de los Productos.
*	- int cont: Contador de Productos, indica cuántos Productos hay en el arreglo.
* 
* @return:
*	+ void: No retorna ningun valor, los datos se guardan directamente en el archivo de texto.
*/
void guardarArchivo(T_Producto Arreglo[], int cont) 
{
	system("CLS");//limpia la pantalla
	cout << endl << endl;
	FILE* archproductos;
	fopen_s(&archproductos, "ferreteria.txt", "w+");

	for (int y = 0; y < cont; y++) 
	{
		if (Arreglo[y].Activo) //solo se guardaran aquellos productos que esten activos
		{
            printf("Codigo del Producto: %i Nombre: %s -guardado- \n", Arreglo[y].Codigo, Arreglo[y].Descripcion);
            fprintf_s(archproductos, "Descripcion: %s\n", Arreglo[y].Descripcion);
            fprintf_s(archproductos, "Codigo: %i\n", Arreglo[y].Codigo);
            fprintf_s(archproductos, "Precio: %.2f\n", Arreglo[y].Precio);
            fprintf_s(archproductos, "Disponible: %i\n", Arreglo[y].Disponible);
            fprintf_s(archproductos, "Activo: %s\n", Arreglo[y].Activo ? "true" : "false");

            if (y != (cont - 1)) 
            {
                fprintf_s(archproductos, "\n"); // Agrega un salto de línea entre productos, excepto al final
            }
		}
	}
	fclose(archproductos);
	cout << endl << " Presione una tecla para continuar..." << endl;
}

/*
* Esta funcion carga los Productos desde un archivo de texto al arreglo de Productos.
* Lee los datos del archivo "cedulas.txt" y los almacena en el arreglo de Productos.
* 
* @param:
*	- T_Producto Arreglo[]: Arreglo donde se almacenaran los Productos.
*	- int& cont: Contador de Productos, se pasa por referencia para que su valor cambie al cargar los datos.
* 
* @return:
*	+ void: No retorna ningun valor, los datos se almacenan directamente en el arreglo pasado por referencia.
*/
void cargarArchivo(T_Producto Arreglo[], int& cont) //El arreglo no debe ingresar como referencia, pero el contador si para que su valor cambie respecto a lo que se hace en la funcion
{
	system("CLS");
	FILE* archproductos;
	fopen_s(&archproductos, "ferreteria.txt", "r");
	if (archproductos == NULL) 
		cout << "no se encontro el archivo" << endl;
	else 
	{
        while (!feof(archproductos)) 
        {
        fscanf_s(archproductos, "Descripcion: %s\n", Arreglo[cont].Descripcion, (unsigned)_countof(Arreglo[cont].Descripcion));  
        fscanf_s(archproductos, "Codigo: %i\n", &Arreglo[cont].Codigo);  
        fscanf_s(archproductos, "Precio: %f\n", &Arreglo[cont].Precio);  
        fscanf_s(archproductos, "Disponible: %i\n", &Arreglo[cont].Disponible);  
        char activo[6];  
        fscanf_s(archproductos, "Activo: %s\n", activo, (unsigned)_countof(activo));  
        Arreglo[cont].Activo = (strcmp(activo, "true") == 0); // Convierte el valor leído a booleano  
        printf("\n\n  Codigo del Producto: %i Nombre: %s		-cargado- \n", Arreglo[cont].Codigo, Arreglo[cont].Descripcion);
        cont++;
        }
		fclose(archproductos);
	}
	cout << endl << " Presione una tecla para continuar..." << endl;
}

/*
* Esta funcion genera tantos Productos como tenga capacidad el arreglo.
* Actualmente no implementa ninguna funcionalidad, pero se puede usar para inicializar o generar Productos de prueba.
* 
* @param:
*	- T_Producto Arreglo[]: Arreglo de Productos donde se almacenaran los datos de los Productos.
* 
* @return:
*	+ void: No retorna ningun valor, solo se puede usar para generar Productos de prueba.
*/
void GenerarElementos(T_Producto Arreglo[])
{
	system("CLS");

	cout << "Generando Productos de prueba..." << endl;
	for (int i = 0; i < Max; i++) 
	{
		Arreglo[i].Codigo = i + 1; // Asigna un codigo unico
		sprintf_s(Arreglo[i].Descripcion, "Producto_%d", i + 1); // Asigna una descripcion unica
		Arreglo[i].Precio = (float)(rand() % 100 + 1); // Precio aleatorio entre 1 y 100
		Arreglo[i].Disponible = i; // Cantidad disponible aleatoria entre 0 y 49
		Arreglo[i].Activo = true; // Marca el Producto como activo
		cont++; // Incrementa el contador de Productos
	}
	cout << "Productos generados correctamente." << endl;
}

void BuscarPorNombre(T_Producto Arreglo[], int cont) 
{
	system("CLS");

	char Nombre[50];
	cout << "Ingrese el nombre del Producto a buscar: ";
	cin >> Nombre;
	bool encontrado = false;
	for (int i = 0; i < cont; i++) 
	{
		if (Arreglo[i].Activo && strcmp(Arreglo[i].Descripcion, Nombre) == 0) 
		{
			cout << "Producto encontrado: " << endl;
			cout << "Codigo: " << Arreglo[i].Codigo << " -- Descripcion: " << Arreglo[i].Descripcion
				<< " -- Precio: " << Arreglo[i].Precio << " -- Disponible: " << Arreglo[i].Disponible << endl;
			encontrado = true;
			break;
		}
	}

	cout << "Producto no encontrado." << endl;
}

/*
* Esta funcion lista todos los Productos activos en el Inventario.
* Recorre el arreglo de Productos y muestra los datos de cada Producto activo.
* @param:
* 	- T_Producto Arreglo[]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- int cont: Contador de Productos, indica cuántos Productos hay en el arreglo.
* 
* @return:
* 	+ void: No retorna ningun valor, solo muestra los datos en la consola.
*/
void Listar(T_Producto Arreglo[], int cont) 
{
	system("CLS");
	int conta = 0;
	cout << "Listado de  Productos" << endl;
	for (int i = 0; i < cont; i++) 
	{
		if (Arreglo[i].Activo)
		{
			cout << "Codigo: " << Arreglo[i].Codigo << " -- " << "Nombre: " << Arreglo[i].Descripcion << " -- " << "Precio: " << Arreglo[i].Precio << " -- "
				<< "Disponibilidad: " << Arreglo[i].Disponible << " " << endl;
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
* 	- T_Producto Arreglo[]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- int cont: Contador de Productos, indica cuántos Productos hay en el arreglo.
* 	- int cual: Codigo del Producto a buscar.
* 
* @return:
* 	+ void: No retorna ningun valor, solo muestra el nombre del Producto si se encuentra.
*/
void BuscarElemento(T_Producto Arreglo[], int cont, int cual)
{
	int i;
	for (i = 0; i < cont; i++) 
	{
		if ((Arreglo[i].Codigo == cual) && (Arreglo[i].Activo == true)) 
		{
			cout << "Codigo: " << Arreglo[i].Codigo << " -- " << "Nombre: " << Arreglo[i].Descripcion << " -- " << "Precio: " << Arreglo[i].Precio << " -- "
				<< "Disponibilidad: " << Arreglo[i].Disponible << " " << endl;
			break;
		}
	}
	if (i == cont)
		cout << " El codigo no fue encontrado." << endl;

}

/*
* Esta funcion borra un Producto del Inventario marcandolo como inactivo.
* Busca el Producto por su Codigo y cambia su estado a inactivo.
* @param:
*	- T_Producto Inventario[Max]: Arreglo de Productos donde se almacenan los datos de los Productos.
* 	- int Cual: Codigo del Producto a borrar.
* 
* @return:
* 	int -1: Si el Producto no se encuentra o ya fue borrado.
*	int -2: Si ocurre un error inesperado.
*/
int BorrarElemento(T_Producto Arreglo[], int Cual)
{
	cout << endl << " ----------------  Buscar persona para borrar  ----------------" << endl << endl;
	int cual;
	cout << " Digite el codigo del Producto a buscar para eliminar: ";
	cin >> cual;
	cout << endl << endl;
	int i;
	for (i = 0; i < cont; i++) 
	{
		if ((Arreglo[i].Codigo == cual) && (Arreglo[i].Activo == true)) 
		{
			cout << endl << " Persona borrada con exito" << endl << endl;
			cont--;//decrementa el contador para que la cuenta de personas sea precisa
			return i;//retorna el numero de lugar en el que esta el nombre en el arreglo
		}
	}
	if (i == cont) 
	{
		cout << " El nombre no ha sido ingresado o ya fue borrado" << endl;
		return -1;//retorna -1 ya q la funcion es tipo entero, y al ser llamada se esper un valor de regreso
	}
	else return -2;//Se escribe para evitar warning

}


void main() {
	bool menu = true;
	T_Producto arreglo[Max]; // Arreglo de Productos

	while (menu) 
	{
		system("CLS");
		cout << endl << endl << "	-----------------	Menu Principal   -----------------" << endl << endl;
		cout << "		1. Generar Productos" << endl;
		cout << "		2. Buscar Producto por nombre" << endl;
		cout << "		3. Buscar Producto por codigo" << endl;
		cout << "		4. Listar todos los Productos" << endl;
		cout << "		5. Borrar Producto" << endl;
		cout << "		6. Guardar Arreglo a archivo" << endl;
		cout << "		7. Cargar Arreglo desde archivo " << endl;
		cout << "		8. Salir" << endl << endl;
		cout << "		Digite una opcion: ";
		int opcion = 0;
		cin >> opcion;
		switch (opcion) 
		{
			case 1: 
			{
				GenerarElementos(arreglo);
				cout << endl << endl << " La persona fue ingresada correctamente." << endl << endl;
				cout << " Presione una tecla para continuar..." << endl;
				_getch();
				break;
			}
			case 2: 
			{
				BuscarPorNombre(arreglo, cont);
				cout << endl << " Presione una tecla para continuar..." << endl;
				_getch();
				break;
			}
			case 3: 
			{
				system("CLS");
				cout << endl << " ----------------  Buscar persona por #cedula  ----------------" << endl << endl << endl;
				int cual;
				cout << " Digite el codigo a buscar: ";
				cin >> cual;
				cout << endl << endl;
				BuscarElemento(arreglo, cont, cual);
				cout << endl << " Presione una tecla para continuar..." << endl;
				_getch();
				break;
			}
			case 4: 
			{
				Listar(arreglo, cont);
				cout << endl << " Presione una tecla para continuar..." << endl;
				_getch();
				break;
			}
			case 5: 
			{
				arreglo[BorrarElemento(arreglo, cont)].Activo = false;// desactiva persona
				cout << endl << " Presione una tecla para continuar..." << endl;
				_getch();
				break;
			}
			case 6: 
			{
				guardarArchivo(arreglo, cont);
				_getch();
				break;
			}
			case 7: 
			{
				if (cont != 0) 
				{
					cout << endl << endl << "  Se perderan los cambios realizados en esta sesion," << endl;
					cout << "  desea continuar(S/N): ";
					char sino[2];
					cin >> sino;
					if ((strcmp(sino, "S") == 0) || (strcmp(sino, "s") == 0)) 
					{
						cont = 0;
						cargarArchivo(arreglo, cont);
					}
					else 
						cout << " No se cargaran datos guardados. " << endl;
				}
				else 
					cargarArchivo(arreglo, cont);
				_getch();
				break;
			}

			case 8: 
			{
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
			default: 
			{
				cout << endl << "La opcion digitada no exite" << endl << endl;
				cout << " Presione una tecla para continuar..." << endl;
				_getch();
			}
		}
	}
}

