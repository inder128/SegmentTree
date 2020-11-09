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

struct node{
	int sum, wSum;
};

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	node NEUTRAL = {LLONG_MIN, LLONG_MIN};
	int NO_OPERATION = 0;
	vector <node> ST;
	vi lazy;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, {0, 0});
		lazy.assign(2 * size - 1, NO_OPERATION);
	}

	void printUtil(int si, int sl, int sr){
		// cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<", "<<lazy[si]<<el;

		if(sl == sr) return;

		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void increase(int si, int sl, int sr, int inc){
		int len = (sr - sl + 1);
		ST[si].sum += inc * len;
		ST[si].wSum += (len * (len + 1) / 2) * inc;
		lazy[si] += inc;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		increase(lsi, sl, mid, lazy[si]);
		increase(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	
	node merge(node n1, node n2, int ln){
		if(n1.sum == LLONG_MIN) return n2;
		if(n2.sum == LLONG_MIN) return n1;

		node ans;
		ans.sum = n1.sum + n2.sum;
		ans.wSum = n1.wSum + n2.sum * ln + n2.wSum;
		return ans;
	}
	void increaseUtil(int si, int sl, int sr, int ql, int qr, int inc){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return increase(si, sl, sr, inc);
		}

		propogate(si, sl, sr);

		increaseUtil(lsi, sl, mid, ql, qr, inc);
		increaseUtil(rsi, mid + 1, sr, ql, qr, inc);

		ST[si] = merge(ST[lsi], ST[rsi], mid - sl + 1);
	}
	void increase(int ql, int qr, int inc){
		return increaseUtil(0, 0, n - 1, ql, qr, inc);
	}


	node getSumUtil(int si, int sl, int sr, int ql, int qr){
		if(qr < sl or sr < ql) return NEUTRAL;

		if(ql <= sl and sr <= qr){
			return ST[si];
		}

		propogate(si, sl, sr);

		node leftSum = getSumUtil(lsi, sl, mid, ql, qr);
		node rightSum = getSumUtil(rsi, mid + 1, sr, ql, qr);
		return merge(leftSum, rightSum, mid - max(ql, sl) + 1);
	}
	int getSum(int ql, int qr){
		return getSumUtil(0, 0, n - 1, ql, qr).wSum;
	}
};

void solve(){
    int n, q; cin>>n>>q;
    segmentTree st(n);
    for (int i = 0; i < n; ++i){
    	int val; cin>>val;
    	st.increase(i, i, val);
    }
    while(q--){
    	int op; cin>>op;
    	if(op == 1){
    		int l, r, d; cin>>l>>r>>d;
    		l--, r--;
    		st.increase(l, r, d);
    	}
    	else{
    		int l, r; cin>>l>>r;
    		l--, r--;
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