#include <iostream>
#include <vector>

using namespace std;

struct DSU {
	vector<int> nodes; // nodes, value stored in vector is representative node (if +), or size (if -)
	DSU(int N) {
		nodes = vector<int>(N, -1);
	}
	int get_representative_node(int x){
		if(nodes[x] < 0){
			return x;
		}
		nodes[x] = get_representative_node(nodes[x]); // path compression
		return nodes[x];
	}
	int get_size(int x){
		return(nodes[x] < 0 ? -x : -nodes[get_representative_node(x)]);
	}
	bool connected(int x, int y){
		return(get_representative_node(x) == get_representative_node(y));
	}
	void union_op(int x, int y){ // one with lesser size > greater size
		int nodex = get_representative_node(x);
		int nodey = get_representative_node(y);
		if(nodex == nodey){ // ie connected
			return;
		}
		// assert that nodex has larger size
		if(nodes[nodex] > nodes[nodey]){
			swap(nodex, nodey);
		}
		// merge nodey into nodex
		nodes[nodex] += nodes[nodey];
		nodes[nodey] = nodex;
	}
};

int main(){
	int N, Q;
	cin >> N >> Q;
	DSU graph(N);
	for(int i = 0; i < Q; i++){
		int t, u, v;
		cin >> t >> u >> v;
		if(t == 0){
			graph.union_op(u,v);
		} else {
			cout << (graph.connected(u, v) ? 1 : 0) << endl;
		}
	}
	return 0;
}
