struct node{
	int pre, suff, mxSum, sum;
};

#define lsi (2*si + 1)
#define rsi (2*si + 2)
#define mid ((sl + sr) >> 1)
class segmentTree{
public :
	int size, n;
	node neutral = {0, 0, 0, 0};
	vector <node> ST;
	int NO_OPERATION = LLONG_MAX;
	vi lazy;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size - 1, neutral);
		lazy.assign(2 * size - 1, NO_OPERATION);
	}

	void printUtil(int si, int sl, int sr){
		// cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<", "<<lazy[si]<<el;

		if(sl == sr) return;

		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void update(int si, int sl, int sr, int val){
		ST[si].sum = val * (sr - sl + 1);
		ST[si].suff = ST[si].pre = ST[si].mxSum = max(0ll, val * (sr - sl + 1));
		lazy[si] = val;
	}
	void propogate(int si, int sl, int sr){
		if(lazy[si] == NO_OPERATION) return;
		update(lsi, sl, mid, lazy[si]);
		update(rsi, mid + 1, sr, lazy[si]);
		lazy[si] = NO_OPERATION;
	}
	

	void merge(int si){
		// sum
		ST[si].sum = ST[lsi].sum + ST[rsi].sum;
		
		// pre
		ST[si].pre = max(ST[lsi].pre, ST[lsi].sum + ST[rsi].pre);

		// suff
		ST[si].suff = max(ST[lsi].suff + ST[rsi].sum, ST[rsi].suff);

		// mxSum
		ST[si].mxSum = max({ST[lsi].mxSum, ST[rsi].mxSum, ST[lsi].suff + ST[rsi].pre});
	}
	void updateUtil(int si, int sl, int sr, int ql, int qr, int val){
		if(qr < sl or sr < ql) return;

		if(ql <= sl and sr <= qr){
			return update(si, sl, sr, val);
		}

		propogate(si, sl, sr);

		updateUtil(lsi, sl, mid, ql, qr, val);
		updateUtil(rsi, mid + 1, sr, ql, qr, val);

		merge(si);
	}
	void update(int ql, int qr, int val){
		return updateUtil(0, 0, n - 1, ql, qr, val);
	}


	int getMaxSubsegmentSum(){
		return ST[0].mxSum;
	}
};