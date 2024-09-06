#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

/*
Nombre: sumarMatrices
Parametro:
vector<vector<int>> &matrizA: referencia del vector de vectores que representa una matriz A.
vector<vector<int>> &matrizB: referencia del vector de vectores que representa una matriz B.
Retorno:
vector<vector<int>> matrizC: vector de vectores que representa la suma de matrizA y matrizB.
*/
vector<vector<int>> sumarMatrices(const vector<vector<int>> &matrizA, const vector<vector<int>> &matrizB){
    int n = matrizA.size();
    vector<vector<int>> matrizC(n, vector<int>(n));
    //Realizar la suma de las dos matrices.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizC[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    return matrizC;
}

/*
Nombre: restarMatrices
Parametro:
vector<vector<int>> &matrizA: referencia del vector de vectores que representa una matriz A.
vector<vector<int>> &matrizB: referencia del vector de vectores que representa una matriz B.
Retorno:
vector<vector<int>> matrizC: vector de vectores que representa la resta de matrizA y matrizB.
*/
vector<vector<int>> restarMatrices(const vector<vector<int>> &matrizA, const vector<vector<int>> &matrizB){
    int n = matrizA.size();
    vector<vector<int>> matrizC(n, vector<int>(n));
    //Realizar la resta de las dos matrices.
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            matrizC[i][j] = matrizA[i][j] - matrizB[i][j];
        }
    }
    return matrizC;
}

/*
Nombre: strassenMulti
Parametro:
vector<vector<int>> &matrizA: referencia del vector de vectores que representa una matriz A.
vector<vector<int>> &matrizB: referencia del vector de vectores que representa una matriz B.
Retorno:
vector<vector<int>> matrizC: vector de vectores que representa el producto de matrizA y matrizB.
*/
vector<vector<int>> strassenMulti(const vector<vector<int>> &matrizA, const vector<vector<int>>  &matrizB){
    int n = matrizA.size();
    if(n == 1){
        vector<vector<int>> matrizC(1, vector<int>(1));
        matrizC[0][0] = matrizA[0][0] * matrizB[0][0];
        return matrizC;
    }
    int mid = n / 2;
    //Dividir las matrices A y B en cuatro submatrices.
    vector<vector<int>> A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)), A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
    vector<vector<int>> B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)), B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));
    for(int i = 0; i < mid; ++i){
        for(int j = 0; j < mid; ++j){
            A11[i][j] = matrizA[i][j];
            A12[i][j] = matrizA[i][j + mid];
            A21[i][j] = matrizA[i + mid][j];
            A22[i][j] = matrizA[i + mid][j + mid];

            B11[i][j] = matrizB[i][j];
            B12[i][j] = matrizB[i][j + mid];
            B21[i][j] = matrizB[i + mid][j];
            B22[i][j] = matrizB[i + mid][j + mid];
        }
    }
    //Calcular siete productos usando la recursión de Strassen.
    vector<vector<int>> M1 = strassenMulti(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = strassenMulti(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = strassenMulti(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = strassenMulti(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = strassenMulti(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = strassenMulti(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = strassenMulti(restarMatrices(A12, A22), sumarMatrices(B21, B22));
    // Calcular las submatrices de la matriz resultante C.
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);
    //Combinar las submatrices en la matriz resultante C.
    vector<vector<int>> matrizC(n, vector<int>(n));
    for(int i = 0; i < mid; ++i){
        for(int j = 0; j < mid; ++j){
            matrizC[i][j] = C11[i][j];
            matrizC[i][j + mid] = C12[i][j];
            matrizC[i + mid][j] = C21[i][j];
            matrizC[i + mid][j + mid] = C22[i][j];
        }
    }
    return matrizC;
}

int main(){
    //Abrir archivo de escritura.
    ofstream write("Strassen.txt");
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
        vector<vector<int>> matrizC = strassenMulti(matrizA, matrizB);
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
    //Cerrar archivos.
    cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
    file.close();
    write.close();
    return 0;
}