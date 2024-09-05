#include "infer/core/tensor.h"
#include <stdexcept>

using namespace std;

/*
 * TensorType
 * */
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

/*
 * Tensor
 * */
template<typename T>
infer::Tensor<T>::Tensor(const infer::Shape& shape){
    this->_shape = shape;
}

template<typename T>
infer::Tensor<T>::Tensor(const std::vector<T> &data, const Shape &shape) {
    if(data.size() != shape.total()){
        // todo error
    }
    this->_data = data;
    this->_shape = shape;
}

template<typename T>
bool infer::Tensor<T>::move_from(vector<T> &data, const Shape& shape) {
    if(!this->_data.empty())
        return false;
    this->_data = data;
    this->_shape = shape;
    return true;
}

template<typename T>
const infer::TensorType<T> &infer::Tensor<T>::dtype() const noexcept {
    return this->_dtype;
}

template<typename T>
const infer::Shape &infer::Tensor<T>::shape() const noexcept {
    return this->_shape;
}

template class infer::Tensor<float>;
template class infer::Tensor<uint8_t>;
template class infer::Tensor<int8_t>;