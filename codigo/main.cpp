#include <iostream>
#include <math.h>

using namespace std;

//Prototipos de funciones
double posXo(double Vo, int angulo, double t);
double posYo(double Vo, int angulo, double t);
double posXd(double Vo, int angulo, double t);
double posYd(double Vo, int angulo, double t);
double distancia(double X1, double Y1, double X2, double Y2);

//Definicion de variables
int opMenu;
// Configuracion de escenario
double Ho, Hd, d, g=9.81;
// Variables disparo ofensivo
double Voo, Vod;  // Velocidades iniciales
int angO, angD; //Angulos de disparo

int main()
{
    cout << "Bienvenido al sistema de simulacion" << endl;
    cout << "Por favor ingrese los parametros de configuracion de escenario" << endl;
    cout << "Inidique la distancia horizontal entre en canones: ";
    cin >> d;
    cout << "Indique la altura en metros del canon ofensivo: " << endl;
    cin >> Ho;
    cout << "Indique la altura en metros del canon defensivo: " << endl;
    cin >> Hd;
    // Menu para seleccionar las opciones a simular
    cout << "MENU DE OPCIONES" << endl << endl;
    cout << "1. Generar disparos (al menos tres) ofensivos que comprometan al otro canon" << endl;
    cout << "2. Generar disparos (al menos tres) ofensivos que comprometan al otro canon" << endl;
    cout << "3. Dado un disparo ofensivo, generar (al menos tres) disparos defensivos, sin importar el canon ofensivo" << endl;
    cout << "4. Dado un disparo ofensivo, generar (al menos tres) disparos defensivos, sin importar el canon ofensivo" << endl;
    cout << "5. Salir";
    cout << "Indique una opcion: ";
    cin >> opMenu;
    switch (opMenu) {
    case 1:


        break;
    case 2:
        break;
    case 3:
        cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
        cout << "Indique la velocidad inicial (m/s) del disparo: ";
        cin >> Voo;
        cout << "Indique el angulo en grados del disparo: " << endl;
        cin >> angO;
        break;
    case 4:
        cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
        cout << "Indique la velocidad inicial (m/s) del disparo: ";
        cin >> Voo;
        cout << "Indique el angulo en grados del disparo: " << endl;
        cin >> angO;
        break;
    case 5:
        break;
    default:
        cout << "La opcion seleccionada no existe";
        break;
    }
    return 0;
}

double posXo(double Vo, int angulo, double t) {
    return Vo*cos(angulo)*t; //Dada la configuracion del escenario se considera Xo(inicial) = 0
}

double posYo(double Vo, int angulo, double t) {
    return Ho + Vo * sin(angulo) - (g*pow(t,2))/2;
}

double posXd(double Vo, int angulo, double t) {
    return d - Vo*cos(angulo)*t;
}

double posYd(double Vo, int angulo, double t) {
    return Hd + Vo * sin(angulo) - (g*pow(t,2))/2;
}

double distancia(double X1, double Y1, double X2, double Y2) {
    double deltaX = X1 - X2;
    double deltaY = Y1 - Y2;
    return  abs(sqrt(pow(deltaX,2)+pow(deltaY,2)));
}

