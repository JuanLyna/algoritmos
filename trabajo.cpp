#include <iostream>
#include <fstream>
using namespace std;
/*función que examina los datos */
const int  clients {8} ;
const int products {5} ; 
//falta hacer el punto 2 y 3  , tienes que hayar una forma de ordernar los km y buscar la inforamción del producto al mismo tiempo 
void order_double(float m[clients] [products] , int c , string n[clients] , string type_products[clients] , int entregas[clients] ,int e[clients]) //está función solo ordena los km y que se vaya ordenando con los productos y entregas 
{   
   int temp  ;
    
        for (int  i = 0; i < products ;i++)
        {
            for (int j = 0; j < products ; j++)
            {
                if(m[c][j]>m[c][j+1])
                {
                    temp= m[c][j] ;
                    m[c][j] = m[c][j+1] ;
                    m[c][j+1] =temp ; 

                    n[j]=type_products[j+1] ;
                    n[j+i] = type_products [j] ;

                    e[j] = entregas [j+1] ; 
                    e[j+1] = entregas[j];
                }
            }
            
        }
        
}

void getTrans (float pesoTrans[clients][products]  , string name_clients[clients] ,string type_products[products] , float distanceRecorry[clients][products] , int entregas[products]) 

{   int count , mayor=0 , clientPosition ; //el clientPosition sirve para el punto 2 , el count y mayor es para saber cuantas entregas de ese producto hizo ese cliente y si fue el que mayor hizo entregas superando los 1300kg 
    int e[clients] ; //punto 2 para evitar desordenar el array de entregas
    string n[products] ; //punto 2  para evitar desordenar el array de producos

    //bucle para iterar sobre todos los clientes y matrices para así buscar quien ha cumplido la condición 
    for (int i = 0; i < clients; i++)
    {   
        count =0; //reiniciamos el contador 

        cout<<"El cliente: "<<name_clients[i]<<endl ;
        //bucle para iterar sobre la matrices de pesos transportados y buscar quien ha transportado >1300 kg 
        for (int j = 0; j < products; j++)
        {   
           //muestro los productos que cumplen el requisito
           if(pesoTrans[i][j]>1300) 
            {   
                cout<<"Ha trasportado el producto: "<<type_products[j] <<" con un peso total de "<<pesoTrans[i][j]<<"kg"<<endl ; 
                count++ ;  //contador  para saber cuantas entregas hizo el cliente mayores a 13000kg
              
            }
           
        }
         if(count ==0 )  
            {
               cout<<"No ha transportado ningún producto con peso mayor a 1300.00 kg" <<endl; 
            }   
        if(count>mayor) //usamos esta sentencia para saber si está posición de cliente (i) es la que hizo mayores entregas  
         {
            mayor=count; //guardamos la variable
            clientPosition = i; //guardamos la posición del cliente que hizo la mayor cantidad de compras para el punto 2 
             }
        
    } 
    //acá iniciamos el punto 2 donde usamos la matriz de de distanceReccory en la posición del cliente que tiene mayores entregas con 1300kg (lo sacamos del bucle de arriba) y ordenamos de forma ascendente pero creamos un array de nombres y entregas para evitar 
    // editar el original 

 order_double(distanceRecorry , clientPosition , n , type_products ,  entregas ,e) ; //ejecutamos la función para ordenar las matrices y vectores de forma ascendente
    //tenemos la posición del cliente que cumple el requisito , así que solo lo cargamos
    cout<<"El cliente con mayor cantidad de productos que han superado los 1300kg es:  "<< name_clients[clientPosition]<<endl;
 
 //2 bucle para mostrar las distancias recorridas  lo cúal ya están ordenadas
 for (int i = 0; i < products; i++)
 {
  
    cout<<" y ha transportado el producto : " << n[i]<< " una distancia total de  : "<<distanceRecorry[clientPosition][i]<<"KM"<<endl ; 

 }

  //como la matriz está ordenada de mayor a menor  con su producto  y entregas correspondiente , entonces solo listo el último elemento del array con el producto correspondiente

    cout<<"La mayor distancia recorrida fue de "<< distanceRecorry[clientPosition][products-1]<<"km"<<endl<<" siendo el producto " << n[products-1]<<endl <<"Con una cantidad total de entrega proveniente de todos los clientes : " <<e[products-1];
}


int main () 
{   //Creó las variables para trabajar 

    int num_client , num_product  ;
    string  name_clients[clients ] {"Bat" , "Bit" , "Hiru" , "Lau" , "Bost", "Sei" , "Zazpi" , "Zortzi"} , type_products [5] {"Alimenticios" , "Electrónicos" , "Metálicos" ,"Textiles" , "Químicos"} ; 
    float peso , distance  ;
    float pesoTrans[clients][products] {} , distanceRecorry[clients][products] {};
    char sep ;
    int entregas[products] {};  
   //archivo de donde vamos a empezar a sacar los datos
    ifstream archi ; 
   

     /*Abrimos el archivo para editarlo */
    archi.open("entrada.txt") ;
    if (!archi  )
    {cout<< "No se ha encontrado el archivo";
    return 1 ; }
  
   
    /*Ingresamos los datos al archivo*/
    cout<<"Cargando los datos . . . . . ."<<endl ; 
    /**/ while(archi>>num_client>>num_product>>peso>>distance) 
    {   
        pesoTrans[num_client][num_product]+=peso ; 
        distanceRecorry[num_client][num_product]+=distance  ; 
        entregas[num_product]++; 

    }   
    cout<<"----DATOS CARGADOS----" <<endl ; 
    //está función resuelve el punto 2 y 3  
    getTrans(pesoTrans, name_clients ,type_products ,distanceRecorry ,entregas);
    
    
    
    archi.close () ;
   
    return 0;
 }