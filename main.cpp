/****************************************************************
/**	Programador: Yansel Y. Flores Vargas
/**	# Estudiante: 842-15-3264
/**	Programador: Gabriel O. Fontanez Gonzalez
/**	# Estudiante: 842-15-3288
/**	Programador: Alexander Santos
/**	# Estudiante: 842-15-
/**	Programador: Carlos Estrada
/**	# Estudiante: 842-15-
/**	Curso: COMP 3081 sec. N01
/**	Programa Final
/**
/**	Propósito: Una oración que describa el propósito del programa.
/**	Input: Los valores que se le proveen al programa.
/**	Output: Los valores o resultados que produce el programa.
/**
/**	Descripción de las variables
/**	cont - contador para acumular la cantidad de números positivos
/**
/**	suma - Lugar donde se acumula la suma de los números positivos
/**
/**	numero - valor que entra el usuario para decidir si es positivo.
/**
/**************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

//Prototipo de variables.
void Crear();
void Mostrar(long);
void ShowAll();
void Editar();
void Borrar();
void Exit();

long buscar();

//Variables globales.
const int num1 = 20;
const int num2 = 80;
const int ZIP_SIZE = 6;
const int TEL_SIZE = 14;
const int num3 = 2;
const int num4 = 4;

//Nombre de archivos
fstream records;
fstream temporal;

//Estructura para el record.
struct Info
{
    char nombre[num2];
    char direccion[num2];
    char ciudad[num1], estado[num1], ZIP[ZIP_SIZE];
    char telefono[num1];
    double balance;
    int dia, mes, year;
};

int main()
{
    // Variables para el menu.
    unsigned const int crear =1, mostrar =2, seeall =3, cambiar =4, borrar =5, salir =6;
    int opcion;
    long posicion;

    //Manipulacion del output.
    cout << fixed << showpoint << setprecision(2);

    // Menu del programa hecho en un do while para que se repita en caso que usuario ponga un numero no deseado
    do
    {
        cout << "\nMenu editor de expedientes\n\n" << endl;
        cout << "1. Crear expediente" << endl;
        cout << "2. Mostrar un expediente" << endl;
        cout << "3. Mostrar todos los expedientes" << endl;
        cout << "4. Cambiar un expediente" << endl;
        cout << "5. Borrar un expediente" << endl;
        cout << "6. Salir del programa" << endl;
        cout << "Entre su opcion: ";
        cin >> opcion;
        cout << endl;

        // Validar la opcion introducida
        if(!cin)
        {
            cin.clear();
            cin.ignore();
        }

        //Responde a la selecion del usuario.
        if (opcion != salir)
        {
           switch (opcion)
            {
                case crear:
                    Crear();
                    break;

                case mostrar:
                    posicion = buscar();
                    Mostrar(posicion);
                    break;

                case seeall:
                    ShowAll();
                    break;

                case cambiar:
                    Editar();
                    break;

                case borrar:
                    Borrar();
                    break;
            }
        }
    } while (opcion != salir);
    return 0;
}
//Funciones sujeto a cambio.

long buscar()
{
    records.open("Records.dat", ios::in | ios::binary);

    char nombre1[num2];
    Info persona;
    long posicion;

    cout << "\nIntroduzca todo el nombre del cliente: ";
    cin.ignore();
    cin.getline(nombre1, 80);

    if (nombre1[0] == '\0') //Si no entra nada.
    {
        return -1;
    }

    while (records.peek()!=EOF)
    {

        records.read(reinterpret_cast<char*>(&persona), sizeof(persona)); //Lee el record

        if (strcmp(persona.nombre,nombre1)== 0 ) // Si valor de búsqueda coincide con nombre de los clientes.
        {

            posicion = records.tellg();
            records.close();
            return posicion - sizeof(persona);
        }
    }
    records.close();
    return -1;


}

void Crear()
{
    records.open("Records.dat", ios::out | ios::app | ios::binary);
    Info OnePerson;

    cout << "\nEntre la siguiente informacion:\n" << endl;
    cin.get();
    cout << "Nombre: ";
    cin.getline(OnePerson.nombre, num2);
    cout << "Direccion: ";
    cin.getline(OnePerson.direccion, num2);
    cout << "Ciudad: ";
    cin.getline(OnePerson.ciudad, num1);
    cout << "Estado: ";
    cin.getline(OnePerson.estado, num1);
    cout << "ZIP: ";
    cin.getline(OnePerson.ZIP, num1);
    cout << "Telefono: ";
    cin.getline(OnePerson.telefono, num1);
    cout << "Balance: ";
    cin >> OnePerson.balance;
    cout << "Entre el ultimo dia de su pago: " << endl;
    cout << "Dia:";
    cin >> OnePerson.dia;
    cout << "Mes(1 - 12): ";
    cin >> OnePerson.mes;
    cout << "Ano : ";
    cin >> OnePerson.year;

    records.write(reinterpret_cast<char*>(&OnePerson), sizeof(OnePerson));

    records.close();
}

void Mostrar(long posicion)
{
    Info persona;
    records.open("Records.dat", ios::in | ios::binary);

    if (records.fail())
    {
        cout << "\nError al abrir el archivo.\n";
        return;
    }
    if (records.peek() == EOF)
    {
        cout << "\nEl archivo esta vacio.\n";
        records.clear();
        records.close();
        return;
    }

    records.seekg(posicion, ios::beg);
    records.read(reinterpret_cast<char*>(&persona), sizeof(Info));

    cout.precision(2);
    cout.setf(ios::fixed | ios::showpoint);
    cout << "\n\nNombre: " << persona.nombre << endl;
    cout << "Direccion: " << persona.direccion << endl;
    cout << "Ciudad: " << persona.ciudad << endl;
    cout << "Estado: " << persona.estado << endl;
    cout << "Zip: " << persona.ZIP << endl;
    cout << "Telefono: " << persona.telefono << endl;
    cout << "Balance de cuenta: " << persona.balance << endl;
    cout << "Fecha de ultimo pago: ";
    cout << persona.dia << "/" << persona.mes << "/" << persona.year << endl;
    records.close();
    cout << "\nPresiona enter para continuar. ";
    cin.get();
}

void ShowAll()
{
    cin.ignore();
    Info OnePerson;
    records.open("Records.dat", ios::in | ios::binary);

    if (records.fail())
    {
        cout << "ERROR NOOOOO" << endl;
        return;
    }

    while (records.peek() != EOF)
    {
        records.read(reinterpret_cast<char*>(&OnePerson), sizeof(OnePerson));
        cout << setprecision(2);
        cout << fixed << showpoint;
        cout << "Nombre:" << OnePerson.nombre << endl;
        cout << "Direccion Postal:" << OnePerson.direccion << endl;
        cout << "Ciudad:" << OnePerson.ciudad << endl;
        cout << "Estado:" << OnePerson.estado << endl;
        cout << "ZIP" << OnePerson.ZIP << endl;
        cout << "Telefono:" << OnePerson.telefono << endl;
        cout << "Balance:" << OnePerson.balance << endl;
        cout << "Fecha de Ultimo Pago:" << OnePerson.dia << "/" << OnePerson.mes << "/" << OnePerson.year << endl;
        cout << endl;
    }
    records.close();
}

void Editar()
{

}

void Borrar()
{
    Info c;
    char choice;
    char name [num2];
    char letter = 's';
    char letra = 'S';
    char address[num2];
    char city[num1], state[num1], ZIP1[ZIP_SIZE];
    char tel[num1];
    double balance1;
    int dia1, mes1, year1;

    cout << "\nHaz seleccionado eliminar un archivo.\n";


    long posicion = buscar();

    records.open("Records.dat", ios::in | ios::app | ios::binary);
    temporal.open("Temporal.dat", ios::out |ios::app|  ios::binary);


    if (records.fail())
    {
        cout << "\nError al abrir el archivo.\n";
        return;
    }
    else
    {
        if (!records.eof())
        {
            records.seekg(posicion, ios::beg);
            records.read(reinterpret_cast<char*>(&c), sizeof(Info));

            name == c.nombre;

            cout.precision(2);
            cout.setf(ios::fixed | ios::showpoint);

            cout << "\n\nNombre: " << c.nombre << endl;
            cout << "Direccion: " << c.direccion << endl;
            cout << "Ciudad: " << c.ciudad << endl;
            cout << "Estado: " << c.estado << endl;
            cout << "Zip: " << c.ZIP << endl;
            cout << "Telefono: " << c.telefono << endl;
            cout << "Balance de cuenta: " << c.balance << endl;
            cout << "Fecha de ultimo pago: ";
            cout << c.dia << "/" << c.mes << "/" << c.year << endl;
        }

        cout << "\nEsta seguro de que quiere eliminar el expediente (S(si)/N(no): ";
        cin >> choice;

        if (choice == letter || choice == letra)
        {
            records >> name;

            while (records.peek()!=EOF)
            {

                if (strcmp(name,c.nombre) == 0)
                {
                    records >> address;
                    records >> city;
                    records >> state;
                    records >> ZIP1;
                    records >> tel;
                    records >> balance1;
                    records >> dia1;
                    records >> mes1;
                    records >> year1;
                    cout << "\nEl expediente ha sido eliminado.\n";
                }
                else
                {
                    temporal << c.direccion;
                    temporal << c.ciudad;
                    temporal << c.estado;
                    temporal << c.ZIP;
                    temporal << c.telefono;
                    temporal << c.balance;
                    temporal << c.dia;
                    temporal << c.mes;
                    temporal << c.year;

                }

            }

            records.close();
            temporal.close();

            remove("Records.dat");

        }

    }

}
