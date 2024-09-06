#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

/*
Función extraida de https://www.geeksforgeeks.org/selection-sort-algorithm-2/ y posteriormente adaptada.
Nombre: selectionSort
Parametros: 
vector<int> &list: referencia de la lista con números a ordenar.
*/
void selectionSort(vector<int> &list){
    int n = list.size();
    //Recorrer cada elemento del vector.
    for(int i = 0; i < n - 1; i++){
        //Encontrar el menor elemento en la colección de elementos.
        int min_idx = i;
        for(int j = i + 1; j < n; j++){
            if(list[j] < list[min_idx]){
                min_idx = j;
            }
        }
        //Intercambiar el menor elemento encontrado con el primer elemento
        if (min_idx != i){
            swap(list[min_idx], list[i]);
        }
    }
}

int main(){
    //Abrir archivo de escritura.
    ofstream write("SelectionSort.txt");
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
        selectionSort(list);
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
    //Cerrar archivos.
    file.close();
    write.close();
    return 0;
}
