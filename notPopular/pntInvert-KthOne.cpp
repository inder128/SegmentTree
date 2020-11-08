#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = 0;
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


	void invertUtil(int si, int sl, int sr, int i){
		if(sl == sr){
			ST[si] = !ST[si];
			return;
		}

		if(i <= mid)
			invertUtil(lsi, sl, mid, i);
		else
			invertUtil(rsi, mid + 1, sr, i);

		ST[si] = ST[lsi] + ST[rsi];
	}
	void invert(int i){
		return invertUtil(0, 0, n - 1, i);
	}


	int getKthOneIndUtil(int si, int sl, int sr, int k){
		if(sl == sr) return sl;

		if(ST[lsi] >= k){
			return getKthOneIndUtil(lsi, sl, mid, k);
		}
		else{
			return getKthOneIndUtil(rsi, mid + 1, sr, k - ST[lsi]);
		}
	}
	int getKthOneInd(int k){
		return getKthOneIndUtil(0, 0, n - 1, k);
	}
};