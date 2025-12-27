#include "parametros.h"
int piso(int ind){
	// Funcion que calcula en que piso esta este indice
	int p;
	p=1+ind/Lx;// Usamos la division entera
	return p;
}

int getZ(int ind){
	// Funcion que calcula en que piso esta este indice
	int p;
	p=ind/Lx;// Usamos la division entera
	return p;
}

int getX(int ind){
	int p;
	p=ind-getZ(ind)*Lx;
	return p;
}

double calculaProbabilidad(int i1,int i2){
	double prob,dife;
	double z1,z2;
	double x1,x2;
	double exp1,exp2;//valores de U_i. Dependen de la posicion solo
	bool estaraConectadaCelda;
	//Usamos esta funcion que empieza en 1 y no en 0
	x1=getX(i1)*1.0;
	z1=piso(i1)*1.0;

	x2=getX(i2)*1.0;
	z2=piso(i2)*1.0;

	dife=0.0;

	// Calculo del termino de la fuerza externa
	if(getX(i1)<x_droplet){
		exp1=1.0;
	} else{
		exp1=exp(-1.0*alpha*(x1-x_droplet));
	}
	if(getX(i2)<x_droplet){
		exp2=1.0;
	} else{
		exp2=exp(-1.0*alpha*(x2-x_droplet));
	}
	//


	////////////////////////////////////
	//cambios entre celdas de liquido //
	////////////////////////////////////


	if((C[i1]==1)&&(C[i2]==2)){
		// Estamos en el caso i1 == agua i2 == aceite
		//      AGUA <--> ACEITE
		dife=J2*(numeroVecinosIndice2Aceite-numeroVecinosIndice1Aceite)+J1*(numeroVecinosIndice1Agua-numeroVecinosIndice2Agua)+J12*(+numeroVecinosIndice1Aceite+numeroVecinosIndice2Agua-numeroVecinosIndice1Agua-numeroVecinosIndice2Aceite);
		dife=dife-J1_diag*(numeroVecinosDiagIndice2Agua-numeroVecinosDiagIndice1Agua)-J2_diag*(numeroVecinosDiagIndice1Aceite-numeroVecinosDiagIndice2Aceite)-J12_diag*(numeroVecinosDiagIndice2Aceite+numeroVecinosDiagIndice1Agua-numeroVecinosDiagIndice2Agua-numeroVecinosDiagIndice1Aceite);
		//dife=dife+A1*(1.0/pow(z1,3.0)-1.0/pow(z2,3.0))+A2*(1.0/pow(z2,3.0)-1.0/pow(z1,3.0));
		//dife=dife+k2*(exp1-exp2)+k1*(exp2-exp1);
		// Como las k1=k2 entonces este termino no hace falta calcularlo
		// Si estan conectados lo estan los 2 y si estan desconectados lo estan los 2
		// Por tanto o son 0 ambos U o son un termino que se va a mantener cte
		dife=dife+gravity*(1-rho_r)*(z2-z1);
	}
	if((C[i1]==2)&&(C[i2]==1)){
		// Estamos en el caso i1 == aceite i2 == agua
		//      ACEITE <--> AGUA
		dife=J2*(numeroVecinosIndice1Aceite-numeroVecinosIndice2Aceite)+J1*(numeroVecinosIndice2Agua-numeroVecinosIndice1Agua)+J12*(numeroVecinosIndice2Aceite+numeroVecinosIndice1Agua-numeroVecinosIndice2Agua-numeroVecinosIndice1Aceite);
		dife=dife-J1_diag*(numeroVecinosDiagIndice1Agua-numeroVecinosDiagIndice2Agua)-J2_diag*(numeroVecinosDiagIndice2Aceite-numeroVecinosDiagIndice1Aceite)-J12_diag*(numeroVecinosDiagIndice2Agua+numeroVecinosDiagIndice1Aceite-numeroVecinosDiagIndice2Aceite-numeroVecinosDiagIndice1Agua);
		//dife=dife+A1*(1.0/pow(z2,3.0)-1.0/pow(z1,3.0))+A2*(1.0/pow(z1,3.0)-1.0/pow(z2,3.0));
		//dife=dife+k2*(exp2-exp1)+k1*(exp1-exp2);
		// Igual que el caso anterior
		dife=dife+gravity*(1-rho_r)*(z1-z2);
	}


	////////////////////////////////////////////
	// cambios entre celdas de liquido y aire //
	////////////////////////////////////////////


	if((C[i1]==1)&&(C[i2]==0)){
		// Estamos en el caso i1 == agua i2 == aire
		//      AGUA <--> AIRE
		dife=J1*(numeroVecinosIndice1Agua-numeroVecinosIndice2Agua)+J12*(numeroVecinosIndice1Aceite-numeroVecinosIndice2Aceite);
		dife=dife-J1_diag*(numeroVecinosDiagIndice2Agua-numeroVecinosDiagIndice1Agua)-J12_diag*(numeroVecinosDiagIndice2Aceite-numeroVecinosDiagIndice1Aceite);
		//dife=dife+A1*(1.0/pow(z1,3.0)-1.0/pow(z2,3.0));
		// Hay que ver si el agua
		// estaraConectadoQ(int i1,int i2) i1:aire i2:liquido nos da si el i1 estara conectado cuando sea liquido
		estaraConectadaCelda=estaraConectadoQ(i2,i1);

		if((conectado[i1]==1)&&estaraConectadaCelda){
			//Conectado antes y despues
			//Los que estan conectados van con k_i y los que no con por*k_i
			dife=dife+k1*(exp2-exp1);
			//dife=final(despues)-inicial(antes)
			//despues=(exp2)    antes=(exp1)
		}
		if((conectado[i1]==0)&&estaraConectadaCelda){
			//No conectado antes y pero sí despues
			
			dife=dife+k1*(exp2)-k1*por*(exp1);
		}
		if((conectado[i1]==0)&&!estaraConectadaCelda){
			//No conectado antes y tampoco despues

			dife=dife+por*k1*(exp2-exp1);
		}
		if((conectado[i1]==1)&&!estaraConectadaCelda){
			//Conectado antes y pero no despues
			
			dife=dife+por*k1*(exp2)-k1*(exp1);
		}
		//
		//dife=dife+k1*(exp2-exp1);//antiguo
		dife=dife+gravity*(z2-z1);
	}
	if((C[i1]==0)&&(C[i2]==1)){
		// Estamos en el caso i1 == aire i2 == agua
		//      AIRE <--> AGUA
		dife=J1*(numeroVecinosIndice2Agua-numeroVecinosIndice1Agua)+J12*(numeroVecinosIndice2Aceite-numeroVecinosIndice1Aceite);
		dife=dife-J1_diag*(numeroVecinosDiagIndice1Agua-numeroVecinosDiagIndice2Agua)-J12_diag*(numeroVecinosDiagIndice1Aceite-numeroVecinosDiagIndice2Aceite);
		//dife=dife+A1*(1.0/pow(z2,3.0)-1.0/pow(z1,3.0));
		estaraConectadaCelda=estaraConectadoQ(i1,i2);

		if((conectado[i2]==1)&&estaraConectadaCelda){
			//Conectado antes y despues
			//Los que estan conectados van con k_i y los que no con por*k_i
			dife=dife+k1*(exp1-exp2);
			//dife=final(despues)-inicial(antes)
			//despues=(exp1)    antes=(exp2)
		}
		if((conectado[i2]==0)&&estaraConectadaCelda){
			//No conectado antes y pero sí despues
			
			dife=dife+por*k1*(exp1)-k1*(exp2);
		}
		if((conectado[i2]==0)&&!estaraConectadaCelda){
			//No conectado antes y tampoco despues
			
			dife=dife+por*k1*(exp1-exp2);
		}
		if((conectado[i2]==1)&&!estaraConectadaCelda){
			//Conectado antes y pero no despues
		
			dife=dife+por*k1*(exp1)-k1*(exp2);
		}
		//
		//dife=dife+k1*(exp1-exp2);//antiguo
		dife=dife+gravity*(z1-z2);
	}
	if((C[i1]==2)&&(C[i2]==0)){
		// Estamos en el caso i1 == aceite i2 == aire
		//      ACEITE <--> AIRE
		dife=J2*(numeroVecinosIndice1Aceite-numeroVecinosIndice2Aceite)+J12*(numeroVecinosIndice1Agua-numeroVecinosIndice2Agua);
		dife=dife-J2_diag*(numeroVecinosDiagIndice2Aceite-numeroVecinosDiagIndice1Aceite)-J12_diag*(numeroVecinosDiagIndice2Agua-numeroVecinosDiagIndice1Agua);
		//dife=dife+A2*(1.0/pow(z1,3.0)-1.0/pow(z2,3.0));
		estaraConectadaCelda=estaraConectadoQ(i2,i1);

		if((conectado[i1]==1)&&estaraConectadaCelda){
			//Conectado antes y despues
			//Los que estan conectados van con k_i y los que no con por*k_i
			dife=dife+k1*(exp2-exp1);
			//dife=final(despues)-inicial(antes)
			//despues=(exp2)    antes=(exp1)
		}
		if((conectado[i1]==0)&&estaraConectadaCelda){
			//No conectado antes y pero sí despues
			
			dife=dife+k1*(exp2)-k1*por*(exp1);
		}
		if((conectado[i1]==0)&&!estaraConectadaCelda){
			//No conectado antes y tampoco despues

			dife=dife+por*k1*(exp2-exp1);
		}
		if((conectado[i1]==1)&&!estaraConectadaCelda){
			//Conectado antes y pero no despues
			
			dife=dife+por*k1*(exp2)-k1*(exp1);
		}
		//
		//dife=dife+k2*(exp2-exp1);//antiguo
		dife=dife+rho_r*gravity*(z2-z1);
	}
	if((C[i1]==0)&&(C[i2]==2)){
		// Estamos en el caso i1 == aire i2 == aceite
		//      AIRE <--> ACEITE
		dife=J2*(numeroVecinosIndice2Aceite-numeroVecinosIndice1Aceite)+J12*(numeroVecinosIndice2Agua-numeroVecinosIndice1Agua);
		dife=dife-J2_diag*(numeroVecinosDiagIndice1Aceite-numeroVecinosDiagIndice2Aceite)-J12_diag*(numeroVecinosDiagIndice1Agua-numeroVecinosDiagIndice2Agua);
		//dife=dife+A2*(1.0/pow(z2,3.0)-1.0/pow(z1,3.0));
		estaraConectadaCelda=estaraConectadoQ(i1,i2);

		if((conectado[i2]==1)&&estaraConectadaCelda){
			//Conectado antes y despues
			//Los que estan conectados van con k_i y los que no con por*k_i
			dife=dife+k1*(exp1-exp2);
			//dife=final(despues)-inicial(antes)
			//despues=(exp1)    antes=(exp2)
		}
		if((conectado[i2]==0)&&estaraConectadaCelda){
			//No conectado antes y pero sí despues
			
			dife=dife+por*k1*(exp1)-k1*(exp2);
		}
		if((conectado[i2]==0)&&!estaraConectadaCelda){
			//No conectado antes y tampoco despues
			
			dife=dife+por*k1*(exp1-exp2);
		}
		if((conectado[i2]==1)&&!estaraConectadaCelda){
			//Conectado antes y pero no despues
		
			dife=dife+por*k1*(exp1)-k1*(exp2);
		}
		//dife=dife+k2*(exp1-exp2);//antiguo
		dife=dife+rho_r*gravity*(z1-z2);
	}
	prob=exp(-beta*dife);
	return prob;
}
