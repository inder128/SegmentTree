#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class SegmentTree {
public :
	int size, n;
	int NEUTRAL = 0;
	vi ST;
	int NO_OPERATION = 0;
	vi lazy;

	SegmentTree (int n) {
		this->n = n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, 0ll);
		lazy.assign(2 * size - 1, NO_OPERATION);
	}

	void print (int si, int sl, int sr) const {
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<", "<<lazy[si]<<el;

		if(sl == sr) return;

		print(lsi, sl, mid);
		print(rsi, mid + 1, sr);
	}
	friend ostream& operator << (ostream& os, const SegmentTree& segTree) {
		segTree.print(0, 0, segTree.n - 1);
		return os;
	}


	void increase (int si, int sl, int sr, int inc) {
		ST[si] += inc * (sr - sl + 1);
		lazy[si] += inc;
	}
	void propogate (int si, int sl, int sr) {
		if(lazy[si] == NO_OPERATION) return;
		increase(lsi, sl, mid, lazy[si]);
		increase(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void increase (int si, int sl, int sr, int ql, int qr, int inc) {
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return increase(si, sl, sr, inc);
		}

		propogate(si, sl, sr);

		increase(lsi, sl, mid, ql, qr, inc);
		increase(rsi, mid + 1, sr, ql, qr, inc);

		ST[si] = ST[lsi] + ST[rsi];
	}
	void increase (int ql, int qr, int inc) {
		return increase (0, 0, n - 1, ql, qr, inc);
	}


	int getSum (int si, int sl, int sr, int ql, int qr) {
		if(qr < sl or sr < ql) return NEUTRAL;

		if(ql <= sl and sr <= qr){
			return ST[si];
		}

		propogate(si, sl, sr);

		int leftSum = getSum(lsi, sl, mid, ql, qr);
		int rightSum = getSum(rsi, mid + 1, sr, ql, qr);
		return leftSum + rightSum;
	}
	int getSum (int ql, int qr) {
		return getSum(0, 0, n - 1, ql, qr);
	}
};