

# include <stdio.h>
# include <stdlib.h>


/* Prototipos de las funciones utilizadas*/
int ***generarMatriz(int *cursor,int *numF,int *numC,char nombre[]);
int buscarImagen(int ***m1,int ***m2,int numF,int numF2,int numC,int numC2);
int encontrarImagen(int ***m1, int ***m2,int numF,int numF2,int numC,int numC2);
int comparar(int m[3],int m2[3]);
int ***voltearImagen(int ***m,int *fila,int *columnas);


/*Funcion Principal*/
int main(){
	

	int cursor;  //Esta variable cuenta el numero de caracteres, se usa para las imagenes a buscar
	int nf,nc,np;
	int numFp, numCp;
	
	int ***imagen; //Aqui se amlacena la imagen principal
	int ***imagenB; //Aqui se iran almacenando las imagenes a buscar
	
	int busqueda;
	int numImagen;
	FILE *archivo;

	
	int numF,numC;	
	char nombre[]="imagenPrincipal.txt";
	char nombre2[]="imagenBuscar.txt";
	
	archivo=fopen("resultado.txt","w"); //Archivo donde se escribe el resultado
	numImagen=1;
	busqueda=0;
	cursor=0;
	
	
	imagen = generarMatriz(&cursor,&numF,&numC,nombre);
	
	numFp=numF; //filas de la matriz principal
	numCp=numC; // columnas de la imagen principal
	
	cursor =0;
	
	
	/* En este ciclo se hace todo el proceso de busqueda*/
	while(1>0){
		imagenB=generarMatriz(&cursor,&numF,&numC,nombre2); // Se almacena la imagen a buscar en cada iteracion
	
		if(imagenB==0){    // Al cumplirse esta condicion se termina el ciclo 
			free(imagen);
			free(imagenB);
			break;
		}


		busqueda=buscarImagen(imagen,imagenB,numFp,numF,numCp,numC); // Se comienza la busqueda de la imagen seleccionada
		
		/* En este secuencia se realiza la escritura en el archivo resultado dependiendo del caso*/
		if(busqueda==1){
			fprintf(archivo,"imagen %i",numImagen);
			fprintf(archivo,"%s"," :encontrada\n");
			numImagen++;

		}
		else{
			fprintf(archivo,"imagen %i",numImagen);
			fprintf(archivo,"%s"," :No encontrada\n");
			numImagen++;
			
		}
		
		free(imagenB);
		
	}
	fclose(archivo);
	printf("El programa se ejecuto correctamente");
	return 0; // Aqui finaliza la ejecucion del programa
}



/** Funcion encargada de generar las matrices que representan a las imagenes**/
/** Para el caso de las imagenes de busqueda se urilizan dos variables que se encargan**/
/** De contar el numero de caracteres recorridos en cada interacion para poder extraer cada imagen de busqueda**/
/* ENTRADA: Un  entero que permite definir que imagen se esta buscando, el numero de filas de la matriz a crear*/
/* Y una cadena de caracteres con el nombre del archivo*/
/* SALIDA: Se retorna la direccion de memoria de la matriz creada*/

