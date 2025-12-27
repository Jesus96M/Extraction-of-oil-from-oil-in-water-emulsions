#include "parametros.h"
void reservaMemoria(){

	//printf("HOLA\n");

	C=malloc(N*sizeof(int));

	r=malloc(N*sizeof(int));
	l=malloc(N*sizeof(int));
	u=malloc(N*sizeof(int));
	d=malloc(N*sizeof(int));
	conectado=malloc(N*sizeof(int));
	vecinosArevisar=malloc(N*sizeof(int));

	nDroplets=1;
	pos_inicial=malloc(nDroplets*sizeof(int));

	distanciaEuclideas=malloc(N*sizeof(double));
	indicesDistancias=malloc(N*sizeof(int));

	alturaMedia=malloc(Lx*sizeof(double));
	alturas=malloc(Lx*sizeof(int));
}

void vecinos(){
	// Funcion que define los vecinos. CC PERIODICAS
	int ind;
	for(ind=0;ind<N;ind++){
		r[ind]=ind+1;
		l[ind]=ind-1;
		u[ind]=ind+Lx;
		d[ind]=ind-Lx;
	}
	// Retocamos la vertical. Solo la del piso de arriba.
	// Ponemos a -1 aquellos vecinos que no existan. En este caso TODOS los bordes
	// Retocamos los de abajo y los de arriba:
	for(ind=0;ind<Lx;ind++){
		d[ind]=-1;//Fila de abajo Piso 1.
		u[ind+(Ly-1)*Lx]=-1;//Fila de arriba. Piso 1
	}
	// Retocamos los de la izquierda y la derecha:
	// Estos los sigo poniendo a -1
	for(ind=0;ind<Ly;ind++){
		l[ind*Lx]=-1;//Columna de la izquierda. Piso 1.
		r[(ind+1)*Lx-1]=-1;//Columna de la derecha. Piso 1
	}
}

double distanciaEuclidea(int ind1,int ind2){
	// Funcion que calcula la distancia euclidea entre dos puntos.
	// Se considera que estan en el mismo piso
	return sqrt(pow(1.0*(getX(ind1)-getX(ind2)),2.0)+pow(1.0*(getZ(ind1)-getZ(ind2)),2.0));
}

void calculaDistancias(int ind1){
	int ind;
	for(ind=0;ind<N;ind++){
		indicesDistancias[ind]=ind;
		distanciaEuclideas[ind]=distanciaEuclidea(ind,ind1);
	}
}

void ordenaDistancias(){
	// Poco eficiente pero sencillo. Solo se va a usar al inicio luego no es un gran problema
	int ind, indd;
	int comodinIndice;
	double comodinDistancia;
	for(ind=0;ind<(N-1);ind++){
		//printf("Bucle %d/%d \n", ind,N);
		for(indd=0;indd<(N-1-ind);indd++){
			// Recorro el bucle dos veces
			if(distanciaEuclideas[indd]>distanciaEuclideas[indd+1]){
				comodinIndice=indicesDistancias[indd];
				comodinDistancia=distanciaEuclideas[indd];
				indicesDistancias[indd]=indicesDistancias[indd+1];
				distanciaEuclideas[indd]=distanciaEuclideas[indd+1];
				indicesDistancias[indd+1]=comodinIndice;
				distanciaEuclideas[indd+1]=comodinDistancia;
			}
		}
	}
	//printf("Salgo del bucle final\n");
}

