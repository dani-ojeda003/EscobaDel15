
#include <iostream>
#include <conio.h>//Libreria para el getch()
#include<stdlib.h>//Libreria para los numeros randoms
#include<time.h>//Libreria para los numeros randoms

using namespace std;

struct lista{int carta; lista *sgte=NULL;};//Lista para cartas en la mesa y cartas tomadas por el jugador

//Funciones con uso general
int transformar_mostrar(int carta)
{
     if(carta>=1 && carta<=10){
         if(carta>=8 && carta<=10){
             return carta+2;
         }else{
             return carta;
          }
     }

     if(carta>=11 && carta<=20){
         if(carta>=18 && carta<=20){
             return carta-8;
         }else{
             return carta-10;
          }
     }

     if(carta>=21 && carta<=30){
         if(carta>=28 && carta<=30){
             return carta-18;
         }else{
             return carta-20;
          }
     }

     if(carta>=31 && carta<=40){
         if(carta>=38 && carta<=40){
                return carta-28;
         }else{
            return carta-30;
          }
     }

 }
 string devolverpalo(int i)
{
    if(i>=1 && i<=10)
        {return "Basto";}
    if(i>=11 && i<=20)
        {return "Espada";}
    if(i>=21 && i<=30)
        {return "Oro";}
    if(i>=31 && i<=40)
        {return "Copa";}
}
int transformar(int carta)
 {
     if(carta>=1 && carta<=10){
         return carta;
     }
     if(carta>=11 && carta<=20){
         return carta-10;
     }
     if(carta>=21 && carta<=30){
         return carta-20;
     }
     if(carta>=31 && carta<=40){
         return carta-30;
     }
 }

//-------------------------------------
//Funciones para calcular puntaje

bool SieteDeOro(lista** pozo_jugadores,int n,int &jugador)
{
    lista* pozo=NULL;
    for(int i=0;i<n;i++){
        lista* pozo=pozo_jugadores[i];
        while(pozo!=NULL){
           if(pozo->carta==27){jugador=i;return true;}
           pozo=pozo->sgte;
        }
    }
    return false;
}
bool Mayoria(lista** pozo_jugadores,int n,int &j)
{
    lista* pozo=NULL;
    int aux,cant=0;
    j=0;
    for(int i=0;i<n;i++){
        lista* pozo=pozo_jugadores[i];
        aux=0;
        while(pozo!=NULL){
            aux++;
            pozo=pozo->sgte;
        }
        if(aux > cant){
            cant=aux;j=i+1;
        }

    }
    if(j!=0){
        return true;
    }
    return false;
}
bool Oros(lista** pozo_jugadores,int n,int &k)
{
    int aux,cant=0;
    k=0;
    lista* pozo=NULL;
    for(int i=0;i<n;i++)
    {
        lista* pozo=pozo_jugadores[i];
        aux=0;
        while(pozo!=NULL)
        {
            if(pozo->carta>=21 &&pozo->carta<=30){aux++;}
            pozo=pozo->sgte;
        }
        if(aux>cant){cant=aux;k=i+1;}
    }
    if(k!=0){return true;}
    return false;
}

bool Sietes(lista** pozo_jugadores,int n,int &z)
{
    lista* pozo=NULL;
    int aux,cant=0;
    z=0;
    for(int i=0;i<n;i++){
        lista* pozo=pozo_jugadores[i];
        aux=0;
        while(pozo!=NULL){
            if( transformar(pozo->carta)==7 ){aux++;}
            pozo=pozo->sgte;
        }
        if(aux>cant){
            cant=aux;z=i+1;
        }
    }
    if(z!=0){
        return true;
    }

    return false;
}

void calcular_puntaje(lista** pozo_jugadores,int puntuacion[],int n)
{
    int i=0,j=0,k=0,z=0;
      if(Mayoria(pozo_jugadores,n,j)){puntuacion[j-1]++;}
      if(SieteDeOro(pozo_jugadores,n,i)){puntuacion[i]++;}
      if(Oros(pozo_jugadores,n,k)){puntuacion[k-1]++;}
      if(Sietes(pozo_jugadores,n,z)){puntuacion[z-1]++;}
}

//-------------------------------------
//Funciones para el manejo de las listas

lista *ObtenerUltimo (lista *L)
{
    while (L && L->sgte){
        L=L->sgte;
    }

    return L;
}

void InsertarLista(lista*& mesa,int carta)
    {
        lista *aux= mesa;
        if (mesa!=NULL){
            aux=ObtenerUltimo(mesa);
            aux->sgte= new lista();
            aux->sgte->carta=carta;
        }else{
            mesa= new lista();
            mesa->carta=carta;
        }
        return;
    }

void BorrarLista(lista*& borrar) {
    while(borrar!=NULL ) {
        lista* aux = borrar;
        borrar = borrar->sgte;
        delete aux;
    }
}

