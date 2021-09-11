#include <iostream>
#include <string>

using namespace std;

int main (){
    ios_base::sync_with_stdio(0);
    int i,n,s,la,lb,c;
    string a,b,res;
    cin >> n;
    while(n--){
        cin>>a>>b;c=0;res = "";
        if(a.size()>b.size())swap(a, b);
        la=a.size();lb=b.size();
        for(s=0;s<lb-la;s++) a += "0";
        for(i=0;i<lb;i++){
            s=a[i]-'0'+b[i]-'0'+c;
            c=s/10;
            s%=10;
            res+=to_string(s); }
        res += to_string(c);
        while(res[0] == '0') res = res.substr(1, res.size()-1);
        while(res[res.size()-1] == '0') res = res.substr(0, res.size()-1);
        cout << res << "\n"; }
    return 0;
}