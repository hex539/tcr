#include <bits/stdc++.h> /*{{{*/
using namespace std;
typedef long long ll; typedef long double ld; /*}}}*/

int main(){
  // enable cin/cout buffering (much faster)
  ios::sync_with_stdio(false);

  // set 6 decimal places for float outputs
  cout.precision(6);
  cout<<fixed;

  // testcase solver loop
  for(int n; cin>>n;){

    cout<<ld(n)+0.5L<<endl;

  }
}

/**** VIMRC ***

" set colourblind mode, disable swapfiles
set background=dark
set noswapfile
set nohlsearch
set nowrap

" sane indentation settings
set autoindent
set expandtab
set tabstop=2
set shiftwidth=2

" fold using {{{ ... }}} inside comments or zf+zc
set foldmethod=marker

*************/
