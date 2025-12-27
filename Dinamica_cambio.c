#include "parametros.h"
int eligeVecino(int indice1){
	int indice2;
	indice2=-1;//value of no reference. Preventing choosing a border
	while(indice2==-1){
		aleatorio=FRANDOM*4;
		indice2=(int) aleatorio;
		if(indice2==0){
			indice2=r[indice1];
		}else if(indice2==1){
			indice2=l[indice1];
		}else if(indice2==2){
			indice2=u[indice1];
		}else if(indice2==3){
			indice2=d[indice1];
		}
	}
	return indice2;
}

void calculaVecinos(int indice1, int indice2){
	int vec;
	numeroVecinosIndice1Agua=0;
	numeroVecinosIndice1Aceite=0;
	numeroVecinosIndice2Agua=0;
	numeroVecinosIndice2Aceite=0;
	//Checkeamos todos los vecinos de indice 1 y vamos acumulando
	vec=r[indice1];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice1Aceite++;
		}
	}
	vec=l[indice1];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice1Aceite++;
		}
	}
	vec=u[indice1];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice1Aceite++;
		}
	}
	vec=d[indice1];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice1Aceite++;
		}
	}
	//Ahora hay que restar el valor de ind2 que tambien se esta contando
	vec=ind2;
	if(C[vec]==1){
		numeroVecinosIndice1Agua--;
	} else if(C[vec]==2){
		numeroVecinosIndice1Aceite--;
	}
	//Ahora hacemos lo mismo para el indice2

	vec=r[indice2];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice2Aceite++;
		}
	}
	vec=l[indice2];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice2Aceite++;
		}
	}
	vec=u[indice2];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice2Aceite++;
		}
	}
	vec=d[indice2];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosIndice2Aceite++;
		}
	}
	//Ahora hay que restar el valor de ind1 que tambien se esta contando
	vec=ind1;
	if(C[vec]==1){
		numeroVecinosIndice2Agua--;
	} else if(C[vec]==2){
		numeroVecinosIndice2Aceite--;
	}
}

void calculaVecinosDiag(int indice1, int indice2){
	int vec;
	numeroVecinosDiagIndice1Agua=0;
	numeroVecinosDiagIndice1Aceite=0;
	numeroVecinosDiagIndice2Agua=0;
	numeroVecinosDiagIndice2Aceite=0;
	//Checkeamos todos los vecinos diagonales del indice 1 y vamos acumulando
	vec=u[r[indice1]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice1Aceite++;
		}
	}
	vec=d[l[indice1]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice1Aceite++;
		}
	}
	vec=l[u[indice1]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice1Aceite++;
		}
	}
	vec=r[d[indice1]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice1Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice1Aceite++;
		}
	}
	
	//Ahora hacemos lo mismo para el indice2

	vec=u[r[indice2]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice2Aceite++;
		}
	}
	vec=d[l[indice2]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice2Aceite++;
		}
	}
	vec=l[u[indice2]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice2Aceite++;
		}
	}
	vec=r[d[indice2]];
	if(vec!=-1){
		if(C[vec]==1){
			numeroVecinosDiagIndice2Agua++;
		} else if(C[vec]==2){
			numeroVecinosDiagIndice2Aceite++;
		}
	}
}

