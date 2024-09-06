#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

/*
Nombre: transponerMatriz
Parametros:
vector<vector<int>> &matriz: referencia del vector de vectores que representa la matriz a transponer.
Retorno:
vector<vector<int>> transpuesta: vector de vectores que representa la matriz ya transpuesta.
*/
vector<vector<int>> transponerMatriz(vector<vector<int>> &matriz){
    int tamano_matriz = matriz.size();
    vector<vector<int>> transpuesta(tamano_matriz, vector<int>(tamano_matriz));
    for (int i = 0; i < tamano_matriz; ++i) {
        for (int j = 0; j < tamano_matriz; ++j) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    return transpuesta;
}

/*
Nombre: cubicMultiOpti
Parametros:
vector<vector<int>> &matrizA: referencia del vector de vectores que representa una matriz A. 
vector<vector<int>> &matrizB: referencia del vector de vectores que representa una matriz B. 
Retorno:
vector<vector<int>> matrizC: vector de vectores que representa el producto de matrizA y matrizB.
*/
vector<vector<int>> cubicMultiOpti(vector<vector<int>> &matrizA, vector<vector<int>> &matrizB){
    //Transponer la segunda matriz.
    matrizB = transponerMatriz(matrizB);
    //Calcular la cantidad de filas y columnas de cada matriz.
    int n = matrizA.size();
    //Inicialar la nueva matriz.
    vector<vector<int>> matrizC(n, vector<int>(n, 0));
    //Multiplicar las matrices.
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                matrizC[i][j] += matrizA[i][k] * matrizB[j][k];
            }
        }
    }
    return matrizC;
}

int main(){
    //Abrir archivo de escritura.
    ofstream write("IterativoCubicoOptimizado.txt");
    if(!write.is_open()){
        cout << "Eror al escribir el archivo." << endl;
        return 0;
    }
    //Abrir archivo de lectura.
    ifstream file("dataset_matriz.txt");
    if(!file.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }
    //Trabajar con ambos archivos.
    double tiempo = 0;
    int cantidad_matrices;
    int tamano_matrices;
    vector<vector<int>> matrizA;
    vector<vector<int>> matrizB;
    file >> cantidad_matrices;
    for(int i = 0; i < cantidad_matrices / 2; i++){
        file >> tamano_matrices;
        //Leer la primera matriz.
        matrizA.resize(tamano_matrices, vector<int>(tamano_matrices, 0));
        for(int i = 0; i < tamano_matrices; i++){
            for(int j = 0; j < tamano_matrices; j++){
                file >> matrizA[i][j];
            }
        }
        //Leer la segunda matriz.
        file >> tamano_matrices;
        matrizB.resize(tamano_matrices, vector<int>(tamano_matrices, 0));
        for(int i = 0; i < tamano_matrices; i++){
            for(int j = 0; j < tamano_matrices; j++){
                file >> matrizB[i][j];
            }
        }
        //Multipicar las matrices.
        auto start = chrono::high_resolution_clock::now();
        vector<vector <int>> matrizC = cubicMultiOpti(matrizA, matrizB);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = (end - start);
        tiempo += duration.count();
        //Agregar la matriz resultante al archivo de escritura.
        for(int i = 0; i < tamano_matrices; i++){
            for(int j = 0; j < tamano_matrices; j++){
                write << matrizC[i][j] << " ";
            }
            write << endl;
        }
        write << endl;
    }
    cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
    //Cerrar archivos.
    file.close();
    write.close();
    return 0;
}