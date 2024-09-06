#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

/*
Función extraida de https://www.geeksforgeeks.org/cpp-program-for-quicksort/ y posteriormente adaptada.
Nombre: partition
Parametros: 
vector<int> &list: refencia de la lista con números a ordenar.
int low: posición del elemento más a la izquieda de la lista.
int high: posición del elemento más a la derecha de la lista.
*/
int partition(vector<int> &list, int low, int high){
    //Selectionar el último elemento de la lista como el pivote.
    int pivot = list[high];
    //Posición del elemento antes del último elemento.
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++){
        //Comparar el elemento actual con el pivote.
        if(list[j] <= pivot){
            i++;
            //Todos los elementos menores que el pivote están antes del índice i.
            swap(list[i], list[j]);
        }
    }
    //Colocar el pivote en su posición.
    swap(list[i + 1], list[high]);
    //Retornar la posición del pivote.
    return (i + 1);
}


/*
Función extraida de https://www.geeksforgeeks.org/cpp-program-for-quicksort/ y posteriormente adaptada.
Nombre: quickSort
Parametros: 
vector<int> &list: refencia de la lista con números a ordenar.
int low: posición del elemento más a la izquieda de la lista.
int high: posición del elemento más a la derecha de la lista.
*/
void quickSort(vector<int> &list, int low, int high){
    if (low < high){
        //Realizar la partición y obtener la posición del pivote (index).
        int pi = partition(list, low, high);
        //Ordenar los elementos antes del index del pivote.
        quickSort(list, low, pi - 1);
        //Ordenar los elementos después del index del pivote.
        quickSort(list, pi + 1, high);
    }   
}

int main(){
    //Abrir archivo de escritura.
    ofstream write("QuickSort.txt");
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
        quickSort(list, 0, list.size() - 1);
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
