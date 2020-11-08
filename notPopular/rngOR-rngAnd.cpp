// can use lazy propogation;

// | is distributive relative to &;
// (a | v) & (b | v) = (a & b) | v ;

// both | and & are associative;
// (a | b) | c = a | (b | c);
// (a & b) & c = a & (b & c);

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	int NEUTRAL = LLONG_MAX, NO_OPERATION = 0;
	vi ST, lazy;
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


	void applyOR(int si, int sl, int sr, int val){
		ST[si] |= val;
		lazy[si] |= val;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		applyOR(lsi, sl, mid, lazy[si]);
		applyOR(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void applyORUtil(int si, int sl, int sr, int ql, int qr, int val){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return applyOR(si, sl, sr, val);
		}

		propogate(si, sl, sr);

		applyORUtil(lsi, sl, mid, ql, qr, val);
		applyORUtil(rsi, mid + 1, sr, ql, qr, val);

		ST[si] = ST[lsi] & ST[rsi];
	}
	void applyOR(int ql, int qr, int val){
		return applyORUtil(0, 0, n - 1, ql, qr, val);
	}


	int getAndUtil(int si, int sl, int sr, int ql, int qr){
		if(qr < sl or sr < ql) return NEUTRAL;

		if(ql <= sl and sr <= qr){
			return ST[si];
		}

		propogate(si, sl, sr);

		int leftAnd = getAndUtil(lsi, sl, mid, ql, qr);
		int rightAnd = getAndUtil(rsi, mid + 1, sr, ql, qr);
		return leftAnd & rightAnd;
	}
	int getAnd(int ql, int qr){
		return getAndUtil(0, 0, n - 1, ql, qr);
	}
};