#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H_LENGHT(heap) (heap->size)

typedef struct {
    int head;
    int size;
    int* array;
} Heap;

void heap_print(Heap *heap){
    printf("Heap(size=%i): ",H_LENGHT(heap));
    for(int i = 0; i < heap->head; i++){
        printf("|%i|", heap->array[i]);
    }
    printf("\n");
}

void _heap_repear_up(Heap *heap, int wo){
    int p = heap->array[wo];
    while(wo>0){
        int parent_index = floor(wo/2);
        if(heap->array[parent_index] >= heap->array[wo]) break;
        heap->array[wo] = heap->array[parent_index];
        wo = parent_index;
    }
    heap->array[wo] = p;
}

void _heap_repear_down(Heap *heap, int wo){
    //repeat until wo is in the last row or in the second to last row, but at vertices that don't have children
    int kind;
    int p = heap->array[wo];
    while(wo < floor(heap->head/2)){
        kind = 2 * wo;
        // check if first or second child is biggest
        if((kind < heap->head) && (heap->array[kind] < heap->array[kind+1])) kind ++;
        if(p > heap->array[kind]) break;
        heap->array[wo] = heap->array[kind];
        wo = kind;
    }
    heap->array[wo] = p;
}


Heap* heap_new(int size){
    int* array = malloc(size*sizeof(int));
    Heap* heap = malloc(sizeof(Heap));
    heap->array = array;
    heap->head = 0;
    heap->size = size;
    return heap;
}

void heap_insert(Heap *heap, int prio){
    //first check if heap is full
    if(heap->head > H_LENGHT(heap)){
        exit(-1);
    }

    //insert at the end of array
    heap->array[heap->head++] = prio;

    //this leaves the heap structure in place, but might destroy heap order.
    //to fix heap order call, repear up, for that vertex
    _heap_repear_up(heap, heap->head-1);
}

int heap_delete_max(Heap *heap){
    //first check if heap is empty
    if(heap->head == 0){
        exit(-1);
    }

    //remove root vertex and put last vertex there
    heap->array[0] = heap->array[--heap->head];

    //this leaves the heap structure in place, but might destroy heap order.
    //to fix heap order call, repear down, from the root
    _heap_repear_down(heap, 0);
}

void heap_change_priority(Heap *heap, int wo, int prio){
    //first check if value exists
    if(wo >= heap->head){
        exit(-1);
    }

    //then get original value
    int p = heap->array[wo];
    //update value
    heap->array[wo] = prio;
    //if value got bigger
    if(prio > p){
        _heap_repear_up(heap,wo);
        return;
    }
    //if value got smaler
    _heap_repear_down(heap,wo);
}

void heap_remove(Heap *heap, int wo){
    //first check if value exists
    if(wo >= heap->head){
        exit(-1);
    }

    //remove wo vertex and put last vertex there
    heap->array[wo] = heap->array[--heap->head];

    //this leaves the heap structure in place, but might destroy heap order.
    //to fix heap order call, repear down, from wo 
    _heap_repear_down(heap, wo);
}

