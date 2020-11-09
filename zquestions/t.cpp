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
	int bCnt, bLen;
	bool lb, rb;
};

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	node NEUTRAL = {0, 0, false, false};
	char NO_OPERATION = 'N';
	vector <node> ST;
	vector <char> lazy;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, {0, 0, false, false});
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


	void update(int si, int sl, int sr, char c){
		if(c == 'B'){
			ST[si] = {1, sr - sl + 1, true, true};
		}
		else{
			ST[si] = {0, 0, false, false};
		}
		lazy[si] = c;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		update(lsi, sl, mid, lazy[si]);
		update(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void merge(int si){
		ST[si].bCnt = ST[lsi].bCnt + ST[rsi].bCnt;
		if(ST[lsi].rb and ST[rsi].lb) ST[si].bCnt--;

		ST[si].bLen = ST[lsi].bLen + ST[rsi].bLen;

		ST[si].lb = ST[lsi].lb;
		ST[si].rb = ST[rsi].rb;
	}
	void updateUtil(int si, int sl, int sr, int ql, int qr, char c){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return update(si, sl, sr, c);
		}

		propogate(si, sl, sr);

		updateUtil(lsi, sl, mid, ql, qr, c);
		updateUtil(rsi, mid + 1, sr, ql, qr, c);

		merge(si);
	}
	void update(int ql, int qr, char c){
		return updateUtil(0, 0, n - 1, ql, qr, c);
	}


	node get(){
		return ST[0];
	}
};

void solve(){
    int q; cin>>q;
    segmentTree st(1000'000 + 1);
    while(q--){
    	char c; cin>>c;
    	int x, l; cin>>x>>l;
    	x += 500000;
    	st.update(x, x + l - 1, c);
    	node ans = st.get();
    	cout<<ans.bCnt<<" "<<ans.bLen<<el;
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