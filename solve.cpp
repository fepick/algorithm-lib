#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
#define ll long long
using namespace std;

struct uf;//구현중
struct seg;
struct fenwick;
struct bfs2d;
struct dfs2d;

set<int> sosu(int maxnum);
ll dnc_pow(ll a,ll b,ll divisor=0);
ll gcd(ll a,ll b);

struct uf{
	int size;
	vector<int> parent;
	uf(int size){
		parent.resize(size+1);
		for(int i=0;i<=size;i++)parent[i]=i;
	}
	uf(vector<vector<int>>&A){

	}
	findparent(int element){
		if(parent[element]==element)return element;
		return parent[element] = findparent(parent[element]);
	}
	add(int a,int b){
		parent[findparent(a)]=findparent(b);
	}
	cycle(int element){

	}
}

set<int> sosu(int maxnum){
	set<int> ans;
	bool eratos[maxnum+1];
	eratos[0]=1;eratos[1]=1;
	for (int i = 2; i <= sqrt(maxnum); i++)
	{
		if(eratos[i])continue;
		ans.insert(i);
		for (int j = i; j <= maxnum; j+=i)eratos[j]=1;
	}
	return ans;
}

ll dnc_pow(ll a,ll b,ll divisor=0){
	ll ans = 1;
	while (b)
	{
		if(b%2==1){
			ans*=a;
			if(divisor)ans%=divisor;
		}
		b=b>>1;
		a*=a;
		if(divisor)a%=divisor;
	}
	return ans;
}

ll gcd(ll a,ll b){ll r;while (b){r=a%b;a=b;b=r;}return a;}


struct fenwick {
    using _T = long long;
    vector<_T> S;
    fenwick(const vector<_T>& A){
        S.assign(A.size()+2,0);
		init(A);
    }
    void init(const vector<_T>& A){
        for (int i = 0; i < A.size(); i++)
        {
            update(i,A[i]);
        }
    }
    _T sum(_T pos){
		++pos;
        _T ret = 0;
        while (pos)
        {
            ret += S[pos];
            pos&=pos-1;
        }
        return ret;
    }
    _T query(int left,int right){
        return sum(right)-sum(left-1);
    }
    void update(_T pos,_T num){
		++pos;
        while (pos < S.size())
        {
            S[pos]+=num;
            pos+= (pos & -pos);
        }
    }
};

struct seg { // https://gravekper-algo.tistory.com/13
	int n;
	using _T = long long;
	vector<_T> S;     
	_T(*op)(_T, _T);  
	_T e;             
	seg(const vector<_T>& A, _T(*op)(_T, _T), _T e) :op(op), e(e) { 
		n = A.size();
		S.resize(4 * n);
		init(A, 0, n - 1, 1); 
	}
	_T init(const vector<_T>& A, int nodeleft, int noderight, int node) {
		if (nodeleft == noderight) {   
			return S[node] = A[nodeleft];
		}
		int mid = (nodeleft + noderight) / 2;
		return S[node] = op(init(A, nodeleft, mid, node * 2),
			init(A, mid + 1, noderight, node * 2 + 1));
	}

	_T query(int left, int right, int node, int nodeleft, int noderight) {
		if (right < nodeleft || noderight < left) return e;
		if (left <= nodeleft && noderight <= right) return S[node];

		int mid = (nodeleft + noderight) / 2;
		return op(query(left, right, node * 2, nodeleft, mid),
			query(left, right, node * 2 + 1, mid + 1, noderight));
	}
	_T query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
	void update(int index, _T newvalue, int node, int nodeleft, int noderight) {
		if (index < nodeleft || noderight < index) return;
		if (nodeleft == noderight) {
			S[node] = newvalue;
			return;
		}
		int mid = (nodeleft + noderight) / 2;
		update(index, newvalue, node * 2, nodeleft, mid);
		update(index, newvalue, node * 2 + 1, mid + 1, noderight);
		S[node] = op(S[node * 2], S[node * 2 + 1]);
	}
	void update(int index, _T newvalue) {
		update(index, newvalue, 1, 0, n - 1);
	}
};