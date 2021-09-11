#include <iostream>
#include <string>

using namespace std;

int main(){
    string line;
    string newline;
    size_t sindex, mbindex, meindex;
    bool multiactive = false;

    getline(cin, line);

    while(true){
        newline = line;

        sindex  = line.find("//");
        mbindex = line.find("/*");
        meindex = line.find("*/");

        //            /*
        if(mbindex != string::npos && !multiactive){
            newline =  line.substr(0, mbindex);
            multiactive = true;

            //          /*  */
            if(meindex != string::npos){
                newline += line.substr(meindex+2);
                multiactive = false;
            } 
                newline += "";            
        }
        //     */
        else if(meindex != string::npos){
            newline = line.substr(meindex+2) + "";
            multiactive = false;
        }
        //       //
        else if(sindex != string::npos){
            newline = line.substr(0, sindex) + "";
        } 
        else if(multiactive)
            newline = "";


        cout << newline;
        if (getline(cin, line))
        {
            if(!multiactive)
                cout << "\n";
        }else {
            break;
        }     
    }

    return 0;
}