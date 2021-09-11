#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<pair<int, int>> q;
    q.push({0, 1});
    
    int a = q.top().first;
    int b = q.top().second;
    
    cout << a << " " << b << "\n";

    return 0;
}