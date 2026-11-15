#include<stdio.h>
#include<stdlib.h>

#define MAX_HEAP 1000

struct HeapNode{
    int vertex;
    float distance;
};

struct MinHeap{
    int size;
    struct HeapNode elements[MAX_HEAP + 1];
};

void initMinHeap(struct MinHeap *heap){
    if(heap==NULL) return;
    heap->size = 0;
    heap->elements[0].vertex = -1;
    heap->elements[0].distance = -1.0;
}

int isEmpty(const struct MinHeap *heap){
    if(heap==NULL || heap->size==0){
        return 1;
    }
    return 0;
}

void heapifyUp(struct MinHeap *heap, int i){
    while(i > 1){
        int parent = i / 2;
        if(heap->elements[i].distance < heap->elements[parent].distance){
            struct HeapNode temp = heap->elements[i];
            heap->elements[i] = heap->elements[parent];
            heap->elements[parent] = temp;
            i = parent;
        }
        else{
            break;
        }
    }
}

void heapifyDown(struct MinHeap *heap, int i){
    while(1){
        int smallest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if(left <= heap->size && heap->elements[left].distance < heap->elements[smallest].distance){
            smallest = left;
        }
        if(right <= heap->size && heap->elements[right].distance < heap->elements[smallest].distance){
            smallest = right;
        }

        if(smallest != i){
            struct HeapNode temp = heap->elements[i];
            heap->elements[i] = heap->elements[smallest];
            heap->elements[smallest] = temp;
            i = smallest;
        }
        else{
            break;
        }
    }
}

int insert(struct MinHeap *heap, int vertex, float distance){
    if(heap==NULL || heap->size >= MAX_HEAP){
        return 0;
    }

    heap->size++;
    heap->elements[heap->size].vertex = vertex;
    heap->elements[heap->size].distance = distance;

    heapifyUp(heap, heap->size);
    return 1;
}

struct HeapNode deleteMin(struct MinHeap *heap){
    struct HeapNode emptyNode;
    emptyNode.vertex = -1;
    emptyNode.distance = -1.0;

    if(isEmpty(heap)){
        return emptyNode;
    }

    struct HeapNode minNode = heap->elements[1];
    heap->elements[1] = heap->elements[heap->size];
    heap->size--;

    if(heap->size > 0){
        heapifyDown(heap, 1);
    }
    return minNode;
}
