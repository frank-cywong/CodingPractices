#include <iostream>
#include <vector>

using namespace std;

struct scc{
	vector<vector<int>> adjlist; // if positive represents out, if negative represents in
	vector<vector<int>> edgelist;
	vector<vector<int>> sccgroups; // Vector of vectors, each subvector is a strongly connected component, with elements in vector being indicies
	vector<bool> visited;
	vector<int> finished;
	vector<int> componentof;
	scc(int N){
		adjlist = vector<vector<int>>(N);
		sccgroups = vector<vector<int>>;
	}
	void addedge(int a, int b){ // adds directed edge from node a to b, where 0 <= a,b < N
		adjlist[a].push_back(b);
		adjlist[b].push_back(-a);
		vector<int> vi = vector(2);
		vi[0] = a;
		vi[1] = b;
		edgelist.push_back(vi);
	}
	private void dfsone(int node){
		if(visited[node]){
			return;
		}
		visited[node] = true;
		for(auto it = adjlist[node].begin(); it != adjlist[node].end(); it++){
			if(*it < 0){
				continue;
			}
			dfsone(*it);
		}
		finished.push_back(node);
	}
	void compscc(){
		visited = vector<bool>(adjlist.size(), false);
		finished = vector<int>(adjlist.size(), false);
		for(int i = 0; i < adjlist.size(); i++){
			dfsone(i);
		}
		componentof = vector<int>(adjlist.size(), -1);
		while(finished.size() != 0){
			int curnode = finished.pop_back();
			if(componentof[curnode] == -1){
				continue;
			}
			visited = vector<bool>(adjlist.size(), false);
			dfstwo(curnode);
		}
	}
};

int main(){
	return 0;
}