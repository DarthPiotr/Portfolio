#include <iostream>
#include <limits>

using namespace std;

float G(int);     /** declaration of G **/
  int F(int n) {
      if (n<2) return 2+n;
      else return F(n-1)*G(n-1);}
float G(int n) {  /** definition of G **/
      return 1.0 + (0.0+F(n-1)) / F(n);}
int main(){
    int cnt = 0;
    float res;
    for(int i = 0; i <= 1000;i++){
    //if (k >= 0)
       //printf("%d\n", F(k));
       res = F(i);
       if(res < 100) cnt++;
       cout << res << "\n";
    }
    cout << "RESULT: " << cnt;
    return 0; }