#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class SegmentTree {
public :
	int size, n;
	int NEUTRAL = LLONG_MAX;
	vi ST;
	int NO_OPERATION = LLONG_MAX;
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


	void update (int si, int sl, int sr, int val) {
		ST[si] = val;
		lazy[si] = val;
	}
	void propogate (int si, int sl, int sr) {
		if(lazy[si] == NO_OPERATION) return;
		update(lsi, sl, mid, lazy[si]);
		update(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void update (int si, int sl, int sr, int ql, int qr, int val) {
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return update(si, sl, sr, val);
		}

		propogate(si, sl, sr);

		update(lsi, sl, mid, ql, qr, val);
		update(rsi, mid + 1, sr, ql, qr, val);

		ST[si] = min(ST[lsi], ST[rsi]);
	}
	void update(int ql, int qr, int val){
		return update(0, 0, n - 1, ql, qr, val);
	}


	int getMin (int si, int sl, int sr, int ql, int qr) {
		if(qr < sl or sr < ql) return NEUTRAL;

		if(ql <= sl and sr <= qr){
			return ST[si];
		}

		propogate(si, sl, sr);

		int leftMin = getMin(lsi, sl, mid, ql, qr);
		int rightMin = getMin(rsi, mid + 1, sr, ql, qr);
		return min(leftMin, rightMin);
	}
	int getMin (int ql, int qr) {
		return getMin(0, 0, n - 1, ql, qr);
	}
};