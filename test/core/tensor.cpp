#include "core_test.h"
#include <vector>

using namespace std;

void tensor_test(){
    vector<float> data(100, 1);
    infer::Shape shape = {1, 1, 1, 100};
    infer::Tensor<float> tensor(data, shape);

    cout << tensor.dtype().to_string() << endl;
    cout << tensor.shape().to_string() << endl;
}

int main(){
    tensor_test();
    return 0;
}