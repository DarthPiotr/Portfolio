#include <vector>

vector <int> vec;
vector <int> size;

for(int i = 0; i <= n; ++i) {
    vec.push_back(i);
         size.push_back(1);
}

void swap(int& a, int& b) {
   int c = a;
   a = b;
   b = c;    
}

int find(int a) {
  if(a == parent[a]) {
    return a;    
  }
  parent[a] = find(parent[a])
  return parent[a];
}

void union(int a, int b) {
    a = find(a);
         b = find(b);
         if(a != b) {
             if(size[a] < size[b]) {
                         swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
         }
}