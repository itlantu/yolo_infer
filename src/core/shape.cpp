#include "infer/core/shape.h"
#include <format>

using namespace std;

infer::Shape::Shape() {
    this->_dim[0] = 0;
    this->_dim[1] = 0;
    this->_dim[2] = 0;
    this->_dim[3] = 0;
}

infer::Shape::Shape(const std::array<int64_t, 4> &arr) {
//    for(int i = 0; i < 4; i++){
//        this->_dim[i] = arr[i];
//    }
    this->_dim[0] = arr[0];
    this->_dim[1] = arr[1];
    this->_dim[2] = arr[2];
    this->_dim[3] = arr[3];
}

infer::Shape::Shape(const vector<int64_t> &vec) {
    const auto size = vec.size();
    if(size != 4 && size != 3){
        // todo 错误处理
        return ;
    }

    this->_dim[0] = 0;
    int i = 0;
    if(size == 4){
        this->_dim[0] = vec[0];
        i = 1;
    }
    this->_dim[1] = vec[i];
    this->_dim[2] = vec[i + 1];
    this->_dim[3] = vec[i + 2];
}


infer::Shape::Shape(const infer::Shape &shape) {
    this->_dim[0] = shape[0];
    this->_dim[1] = shape[1];
    this->_dim[2] = shape[2];
    this->_dim[3] = shape[3];
}

string infer::Shape::to_string() const {
    string result = "[";
    if(this->_dim[0] != 0){
        result += std::to_string(this->_dim[0]);
        result.push_back(',');
    }

    for(int i = 1; i < 4; i++){
        result += std::to_string(this->_dim[i]);
        char ch;
        if(i != 3)
            ch = ',';
        else
            ch = ']';
        result.push_back(ch);
    }
    return result;
}

constexpr int64_t infer::Shape::operator[](int index) const noexcept{
    return (index > 3 || index < 0) ? 0 : this->_dim[index];
}

infer::Shape::Shape(int n, int c, int h, int w) {
    this->_dim[0] = n;
    this->_dim[1] = c;
    this->_dim[2] = h;
    this->_dim[3] = w;
}

int infer::Shape::ndim() const noexcept{
    int res = 0;
    for(int i = 0; i < 4; i++, res++){
        if(!this->_dim[3 - i])
            break;
    }
    return res;
}

int64_t infer::Shape::total() const noexcept {
    int64_t result = 0;
    for(int i = 0, len = this->ndim(); i < len; i++){
        result += this->_dim[3 - i];
    }
    return result;
}