void CambiarDeLista(lista* retorno, lista*& mesa, lista**& pozo_jugadores,int i)
 {
lista* aux=mesa;
     lista* aux_p=pozo_jugadores[i];
     lista* anterior=NULL;

     while(retorno!=NULL)
        {

            while(aux!=NULL)
                {

                    if(aux->carta==retorno->carta)
                    {
                        if(anterior==NULL){mesa=mesa->sgte;}
                        else{anterior->sgte=aux->sgte;}
                        while(aux_p->sgte!=NULL){aux_p=aux_p->sgte;}
                        aux_p->sgte=aux;
                        aux_p->sgte->sgte=NULL;
                        break;
                    }
                    anterior=aux;
                    aux=aux->sgte;
                }

            aux=mesa;
            retorno=retorno->sgte;
            aux_p=pozo_jugadores[i];
        }
 }

//-------------------------------------




//-------------------------------------
//Funciones para crear la baraja

bool verificar (int num, int mazo[])//Verifica si la carta ya se cargo
{
    for (int i=0; i<40; i++){
        if (num==mazo[i]){
            return true;
        }

    }
    return false;
}

void barajear(int mazo[])//Crea una baraja aleatoria
{
    int num=0;
    for (int i=0; i<40; i++){
        do{
            num = 1+ rand() % 40;
        } while (verificar (num, mazo));
        mazo[i] = num;
    }
}





  void mostrar_mesa(lista* mesa)
{
    lista *aux=mesa;
    cout<<"Las cartas de la mesa son"<<endl;
    while(aux!=NULL){
        cout<<transformar_mostrar(aux->carta)<<" "<<devolverpalo(aux->carta)<<"||"<<endl;
        aux=aux->sgte;
    }
}

bool verificar_mano(int** players,int n)
{
    for (int i = 0; i < 3; i++){
        if (players[n-1][i]!=0){
            return false;
        }
     }
    return true;
}

void repartir_jugador(int mazo[], int** jugadores, int cant)
 {
    for (int i = 0; i < cant; ++i){
        for (int j = 0; j < 3; ++j){
            for (int k = 0; k < 40; ++k){
                if (mazo[k] != 0){
                    jugadores[i][j] = mazo[k];
                    mazo[k] = 0;
                    break;
                }
            }
        }
     }
 }

void repartir_mesa(int mazo[], lista*& mesa)
{
  int i=0;
  while(mazo[i]==0){i++;}
  for(int j=0;j<4;j++){
      InsertarLista(mesa,mazo[i]);
      mazo[i]=0;
      i++;
  }
}

void reiniciar(lista** &pozo_jugadores,int** &players,lista* &mesa,int n,int puntuacion[],int baraja[])
{
    for(int i=0;i<40;i++){baraja[i]=0;}
    barajear(baraja);
    calcular_puntaje(pozo_jugadores,puntuacion,n);
    for(int i=0;i<n;i++){
        BorrarLista(pozo_jugadores[i]);
    }
	BorrarLista(mesa);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			players[i][j]=0;
		}
	}
   for(int i=0;i<n;i++){cout<<"puntuacion "<<i<<"°:"<<puntuacion[i]<<endl;}
   getch();
}

void mostrar_mano(int** jugadores,int n)
{
     cout<<"Las cartas del Jugador "<< n <<" son:"<<endl;
     for(int j=0;j<3;j++){
            cout<<transformar_mostrar(jugadores[n-1][j]);
            if(jugadores[n-1][j]!=0){
                cout<<" "<<devolverpalo(jugadores[n-1][j]);
            }
            cout<<"|| ";

     }
     cout<<endl;
}




bool hay_15(int** jugadores,lista* mesa,int n,int carta,lista*& retorno){
   int contador=0,suma=transformar(jugadores[n-1][carta-1]),posc=0,posc2=0,memoria=transformar(jugadores[n-1][carta-1]);
   lista* aux=mesa;
   while(aux!=NULL){contador++;aux=aux->sgte;}//Cuenta la cantidad de cartas en mesa
   aux=mesa;
   int *vec=new int[contador]();
   for(int i=0;i<contador;i++){
      vec[i]=aux->carta;
      aux=aux->sgte;
   }
   while(true){

       while(true){

           for( int i=0 ; i<contador ; i++ ){

               if( posc>0 && i!=0 ){
                   memoria+=transformar(vec[i+posc+posc2]);
                   InsertarLista(retorno,vec[i+posc+posc2]);
               }

               for(int j=0;j<contador;j++){

                    suma=memoria;
                    if(j+posc+posc2+i>=contador){break;}
                     if(posc2+posc>=1){
                         suma+=transformar(vec[posc+posc2+i+j+1]);
                         if(suma==15){
                         InsertarLista(retorno,vec[j+i+posc+posc2+1]);
                         delete[] vec;
                         return true;
                         }
                     }else{suma+=transformar(vec[i+j]);
                          if(suma==15){
                          InsertarLista(retorno,vec[j+i]);
                          delete[] vec;
                          return true;
                      }

                  }
               }
               if( posc==0 && posc2==0){
                   memoria+=transformar(vec[i]);
                   InsertarLista(retorno,vec[i]);
               }
               if(posc+i+1+posc2>=contador){break;}
           }
          BorrarLista(retorno);
          if( (posc+posc2+posc2+1)>=contador ){break;}
          posc++;
          InsertarLista(retorno,vec[posc]);
          memoria=transformar(jugadores[n-1][carta-1]);
          memoria+=transformar(vec[posc]);
       }
       if( (posc2+1)>=contador ){return false;}
       posc2++;
       InsertarLista(retorno,vec[posc2]);
       memoria=transformar(jugadores[n-1][carta-1]);
       memoria+=transformar(vec[posc2]);
   }
 }

 bool verificar_mesa(lista* mesa) {
   if (mesa!= NULL){
            return false;
        }
   return true;
}

