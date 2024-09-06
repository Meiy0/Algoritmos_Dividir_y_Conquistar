#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 
using namespace std;

void generarArchivo(const string nombre_archivo, int cantidad_matrices, int tamano_matrices, int rango_max){
    ofstream archivo(nombre_archivo);
    if(!archivo.is_open()){
        cout << "Eror al escribir el archivo." << endl;
        return;
    }
    archivo << cantidad_matrices << endl;
    srand(static_cast<unsigned>(std::time(nullptr)));
    
    for(int i = 0; i < cantidad_matrices; i++){
        archivo << tamano_matrices << endl;
        for(int j = 0; j < tamano_matrices; j++){
            for(int k = 0; k < tamano_matrices; k++){
            int numero = rand() % rango_max;
                if(k + 1 == tamano_matrices){
                    archivo << numero;
                }
                else{
                    archivo << numero << " ";
                }
            }
            archivo << endl;
        }
    }
    archivo.close();
}

int main(){
    string nombre_archivo = "dataset_matriz.txt";
    int cantidad_matrices = 40;    //Debe ser multiplo de 2 
    int tamano_matrices = 512;    //Debe ser potencia de 2
    int rango_max = 100;
    generarArchivo(nombre_archivo, cantidad_matrices, tamano_matrices, rango_max);
    return 0;
}