#include <iostream>
#include <vector>

using namespace std;

struct SCC{
	vector<vector<int>> adjlist; // if positive represents out, if negative represents in
	vector<vector<int>> edgelist;
	vector<vector<int>> sccgroups; // Vector of vectors, each subvector is a strongly connected component, with elements in vector being indicies
	vector<bool> visited;
	vector<int> finished;
	vector<int> componentof;
	SCC(int N){
		adjlist = vector<vector<int>>(N);
		sccgroups = vector<vector<int>>();
	}
	void addedge(int a, int b){ // adds directed edge from node a to b, where 0 <= a,b < N
		adjlist[a].push_back(b);
		adjlist[b].push_back((-1*a)-1);
		vector<int> vi = vector(2, 0);
		vi[0] = a;
		vi[1] = b;
		edgelist.push_back(vi);
	}
	private: void dfsone(int node){
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
	private: void dfstwo(int node, int grouptoaddto){
		if(componentof[node] != -1 || visited[node]){
			return;
		}
		visited[node] = true;
		sccgroups[grouptoaddto].push_back(node);
		componentof[node] = grouptoaddto;
		for(auto it = adjlist[node].begin(); it != adjlist[node].end(); it++){
			if(*it >= 0){
				continue;
			}
			dfstwo((*it)*(-1)-1, grouptoaddto);
		}
	}
	public: void compscc(){
		visited = vector<bool>(adjlist.size(), false);
		finished = vector<int>(adjlist.size(), false);
		for(int i = 0; i < adjlist.size(); i++){
			dfsone(i);
		}
		componentof = vector<int>(adjlist.size(), -1);
		while(finished.size() != 0){
			int curnode = finished.back();
			finished.pop_back();
			if(componentof[curnode] != -1){
				continue;
			}
			visited = vector<bool>(adjlist.size(), false);
			sccgroups.push_back(vector<int>());
			dfstwo(curnode, sccgroups.size() - 1);
		}
	}
};

int main(){
	int N; // node count
	int E; // edge count
	cin >> N >> E;
	SCC graph(N);
	for(int i = 0; i < E; i++){
		int tempa, tempb;
		cin >> tempa >> tempb;
		graph.addedge(tempa, tempb);
	}
	graph.compscc();
	for(auto it = graph.sccgroups.begin(); it != graph.sccgroups.end(); it++){
		cout << "Strongly connected component: ";
		for(auto it2 = it->begin(); it2 != it->end(); it2++){
			cout << *it2 << " ";
		}
		cout << endl;
	}
	return 0;
}