void condicionesIniciales(){
	// Funcion que pone las condiciones iniciales
	int ind;
	//int indd;
	//bool ok;
	//double radio;
	double xr, yr;
	//gravity=9.8;
	numeroCeldasAgua=0;
	numeroCeldasAire=0;
	numeroCeldasAceite=0;

	aceite5medidoQ=false;
	aceite10medidoQ=false;
	aceite15medidoQ=false;
	aceite20medidoQ=false;
	aceite25medidoQ=false;
	aceite30medidoQ=false;
	aceite35medidoQ=false;
	aceite40medidoQ=false;
	aceite45medidoQ=false;
	aceite50medidoQ=false;
	aceiteExtracionmedidoQ=false;
	
	//tamanhoDroplets=(int) (N*1.0*density/(2.0*nDroplets));
	//printf("Tamanho droplets %d\n", tamanhoDroplets);
	//radio=sqrt(tamanhoDroplets*2.0/(N))/2.0;
	nDroplets=1;
	//printf("Radio droplets %lf\n", radio);
	//printf("Calculando la pos de los droplets\n");
	// Elegimos nDroplets de puntos donde van a ir las gotas de aceite
	/*
	for(ind=0;ind<nDroplets;ind++){
		//Elijo aleatoriamente 3 puntos entre 0 y N/2
		aleatorio=FRANDOM*N/2.0;
		pos_inicial[ind]= (int) aleatorio;
		ok=true;
		while(ok){
			ok=false;
			// Checkeamos la distancia con los otros
			for(indd=0;indd<ind;indd++){
				if(distanciaEuclidea(pos_inicial[ind],pos_inicial[indd])<1.5*radio){
					//printf("ind %d indd %d\n", ind,indd);
					//printf("ind %lf %lf\n", getX(ind),getZ(ind));
					//printf("indd %lf %lf\n", getX(indd),getZ(indd));
					// Genero otra posicion para esta gota
					aleatorio=FRANDOM*N/2.0;
					pos_inicial[ind]= (int) aleatorio;
					ok=true;//Vuelve a entrar en el bucle a checkear la distancia
					break;// Sal del bucle ya da igual el resto de distancias
				}
			}
		}
		//printf("Pos droplets %d es %d \n", ind, pos_inicial[ind]);
	}
	*/
	//pos_inicial[0]=x_inicial+y_inicial*Lx;
	//printf("Pos de los droplets calculada\n");

	//printf("tamanho gotas aceite %d\n",tamanhoDroplets);
	// En la mitad superior se pone incialmente aire
	//printf("Pongo agua\n");
	/*
	for(ind=0;ind<(N/2);ind++){
		C[ind]=1;// agua incialmente
	}
	//printf("Pongo aire\n");
	for(ind=(N/2);ind<N;ind++){
		C[ind]=0;// aire inicialmente
	}
	// Ahora metemos las gotas de aceite
	//printf("Pongo aceite\n");
	for(ind=0;ind<nDroplets;ind++){
		//printf("Calc distan\n");
		calculaDistancias(pos_inicial[ind]);
		//printf("Orden distan\n");
		ordenaDistancias();
		for(indd=0;indd<tamanhoDroplets;indd++){
			//Anadimos un vecino de esta celda que no sea aceite
			//printf("indice aceite %d\n",indicesDistancias[indd]);
			C[indicesDistancias[indd]]=2;// Anadimos el aceite
		}
	}
	*/
	for(ind=0;ind<N;ind++){
		C[ind]=0;// aire incialmente
		conectado[ind]=0;
	}
	for(ind=0;ind<N;ind++){
		xr=(getX(ind)+1-Lx/2)*1.0;
		yr=(getZ(ind)+1+3.0*Ly)*1.0;
		if((xr*xr+yr*yr<(36.0/3.0*Ly*Ly))){
			aleatorio=FRANDOM;
			if(aleatorio<per){
				C[ind]=2;//Ponemos aceite
				conectado[ind]=1;
			}else{
				C[ind]=1;//Ponemos agua
				conectado[ind]=1;
			}
		}
	}
	/*
	for(ind=0;ind<Lx;ind++){
		C[ind]=1;//La fila de abajo llena de agua
	}
	*/
	/*
	for(ind=0;ind<nDroplets;ind++){
		//printf("Calc distan\n");
		calculaDistancias(pos_inicial[ind]);
		//printf("Orden distan\n");
		ordenaDistancias();
		for(indd=0;indd<tamanhoDroplets;indd++){
			//Anadimos un vecino de esta celda que no sea aceite
			//printf("indice aceite %d\n",indicesDistancias[indd]);
			C[indicesDistancias[indd]]=2;// Anadimos el aceite
		}
	}
	*/
	//printf("Aceite puesto\n");
	//Checkeamos cuantas celdas hay de cada tipo
	for(ind=0;ind<N;ind++){
		if(C[ind]==0){
			numeroCeldasAire++;
		}
		if(C[ind]==1){
			numeroCeldasAgua++;
		}
		if(C[ind]==2){
			numeroCeldasAceite++;
		}
	}
}
