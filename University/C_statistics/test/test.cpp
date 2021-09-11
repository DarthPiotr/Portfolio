#include <iostream>

using namespace std;

class vect{
public:
    int x, y;
    void set_z(int newz){ z = newz; }
private:
    int z;
};

void odejmij(int &a){
    a -= 10;
}

int main(){
    int a = 10;

    vect v1;
    v1.x = 10;
    v1.y = 20;
    v1.set_z(30);

    vect* v2;
    (*v2).x = 10;
    v2->y = 20;

    odejmij(a);

    cout << a << "\n";

    //int *tab = (int*)malloc(sizeof(int) * a);
    //free(tab);
    int *tab = new int[a];

    delete tab;


    int tab2[20];

    for(int &elem : tab2){
        elem = 15;
    }

    return 0;
}