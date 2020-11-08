#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = LLONG_MIN;
	vi ST;
	int NO_OPERATION = 0;
	vi lazy;
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


	void increase(int si, int sl, int sr, int inc){
		ST[si] += inc;
		lazy[si] += inc;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		increase(lsi, sl, mid, lazy[si]);
		increase(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void increaseUtil(int si, int sl, int sr, int ql, int qr, int inc){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return increase(si, sl, sr, inc);
		}

		propogate(si, sl, sr);

		increaseUtil(lsi, sl, mid, ql, qr, inc);
		increaseUtil(rsi, mid + 1, sr, ql, qr, inc);

		ST[si] = max(ST[lsi], ST[rsi]);
	}
	void increase(int ql, int qr, int inc){
		return increaseUtil(0, 0, n - 1, ql, qr, inc);
	}


	int getLeftmostNotLessUtil(int si, int sl, int sr, int l, int val){
		if(sr < l) return -1;

		if(ST[si] < val) return -1;

		if(sl == sr) return sl;

		propogate(si, sl, sr);

		int ans = getLeftmostNotLessUtil(lsi, sl, mid, l, val);
		if(ans == -1){
			ans = getLeftmostNotLessUtil(rsi, mid + 1, sr, l, val);
		}
		return ans;
	}
	int getLeftmostNotLess(int l ,int val){
		return getLeftmostNotLessUtil(0, 0, n - 1, l, val);
	}
};