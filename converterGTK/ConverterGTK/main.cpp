#include <iostream>
#include "converter.h"
#include "gtk.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc <= 2)
        cout << "end converter" << endl;
    else{
        cout << argv[1] << argv[2] << endl;
        Converter().convert(argv[1],argv[2]);
        //Converter().convert("D:\\2019_12_19_08-17-14(42TS_M-EMDS_печка_отказ 154).gfm","lis");
    }
    return 0;
}
