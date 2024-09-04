#include "core_test.h"
#include <exception>

using namespace std;

void shape_test(){
    infer::Shape shape1 = {1, 2, 3, 4};
    infer::Shape shape2 = array<int, 4>({5, 6, 7, 8});

    cout << shape1.to_string() << endl;
    cout << shape2.to_string() << endl;

    cout << "ndim: " << shape1.ndim();
    for(int i = 0; i < 4; i++){
        if(shape1[i] != i + 1){
            cout << "test/shape.cpp: value error, i = " << i << endl;
            throw runtime_error("test/shape.cpp: value error");
        }
    }
}