void cambio(int h1,int h2){
	int valor1, valor2;
	valor1=C[h1];
	valor2=C[h2];
	C[h1]=valor2;
	C[h2]=valor1;
	
	// Hay que actulizar los valores de conectado tambien
	// Aqui solo se llega si el cambio es no trivial

	// Si ambos están conectados no hay que tocar nada

	// Si ambos no estan conectados solo hay que comprobar si alguno es liquido y en la primera fila
	if((h1<Lx)&&(C[h1]!=0)){
		//Si h1 esta en la primera fila y es liquido hay que conectarla y revisar sus vecinos.
		conectado[h1]=1;
		revisaVecinosDeCelda(h1);
	}
	if((h2<Lx)&&(C[h2]!=0)){
		//Lo mismo para h2.
		conectado[h2]=1;
		revisaVecinosDeCelda(h2);
	}

	// El resto son cambios conectado<-->desconectado que involucran sí o sí al aire

	if(C[h1]==0){// En h1 hay aire. Entonces en h2 debe haber liquido ya que el cambio es no trivial
		// Ponemos a 0 ambos
		conectado[h1]=0;
		conectado[h2]=0;
		// Revisamos los valores de los vecinos del que va a ser liquido (h2)
		// Si hay algun vecino conectado se conecta tambien
		if(algunVecinoConectadoQ(h2)){
			conectado[h2]=1;
			revisaVecinosDeCelda(h2);
		}
	}
	if(C[h2]==0){// En h2 hay aire
		// Ponemos a 0 ambos
		conectado[h1]=0;
		conectado[h2]=0;
		// Revisamos los valores de los vecinos del que va a ser liquido (h1)
		// Si hay algun vecino conectado se conecta tambien
		if(algunVecinoConectadoQ(h1)){
			conectado[h1]=1;
			revisaVecinosDeCelda(h1);
		}
	}
}

bool algunVecinoConectadoQ(int indice1){
	int vec;
	vec=r[indice1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			return true;
		}
	}
	vec=l[indice1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			return true;
		}
	}
	vec=u[indice1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			return true;
		}
	}
	vec=d[indice1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			return true;
		}
	}
	return false;
}

void revisaVecinosDeCelda(int celda){
	//La celda esta conectada y recien añadida. Hay que mirar todos los posibles vecinos
	int vec,vecinoRevisando;
	longitudVecinos=0;//Reiniciamos la lista
	//printf("Checkeando vecinos\n");
	//fflush(stdout);
	vec=r[celda];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==0){//No esta conectado
			if(C[vec]!=0){//Es liquido
				anadirVecino(vec);//Lo anadimos a la lista para revisar
				//printf("Anadiendo vecino %d C[]=%d conectado[]=%d\n",vec,C[vec],conectado[vec]);
				//fflush(stdout);
			}
		}
	}
	vec=l[celda];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==0){//No esta conectado
			if(C[vec]!=0){//Es liquido
				anadirVecino(vec);//Lo anadimos a la lista para revisar
				//printf("Anadiendo vecino %d C[]=%d conectado[]=%d\n",vec,C[vec],conectado[vec]);
				//fflush(stdout);
			}
		}
	}
	vec=u[celda];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==0){//No esta conectado
			if(C[vec]!=0){//Es liquido
				anadirVecino(vec);//Lo anadimos a la lista para revisar
				//printf("Anadiendo vecino %d C[]=%d conectado[]=%d\n",vec,C[vec],conectado[vec]);
				//fflush(stdout);
			}
		}
	}
	vec=d[celda];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==0){//No esta conectado
			if(C[vec]!=0){//Es liquido
				anadirVecino(vec);//Lo anadimos a la lista para revisar
				//printf("Anadiendo vecino %d C[]=%d conectado[]=%d\n",vec,C[vec],conectado[vec]);
				//fflush(stdout);
			}
		}
	}
	// Ahora vamos a hacer un while haya vecinos que revisar
	while(longitudVecinos>0){
		//printf("Dentro del while. Hay %d vecinos a checkear\n",longitudVecinos);
		//fflush(stdout);
		//Escogemos el primer vecino vecinosArevisar[0]

		vecinoRevisando=vecinosArevisar[0];
		//printf("Checkeando el vecino %d \n",vecinoRevisando);
		//fflush(stdout);
		conectado[vecinoRevisando]=1;//Lo conectamos
		//Revisamos sus vecinos. Hay que ver 
		vec=r[vecinoRevisando];
		if(vec!=-1){//Podemos referenciarlo
			if(conectado[vec]==0){//No esta conectado
				if(C[vec]!=0){//Es liquido
					if(!perteneceVecinoQ(vec)){//No está ya en la lista
						anadirVecino(vec);//Lo anadimos a la lista para revisar
					}
				}
			}
		}
		vec=l[vecinoRevisando];
		if(vec!=-1){//Podemos referenciarlo
			if(conectado[vec]==0){//No esta conectado
				if(C[vec]!=0){//Es liquido
					if(!perteneceVecinoQ(vec)){//No está ya en la lista
						anadirVecino(vec);//Lo anadimos a la lista para revisar
					}
				}
			}
		}
		vec=u[vecinoRevisando];
		if(vec!=-1){//Podemos referenciarlo
			if(conectado[vec]==0){//No esta conectado
				if(C[vec]!=0){//Es liquido
					if(!perteneceVecinoQ(vec)){//No está ya en la lista
						anadirVecino(vec);//Lo anadimos a la lista para revisar
					}
				}
			}
		}
		vec=d[vecinoRevisando];
		if(vec!=-1){//Podemos referenciarlo
			if(conectado[vec]==0){//No esta conectado
				if(C[vec]!=0){//Es liquido
					if(!perteneceVecinoQ(vec)){//No está ya en la lista
						anadirVecino(vec);//Lo anadimos a la lista para revisar
					}
				}
			}
		}
		// Lo eliminamos de la lista
		quitarVecino(vecinoRevisando);
	}
}


