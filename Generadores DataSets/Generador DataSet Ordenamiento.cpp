#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 
using namespace std;

/*
Nombre: generarArchivo
Parametros:
cont string nombre_archivo: nombre del archivo donde se generarán los vectores.
int cantidad_vectores: cantidad de vectores en el archivo.
int tamano_vectoes: tamaño de cada vector.
int rango_max: rago máximo que el valor de cada número puede tomar.

Esta función genera un archivo donde cada linea representa  un vector, donde cada número en la linea es un elemento en el 
vector, este archivo es utilizado como dataset.
*/
void generarArchivo(const string nombre_archivo, int cantidad_vectores, int tamano_vectores, int rango_max){
    ofstream archivo(nombre_archivo);
    if(!archivo.is_open()){
        cout << "Eror al escribir el archivo." << endl;
        return;
    }
    srand(static_cast<unsigned>(std::time(nullptr)));
    
    for(int i = 0; i < cantidad_vectores; i++){
        for(int j = 0; j < tamano_vectores; j++){
            int numero = rand() % rango_max;
            if(j + 1 == tamano_vectores){
                archivo << numero;
            }
            else{
                archivo << numero << " ";
            }
            
        }
        archivo << endl;
    }
    archivo.close();
}

int main(){
    string nombre_archivo = "dataset_ordenamiento.txt";
    int cantidad_vectores = 5000;
    int tamano_vectores = 5000;
    int rango_max = 3000;
    generarArchivo(nombre_archivo, cantidad_vectores, tamano_vectores , rango_max);
    return 0;
}