#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion{
    vector<int> parent, size;
public:
    DisjointSetUnion(int n){
        parent.resize(n);
        size.resize(n);
        for(int i=0;i<n;i++)
            make_set(i);
    }
    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
    
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    int get_size(int v){
        return size[v];
    }
};