void revisaConectados(){
	/*
	// Version antigua
	int ind,indIzq,indDer,vec;
	int half;
	bool hayAire;
	half=Lx/2;
	indIzq=half;
	indDer=half;
	// Empezamos en x=Lx/2 y vamos mirando a izq y derecha en la primera fila
	for(ind=half;ind<Lx;ind++){
		if(C[ind]!=0){
			conectado[ind]=1;
			indDer=ind;
		}
	}
	for(ind=half;ind>0;ind--){
		if(C[ind]!=0){
			conectado[ind]=1;
			indIzq=ind;
		}
	}
	for(ind=indIzq;ind<(indDer+1);ind++){
		//Para cada indice recorremos en vertical hasta encontrar aire
		vec=u[ind];
		// Vemos si el primer vecino es aire
		if(C[vec]==0){
			hayAire=true;
		}else{
			hayAire=false;
		}
		// Hacemos el bucle
		while(!hayAire){
			// Cada vez que no haya aire lo conectamos
			conectado[vec]=1;
			// Comprobamos el vecino de arriba
			vec=u[vec];
			if(C[vec]==0){
				hayAire=true;
			}else{
				hayAire=false;
			}
		}
	}
	*/
	// nueva Version
	int ind;
	for(ind=0;ind<N;ind++){
		conectado[ind]=0;
	}
	// Empezamos en x=Lx/2 y vamos mirando a izq y derecha en la primera fila
	for(ind=0;ind<Lx;ind++){
		if(C[ind]!=0){
			conectado[ind]=1;
			revisaVecinosDeCelda(ind);
		}
	}
}

bool estaraConectadoQ(int i1,int i2){
	// Para ver si esta celda de aire cuando sea ocupada por líquido
	// estará conectada o no cuando se rellene
	// -------------------------------------------------------------------------------------------
	// Estamos suponiendo que se trata de un cambio aire liquido.
	// Si no es trivial (misma especie) y es liquido liquido ambos se mantendrán igual
	// -------------------------------------------------------------------------------------------
	// i1: aire i2: liquido
	// El numero de vecinos que debe tener el aire depende de si el liquido esta conectado o no
	int numVecNecesarios,vec;
	if(conectado[i2]==1){
		// Si el liquido esta conectado necesitamos que haya dos vecinos, uno más del que ya hay y 
		// que va a ser aire cuando se haga el cambio y que estara desconectado
		numVecNecesarios=2;
	} else{
		// Si esta desconectado basta con un vecino.
		numVecNecesarios=1;
	}
	vec=r[i1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			numVecNecesarios--;
			if(numVecNecesarios==0){
				return true;
			}
		}
	}
	vec=l[i1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			numVecNecesarios--;
			if(numVecNecesarios==0){
				return true;
			}
		}
	}
	vec=u[i1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			numVecNecesarios--;
			if(numVecNecesarios==0){
				return true;
			}
		}
	}
	vec=d[i1];
	if(vec!=-1){//Podemos referenciarlo
		if(conectado[vec]==1){//Esta conectado
			numVecNecesarios--;
			if(numVecNecesarios==0){
				return true;
			}
		}
	}
	return false;
}

