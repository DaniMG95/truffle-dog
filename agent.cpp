#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;
// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
    switch(ult_accion_){
        case actFORWARD:
                if(bump_){//Si se choca pone un -1 en la posicion de la matriz donde se choco para volver a chocar
                    switch(orientacion_){
                        case 0 :
                            mapa[fila-1][columna]=-1;
                        break;

                        case 1 :
                            mapa[fila][columna+1]=-1;
                        break;
                        case 2 :
                            mapa[fila+1][columna]=-1;
                        break;
                        case 3 :
                            mapa[fila][columna-1]=-1;
                    }
                }
                else{//Si no se choca se actualiza su posicion en la matriz
                    switch(orientacion_){
                        case 0 :
                            fila=fila-1;
                        break;
                        case 1 :
                            columna=columna+1;
                        break;
                        case 2 :
                            fila=fila+1;
                        break;
                        case 3 :
                            columna=columna-1;
                        break;
                    }
                    //Pone a 0 en la posicion de la matriz donde encuentra actualmente para saber que ha pasado recientemente por esa poscion.
                    mapa[fila][columna]=0;
                }
                break;
        case actTURN_R:
            orientacion_++;
            if(orientacion_>3)
                orientacion_=0;
            break;
        case actTURN_L:
            orientacion_--;
            if(orientacion_<0)
                orientacion_=3;
            break;
    }

    ActionType accion;
    switch(orientacion_){
        case 0://Momento que esta mirando hacia el norte
            sensores_[0]= mapa[fila-1][columna];
            sensores_[1]= mapa[fila][columna+1];
            sensores_[2]= mapa[fila+1][columna];
            sensores_[3]= mapa[fila][columna-1];
        break;
        case 1 : //Momento que esta mirando hacia el este
            sensores_[0]= mapa[fila][columna+1];
            sensores_[1]= mapa[fila+1][columna];
            sensores_[2]= mapa[fila][columna-1];
            sensores_[3]= mapa[fila-1][columna];
        break;
        case 2 ://Momento que esta mirando hacia el sur
            sensores_[0]= mapa[fila+1][columna];
            sensores_[1]= mapa[fila][columna-1];
            sensores_[2]= mapa[fila-1][columna];
            sensores_[3]= mapa[fila][columna+1];
        break;
        case 3 ://Momento que esta mirando hacia el oeste
            sensores_[0]= mapa[fila][columna-1];
            sensores_[1]= mapa[fila-1][columna];
            sensores_[2]= mapa[fila][columna+1];
            sensores_[3]= mapa[fila+1][columna];
        break;
    }
    //Inicializacion de busqueda de casilla mayor
    int mayor=-2;
	int indice=-1;
	//Busqueda de la casilla mayor para saber que casilla debe elegir , la casilla con mayor tamaño es la cual ha pasado menos veces o no ha pasado aun
	for(int i=0;i<4;i++){
        if(sensores_[i]>mayor){
            mayor=sensores_[i];
            indice=i;
        }
	}
	if(trufa_size_>6){//Deja crecer las trufas hasta 6 para asi recoger mayor numero de trufas
        accion=actEXTRACT;
	}
	else if(trufa_size_==-1){
        accion=actSNIFF;
	}
    else{
        switch(indice){//Segun donde se encuentre la casilla con mayor numero , el perro realizara un movimiento
            case 0://Caso cuando la casilla mayor esta enfrente suya
                accion=actFORWARD;
                break;
            case 1://Caso cuando la casilla mayor esta a su derecha
                accion=actTURN_R;
                break;
            case 2://Caso cuando la casilla mayor esta detras suya
                accion=actTURN_R;
                break;
            case 3://Caso cuando la casilla mayor esta a su izquierda
                accion=actTURN_L;
                break;
        }
    }
    //Incremento de la matriz para saber donde ha pasado menos veces o ninguna vez
    for(int i=0;i<40;i++){
            for(int j=0;j<40;j++){
                    if( mapa[i][j]!=-1)
                        mapa[i][j]=mapa[i][j]+1;
            }
        }
    ult_accion_=accion;
	return accion;
}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	trufa_size_ = env.TrufaAmount();
	bump_ = env.isJustBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSNIFF: return "SNIFF";
	case Agent::actEXTRACT: return "EXTRACT";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