void play(int** &jugadores,lista* &mesa,lista** &pozo_jugadores,int n,int puntuacion[]){
    int posc;
    //verifica cuantas cartas tiene en la mano
    lista* retorno=NULL;
    while(true)
        {
         cout<<"Elegi la posicion de la carta que vas a jugar"<<endl;
         cin >> posc;
         if(posc<=3 && posc>=1){if(jugadores[n-1][posc-1]!=0){break;}}
        }
    if(hay_15(jugadores, mesa, n, posc, retorno))
        {
            InsertarLista(pozo_jugadores[n-1],jugadores[n-1][posc-1]);
            jugadores[n-1][posc-1]=0;
            CambiarDeLista(retorno,mesa,pozo_jugadores,n-1);
            if(verificar_mesa(mesa))
                {
                    puntuacion[n-1]++;

                };
            BorrarLista(retorno);
        }
    else
        {
          InsertarLista(mesa,jugadores[n-1][posc-1]);
          jugadores[n-1][posc-1]=0;
          delete retorno;
        }
}



bool verificar_juego(int** jugadores,int baraja[],lista* mesa,int n)
{
    if(baraja[39]==0){return true;}
    if(baraja[36]==0 && verificar_mesa(mesa)){return true;}
    if(baraja[39-(3*n)]==0 && verificar_mano(jugadores,n)){return true;}
    return false;
}





int main()
{
    srand(time(NULL));
    int n;
    cout <<"Bienvenido a la Escoba 15" << endl;
    while(true)//Verifica que la cantidad de jugadores sea 2 o 3
        {
         cout <<"Indique la cantidad de Jugadores:";
         cin >> n;
         system("cls");
         if(n<4 && n>1){break;}
        }
        int *puntuacion=NULL;
        puntuacion=new int[n];
        for(int i=0;i<n;i++){puntuacion[i]=0;}


        int **players=new int*[n];//Primera dimension de la matriz
        for (int i = 0; i < n; ++i)
            {
                players[i] = new int[3]; // Segunda dimensión
            }


        int baraja[40]={0};//0->La carta en esa pocision ya fue repartida || 1-10=Basto, 11-20=Espada, 21-30=Oro, 31-40=Copas || 10->8 11->9 12->10
        lista *mesa=NULL; //Lista de las cartas en la mesa

        lista **pozo_jugadores=new lista*[n];
        for(int i=0;i<n;i++)
            {
                pozo_jugadores[i]=NULL;
            };//Lista de las cartas tomadas, tiene que ser un vector N de listas
        barajear(baraja);
        repartir_mesa(baraja, mesa);
        repartir_jugador(baraja,players,n);

        int i=1;//contador para saber que jugador toca

        while(true)
            {
               mostrar_mesa(mesa);
               mostrar_mano(players, i);
               play(players,mesa,pozo_jugadores,i,puntuacion);//El Jugador elige la carta y la maquina juega la primera combinacion que encuentre, si es escoba suma 1 a puntuacion
               if(puntuacion[i-1]>=15){ cout<<"Gano el Jugador"<< i <<"con "<<puntuacion[i-1]<<" puntos." ;return 0;}
               if(verificar_juego(players,baraja,mesa,n))
                     {reiniciar(pozo_jugadores,players,mesa,n,puntuacion,baraja);}
               if(puntuacion[i-1]>=15){return 0;}
               if(verificar_mesa(mesa))
                     {repartir_mesa(baraja,mesa);}//verifica si la mesa necesita repartir
               if(verificar_mano(players,n) && i==n)
                     {repartir_jugador(baraja,players,n);}
               if(verificar_juego(players,baraja,mesa,n))
                     {reiniciar(pozo_jugadores,players,mesa,n,puntuacion,baraja);repartir_jugador(baraja,players,n);}


               i++;
               if(i>n){i=1;}
               system("cls");
            }

}
