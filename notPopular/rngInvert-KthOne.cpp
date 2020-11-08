#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = 0;
	bool NO_OPERATION = false;
	vi ST;
	vector <bool> lazy;
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


	void invert(int si, int sl, int sr){
		ST[si] = (sr - sl + 1) - ST[si];
		lazy[si] = !lazy[si];
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		invert(lsi, sl, mid);
		invert(rsi, mid + 1, sr);
		lazy[si] = NO_OPERATION;
	}
	

	void invertUtil(int si, int sl, int sr, int ql, int qr){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return invert(si, sl, sr);
		}

		propogate(si, sl, sr);

		invertUtil(lsi, sl, mid, ql, qr);
		invertUtil(rsi, mid + 1, sr, ql, qr);

		ST[si] = ST[lsi] + ST[rsi];
	}
	void invert(int ql, int qr){
		return invertUtil(0, 0, n - 1, ql, qr);
	}


	int getKthOneIndUtil(int si, int sl, int sr, int k){
		if(sl == sr) return sl;

		propogate(si, sl, sr);

		if(ST[lsi] > k){
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