int ***generarMatriz(int *cursor,int *numF, int *numC,char nombre[]){
	

	int numFilas;
	int numColumnas;
	int ***m; // Esta funcion retorna la direccion de memoria de m
	
	char cadena[4];
	char caracter; // aqui se van almacenando los caracteres leidos 
	char numMatrizf[100]; //Almacena el numero de filas que puede ser de hasta 100 caracteres
	char numMatrizc[100]; //Almacena el numero de columnas que puede ser de hasta 100 caracteres
	int nf,nc,np,i; // Estas variables corresponden a diferentes contadores usado en la funcion
	int numero;
	
	FILE *archivo;
	archivo=fopen(nombre,"r");
	if(archivo==NULL){
		printf("El archivo no existe");
		exit(1);
	}
	
	/* En este ciclo se avanza el cursor hata el punto en que quedo*/
	/* en la ultima iteracion, con el fin de capturar la siguiente imagen de busqueda*/
	i=0;
	while(i<*cursor){
		
		if(feof(archivo)!=0){
			return 0;
		}
		
		fgetc(archivo);
		i=1+i;
	}
	
	/* En esta secuencia se define el numero de filas de la matriz*/
	caracter=fgetc(archivo);
	numMatrizf[0]=caracter;
	++*cursor;
	i=1;
	while(caracter!=32){
		
		caracter=fgetc(archivo);
		if(caracter==32){
			break;
		}
		numMatrizf[i]=caracter;
	
		++*cursor;
		i++;
	}
	++*cursor;
	numFilas=atoi(numMatrizf);
	
	/* En esta secuencia se define el numero de columnas de la matriz*/
	caracter=fgetc(archivo);
	numMatrizc[0]=caracter;
	i=1;
	++*cursor;
	while(caracter!=10){
		
		
		caracter=fgetc(archivo);
		if(caracter==10){
			break;
		}
		numMatrizc[i]=caracter;

	
		++*cursor;
		i++;
	}
	++*cursor;
	numColumnas=atoi(numMatrizc);
	

	/* En esta secuencia se reserva la memoria que ha de ocupar la matriz*/
	m=(int***)malloc(numFilas*sizeof(int**));
	if(m==NULL){
		printf("No se pudo reservar espacion en la memoria");
		exit(1);
	}
	
	for(nf=0;nf<numFilas;nf++){
		m[nf]=(int**)malloc(numColumnas*sizeof(int*));
		if(m[nf]==NULL){
			printf("No se pudo reservar espacio en la memoria");
			exit(1);	
		
		}
	}

	
	for(nf=0;nf<numFilas;nf++){
		for(nc=0;nc<numColumnas;nc++){
			m[nf][nc]=(int*)malloc(3*sizeof(int));
			if(m[nf][nc]==NULL){
				printf("No se pudo reservar espacio en la memoria");
				exit(1);
			}	
		}
	}
	

	
	
	nf=0;
	nc=0;
	np=0;
	i=0;
	/*En este ciclo se forma la matriz tomando los elementos del archivo*/
	while(feof(archivo)==0 && caracter!=45){
		caracter=fgetc(archivo);
		
		*cursor=*cursor+1; // Esta variable cuenta cuantos caracteres se avanza para la proxima iteracion
	
		if(nf>=numFilas){
			break;
		}
		else if(caracter==44){
			cadena[3]='\0';
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			i=0;
			np++;
			
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
			
		}
		else if(caracter==32){
			
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			i=0;
			np=0;
			nc++;
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
			
		}
		else if(caracter==10){
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			nf++;
			nc=0;
			i=0;
			np=0;
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
		}
		else{
			cadena[i]=caracter;
			i++;
		}
		
		
	}
	
	if(nf<numFilas){  //Esta codicion se utiliza en caso de que no exista un salto de linea al final
		numero=atoi(cadena);
		m[nf][nc][np]=numero;
	}
	
	fclose(archivo);
	
	
	
	
	i=0;
	while(i<5){    // Se avanza la cantidad de caracteres que ocupan los giones para las imagenes de busqueda
		*cursor=*cursor+1;
		i++;
	}
	
	*numF=numFilas;
	*numC=numColumnas;
	
	return m;
	
}


/** Esta funcion se encarga de controlar la busqueda de las imagenes **/
/** De tal forma que se encarga de voltearlas y llamar a otra funcion que realiza la busqueda**/
/*ENTRADA: las matriz principal y aquella que se desea buscar, asi como las filas y columnas de estas*/
/*SALIDA: 0 si no se encuentra la imagen, 1 si se encuentra la imagen*/

int buscarImagen(int ***m1,int ***m2,int numF,int numF2,int numC,int numC2){
	
	int busqueda;
	int i;
	
	i=0;

	while(i<4){
		busqueda=encontrarImagen(m1,m2,numF,numF2,numC,numC2); // Funcion que busca la imagen en la matriz principal
		
		if(busqueda==1){
			return 1; 
			
		}
		m2=voltearImagen(m2,&numF2,&numC2); // Funcion que se encarga de voltear la imagen
		i++;
	}
	return 0;
}






/** Funcion que se encarga de buscar la matriz dada en la principal**/
/*ENTRADA: Las dos matrices  y sus numeros de filas y columnas*/
/*SALIDA: 1 si se encontro la imagen, o si esta no se encuentra*/