void calculaInicioDroplet(){
	//int altura;
	int ind,indd;
	//double mayorSalto;
	//int numVecinosMedia;
	//int vecinoDerecha,vecinoIzquierda;
	//int alturaMax,alturaMin,deltaH;
	/////////////////////////////////////////////
	// Metodo de la altura parcial.
	/////////////////////////////////////////////
	
	/*
	altura=0;
	// Primero calculamos cual es la mayor altura de la gota (celda de agua o aceite con mayor altura)
	for(ind=0;ind<N;ind++){
		if((C[ind]==1)||(C[ind]==2)){// si esta lleno
			if(getZ(ind)>altura){// si la altura es mayor
				altura=getZ(ind);
			}
		}
	}
	// En cuanto una celda supere esa altura limite (en este caso 1/3 de la total, paramos)
	x_droplet=0;
	for(ind=0;ind<Lx;ind++){
		indd=ind+Lx*(altura/3);
		if((C[indd]==1)||(C[indd]==2)){
			x_droplet=ind;
			break;
		}
	}
	*/
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// Despues de la medida normal relativa hacemos el desplazamiento por si hay agua
	//////////////////////////////////////////////////////////////////////////////////////////
	// Metodo antiguo que desplazaba la medida antterior por qsi se colaba agua la menisco. Obsoleto ya, el agua se puede colar.
	
	/*
	for(ind=x_droplet;ind>=0;ind--){
		for(indd=(Ly-1);indd>=0;indd--){
			if(C[ind+indd*Lx]==1){
				//printf("ind %d indd %d\n",ind,indd);
				//printf("C[ind+indd*Lx]= %d \n",C[ind+indd*Lx]);
				//printf("x d cambiado\n");
				x_droplet=ind;
			}
		}
	}
	*/
	
	/////////////////////////////////////////////
	// Metodo de thickness permitido
	/////////////////////////////////////////////
	//En este metodo se permite solo un numero concreto de capas (en este caso 2)
	
	/*
	for(ind=0;ind<Lx;ind++){
		indd=ind+Lx*2;//thickness de 2 permitido
		if((C[indd]==1)||(C[indd]==2)){
			x_droplet=ind;
			break;
		}
	}
	*/
	
	/////////////////////////////////////////////
	// Metodo de thickness permitido V2
	/////////////////////////////////////////////
	//En este metodo se permite solo un numero concreto de capas (en este caso 2)
	// Ademas se pide que este conectado a la gota via vecinos a la derecha
	
	
	for(ind=0;ind<Lx;ind++){
		indd=ind+Lx*2;//thickness de 2 permitido
		if((C[indd]==1)||(C[indd]==2)){
			if(conectadoGotaQ(indd)){
				x_droplet=ind;
				break;
			}
		}
	}
	
	
	/////////////////////////////////////////////
	// Metodo de la media movil
	/////////////////////////////////////////////
	
	/*
	for(ind=0;ind<Lx;ind++){
		alturas[ind]=0;
		for(indd=0;indd<Ly;indd++){
			if(C[ind+indd*Lx]==0){
				alturas[ind]=indd;
				break;
			}
		}
	}
	numVecinosMedia=3;
	for(ind=numVecinosMedia;ind<(Lx-numVecinosMedia);ind++){
		alturaMedia[ind]=0.0;
		alturaMedia[ind]=alturaMedia[ind]+alturas[ind];
		vecinoDerecha=ind;
		vecinoIzquierda=ind;
		for(indd=0;indd<numVecinosMedia;indd++){
			vecinoDerecha=r[vecinoDerecha];
			vecinoIzquierda=l[vecinoIzquierda];
			alturaMedia[ind]=alturaMedia[ind]+alturas[vecinoDerecha];
			alturaMedia[ind]=alturaMedia[ind]+alturas[vecinoIzquierda];
		}
		alturaMedia[ind]=alturaMedia[ind]/((2*numVecinosMedia+1)*1.0);
	}
	x_droplet=0;
	mayorSalto=0.0;
	for(ind=numVecinosMedia;ind<(Lx-numVecinosMedia);ind++){
		if((alturaMedia[ind]-alturaMedia[ind-1])>mayorSalto){
			mayorSalto=alturaMedia[ind]-alturaMedia[ind-1];
			x_droplet=ind;
		}
	}
	*/
	
	/////////////////////////////////////////////
	// Metodo nuevo (delta h)
	/////////////////////////////////////////////
	/*
	alturaMax=0;
	alturaMin=Ly;
	// Primero calculamos cual es la mayor altura de la gota (celda de agua o aceite con mayor altura)
	for(ind=0;ind<N;ind++){
		if((C[ind]==1)||(C[ind]==2)){// si esta lleno de liquido (agua o aceite)
			if(getZ(ind)>alturaMax){// si la altura es mayor
				alturaMax=getZ(ind);
			}
		}
		if(C[ind]==0){// si esta vacio (aire)
			if(getZ(ind)<alturaMin){// si la altura es mayor
				alturaMin=getZ(ind);
			}
		}
	}
	deltaH=alturaMax-alturaMin;
	//printf("alturaMax:%d alturaMin:%d deltaH:%d\n",alturaMax,alturaMin,deltaH);
	altura=( (int) alturaMin+deltaH*0.2+0.5 );//El +0.5 es para que haga el round y no el cast entero (Que 4.8-> 5)
	//printf("altura:%d \n",altura);
	x_droplet=0;
	for(ind=0;ind<Lx;ind++){
		indd=ind+altura*Lx;
		//printf("bucle indd:%d \n",indd);
		if((C[indd]==1)||(C[indd]==2)){
			// posible candidato a ser el borde. Checkeamos si estaa conectado al resto de la gota.
			if(conectadoGotaQ(indd)){
				x_droplet=ind;
				break;
			}
		}
	}
	*/
}

