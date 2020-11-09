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

#define lsi 2*si + 1
#define rsi 2*si + 2
class segmentTree{
public :
	int size, n, neutral = LLONG_MAX;
	vi ST;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size, neutral);
	}


	inline int getMid(int &sl, int &sr){
		return (sl + sr) >> 1;
	}
	void printUtil(int si, int sl, int sr){
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<el;

		if(sl == sr) return;

		int mid = getMid(sl, sr);
		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void updateUtil(int si, int sl, int sr, int i, int newVal){
		if(sl == sr){
			ST[si] = newVal;
			return;
		}

		int mid = getMid(sl, sr);
		if(i <= mid)
			updateUtil(lsi, sl, mid, i, newVal);
		else
			updateUtil(rsi, mid + 1, sr, i, newVal);

		ST[si] = min(ST[lsi], ST[rsi]);
	}
	void update(int i, int newVal){
		return updateUtil(0, 0, n - 1, i, newVal);
	}


	int getUtil(int si, int sl, int sr, int ql, int qr, int val){
		if(sr < ql or qr < sl) return -1;

		if(ST[si] > val) return -1;

		if(sl == sr) return sl;

		int mid = getMid(sl, sr);
		int ans = getUtil(lsi, sl, mid, ql, qr, val);
		if(ans == -1){
			ans = getUtil(rsi, mid + 1, sr, ql, qr, val);
		}
		return ans;
	}
	int getLeftmostNotMore(int ql, int qr, int val){
		return getUtil(0, 0, n - 1, ql, qr, val);
	}
};

void solve(){
    int n, m; cin>>n>>m;
    segmentTree st(n);
    while(m--){
    	int op; cin>>op;
    	if(op == 1){
    		int i, val; cin>>i>>val;
    		st.update(i, val);
    	}
    	else{
    		int l, r, val; cin>>l>>r>>val;
    		r--;
    		int ans = 0;
    		while(true){
    			int i = st.getLeftmostNotMore(l, r, val);
    			if(i == -1) break;
    			ans++;
    			st.update(i, LLONG_MAX);
    		}
    		cout<<ans<<el;
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