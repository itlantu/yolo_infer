#include "infer/core/tensor.h"
#include <stdexcept>

using namespace std;

template <typename T>
const vector<string> infer::TensorType<T>::_typename = {
        "float32",
        "int8",
        "uint8",
};

template<typename T>
infer::TensorType<T>::TensorType() {
    this->_type = 255;
    if constexpr (is_same_v<T, float>)
        this->_type = 0;
    if constexpr (is_same_v<T, int8_t>)
        this->_type = 1;
    if constexpr (is_same_v<T, uint8_t>)
        this->_type = 2;
}

template<typename T>
const string &infer::TensorType<T>::to_string() const noexcept {
    static string none = "None";

    if(this->_type >= infer::TensorType<T>::_typename.size())
        return none;
    return infer::TensorType<T>::_typename[this->_type];
}


template class infer::TensorType<float>;
template class infer::TensorType<int8_t>;
template class infer::TensorType<uint8_t>;