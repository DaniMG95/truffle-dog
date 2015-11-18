#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
        trufa_size_=-1;
        bump_=false;
        fila=20;
        columna=20;
        orientacion_=0;
        for(int i=0;i<4;i++){
            sensores_[i]=-1;
        }
        for(int i=0;i<40;i++){
            for(int j=0;j<40;j++){
                mapa[i][j]=0;
            }
        }
        ult_accion_=actIDLE;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSNIFF,
	    actEXTRACT,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();
private:
	int trufa_size_;
	bool bump_;
	int orientacion_;
	int sensores_[4];
	int mapa[40][40];
	int fila;
	int columna;
	ActionType ult_accion_;

};

string ActionStr(Agent::ActionType);

#endif
