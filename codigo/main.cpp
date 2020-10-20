#include <iostream>
#include <math.h>

using namespace std;

//Prototipos de funciones
double posXo(double Vo, double angulo, double t);
double posYo(double Vo, double angulo, double t);
double posXd(double Vo, double angulo, double t);
double posYd(double Vo, double angulo, double t);
double distancia(double X1, double Y1, double X2, double Y2);
double maxT(double Vo, double angulo);

//Definicion de variables
int opMenu;
// Configuracion de escenario
double Ho, Hd, d, dist, rangoO, rangoD, g=9.81;
// Variables disparo ofensivo
double Voo, Vod;  // Velocidades iniciales
double Yo, Yd, Xo, Xd;
double tiempo, maxTiempo;
int angO, angD, angTest[3]={45, 50, 60}; //Angulos de disparo
bool flag = true;
double pi = 2*acos(0.0);

int main()
{
    cout << "Bienvenido al sistema de simulacion" << endl;
    cout << "Por favor ingrese los parametros de configuracion de escenario" << endl;
    cout << "Inidique la distancia horizontal entre en canones: ";
    cin >> d;
    //Se calculan rangos de impacto
    rangoO=0.05*d;
    rangoD=0.025*d;
    cout << "Indique la altura en metros del canon ofensivo: ";
    cin >> Ho;
    cout << "Indique la altura en metros del canon defensivo: ";
    cin >> Hd;
    // Menu para seleccionar las opciones a simular
    cout << "MENU DE OPCIONES" << endl << endl;
    cout << "1. Generar disparos (al menos tres) ofensivos que comprometan al otro canon" << endl;
    cout << "2. Generar disparos (al menos tres) defensivos que comprometan al otro canon" << endl;
    cout << "3. Dado un disparo ofensivo, generar (al menos tres) disparos defensivos, sin importar el canon ofensivo" << endl;
    cout << "4. Dado un disparo ofensivo, generar (al menos tres) disparos defensivos, sin importar el canon ofensivo" << endl;
    cout << "5. Salir" << endl;
    cout << endl << "Indique una opcion: ";
    cin >> opMenu;
    switch (opMenu) {
    case 1:
        cout << endl;
        //Para generar los 3 disparon se define un set angulos 45, 50 y 60
        //Se tienen conocidos el angulo y las alturas; Se calcularan los Vo requeridos
        //Se itera en los 3 angulos definidos
        for (int i=0; i<3; i++) {
            flag = false;
            //Se itera en velocidad inicial
            for (int v=0; v<1000; v++) {
                //Se itera en tiempo
                for (double t=0.1; t<1000; t+=0.1) {
                    Xo = posXo(v,angTest[i]*pi/180,t);
                    Yo = posYo(v,angTest[i]*pi/180,t);
                    // Se limita para que el escenario tenga piso en 0,
                    // asi que si se dan valores negativos no se tienen en cuenta.
                    if (Yo<0) continue;
                    dist = distancia(Xo,Yo,d,Hd);
                    if (dist <=rangoO) {
                        tiempo = t;
                        Voo = v;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            cout << "Para angulo " << angTest[i] << " y velocidad " << Voo << " se logra generar danio en X=" << Xo << " y Y=" << Yo << " en tiempo " << tiempo << endl;
        }
        break;
    case 2:
        cout << endl;
        //Para generar los 3 disparon se define un set angulos 45, 50 y 60
        //Se tienen conocidos el angulo y las alturas; Se calcularan los Vo requeridos
        //Se itera en los 3 angulos definidos
        for (int i=0; i<3; i++) {
            flag = false;
            //Se itera en velocidad inicial
            for (int v=0; v<1000; v++) {
                //Se itera en tiempo
                for (double t=0.1; t<1000; t+=0.1) {
                    Xd = posXd(v,angTest[i]*pi/180,t);
                    Yd = posYd(v,angTest[i]*pi/180,t);
                    // Se limita para que el escenario tenga piso en 0,
                    // asi que si se dan valores negativos no se tienen en cuenta.
                    if (Yd<0) continue;
                    dist = distancia(0,Ho,Xd,Yd);
                    if (dist <=rangoD) {
                        tiempo = t;
                        Voo = v;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            cout << "Para angulo " << angTest[i] << " y velocidad " << Voo << " se logra generar danio en X=" << Xd << " y Y=" << Yd << " en tiempo " << tiempo << endl;
        }
        break;
    case 3:
        Vod = 0;
        flag = false;
        cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
        cout << "Indique la velocidad inicial (m/s) del disparo: ";
        cin >> Voo;
        cout << "Indique el angulo en grados del disparo: " << endl;
        cin >> angO;
        //Para el angulo y velocidad dada se puede calcular el tiempo maximo de iteracion, esto para una distancia de maximo (d + rangoOfensivo)
        maxTiempo = maxT(Voo,angO*pi/180);
        // Con este tiempo maximo primero se analiza si el disparo podría hacer daño
        //Se itera en tiempo hasta el maxTiempo
        for (double t=0.1; t<maxTiempo; t+=0.1) {
            Xo = posXo(Voo,angO*pi/180,t);
            Yo = posYo(Voo,angO*pi/180,t);
            dist = distancia(Xo,Yo,d,Hd);
            if (dist <=rangoO) {
                tiempo = t;
                flag = true;
                break;
            }
        }
        // Si el disparo ofensivo puede hacer daño, defino un angulo fijo de defensa 45 y simulo velocidades
        if (flag) {
            //Se reutiliza bandera en este caso para saber si la velocidad evaluada puede evitar el disparo ofensivo
            flag = false;
            //Se itera en velocidad inicial
            for (int v=1; v<1000; v++) {
                //Se itera en tiempo hasta el maxTiempo
                for (double t=0.1; t<tiempo; t+=0.01) {
                    Xo = posXo(Voo,angO*pi/180,t);
                    Yo = posYo(Voo,angO*pi/180,t);
                    Xd = posXd(v,45*pi/180,t+2.5);
                    Yd = posYd(v,45*pi/180,t+2.5);
                    dist = distancia(Xo,Yo,Xd,Yd);
                    // Se limita para que el escenario tenga piso en 0,
                    // asi que si se dan valores negativos no se tienen en cuenta.
                    if ((Yd<0)||(Yo<0)) continue;
                    else if (dist <=rangoD) {
                        tiempo = t;
                        Vod = v;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            cout << "Para angulo ofensivo " << angO << " y velocidad " << Voo;
            if (Vod==0) {
                cout << " no se puede evitar el impacto." << endl;
            } else {
                cout<< " se puede evitar impacto con" << endl;
                cout << "un angulo defensivo 45 y una velocidad " << Vod << " en tiempo " << tiempo + 2.5 << endl;
            }
        } else {
            cout << "Los datos ingresados no pueden generar danio." << endl;
        }
        break;
    case 4:
        Vod = 0;
        flag = false;
        cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
        cout << "Indique la velocidad inicial (m/s) del disparo: ";
        cin >> Voo;
        cout << "Indique el angulo en grados del disparo: " << endl;
        cin >> angO;
        //Para el angulo y velocidad dada se puede calcular el tiempo maximo de iteracion, esto para una distancia de maximo (d + rangoOfensivo)
        maxTiempo = maxT(Voo,angO*pi/180);
        // Con este tiempo maximo primero se analiza si el disparo podría hacer daño
        //Se itera en tiempo hasta el maxTiempo
        for (double t=0.1; t<maxTiempo; t+=0.1) {
            Xo = posXo(Voo,angO*pi/180,t);
            Yo = posYo(Voo,angO*pi/180,t);
            dist = distancia(Xo,Yo,d,Hd);
            if (dist <=rangoO) {
                tiempo = t;
                flag = true;
                break;
            }
        }
        // Si el disparo ofensivo puede hacer daño, defino un angulo fijo de defensa 45 y simulo velocidades
        if (flag) {
            //Se reutiliza bandera en este caso para saber si la velocidad evaluada puede evitar el disparo ofensivo
            flag = false;
            //Se itera en velocidad inicial
            for (int v=1; v<1000; v++) {
                //Se itera en tiempo hasta el maxTiempo
                for (double t=0.1; t<tiempo; t+=0.01) {
                    Xo = posXo(Voo,angO*pi/180,t);
                    Yo = posYo(Voo,angO*pi/180,t);
                    Xd = posXd(v,45*pi/180,t+2.5);
                    Yd = posYd(v,45*pi/180,t+2.5);
                    dist = distancia(Xo,Yo,Xd,Yd);
                    // Se limita para que el escenario tenga piso en 0,
                    // asi que si se dan valores negativos no se tienen en cuenta.
                    if ((Yd<0)||(Yo<0)) continue;
                    else if (dist <=rangoD) {
                        tiempo = t;
                        Vod = v;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            cout << "Para angulo ofensivo " << angO << " y velocidad " << Voo;
            if (Vod==0) {
                cout << " no se puede evitar el impacto." << endl;
            } else {
                cout<< " se puede evitar impacto con" << endl;
                cout << "un angulo defensivo 45 y una velocidad " << Vod << " en tiempo " << tiempo + 2.5 << endl;
            }
        } else {
            cout << "Los datos ingresados no pueden generar danio." << endl;
        }
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "La opcion seleccionada no existe";
        break;
    }
    return 0;
}

double posXo(double Vo, double angulo, double t) {
    return Vo*cos(angulo)*t; //Dada la configuracion del escenario se considera Xo(inicial) = 0
}

double posYo(double Vo, double angulo, double t) {
    return Ho + Vo * sin(angulo) - (g*pow(t,2))/2;
}

double posXd(double Vo, double angulo, double t) {
    return d - Vo*cos(angulo)*t;
}

double posYd(double Vo, double angulo, double t) {
    return Hd + Vo * sin(angulo) - (g*pow(t,2))/2;
}

double distancia(double X1, double Y1, double X2, double Y2) {
    double deltaX = X1 - X2;
    double deltaY = Y1 - Y2;
    return  abs(sqrt(pow(deltaX,2)+pow(deltaY,2)));
}

double maxT(double Vo, double angulo) {
    return (d+rangoO)/(Vo*cos(angulo));
}

