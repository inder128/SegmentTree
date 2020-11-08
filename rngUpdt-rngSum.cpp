#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = 0;
	vi ST;
	int NO_OPERATION = LLONG_MAX;
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


	void update(int si, int sl, int sr, int val){
		ST[si] = val * (sr - sl + 1);
		lazy[si] = val;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		update(lsi, sl, mid, lazy[si]);
		update(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void updateUtil(int si, int sl, int sr, int ql, int qr, int val){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return update(si, sl, sr, val);
		}

		propogate(si, sl, sr);

		updateUtil(lsi, sl, mid, ql, qr, val);
		updateUtil(rsi, mid + 1, sr, ql, qr, val);

		ST[si] = ST[lsi] + ST[rsi];
	}
	void update(int ql, int qr, int val){
		return updateUtil(0, 0, n - 1, ql, qr, val);
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