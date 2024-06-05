#pragma once
#include "DataUtil.h"

//arbone binar max/min complet
//lucram cu vector deoarece complexitatea este O(1) si pe arbore este logaritmica
//lChild = index*2+1
//rChild = index*2+2
//parinte = [(index-1)/2]


typedef struct PQueue
{
    Student** items; // vector de pointeri la studenti
    int size; //dim masiv 
    int index; //indexul ultimului element
}PriorityQueue, *PPriorityQueue;

#define PQueueInitialSize 7 

void ReheapUp(PPriorityQueue pQueue, int childIndex) //
{
    if (childIndex > 0 ) // daca nu suntem la radacina
    {
        int parentIndex = (childIndex - 1) / 2; // calculam indexul parintelui
        if (pQueue->items[childIndex]->income > pQueue->items[parentIndex]->income) // daca copilul este mai mare decat parintele
        {
            Student* tmp = pQueue->items[childIndex]; // interschimbam valorile
            pQueue->items[childIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = tmp;
            ReheapUp(pQueue, parentIndex); // apelam recursiv ReheapUp
        } 
    }
}

void enque(PPriorityQueue pQueue, Student* stud) // adaugare 
{
    if (pQueue->items == NULL) // daca nu exista elemente in coada
    {
        pQueue->items = (Student**)malloc(sizeof(Student*)*PQueueInitialSize); //default size de 7 items
        memset(pQueue->items, 0, sizeof(Student*)*PQueueInitialSize); //initializam cu 0
        pQueue->size = PQueueInitialSize; //size ia valoarea default
    }
    else
    {
       pQueue->items[pQueue->index] = stud; //adaugam studentul la sfarsitul cozii
       ReheapUp(pQueue,pQueue->index); //la inserare folosim reheapup si la stergere reheapdown ->ordonam lista
       pQueue->index++; //incrementam indexul
    }
}

void ReheapDown(PPriorityQueue pQueue, int parentIndex) //
{
    int leftChildIndex = 2 * parentIndex + 1; //
    int rightChildIndex = 2 * parentIndex + 2; // calculam indexii copiilor
    int maxIndex = parentIndex; //maxIndex ia valoarea parintelui

    // vf daca exista leftchild si daca este mai mare decat parintele
    if (leftChildIndex < pQueue->index && pQueue->items[leftChildIndex]->income > pQueue->items[maxIndex]->income)
    {
        maxIndex = leftChildIndex; //maxIndex ia valoarea leftChildIndex
    }

    // vf daca exista rightchild si daca este mai mare decat parintele
    if (rightChildIndex < pQueue->index && pQueue->items[rightChildIndex]->income > pQueue->items[maxIndex]->income)
    {
        maxIndex = rightChildIndex; //maxIndex ia valoarea rightChildIndex
    }
    
    // daca maxIndex este diferit de parintele, interschimbam valorile si apelam recursiv ReheapDown    
    if (maxIndex != parentIndex) 
    {
        Student* tmp = pQueue->items[parentIndex]; 
        pQueue->items[parentIndex] = pQueue->items[maxIndex];
        pQueue->items[maxIndex] = tmp;
        ReheapDown(pQueue, maxIndex);//apelam recursiv ReheapDown
    }

}

void deque(PPriorityQueue pQueue) //stergere
{
    //ultimul elem ia locul primului, decrementam index 
    //reheapdown
     if (pQueue->index == 0) // daca nu exista elemente in coada
    {
        printf("Priority queue is empty!\n");
    }
    else{
    pQueue->items[0] = pQueue->items[pQueue->index-1];
    pQueue->items[pQueue->index-1] = NULL; 
    pQueue->index--; //decrementam indexul  

    // reordonam coada
    ReheapDown(pQueue, 0);
    }
}

void printQueue(PriorityQueue pQueue) {
    if (pQueue.index == 0) {
        printf("Priority queue is empty\n");
    }
    else {
    for (int i = 0; i < pQueue.index; i++) {
        printf("Index: %d, Name: %s, Income: %.2f\n", i, pQueue.items[i]->name, pQueue.items[i]->income);
    }
    }
}

