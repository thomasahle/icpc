#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct seats {
    int n;
    vector<int> tree;
    seats(int _n) : n(_n), tree(4*_n, 0) { buildTree(1, 1, _n); }
    int getBestSeatPosition(int start) {
        int x = getTree(1, 1, n, 1, start-1), y = getTree(1, 1, n, start+1, n);
        int p1 =  leftSearch(1, 1, n, x+1);
        int p2 = rightSearch(1, 1, n, y+1);
        if(p1 == -1) return p2;
        if(p2 == -1) return p1;
        if(abs(p1-start) == abs(p2-start)) {
            return min(p1, p2);
        } else if(abs(p1-start) < abs(p2-start)) {
            return p1;
        } else {
            return p2;
        }
    }
    void seatPerson(int position) {
        addTree(1, 1, n, position, -1);
    }
    void leavePerson(int position) {
        addTree(1, 1, n, position, 1);
    }
    int freeSeats(int from, int to) {
        return getTree(1, 1, n, from, to);
    }
    int rightSearch(int p, int i, int j, int value) {
        if(i == j) return tree[p] == value ? i : -1;
        if(tree[2*p+1] >= value) {
            rightSearch(2*p+1, (i+j)/2+1, j, value);
        } else {
            rightSearch(2*p, i, (i+j)/2, value-tree[2*p+1]);
        }
    }
    int leftSearch(int p, int i, int j, int value) {
        if(i == j) return tree[p] == value ? i : -1;
        if(tree[2*p] >= value) {
            leftSearch(2*p, i, (i+j)/2, value);
        } else {
            leftSearch(2*p+1, (i+j)/2+1, j, value-tree[2*p]);
        }
    }
    int getTree(int p, int i, int j, int from, int to) {
        if(i > to || j < from) return 0;
        if(from <= i  && to >= j) return tree[p];
        return getTree(2*p, i, (i+j)/2, from, to)+
               getTree(2*p+1, (i+j)/2+1, j, from, to);
    }
    void buildTree(int p, int i, int j) {
        tree[p] = j-i+1;
        if(i < j) {
            buildTree(2*p, i, (i+j)/2);
            buildTree(2*p+1, (i+j)/2+1, j);
        }
    }
    void addTree(int p, int i, int j, int pos, int value) {
        if(i <= pos && pos <= j) {
            tree[p] += value;
            if(i < j) {
                addTree(2*p, i, (i+j)/2,     pos, value);
                addTree(2*p+1, (i+j)/2+1, j, pos, value);
            }
        }
    }
};

int main() {
    int n, m;
    cin.tie(NULL);
    cin >> n >> m;
    seats s(n);
    while(m --> 0) {
        char c;
        int pos;
        cin >> c >> pos;
        if(c == 'C') {
            int bestPos = s.getBestSeatPosition(pos);
            s.seatPerson(bestPos);
            cout << bestPos << '\n';
        } else {
            s.leavePerson(pos);
        }
    }
    return 0;
}
