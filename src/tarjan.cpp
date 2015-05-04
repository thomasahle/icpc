#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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

int main() {
	vector< vector<int> > adjList(5, vector<int>(0));
	adjList[0].push_back(1);
	adjList[1].push_back(3);
	adjList[1].push_back(2);
	adjList[2].push_back(3);
	adjList[3].push_back(2);
	adjList[3].push_back(4);
	adjList[4].push_back(0);
	vector< vector<int> > components = tarjan(adjList.size(), adjList);
	cout << "Number of connected components: " << components.size() << endl;
	for(int i = 0; i < components.size(); ++i) {
		cout << i << ": ";
		for(int j = 0;j < components[i].size(); ++j) {
			cout << components[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}