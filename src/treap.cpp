#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

struct node
{
    int key;
    int pri;
    int cnt;
    node *l, *r;
    node() { }
    node(int _key, int _pri) :
        key(_key), pri(_pri), l(NULL), r(NULL), cnt(0)
    { }
};

typedef node *pnode;

void upd_cnt(node *n)
{
    if (!n)
        return;
    n->cnt = 1;
    if (n->l)
        n->cnt += n->l->cnt;
    if (n->r)
        n->cnt += n->r->cnt;
}

void split(node *n, int key, pnode &l, pnode &r)
{
    if (!n)
        l = r = NULL;
    else if (key < n->key)
    {
        split(n->l, key, l, n->l);
        r = n;
    }
    else
    {
        split(n->r, key, n->r, r);
        l = n;
    }
    upd_cnt(n);
}

void insert(pnode &n, int key, int pri)
{
    if (!n)
    {
        node *el = new node(key, pri);
        n = el;
    }
    else if (pri > n->pri)
    {
        // All the following nodes have less priority. Split them into
        // two subtrees and we're done.
        node *el = new node(key, pri);
        split(n, el->key, el->l, el->r);
        n = el;
    }
    else
        insert(key < n->key ? n->l : n->r, key, pri);
    upd_cnt(n);
}

void merge(pnode &n, pnode l, pnode r)
{
    if (!l || !r)
        n = l ? l : r;
    else if (l->pri > r->pri)
    {
        merge(l->r, l->r, r);
        n = l;
    }
    else
    {
        merge(r->l, l, r->l);
        n = r;
    }
    upd_cnt(n);
}

void del(pnode &n, int key)
{
    if (n->key == key)
    {
        node *old = n;
        merge(n, n->l, n->r);
        delete old;
    }
    else
        del(key < n->key ? n->l : n->r, key);
    upd_cnt(n);
}

pnode search(pnode n, int key)
{
    if (!n)
        return NULL;
    if (n->key == key)
        return n;
    else
        return search(key < n->key ? n->l : n->r, key);
}

int count(pnode n, int key)
{
    if (!n)
        return 0;
    if (n->key < key)
    {
        if (n->l)
            return 1 + n->l->cnt + count(n->r, key);
        return 1 + count(n->r, key);
    }
    else
        return (n->key == key ? 1 : 0) + count(n->l, key);
}

int main()
{
    srand(1641235); // Some seed. We probably can't use time in contest.

    int t;
    cin >> t;
    while (t-- > 0)
    {
        node *root = NULL;
        int n,m;
        cin >> n >> m;
        map<int,int> ma;
        for (int i = 1; i <= n; ++i)
        {
            ma[i] = i;
            insert(root, i, rand());
        }
        for (int i = 0; i < m; ++i)
        {
            int x;
            cin >> x;
            int j = ma[x];
            cout << count(root, j)-1 << " ";
            del(root, j);
            j = -i;
            ma[x] = j;
            insert(root, j, rand());
        }
        cout << endl;
    }
}
