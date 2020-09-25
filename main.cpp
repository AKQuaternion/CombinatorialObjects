#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <deque>
using std::deque;
#include <exception>
using std::runtime_error;
#include <numeric>//for std::iota


void printVector(const vector<int> &v) {
   for (auto i : v)
      cout << i << " ";
   cout << endl;
}

// print least significant n bits of number
void printBits(size_t n, size_t number) {
   for (auto ii = int(n) - 1; ii >= 0; --ii)
      if (1u << (unsigned) ii & number)
         cout << "1";
      else
         cout << "0";
   cout << endl;
}

// prints the indices of bits set in number
void printSet(size_t n, size_t number) {
   for (auto jj = 0u; jj < n; ++jj)
      if (1u << jj & number)
         cout << jj + 1 << " ";
   cout << endl;
}

void subsets(size_t n) {
   for (auto ii = 0u; ii < 1u << n; ++ii) {
      printBits(n, ii);
      printSet(n, ii);
      cout << endl;
   }
}

vector<vector<int>> subsetsDecreaseBy1(int n) {
   if (n == 0)
      return {{}};
   auto subsets = subsetsDecreaseBy1(n - 1);
   auto howMany = subsets.size();
   for (int i = 0; i < howMany; ++i) {
      subsets.push_back(subsets[i]);
      subsets.back().push_back(n);
   }
   return subsets;
}

void flip(size_t &bits, size_t pos) { bits ^= (1u << pos); }

size_t leastSignificantOnePosition(size_t n) {
   for (auto ii = 0u; ii < 8 * sizeof(n); ++ii)
      if (n & 1u << ii)
         return ii;
   throw runtime_error("leastSignificantOnePosition(0)");
}

void grayCode(size_t n) {
   size_t bits = 0;
   auto ii = 0u;
   while (ii < 1u << n) {
      printBits(n, bits);
      printSet(n, bits);
      cout << endl;
      ++ii;
      flip(bits, leastSignificantOnePosition(ii));
   }
}

void stlPermutations(size_t n) {
   vector<int> v(n);
   std::iota(begin(v), end(v), 1);// fill with 1 to n

   do
      printVector(v);
   while (next_permutation(begin(v), end(v)));
}

void printSubset(const deque<bool> &comb) {
   for (auto ii = 0u; ii < comb.size(); ++ii)
      if (comb[ii])
         cout << ii + 1 << " ";
   cout << endl;
}

void combinations(size_t n, size_t k) {
   deque<bool> comb(n, false);
   fill(comb.begin(), comb.begin() + (long) k, true);

   do
      printSubset(comb);
   while (prev_permutation(begin(comb), end(comb)));
}

// goes through every possibility for true/false
// for positions n through v.size()-1 of v
void recursiveSubsets(int n, deque<bool> &v) {
   if (n == v.size()) {//base case, nothing to try
      printSubset(v);
      return;
   }
   v[n] = false;              // put false in position n,
   recursiveSubsets(n + 1, v);// go through possibilities for positions n+1 on
   v[n] = true;               // put true in position n
   recursiveSubsets(n + 1, v);// go through possibilities for positions n+1 on
}

vector<vector<int>> recursivePermutations(int n) {
   if (n == 0)
      return {{}};

   auto smallerPerms = recursivePermutations(n - 1);

   vector<vector<int>> perms;
   for (auto &p : smallerPerms) {
      p.push_back(n);
      perms.push_back(p);
      for (auto i = p.end() - 1; i != p.begin(); --i) {
         std::swap(*i, *(i - 1));
         perms.push_back(p);
      }
   }
   return perms;
}

void banner(const string &s) {
   cout << " -----------------------------------------------------------------\n";
   cout << s << endl;
   cout << " -----------------------------------------------------------------\n";
}

int main() {
   banner("subsets(5)");
   subsets(5);

   banner("deque<bool> d(5); recursiveSubsets(0, d);");
   deque<bool> d(5);
   recursiveSubsets(0, d);

   banner("subsetsDecreaseBy1(5);");
   auto ss = subsetsDecreaseBy1(5);
   for (const auto &s : ss)
      printVector(s);


   banner("recursivePermutations(i) for i=0,1,2,3,4");
   for (auto i = 0; i <= 4; ++i) {
      auto perms = recursivePermutations(i);
      cout << "Permutations of " << i << " elements.\n";
      for (const auto &p : perms)
         printVector(p);
   }

   banner("grayCode(5);");
   grayCode(5);

   banner("stlPermutations(4)");
   stlPermutations(4);

   banner("combinations(5, 3)");
   combinations(5, 3);


   banner("permutations of o o l r c");
   string word("oolrc");
   sort(begin(word),end(word));
   do {
      cout << word << endl;
   } while (std::next_permutation(begin(word),end(word)));

   return 0;
}