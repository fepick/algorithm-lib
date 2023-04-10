#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
#define ll long long
using namespace std;

struct uf;//대충구현, 사이클판별 구현예정
struct seg;
struct fenwick;
struct bfs2d; //option(추가적인 bool 조건 판단)구현예정
struct dfs2d;

struct bfs2d
{
    int H;
    int W;
    const int dx[4] = {1,0,-1,0};
    const int dy[4] = {0,1,0,-1};
    const int ddx[8] = {1,1,0,-1,-1,-1,0,1};
    const int ddy[8] = {0,1,1,1,0,-1,-1,-1};
    vector<vector<int>> arr;
    vector<vector<int>> vis;
    queue<pair<int,int>> qq;
    bfs2d(int H,int W):H(H),W(W){
        arr.assign(H+1,vector<int>(W+1));
        vis.assign(H+1,vector<int>(W+1));
    }
    bfs2d(vector<vector<int>> v){
        H = v.size()-1;
        W = v[0].size()-1;
        arr=v;
        vis.assign(H+1,vector<int>(W+1));
    }
    void visset(int y,int x,int value){
        vis[y][x]=value;
    }
    void qset(int y,int x){
        qq.emplace(y,x);
    }
    void bfs4way(){
        while (!qq.empty())
        {
            pair<int,int> cur = qq.front();
            qq.pop();
            for (int i = 0; i < 4; i++)
            {
                int ny = cur.first+dy[i];
                int nx = cur.second+dx[i];
                if(ny>H||ny<1||nx>W||nx<1)continue;
                if(vis[ny][nx]||arr[ny][nx]==-1)continue;
                vis[ny][nx]=vis[cur.first][cur.second]+1;
                qq.emplace(ny,nx);
            }
        }
    }
    void bfs8way(){
        while (!qq.empty())
        {
            pair<int,int> cur = qq.front();
            qq.pop();
            for (int i = 0; i < 8; i++)
            {
                int ny = cur.first+ddy[i];
                int nx = cur.second+ddx[i];
                if(ny>H||ny<1||nx>W||nx<1)continue;
                if(vis[ny][nx]||arr[ny][nx]==-1)continue;
                vis[ny][nx]=vis[cur.first][cur.second]+1;
                qq.emplace(ny,nx);
            }
        }
    }
    void arrprint(){
        cout<<"-------arrprint--------\n";
        for (auto i:arr)
        {
            for (auto j:i)
            {
                cout<<setw(3)<<j<<" ";
            }
            cout<<"\n";
        }
        cout<<"-------arrprint--------\n";
    }
    void visprint(){
        cout<<"-------visprint--------\n";
        for (auto i:vis)
        {
            for (auto j:i)
            {
                cout<<setw(3)<<j<<" ";
            }
            cout<<"\n";
        }
        cout<<"-------visprint--------\n";
    }
};

struct dfs2d
{
    int H;
    int W;
    const int dx[4] = {1,0,-1,0};
    const int dy[4] = {0,1,0,-1};
    const int ddx[8] = {1,1,0,-1,-1,-1,0,1};
    const int ddy[8] = {0,1,1,1,0,-1,-1,-1};
    vector<vector<int>> arr;
    vector<vector<int>> vis;
    stack<pair<int,int>> qq;
    dfs2d(int H,int W):H(H),W(W){
        arr.assign(H+1,vector<int>(W+1));
        vis.assign(H+1,vector<int>(W+1));
    }
    dfs2d(vector<vector<int>> v){
        H = v.size()-1;
        W = v[0].size()-1;
        arr=v;
        vis.assign(H+1,vector<int>(W+1));
    }
    void visset(int y,int x,int value){
        vis[y][x]=value;
    }
    void stackset(int y,int x){
        qq.emplace(y,x);
    }
    void dfs4way(){
        while (!qq.empty())
        {
            pair<int,int> cur = qq.top();
            qq.pop();
            for (int i = 0; i < 4; i++)
            {
                int ny = cur.first+dy[i];
                int nx = cur.second+dx[i];
                if(ny>H||ny<1||nx>W||nx<1)continue;
                if(vis[ny][nx]||arr[ny][nx]==-1)continue;
                vis[ny][nx]=vis[cur.first][cur.second]+1;
                qq.emplace(ny,nx);
            }
        }
    }
    void dfs8way(){
        while (!qq.empty())
        {
            pair<int,int> cur = qq.top();
            qq.pop();
            for (int i = 0; i < 8; i++)
            {
                int ny = cur.first+ddy[i];
                int nx = cur.second+ddx[i];
                if(ny>H||ny<1||nx>W||nx<1)continue;
                if(vis[ny][nx]||arr[ny][nx]==-1)continue;
                vis[ny][nx]=vis[cur.first][cur.second]+1;
                qq.emplace(ny,nx);
            }
        }
    }
    void arrprint(){
        cout<<"-------arrprint--------\n";
        for (auto i:arr)
        {
            for (auto j:i)
            {
                cout<<setw(3)<<j<<" ";
            }
            cout<<"\n";
        }
        cout<<"-------arrprint--------\n";
    }
    void visprint(){
        cout<<"-------visprint--------\n";
        for (auto i:vis)
        {
            for (auto j:i)
            {
                cout<<setw(3)<<j<<" ";
            }
            cout<<"\n";
        }
        cout<<"-------visprint--------\n";
    }
};

set<int> sosu(int maxnum);
ll dnc_pow(ll a,ll b,ll divisor=0);
ll gcd(ll a,ll b);
int ccw(pair<ll,ll> a,pair<ll,ll> b, pair<ll,ll> c);

int ccw(pair<ll,ll> a,pair<ll,ll> b, pair<ll,ll> c){
    	ll ans=0;
	ll ax = a.first,ay=a.second;
	ll bx = b.first,by=b.second;
	ll cx = c.first,cy=c.second;
    	ans+=ax*by;
    	ans+=bx*cy;
    	ans+=cx*ay;
    	ans-=ay*bx;
    	ans-=by*cx;
    	ans-=cy*ax;
    	if(ans==0)return 0;
    	else if(ans>0)return 1;
    	else return -1;
}

struct uf{
	int size;
	vector<int> parent;
	uf(int size){
		parent.resize(size+1);
		for(int i=0;i<=size;i++)parent[i]=i;
	}
	int findparent(int element){
		if(parent[element]==element)return element;
		return parent[element] = findparent(parent[element]);
	}
	void insert(int a,int b){
		parent[findparent(a)]=findparent(b);
	}
};

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
