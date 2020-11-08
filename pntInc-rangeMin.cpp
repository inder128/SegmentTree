#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n, NEUTRAL = LLONG_MAX;
	vi ST;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, NEUTRAL);
	}

	void printUtil(int si, int sl, int sr){
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<el;

		if(sl == sr) return;

		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void increaseUtil(int si, int sl, int sr, int i, int inc){
		if(sl == sr){
			ST[si] += inc;
			return;
		}

		if(i <= mid)
			increaseUtil(lsi, sl, mid, i, inc);
		else
			increaseUtil(rsi, mid + 1, sr, i, inc);

		ST[si] = min(ST[lsi], ST[rsi]);
	}
	void increase(int i, int inc){
		return increaseUtil(0, 0, n - 1, i, inc);
	}


	int getMinUtil(int si, int sl, int sr, int ql, int qr){
		if(sr < ql or qr < sl) return NEUTRAL;

		if(ql <= sl and sr <= qr) return ST[si]; 

		int leftMin = getMinUtil(lsi, sl, mid, ql, qr);
		int rightMin = getMinUtil(rsi, mid + 1, sr, ql, qr);
		return min(leftMin, rightMin);
	}
	int getMin(int ql, int qr){
		return getMinUtil(0, 0, n - 1, ql, qr);
	}
};