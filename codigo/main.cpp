#include <iostream>

using namespace std;

//Definicion de variables
int opMenu;
// Configuracion de escenario
double Ho, Hd, d;


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
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        cout << "La opcion seleccionada no existe";
        break;
    }
    return 0;
}
