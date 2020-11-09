#include <bits/stdc++.h>
using namespace std;
 
#define rng(x) x.begin(), x.end()
#define maxi(x, y) x = max(x, (y))
#define mini(x, y) x = min(x, (y))
#define pb push_back
#define F first
#define S second
#define el '\n'
#define int long long
template<typename T>
istream&operator>>(istream&is,vector<T>&v){for(auto&it:v)is>>it;return is;}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.F << "," << P.S << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
#define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout<<name<<" : "<<arg1<<'\n';}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout.write(names,comma-names)<<" : "<<arg1<<" |";__f(comma+1, args...);}
typedef pair<int,int> pi; typedef vector<int> vi; typedef vector<vi> vvi;
 
/*-----------------------------Code begins----------------------------------*/

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	pi NO_OPERATION = {LLONG_MIN, LLONG_MAX};
	vector <pi> lazy;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		lazy.assign(2 * size - 1, NO_OPERATION);
		lazy[0] = {0, 0};
	}

	void printUtil(int si, int sl, int sr){
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<lazy[si]<<el;

		if(sl == sr) return;

		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void update(int si, int sl, int sr, pi op){
		// todo : 
		if(op.S <= lazy[si].F){
			lazy[si].F = lazy[si].S = op.S;
		}
		else if(op.F >= lazy[si].S){
			lazy[si].F = lazy[si].S = op.F;
		}
		else{
			lazy[si].F = max(lazy[si].F, op.F);
			lazy[si].S = min(lazy[si].S, op.S);
		}
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		update(lsi, sl, mid, lazy[si]);
		update(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void updateUtil(int si, int sl, int sr, int ql, int qr, pi op){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return update(si, sl, sr, op);
		}

		propogate(si, sl, sr);

		updateUtil(lsi, sl, mid, ql, qr, op);
		updateUtil(rsi, mid + 1, sr, ql, qr, op);
	}
	void update(int ql, int qr, pi op){
		return updateUtil(0, 0, n - 1, ql, qr, op);
	}


	int getUtil(int si, int sl, int sr, int i){
		if(sl == sr){
			return lazy[si].F;
		}

		propogate(si, sl, sr);

		if(i <= mid){
			return getUtil(lsi, sl, mid, i);
		}
		else{
			return getUtil(rsi, mid + 1, sr, i);
		}
	}
	int get(int i){
		return getUtil(0, 0, n - 1, i);
	}
};


void solve(){
    int n, q; cin>>n>>q;
    segmentTree st(n);
    while(q--){
    	int op, l, r, val; cin>>op>>l>>r>>val;
    	if(op == 1){
    		st.update(l, r, {val, LLONG_MAX});
    	}
    	else{
    		st.update(l, r, {LLONG_MIN, val});
    	}
    }
    for (int i = 0; i < n; ++i){
    	cout<<st.get(i)<<el;
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}