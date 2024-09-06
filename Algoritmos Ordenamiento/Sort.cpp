#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
using namespace std;

int main(){
    //Abrir archivo de escritura.
    ofstream write("Sort.txt");
    if(!write.is_open()){
        cout << "Eror al escribir el archivo." << endl;
        return 0;
    }
    //Abrir archivo de lectura.
    ifstream file("dataset_ordenamiento.txt");
    if(!file.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }
    //Trabajar con ambos archivos.
    double tiempo = 0;
    string line;
    vector<int> list;
    while(getline(file, line)){
        vector<int> list;
        istringstream iss(line);
        int num;
        //Agregar el número al vector.
        while (iss >> num){
            list.push_back(num);
        }
        //Realizar el sort.
        auto start = chrono::high_resolution_clock::now();
        sort(list.begin(), list.end());
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = (end - start);
        tiempo += duration.count();
        //Agregar el vector ordenado al archivo de escritura.
        int n = list.size();
        for(int i = 0; i < n; i++){
            if(i + 1 == n){
                write << list[i] << endl;
            }
            else{
                write << list[i] << " ";
            }
        }
    }
    cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
    //Cerrar archivo.
    file.close();
    write.close();
    return 0;
}
