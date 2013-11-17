#include <bits/stdc++.h>
using namespace std;

/**
  aho<N>::corasick(vector<string> keywords)

  Multi-string matching in O(N).
**/

template <int N> struct aho{
  aho *good[N], *fail;
  int hits;

  aho(): fail(0), hits(0) {for (int i=N; i--;) good[i]=0;}

  struct corasick{
    aho *root;

    corasick(vector<string> dict){
      root=new aho();
      root->fail=root;
      for (int i=dict.size(),j; j=0,i--;)
        for (aho *on=root; j!=dict[i].size() or (++on->hits,false); on=on->good[dict[i][j++]])
          if (not on->good[dict[i][j]])
            on->good[dict[i][j]]=new aho();
      queue<aho*> bfs;
      queue<int> bft;
      for (bfs.push(root), bft.push(-1); not bfs.empty(); bfs.pop(),bft.pop()){
        while (bfs.front()->fail!=root   and not bfs.front()->fail->good[bft.front()]) bfs.front()->fail = bfs.front()->fail->fail;
        if (bfs.front() != bfs.front()->fail and bfs.front()->fail->good[bft.front()] and bfs.front()->fail->good[bft.front()]!=bfs.front())
          bfs.front()->fail = bfs.front()->fail->good[bft.front()];
        bfs.front()->hits+=bfs.front()->fail->hits;
        for (int i=N; i--;)
          if (bfs.front()->good[i] and not bfs.front()->good[i]->fail)
            bfs.front()->good[i]->fail=bfs.front()->fail,
            bfs.push(bfs.front()->good[i]),
            bft.push(i);
      }
    }

    ~corasick(){
      queue<aho*> bfs,del;
      for (bfs.push(root); not bfs.empty(); del.push(bfs.front()), bfs.pop())
        for (int i=N; i--;)
          if (bfs.front()->good[i] and bfs.front()->good[i]->fail)
            bfs.push(bfs.front()->good[i]),
            bfs.front()->good[i]->fail=0;
      for (; not del.empty(); del.pop())
        delete del.front();
    }

    int count(string const hay){
      int res=0;
      aho *state=root;
      for (int i=0; i<hay.size(); i++){
        while (state!=root and not state->good[hay[i]]) state=state->fail;
        if (state->good[hay[i]]) state=state->good[hay[i]];
        res+=state->hits;
      }
      return res;
    }
  };
};

/*
  *always* normalise strings to the range 0..N-1, where the N is from from "aho<N>::corasick"

  for (int i=str.size(); i--;)
    str[i] = (hay[i]==' '? 26: hay[i]-'a');
*/
