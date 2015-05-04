#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > tarjan(int n, const vector< vector<int> >& adjList);

//der er n udsagn x(0), .., x(n-1).
//i svarer til x(i) og n+i svarer til not x(i) for i = 0,..,n-1
//(a,b) er med i conditions hvis a eller b.
bool sat2(int n, const vector< pair<int, int> >& conditions) {
	vector< vector<int> > adjList(2*n, vector<int>(0));
	for(vector< pair<int,int> >::const_iterator pIt = conditions.begin(); pIt != conditions.end(); ++pIt) {
		int a = pIt->first, b = pIt->second;
		adjList[(a+n)%(2*n)].push_back(b%(2*n)); //(not a) => b
		adjList[(b+n)%(2*n)].push_back(a%(2*n)); //(not b) => a
	}
	vector< vector<int> > components = tarjan(2*n, adjList);
	vector<int> componentNum(2*n, -1);
	for(int i = 0;i < components.size(); ++i) {
		for(int j = 0;j < components[i].size(); ++j) {
			componentNum[components[i][j]] = i;
		}
	}
	bool satisfiable = true;
	for(int i = 0;i < n; ++i) {
		if(componentNum[i] == componentNum[i+n]) {
			satisfiable = false;
		}
	}
	return satisfiable;
}

int main() {
	return 0;
}

void tarjanSeek(int pos, const vector< vector<int> >& adjList, vector<int>& stack, vector<int>& visitNum,
				vector<int>& lowerLimit, vector<bool>& inStack, int& counter, vector< vector<int> >& components) {
	visitNum[pos] = lowerLimit[pos] = counter++;
	stack.push_back(pos);
	inStack[pos] = true;
	for(vector<int>::const_iterator pIt = adjList[pos].begin(); pIt != adjList[pos].end(); ++pIt) {
		int j = *pIt;
		if(visitNum[j] == -1) {	
			tarjanSeek(j, adjList, stack, visitNum, lowerLimit, inStack, counter, components);
			lowerLimit[pos] = min(lowerLimit[pos], lowerLimit[j]);
		} else if(inStack[j]) {
			lowerLimit[pos] = min(lowerLimit[pos], visitNum[j]);
		}
	}
	if(lowerLimit[pos] == visitNum[pos]) {
		int i = stack.size()-1;
		while(stack[i] != pos) inStack[stack[i--]] = false;
		inStack[pos] = false;
		components.push_back(vector<int>(stack.begin()+i, stack.end()));
		stack.erase(stack.begin()+i, stack.end());
	}
}

vector< vector<int> > tarjan(int n, const vector< vector<int> >& adjList) {
	vector< vector<int> > components;
	vector<int> stack(0);
	vector<int> visitNum(n, -1), lowerLimit(n, -1);
	vector<bool> inStack(n, false);
	int counter = 0;
	for(int i = 0; i < n; ++i) {
		if(visitNum[i] == -1) {
			tarjanSeek(i, adjList, stack, visitNum, lowerLimit, inStack, counter, components);
		}
	}
	return components;
}