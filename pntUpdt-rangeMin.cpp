#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class SegmentTree {
public :
	int size, n;
	int NEUTRAL = LLONG_MAX;
	vi ST;

	SegmentTree (int n) {
		this->n = n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, NEUTRAL);
	}

	void print (int si, int sl, int sr) const {
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<el;

		if(sl == sr) return;

		print(lsi, sl, mid);
		print(rsi, mid + 1, sr);
	}
	friend ostream& operator << (ostream& os, const SegmentTree& segTree) {
		segTree.print(0, 0, segTree.n - 1);
		return os;
	}


	void update (int si, int sl, int sr, int i, int newVal) {
		if(sl == sr){
			ST[si] = newVal;
			return;
		}

		if(i <= mid){
			update(lsi, sl, mid, i, newVal);
		}
		else{
			update(rsi, mid + 1, sr, i, newVal);
		}

		ST[si] = min(ST[lsi], ST[rsi]);
	}
	void update (int i, int newVal) {
		return update(0, 0, n - 1, i, newVal);
	}


	int getMin (int si, int sl, int sr, int ql, int qr) {
		if(sr < ql or qr < sl) return NEUTRAL;

		if(ql <= sl and sr <= qr) return ST[si]; 

		int leftMin = getMin(lsi, sl, mid, ql, qr);
		int rightMin = getMin(rsi, mid + 1, sr, ql, qr);
		return min(leftMin, rightMin);
	}
	int getMin(int ql, int qr){
		return getMin(0, 0, n - 1, ql, qr);
	}
};