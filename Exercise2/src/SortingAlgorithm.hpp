#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace SortLibrary {

template<typename T>
concept Sortable = requires(T& t) {
    // Verifica che il tipo T supporti l'operatore di confronto "<"
    {t < t} -> convertible_to<bool>; // Il risultato dell'espressione deve essere convertito in booleano
};

// Implementazione del BubbleSort
template<Sortable T>
void BubbleSort(vector<T>& v)
{
    const unsigned int n = v.size();

    for(unsigned int i = 0; i < n - 1; i++)
    {
        // Ciclo interno per confrontare gli elementi adiacenti
        for(unsigned int j = i + 1; j < n; j++)
        {
            //Se l'elemento attuale è più piccolo del precedente scambiamo i 2 elementi
            if(v[j] < v[i])
            { 
                T tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
        }
    }
}

// Heapify: converte un sotto-vettore in un heap, partendo dal nodo i
template<Sortable T>
void Heapify(vector<T>& v, unsigned int n, unsigned int i)
{
    // Inizializza il nodo più grande come radice
    unsigned int largest = i;
    // Indice figlio sinistro
    unsigned int left = 2 * i + 1;
    unsigned int right = 2 * i + 2;  //destro

    // Controlla se figlio sx è maggiore della radice
    if (left < n && v[left] > v[largest])
        largest = left;
    // Controlla se figlio dx è maggiore della radice
    if (right < n && v[right] > v[largest])
        largest = right;

    // Se il nodo attuale non è il più grande, scambialo e ricostruisci l'heap
    if (largest != i)
    {
        T tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;

        // Assicura che la struttura heap venga mantenuta
        Heapify(v, n, largest);
    }
}

// Implementazione di HeapSort
template<Sortable T>
void HeapSort(vector<T>& v)
{
    const int n = v.size();

    // Costruisce l'heap partendo dagli elementi non foglia
    for(int i = n/2 - 1; i >= 0; i--)
        Heapify(v, n, i);

    // Estrazione elementi dall'heap
    for(int i = n - 1; i > 0; i--)
    {
        // Scambia l'elemento massimo (in cima all'heap) con l'ultimo elemento non ordinato.
        // Questo pone il massimo nella sua posizione finale nel vettore ordinato.
        T tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;

        // Ricostruisce l'heap ridotto (escludendo l'ultima posizione ora ordinata)
        Heapify(v, i, 0);
    }
}

}


