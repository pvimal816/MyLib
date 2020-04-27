#include<bits/stdc++.h>
using namespace std;
#define _INF 1000000005
#define ll long long
class SegmentTree
{
	vector<ll> a; //segment array
	vector<ll> b; //lazy array
	int n;
	int left(int x)
	{
		return (x << 1) + 1;
	}
	int right(int x)
	{
		return (x << 1) + 2;
	}
	void build(vector<ll> &a, int pos, int low, int high)
	{
		if (low == high)
		{
			this->a[pos] = a[low];
			return;
		}
		int mid = (low + high) / 2;
		build(a, left(pos), low, mid);
		build(a, right(pos), mid + 1, high);
		this->a[pos] = max(this->a[left(pos)], this->a[right(pos)]);
	}
 
	ll query_util(int x, int y, int pos, int low, int high)
	{	
		if(low>high){
			assert(low<=high);
			return -_INF;
		}
		
		//perform pending updates
		a[pos] += b[pos];
		if(low!=high){
			//Non leaf node. So, delay updates to child nodes.
			b[left(pos)] += b[pos];
			b[right(pos)] += b[pos];
		}
		b[pos] = 0;
 
		if (y < low || x > high)
			//no overlap so return identity.
			return -_INF;
		
		if (x <= low && high <= y)
			return this->a[pos];
 
		int mid = (low + high) / 2;
		return max(query_util(x, y, left(pos), low, mid),
			query_util(x, y, right(pos), mid + 1, high));
	}
 
	void update_util(int x, int y, int pos, int low, int high, ll value)
	{
		if(low>high){
			assert(low<=high);
			return;
		}
 
		//perform pending updates
		a[pos] += b[pos];
		if(low!=high){
			//Non leaf node. So, delay updates to child nodes.
			b[left(pos)] += b[pos];
			b[right(pos)] += b[pos];
		}
		b[pos] = 0;
 
		//At this point we this node is up-to-date. 
		//But it's children might not be.
 
		if(y<low || x>high)
			//No overlap
			return;
		
		if(x<=low and high<=y){
			//total overlap
			a[pos] += value;
			if(low!=high){
				//delay updates to children
				b[left(pos)] += value;
				b[right(pos)] += value;
			}
			return;
		}
		
		//partial overlap
		int mid = (low+high)/2;
		update_util(x, y, left(pos), low, mid, value);
		update_util(x, y, right(pos), mid + 1, high, value);
		a[pos] = max(a[left(pos)], a[right(pos)]);
	}
 
public:
	SegmentTree(vector<ll> &a)
	{
		this->n = a.size();
		this->a.resize(a.size() * 4);
		this->b.resize(a.size() * 4, 0);
		build(a, 0, 0, n - 1);
	}
	SegmentTree(int size){
		this->n = size;
		this->a.resize(size * 4, 0);
		this->b.resize(size * 4, 0);
	}
	ll query(int x, int y)
	{
		return query_util(x, y, 0, 0, n - 1);
	}
	void update(int x, int y, ll value){
        if(x>y) return;
		update_util(x, y, 0, 0, n - 1, value);
	}
	void printTree(){
		cout << "Cummulative tree is: ";
		for(auto &i: a)
			cout << i << "\t";
		cout << endl;
	}
};