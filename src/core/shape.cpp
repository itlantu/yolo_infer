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

infer::Shape::Shape(const infer::Shape &shape) {
    this->_dim[0] = shape[0];
    this->_dim[1] = shape[1];
    this->_dim[2] = shape[2];
    this->_dim[3] = shape[3];
}

std::string infer::Shape::to_string() const {
    return format("[{}, {}, {}, {}]", this->_dim[0], this->_dim[1], this->_dim[2], this->_dim[3]);
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
