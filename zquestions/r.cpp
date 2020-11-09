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

typedef pair<bool, int> operation;

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = 0;
	vi ST;
	vector <operation> lazy;
	// NO_OPERATION -> a value which can never occur in lazy;
	operation NO_OPERATION = {false, LLONG_MAX};
	// lazy[i].F == true -> it is assign operation;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, 0ll);
		lazy.assign(2 * size - 1, NO_OPERATION);
	}

	void printUtil(int si, int sl, int sr){
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<", "<<lazy[si]<<el;

		if(sl == sr) return;

		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void apply(int si, int sl, int sr, operation op){
		if(op.F){ // assignment operation;
			ST[si] = op.S * (sr - sl + 1);
			lazy[si] = op;
		}
		else{ // increment operation;
			ST[si] += op.S * (sr - sl + 1);
			if(lazy[si] == NO_OPERATION)
				lazy[si] = op;
			else
				lazy[si].S += op.S;
		}
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		apply(lsi, sl, mid, lazy[si]);
		apply(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void applyUtil(int si, int sl, int sr, int ql, int qr, operation op){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return apply(si, sl, sr, op);
		}

		propogate(si, sl, sr);

		applyUtil(lsi, sl, mid, ql, qr, op);
		applyUtil(rsi, mid + 1, sr, ql, qr, op);

		ST[si] = ST[lsi] + ST[rsi];
	}
	void apply(int ql, int qr, operation op){
		return applyUtil(0, 0, n - 1, ql, qr, op);
	}


	int getSumUtil(int si, int sl, int sr, int ql, int qr){
		if(qr < sl or sr < ql) return NEUTRAL;

		if(ql <= sl and sr <= qr){
			return ST[si];
		}

		propogate(si, sl, sr);

		int leftSum = getSumUtil(lsi, sl, mid, ql, qr);
		int rightSum = getSumUtil(rsi, mid + 1, sr, ql, qr);
		return leftSum + rightSum;
	}
	int getSum(int ql, int qr){
		return getSumUtil(0, 0, n - 1, ql, qr);
	}
};

void solve(){
    int n, q; cin>>n>>q;
    segmentTree st(n);
    while(q--){
    	int op; cin>>op;
    	if(op == 1){
    		int l, r, val; cin>>l>>r>>val;
    		r--;
    		st.apply(l, r, {true, val});
    	}
    	else if(op == 2){
    		int l, r, inc; cin>>l>>r>>inc;
    		r--;
    		st.apply(l, r, {false, inc});
    	}
    	else{
    		int l, r; cin>>l>>r;
    		r--;
    		cout<<st.getSum(l, r)<<el;
    	}
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