#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class SegmentTree {
public :
	int size, n;
	int NEUTRAL = 0;
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


	void increase (int si, int sl, int sr, int i, int inc) {
		if(sl == sr){
			ST[si] += inc;
			return;
		}

		if(i <= mid){
			increase(lsi, sl, mid, i, inc);
		}
		else{
			increase(rsi, mid + 1, sr, i, inc);
		}

		ST[si] = ST[lsi] + ST[rsi];
	}
	void increase (int i, int inc) {
		return increase(0, 0, n - 1, i, inc);
	}


	int getSum (int si, int sl, int sr, int ql, int qr) {
		if(sr < ql or qr < sl) return NEUTRAL;

		if(ql <= sl and sr <= qr) return ST[si]; 

		int leftSum = getSum(lsi, sl, mid, ql, qr);
		int rightSum = getSum(rsi, mid + 1, sr, ql, qr);
		return leftSum + rightSum;
	}
	int getSum (int ql, int qr) {
		return getSum(0, 0, n - 1, ql, qr);
	}
};