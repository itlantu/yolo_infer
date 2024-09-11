#include "core_test.h"

using namespace std;

void shape_test(){
    infer::Shape shape1 = {1, 2, 3, 4};
    infer::Shape shape2(array<int64_t, 4>({5, 6, 7, 8}));

    cout << shape1.to_string() << endl;
    cout << shape2.to_string() << endl;

    cout << "ndim: " << shape1.ndim() << endl;
    if(shape1.ndim() != 4){
        cout << "test/shape.cpp: ndim error, ndim != 4 = " << shape1.ndim() << endl;
        throw runtime_error("test/shape.cpp: ndim error");
    }

    for(int i = 0; i < 4; i++){
        if(shape1[i] != i + 1){
            cout << "test/shape.cpp: value error, i = " << i << endl;
            throw runtime_error("test/shape.cpp: value error");
        }
    }

    cout << "total: " << shape1.total() << endl;
    int64_t n = 1 + 2 + 3 + 4;
    if(shape1.total() != n){
        cout << "test/shape.cpp: total value error, total != " << n << " = " << shape1.total() << endl;
        throw runtime_error("test/shape.cpp: total error");
    }

    infer::Shape shape3(vector<int64_t>{1, 2, 3});
    infer::Shape shape4(vector<int64_t>{1, 2, 3, 4});

    if(shape3.ndim() != 3){
        cout << "test/shape.cpp: ndim value error, ndim != 3  = " << shape3.ndim() << endl;
        throw runtime_error("test/shape.cpp: ndim error");
    }

    cout << "shape3: " << shape3.to_string()  << " ndim:" << shape3.ndim() << endl;
    cout << "shape4: " << shape4.to_string() << " ndim:" << shape4.ndim() << endl;
}

int main(){
    shape_test();
    return 0;
}