int encontrarImagen(int ***m1, int ***m2,int numF,int numF2,int numC,int numC2){

	int pivote[2]; // Arreglo de enteros que actua como pivote  para el inicio de una secuencia de comparaciones
	int nf,nc;
	int nf2,nc2;
	int comparacion;
	
	nf=0; //Contador filas de la matriz principal
	nc=0; //Contador columna de la matriz principal
	nf2=0; //Contador filas de la matriz buscada
	nc2=0; // Contador columna de la matriz buscada
	pivote[0]=0; // Guarda la fila en que se encuentra dl pivote
	pivote[1]=0; //Guarda la columna en que se encuentra el pivote
	comparacion=0; // valor a ser retornado
	
	/* Este ciclo se encarga de realizar la busqueda de la imagen mediante el uso de un pivote*/
	while(nf<numF){
		
		comparacion=comparar(m1[nf][nc],m2[nf2][nc2]); //Se encarga de comparar las secuencia rgb que conforman a las matrices
	
		if( comparacion==1){
			
			pivote[0]=nf;
			pivote[1]=nc;
			nc++;
			
			while(comparacion==1){
			
				nc2++;
				
				if(nc2>=numC2){
					nf++;
					nc=pivote[1];
					nf2++;
					nc2=0;
					
				}
				if(nf2>=numF2){
					return 1;
				}
				
				if(nc>=numC){
					nf++;
					nc=pivote[1];
				}
				if(nf>=numF){
					break;
				}
				comparacion=comparar(m1[nf][nc],m2[nf2][nc2]);
				nc++;
			}
			
			nf=pivote[0];
			nc=pivote[1]+1;
			nc2=0;
			nf2=0;
			if(nc>=numC){
				nf++;
				nc=0;
			}
		}
		
		else{
			nc++;
			if(nc>=numC){
				nf++;
				nc=0;
			}	
		}
	}
		
		return 0;
}
	
	
	
	
/** Esta funcion compara los elementos que conforma a cada matriz]**/
/*ENTRRADA: arreglo de tamaño 3 compuesto por 3 enteros que han de ser comparados*/
/*SALIDA: 1 si la secuencia RGB es igual, 0 si esta es falsa*/
int comparar(int m1[3],int m2[3]){

	int i;
	for(i=0;i<3;i++){
	
		if(m1[i]!=m2[i]){
			return 0;
		}
	}
	return 1;
}


/** Esta funcion se encarga de voltear en 90°  la matriz entregada**/
/*ENTRADA: Matriz que se desea voltear, junto con sus numeros de filas y columnas*/
/*SALIDA: Direccion de memoria de la matriz volteada*/
int ***voltearImagen(int ***imagen,int *filas,int *columnas){
	int ***m; // Nueva matriz que almacenara a aquella entregada como entrada, pero volteada
	int nf,nc; //Contador de fila y columnas de la nueva matriz
	int nf2,nc2; // Contador de fila y columna de la matriz a ser volteada
	int aux;
	
	
	/* En este bloque  se reserva la memoria para la matriz  volteada*/
	m=(int***)malloc(*columnas*sizeof(int**));
	if(m==NULL){
		printf("No se pudo reservar espacion en la memoria");
		exit(1);
	}
	
	for(nf=0;nf<*columnas;nf++){
		m[nf]=(int**)malloc(*filas*sizeof(int*));
		if(m[nf]==NULL){
			printf("No se pudo reservar espacio en la memoria");
			exit(1);	
		
		}
	}

	
	for(nf=0;nf<*columnas;nf++){
		for(nc=0;nc<*filas;nc++){
			m[nf][nc]=(int*)malloc(3*sizeof(int));
			if(m[nf][nc]==NULL){
				printf("No se pudo reservar espacio en la memoria");
				exit(1);
			}	
		}
	}

	
	nf=0;
	nc=0;
	nf2=0;
	nc2=*columnas;	
	/* En este ciclo se voltea en 90° la matriz*/
	while (nc2!=0){
		if(nf2>=*filas){
			nc2--;
			nf++;
			nf2=0;
			nc=0;
		}
		if(nc2==0){
			break;
		}
		m[nf][nc]=imagen[nf2][nc2-1];
		nc++;
		nf2++;
	}
	
	/* Se intercambia el numero de fila con el de columna*/
	aux=*columnas;
	*columnas=*filas;
	*filas=aux;
	return m;
}
