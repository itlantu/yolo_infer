#include "core_test.h"

using namespace std;

void tensor_type_test(){
    infer::TensorType<float> t1;
    infer::TensorType<int8_t> t2;
    cout << "t1: " << t1.to_string() << endl;
    cout << "t2: " << t2.to_string() << endl;

    if((t1 == t2) || !(t1 != t2)){
        cout << "tensor_type_test: equal error" << endl;
        throw runtime_error("tensor_type_test: equal error");
    }
}