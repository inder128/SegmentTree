#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class SegmentTree {
public :
	int size, n;
	int NEUTRAL = LLONG_MIN;
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

		ST[si] = max(ST[lsi], ST[rsi]);
	}
	void increase (int i, int inc) {
		return increase(0, 0, n - 1, i, inc);
	}


	int getLeftmostNotLess (int si, int sl, int sr, int val) {
		if(ST[si] < val) return -1;

		if(sl == sr) return sl;

		int ans = getLeftmostNotLess(lsi, sl, mid, val);
		if(ans == -1){
			ans = getLeftmostNotLess(rsi, mid + 1, sr, val);
		}
		return ans;
	}
	int getLeftmostNotLess(int val){
		return getLeftmostNotLess(0, 0, n - 1, val);
	}
};