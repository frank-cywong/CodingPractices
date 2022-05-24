#include <iostream>

using namespace std;

typedef long long ll;

struct Point{
	int x;
	int y;
	Point(int _x, int _y){
		x = _x;
		y = _y;
	}
	Point operator+ (Point const &other){
		Point o = Point(x + other.x, y + other.y);
		return o;
	}
	Point operator- (Point const &other){
		Point o = Point(x - other.x, y - other.y);
		return o;
	}
	ll dot(Point* other){
		ll o = 0;
		o += (ll)(x) * (ll)(other->x);
		o += (ll)(y) * (ll)(other->y);
		return o;
	}
	ll cross(Point* other){
		ll o = 0;
		o += (ll)(x) * (ll)(other->y);
		o -= (ll)(y) * (ll)(other->x);
		return o;
	}
};

int sig(ll a){
	return (a == 0 ? 0 : (a > 0 ? 1 : -1));
}

bool inRange(int toCheck, int boundA, int boundB){
	if(boundB < boundA){
		swap(boundA, boundB);
	}
	return(toCheck >= boundA && toCheck <= boundB);
}

// check if [a,b], [c,d] have a non-empty intersection
bool inRange(int a, int b, int c, int d){
	if(b < a){
		swap(a,b);
	}
	if(d < c){
		swap(c,d);
	}
	return(a <= d && c <= b);
}


// tested on https://cses.fi/problemset/task/2190/
int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		int a,b,c,d,e,f,g,h;
		cin >> a >> b >> c >> d >> e >> f >> g >> h;
		Point pa = Point(a,b);
		Point pb = Point(c,d);
		Point pc = Point(e,f);
		Point pd = Point(g,h);
		Point npb = pb - pa;
		Point npc = pc - pa;
		Point npd = pd - pa;
		int s1 = sig(npb.cross(&npc));
		int s2 = sig(npb.cross(&npd));
		if(s1 == 0 && s2 == 0){ // colinear
			if(!inRange(npc.x, npd.x, 0, npb.x) || !inRange(npc.y, npd.y, 0, npb.y)){
				cout << "NO" << endl;
				continue;
			}
			cout << "YES" << endl;
			continue;
		}
		if(s1 == 0){
			if(!inRange(npc.x, 0, npb.x) || !inRange(npc.y, 0, npb.y)){
				cout << "NO" << endl;
				continue;
			}
			cout << "YES" << endl;
			continue;
		}
		if(s2 == 0){
			if(!inRange(npd.x, 0, npb.x) || !inRange(npd.y, 0, npb.y)){
				cout << "NO" << endl;
				continue;
			}
			cout << "YES" << endl;
			continue;
		}
		if(s1 == s2){
			cout << "NO" << endl;
			continue;
		}
		npb = pd - pc;
		npc = pa - pc;
		npd = pb - pc;
		s1 = sig(npb.cross(&npc));
		s2 = sig(npb.cross(&npd));
		if(s1 == s2){
			cout << "NO" << endl;
			continue;
		}
		cout << "YES" << endl;
	}
	return 0;
}

