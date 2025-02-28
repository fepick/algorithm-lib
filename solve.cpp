#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
#define ll long long
using namespace std;

class Mykmp;
class mytrie;
class MyMatrix;
struct uf;//대충구현, 사이클판별 구현예정
struct seg;
struct fenwick;
struct bfs2d; //option(추가적인 bool 조건 판단)구현예정
struct dfs2d;
struct dijkstra;

vector<ll> sosu(ll maxnum);
ll dnc_pow(ll a,ll b,ll divisor=0);
ll gcd(ll a,ll b);
int ccw(pair<ll,ll> a,pair<ll,ll> b, pair<ll,ll> c);

class rotate90_arr2d{
    // if(t%4==0){//1번회전
    //     return {y,N+1-x};
    // }
    // else if(t%4==1){//2번회전
    //     return {N+1-x,N+1-y};
    // }
    // else if(t%4==2){//3번회전
    //     return {N+1-y,x};
    // }
    // else{
    //     return {x,y};
    // }
};

class Mykmp
{
    vector<int> failf(string s)
    {
        int len = s.length();
        int j = 0;
        vector<int> ans(len, 0);
        for (int i = 1; i < len; i++)
        {
            while (j > 0 && s[i] != s[j])
                j = ans[j - 1];
            if (s[i] == s[j])
                ans[i] = ++j;
        }
        return ans;
    }
    vector<int> kmp(string T, string P)
    {
        vector<int> ans;
        vector<int> pi = failf(P);
        int n = T.length(), m = P.length();
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            while (j > 0 && P[j] != T[i])
                j = pi[j - 1];
            if (T[i] == P[j])
            {
                if (j == m - 1)
                {
                    ans.push_back(i - m + 1);
                    j = pi[j];
                }
                else
                    j++;
            }
        }
        return ans;
    }
};

class mytrie	//from http://boj.kr/62d74191dbe8440c88d98f0e19a0aa7f
{
private:
    #define is_debug 0
    struct node
    {
        int idx = 0;
        bool isend = 0;
        int leafcnt = 0;
        node* leafs[26]={0,};
    };    
    node* head;
public:
    int getans(string S){
        node* cur = head->leafs[S[0]-'a'];
        int ans = 1;
        int pos = 1;
        while (pos<S.length())
        {
            if(cur->isend||cur->leafcnt>1)ans++;
            cur=cur->leafs[S[pos++]-'a'];
        }
        if(is_debug)cout<<"ans of "<<S<<" is "<<ans<<"\n";
        return ans;
    }
    void insert(string S){
        node* cur = head;
        int pos = 0;
        while (pos<S.length())
        {
            if(cur->leafs[S[pos]-'a']){//있으면 커서 이동
                cur=cur->leafs[S[pos]-'a'];
                pos++;
                if(is_debug)cout<<"cur moved "<<(char)(cur->idx+'a')<<"\n";
            }
            else{//없으면 노드 추가
                node* newnode = new node();
                cur->leafs[S[pos]-'a']=newnode;
                cur->leafcnt++;

                cur = newnode;
                cur->idx=S[pos]-'a';
                pos++;
                if(is_debug)cout<<"node added and cur moved "<<(char)(cur->idx+'a')<<"\n";
            }
        }
        if(is_debug)cout<<"is end :"<<(char)(cur->idx+'a')<<"\n";
        cur->isend=1;
    }
    void erase(node* n){
        for (int i = 0; i < 26; i++)
        {
            if(n->leafs[i]){
                erase(n->leafs[i]);
            }
        }
        if(is_debug)cout<<"node erased : "<<(char)(n->idx+'a')<<"\n";
        delete n;
    }
    mytrie(){
        head = new node();
    };
    ~mytrie(){
        erase(head);
    };
};

class MyMatrix
{
public:
	void printMatrix(vector<vector<ll>> A)
	{
		cout << "\nprint mat start------\n";
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < A[0].size(); j++)
			{
				cout << A[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "print mat end------\n";
	}
	void getNullMatrix(vector<vector<ll>> &A, ll rsize, ll csize)
	{
		A.clear();
		A.assign(rsize, vector<ll>(csize, 0));
	}
	void getUnitMatrix(vector<vector<ll>> &A, ll size)
	{
		getNullMatrix(A,size,size);
		for (int i = 0; i < size; i++)
		A[i][i] = 1;
	}
	void transposeMatrix(vector<vector<ll>> A, vector<vector<ll>> &B)
	{
		int rsize = A.size();
		int csize = A[0].size();
		getNullMatrix(B,csize,rsize);
		for (int i = 0; i < rsize; i++)
		for (int j = 0; j < csize; j++)
		A[i][j] = B[j][i];
	}
	void mulMatrix(vector<vector<ll>> A, vector<vector<ll>> B, vector<vector<ll>> &C, ll divnum = 1e9+7)
	{
		getNullMatrix(C,A.size(),B[0].size());
		for (int i = 0; i < A.size(); i++)
			for (int j = 0; j < B[0].size(); j++)
				for (int k = 0; k < B.size(); k++){
					C[i][j] += A[i][k] * B[k][j];
					C[i][j] %= divnum;
				}
	}
	void powMatrix(vector<vector<ll>> A, vector<vector<ll>> &B, ll n, ll divnum = 1e9+7)
	{
		if(n==1)B=A;
		else if(n==2)mulMatrix(A,A,B,divnum);
		else{
			vector<vector<ll>> tmp;
			getUnitMatrix(B,A.size());
			while (n)
			{
				if(n%2==1){
					mulMatrix(B,A,tmp,divnum);
					B=tmp;
					--n;
				}
				else{
					mulMatrix(A,A,tmp,divnum);
					A=tmp;
					n=n>>1;
				}
			}
		}
	}
};

struct dijkstra
{
    const int inf = 0x3f3f3f3f;
    int V;
    vector<vector<pair<int,int>>> arr;
    vector<int> ans;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    dijkstra(vector<vector<pair<int,int>>> A){
        arr = A;
        V=A.size();
        ans.assign(V,inf);
    }
    vector<int> go(int st){
        ans[st]=0;
        pq.emplace(0,st);
        while (!pq.empty())
        {
            auto [cost,cur] = pq.top();
            pq.pop();
            if(cost>ans[cur])continue;
            for (auto i:arr[cur])
            {
                int ncost = i.first+cost;
                int next = i.second;
                if(ncost<ans[next]){
                    ans[next]=ncost;
                    pq.emplace(ncost,next);
                }
            }
        }
        return ans;
    }
};


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

vector<ll> sosu(ll maxnum){
	vector<ll> ans;
	bool eratos[maxnum+1]={0,};
	eratos[0]=1;eratos[1]=1;
	for (ll i = 2; i <= maxnum; i++)
	{
		if(eratos[i])continue;
		ans.push_back(i);
		for (ll j = i; j <= maxnum; j+=i)eratos[j]=1;
	}
	return ans;
}

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

struct dfs2d{
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