bool conectadoGotaQ(int indd){
	int vec,acum;
	//int lim;
	acum=0;
	/*
	vec=r[indd];//vec 1
	//El limite se fija como 50 casillas a la derecha o Lx (para no salirnos del sistema)
	if((getX(vec)+50)>Lx){
		lim=Lx;
	}else{
		lim=getX(vec)+50;
	}
	//printf("FUERA %d\t%d\n",vec,lim);
	while(getX(vec)<lim){//hasta llegar lejos
		//printf("DENTRO %d\t%d\n",vec,lim);
		if(C[vec]==0){
			return false;
		}else{
			vec=r[vec];
		}
	}
	return true;
	*/
	
	vec=r[indd];//vec 1
	if(C[vec]==0){
		return false;
	}else{
		vec=r[vec];//vec 2
		if(C[vec]==0){
			return false;
		}else{
			vec=r[vec];//vec 3
			if(C[vec]==0){
				return false;
			}else{
				//Una vez comprobado que los 3 primeros vecinos no son aire exigimos que al menos 6 de los 7 proximos esten llenos
				vec=r[vec];//vec 4
				acum+=(C[vec]+1)/2;//Si es agua (1) o aceite (2) suma 1 si es aire suma 0
				vec=r[vec];//vec 5
				acum+=(C[vec]+1)/2;
				vec=r[vec];//vec 6
				acum+=(C[vec]+1)/2;
				vec=r[vec];//vec 7
				acum+=(C[vec]+1)/2;
				vec=r[vec];//vec 8
				acum+=(C[vec]+1)/2;
				vec=r[vec];//vec 9
				acum+=(C[vec]+1)/2;
				vec=r[vec];//vec 10
				acum+=(C[vec]+1)/2;
				if(acum>5){
					return true;
				}else{
					return false;
				}
			}
		}
	}
	
	/*
	vec=r[indd];//vec 1
	if(C[vec]==0){
		return false;
	}else{
		vec=r[vec];//vec 2
		if(C[vec]==0){
			return false;
		}else{
			vec=r[vec];//vec 3
			if(C[vec]==0){
				return false;
			}else{
				vec=r[vec];//vec 4
				if(C[vec]==0){
					return false;
				}else{
					vec=r[vec];//vec 5
					if(C[vec]==0){
						return false;
					}else{
						vec=r[vec];//vec 6
						if(C[vec]==0){
							return false;
						}else{
							vec=r[vec];//vec 7
							if(C[vec]==0){
								return false;
							}else{
								vec=r[vec];//vec 8
								if(C[vec]==0){
									return false;
								}else{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	*/
}
