#include <iostream>
#include <vector>
#include <functional>
#include <climits>

using namespace std;

struct SEGTREE{
	vector<int> data; // let 1 be the top pos, then values from [1, 2N-1] are used
	int N, identityval; // array size
	function<int(int, int)> opfunc; // operator, can be non-commutative but must be associative
	SEGTREE(int size, int identity, function<int(int,int)> operatorfunction){
		N = size;
		identityval = identity;
		opfunc = operatorfunction;
		data = vector<int>(2*N, identityval);
	}
	void update(int index, int val){
		index += N;
		data[index] = val;
		index /= 2;
		while(index > 0){
			data[index] = data[2*index] + data[2*index+1];
			index /= 2;
		}
	}
	int query(int start, int end){
		int leftopval = identityval;
		int rightopval = identityval;
		start += N;
		end += N;
		while(start <= end){
			if(start % 2 == 1){
				leftopval = opfunc(leftopval, data[start]);
				start++;
			}
			if(end % 2 == 0){
				rightopval = opfunc(data[end], rightopval);
				end--;
			}
			start /= 2;
			end /= 2;
		}
		return(opfunc(leftopval, rightopval));
	}
};

int minfunc(int a, int b){
	return(a <= b ? a : b);
}

int main(){ // tested using https://cses.fi/problemset/task/1649
	int N, Q;
	cin >> N >> Q;
	SEGTREE segtree(N, INT_MAX, &minfunc);
	for(int i = 0; i < N; i++){
		int temp;
		cin >> temp;
		segtree.update(i, temp);
	}
	for(int i = 0; i < Q; i++){
		int opcode, argone, argtwo;
		cin >> opcode >> argone >> argtwo;
		if(opcode == 1){
			segtree.update(argone, argtwo);
		} else {
			cout << segtree.query(argone, argtwo) << endl;
		}
	}
}
