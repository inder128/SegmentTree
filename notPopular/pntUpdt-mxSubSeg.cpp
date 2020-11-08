struct node{
	int pre, suff, mxSum, sum;
};

#define lsi 2*si + 1
#define rsi 2*si + 2
class segmentTree{
public :
	int size, n;
	node neutral = {0, 0, 0, 0};
	vector <node> ST;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size, neutral);
	}


	inline int getMid(int &sl, int &sr){
		return (sl + sr) >> 1;
	}
	void printUtil(int si, int sl, int sr){
		// cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<el;

		if(sl == sr) return;

		int mid = getMid(sl, sr);
		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
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
	void updateUtil(int si, int sl, int sr, int i, int newVal){
		if(sl == sr){
			int tmp = max(0ll, newVal);
			ST[si] = {tmp, tmp, tmp, newVal};
			return;
		}

		int mid = getMid(sl, sr);
		if(i <= mid)
			updateUtil(lsi, sl, mid, i, newVal);
		else
			updateUtil(rsi, mid + 1, sr, i, newVal);

		merge(si);
	}
	void update(int i, int newVal){
		return updateUtil(0, 0, n - 1, i, newVal);
	}


	int getMaxSubsegmentSum(){
		return ST[0].mxSum;
	}
};