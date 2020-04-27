#include <bits/stdc++.h>

using namespace std;

template<typename ValType>
class HeapNode {
public:
    int key;
    ValType val;

    HeapNode(){}
    HeapNode(int key, ValType val): val(val), key(key){}

    bool operator > (HeapNode const& other) const{
        return val>other.val;
    }

    bool operator < (HeapNode const& other) const{
        return val<other.val;
    }
};

template<typename ValType>
class Heap {
    vector<HeapNode<ValType> > heap;
    vector<size_t> ht;
    size_t size;

    inline size_t left(size_t a){
        return (a<<1)+1;
    }

    inline size_t right(size_t a){
        return (a<<1)+2;
    }

    inline size_t parent(size_t a){
        return (a-1)>>1;
    }

    void heapify(size_t x){
        size_t maxx=x;
        if(left(x)<size and heap[left(x)]>heap[maxx])
            maxx=left(x);
        if(right(x)<size and heap[right(x)]>heap[maxx])
            maxx=right(x);
        if(maxx!=x){
            ht[heap[x].key] = maxx;
            ht[heap[maxx].key] = x;
            swap(heap[x], heap[maxx]);
            heapify(maxx);
        }
    }


public:
    Heap(const vector<ValType> &a, size_t size):size(size){
        heap.resize(size);
        ht.resize(size);
        for (int i = 0; i < size; i++){
            heap[i] = HeapNode(i, a[i]);
            ht[i] = i;
        }
        for(int i=size/2; i>=0; i--)
            heapify(i);
    }

    Heap(int size): Heap(vector<ValType>(size), size){}

    int top(){
        return heap[0].key;
    }

    ValType get_val(int key){
        return heap[ht[key]].val;
    }

    int pop(){
        int ret = heap[0].key;
        ht[ret]=-1;
        heap[0] = heap[--size];
        ht[heap[0].key] = 0;
        heapify(0);
        return ret;
    }

    void update(int key, ValType val){
        HeapNode node(key, val);
        if(heap[ht[key]] > node){
            heap[ht[key]] = node;
            heapify(ht[key]);
        }else {
            int x = ht[key];       
            while(x>0 and heap[parent(x)]<node){
                ht[heap[parent(x)].key] = x;
                heap[x] = heap[parent(x)];
                x=parent(x);
            }
            ht[node.key] = x;
            heap[x] = node;
        }
    }

    bool empty(){
        return size==0;
    }
};
