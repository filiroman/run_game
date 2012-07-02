/* 
	A* algorithm
*/
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using std::set;
using std::pair;
using std::vector;
typedef vector<pair<int,int> > myvec;
const int n = 10;
int ar[n][n];
bool used[n][n];
int p[n][n];
int g[n][n];
pair<int,int> start, end;
int near[] = {-1, 0, 1, 0, -1};

int h(const int &x) {
	return abs(x/n - end.first) + abs(x%n - end.second);
}

int f(const int &x) {
	return g[x/n][x%n] + h(x);
}

class mycompare {
public:
	bool operator() (const int& lhs, const int& rhs) const {
		return f(lhs)<(rhs);
	};
};

//priority_queue< int, std::vector<int>, mycompare > q;
set<int, mycompare> q;

void A_star() {
	q.insert(start.first*n+start.second);
	g[start.first][start.second] = 0;
	p[start.first][start.second] = -1;
	while (!q.empty()) {
		set<int, mycompare>::iterator it = q.end(); it--;
		int v = *it;
		q.erase(it);
		int i = v/n, j = v%n;
		used[i][j] = true;
		if (i == end.first && j == end.second)
			return;
		
		for(int k=0;k<4;++k) {
			int m = i+near[k], l = j+near[k+1];
			if (m > n-1 || m < 0 || l > n-1 || l < 0)
				continue;
			if (used[m][l] || ar[m][l] == 1)
				continue;
			
			bool better;
			set<int, mycompare>::iterator ti = q.find(m*n+l);
			if (ti == q.end()) {
				p[m][l] = i*n+j;
				q.insert(m*n+l);	
			}
			else {
				g[i][j]+1 < g[m][l] ? better=true : better=false;
			}
			
			if (better) {
				p[m][l] = i*n+j;
				g[m][l] = g[i][j]+1;
			}					
		}
	}	
}

myvec path() {
	int i = end.first, j = end.second,k;
	k = p[i][j];
	vector<pair<int,int> > v;
	v.push_back(end);
	while (k != -1) {
		v.push_back(std::make_pair(k/n,k%n));
		k = p[k/n][k%n];
		//printf("%d\n",k);
	}		
	std::reverse(v.begin(),v.end());		
	return v; 
}

int main() {
	memset(ar,0,sizeof(int)*n*n);
	memset(p,0,sizeof(int)*n*n);
	memset(used,0,sizeof(bool)*n*n);
	int w;
	int m,n;
	scanf("%d",&w);
	for(int i=0;i<w;++i) {
		scanf("%d%d",&m,&n);
		ar[m][n] = 1;
	}
	start.first = 7;
	start.second = 9;
	end.first = 9;
	end.second = 9;
	A_star();
	myvec res = path();
	for(myvec::iterator it = res.begin(); it!=res.end(); ++it)
		printf("%d %d\n",it->first,it->second);	
	return 0;
}
