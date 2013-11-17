// <algorithm> <cstdio> {typedef long long ll}

/**
  Precompute N choose K in O(n^2) time

  Limits:
    [34][34]   (up to 33)  for  32-bit integers (int)
    [67][67]   (up to 66)  for  64-bit integers (ll)
    [131][131] (up to 130) for 128-bit integers (__int128)
**/

ll choose[67][67];
void choose_fill() {
  for (int i=0; i<67; i++)
    choose[0][i] = 0,
    choose[i][0] = 1;

  for (int i=1; i<67; i++)
    for (int j=1; j<67; j++)
      choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
}

/**
  Fast method for one-off calculation: O(min(k,n-k))
**/

ll choice(int n,int k){
  k=min(k,n-k);
  ll res = (n>=k);
  for (ll i=1; i<=k; i++)
    res *= (i+n-k),
    res /= i;
  return res;
}

/* Example usage
  choose_fill();

  printf("%lld\n",choose[23][7]);
  printf("%lld\n",choice(23,7));
*/

/* Stirling number of the first kind
 *
 * ie. the number of permutations of length N
 * with exactly K cycles
 *
 * actual Stirling numbers can be negative, iff
 * (N-K) is congruent to 1 mod 2
 */
ll stirling_one(ll n,ll k){
  static ll s[50][50];

  return
    !(n&&k)? not k
  : s[n][k]? s[n][k]
  :          s[n][k] = stirling_one(n-1,k) + stirling_one(n-1,k-1) * (n-1);
}

/* Stirling number of the second kind
 *
 * ie. the number of ways of splitting N objects
 * into exactly K non-empty sets
 *
 */
ll stirling_two(ll n,ll k){
  static ll s[50][50];

  return
    n<2 or k<1? k==n
  : s[n][m]?    s[n][k]
  :             s[n][k] = stirling_two(n-1,k-1) + stirling_two(n-1,k) * k;
}
