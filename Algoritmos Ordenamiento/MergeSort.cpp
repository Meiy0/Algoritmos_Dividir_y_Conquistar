#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

/*
Función extraida de https://www.geeksforgeeks.org/merge-sort/ y posteriormente adaptada.
Nombre: merge
Parametros: 
vector<int> &list: refencia de la lista con números a ordenar.
int left: posición del elemento más a la izquieda de la lista.
int mid: posición del elemento en la mitad de la lista.
int right: posición del elemento más a la derecha de la lista.
*/
void merge(vector<int> &list, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    //Crear vectores temporales.
    vector<int> L(n1), R(n2);
    //Copiar datos a los vectores temporales.
    for (int i = 0; i < n1; i++){
        L[i] = list[left + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = list[mid + 1 + j];
    }
    int i = 0, j = 0;
    int k = left;
    //Fusionar los vectores temporales en la lista.
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            list[k] = L[i];
            i++;
        }
        else {
            list[k] = R[j];
            j++;
        }
        k++;
    }
    //Copiar los elementos restantes de L[].
    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
    }
    //Copiar los elementos restantes de R[].
    while (j < n2) {
        list[k] = R[j];
        j++;
        k++;
    }
}

/*
Función extraida de https://www.geeksforgeeks.org/merge-sort/ y posteriormente adaptada.
Nombre: mergeSort
Parametros: 
vector<int> &list: refencia de la lista con números a ordenar.
int left: posición del elemento más a la izquieda de la lista.
int right: posición del elemento más a la derecha de la lista.
*/
void mergeSort(vector<int> &list, int left, int right){
    if(left >= right){
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(list, left, mid);
    mergeSort(list, mid + 1, right);
    merge(list, left, mid, right);
}


int main(){
    //Abrir archivo de escritura.
    ofstream write("MergeSort.txt");
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
        mergeSort(list, 0, list.size() - 1);
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
    system("pause");
    return 0;
}