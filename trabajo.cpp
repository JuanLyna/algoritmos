#include <iostream>
#include <fstream>
using namespace std;

const int  clients {8} ;
const int products {5} ; 

void order_double(double m[clients] [products] , double distanceOrd [products] , string productsOrd[products] , string type_products[products] , int clientUp ) //está función solo ordena los km y que se vaya ordenando con los productos y entregas 
{   
   
   for (int i = 0; i < products-1; i++)//hacemos esto para no dañar el array original
   {
        productsOrd[i] = type_products[i] ; 
        distanceOrd[i] = m[clientUp][i] ; 

   };
   
   
   
   for(int i=0; i<products;i++){
		for(int j = 0; j < products-1; j++){
				if(distanceOrd[j]> distanceOrd[j+1]){
					double temp=distanceOrd[j];
					distanceOrd[j] = distanceOrd[i+1];
					distanceOrd[j+1] = temp;
					string tempS = productsOrd[j];
					productsOrd[i] = productsOrd[i+1];
					productsOrd[i+1] = tempS;

				}
		}
	}
   
   
   
        
}


void getTransBetter (double pesoTrans[clients][products] , string nameClient[clients] , string typeProd[products] , int ClientUp)
{
    int cant=0 , better=0 ; 
    for(int i =0; i<clients; i++){
		cout<<"Nombre de Cliente: " <<nameClient[i];
		for(int j = 0; j<products; j++ ){
			if(pesoTrans[i][j]>13000 ){
				cant++;
				cout<<" Producto Transportado: "<<typeProd[j]<<endl;
				if (cant>better){
					better = cant;
					ClientUp= i;
				}
			}
		}
		cant=0;
		
	}

}

void getDistanceBetter (double distanceRecorry[clients][products] ,double distanceOrd[products] , string typeProdOrd[products] , int ClientUp ,int send)
{
    int better= 0 ; 
    for(int i =0; i<products; i++){
		cout<<"El producto : "<<typeProdOrd[i];
		cout<<" con una distancia de : "<<distanceOrd[i]<<endl;
		//mintras muestro, busco el mayor kilometraje
		if( distanceRecorry[ClientUp][i]>better){
			better=  distanceRecorry[ClientUp][i];
			send= i;
		}
	}
}

int main () 
{   //Creó las variables para trabajar 

    int num_client , num_product , clientUp =0 , send =0 ,cl=0 ,pr =0  ; //clientUp y send sirven para guardar al cliente q hizo más transportes de determinado kg
    string  name_clients[clients ] {} , type_products [5] {} ,productsOrd[]{} ; 
    string nameC ; 
    
    double peso , distance  ;
    double pesoTrans[clients][products] {} , distanceRecorry[clients][products] {} , distanceRecorryOrd[products]{};
    char sep ;
    int entregas[products] {};  
   //archivo de donde vamos a empezar a sacar los datos
    ifstream archi ; 
    fstream archiNombres ; 
    //INTRODUCIMOS LOS NOMBRES
    archiNombres.open("Nombres.txt");
	if(!archiNombres){
		cout<<"No se ha encontrado el archivo";
	}

    //carga de datos de los nombres
	while(getline(archiNombres,nameC))
    {
        
        if(cl<clients){
			
			name_clients[cl]=nameC;
            
		}else{
			type_products[pr]=nameC;
			pr++;
		}
		cl++; 
	}
	archiNombres.close();

    

     /*Abrimos el archivo para editarlo */
    archi.open("entrada.txt") ;
    if (!archi  )
    {cout<< "No se ha encontrado el archivo";
    return 1 ; }
  
   
    /*Ingresamos los datos al archivo Entrada*/
    cout<<"Cargando los datos . . . . . ."<<endl ; 
    /**/ while(archi>>num_client>>num_product>>peso>>distance) 
    {   
        pesoTrans[num_client][num_product]+=peso ; 
        distanceRecorry[num_client][num_product]+=distance  ; 
        entregas[num_product]++; 

    }   
    cout<<"----DATOS CARGADOS----" <<endl ; 
    
    archi.close () ;
   
   
    getTransBetter(pesoTrans,name_clients,type_products,clientUp) ; 
    order_double(distanceRecorry,distanceRecorryOrd,productsOrd , type_products,clientUp);
    getDistanceBetter(distanceRecorry,distanceRecorryOrd,type_products,clientUp,send);

    cout<<"El producto : " <<type_products[send];
	cout<<" tiene un total de: "<<entregas[send]<<" entregas";
    return 0;
 }
