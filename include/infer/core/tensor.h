#ifndef YOLO_INFER_TENSOR_H
#define YOLO_INFER_TENSOR_H

#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>
#include "infer/core/shape.h"

namespace infer{
    template<typename T>
    class TensorType{
    private:
        static const std::vector<std::string> _typename;

        static_assert(
                std::is_same_v<T, float> || std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>,
                "unsupported type");
    public:
        int _type = 255;
        TensorType();
        [[nodiscard]] const std::string& to_string() const noexcept;

        template<typename Ty>
        bool operator==(const TensorType<Ty>& tt) const noexcept { return this->_type == tt._type;};
        template<typename Ty>
        bool operator!=(const TensorType<Ty>& tt) const noexcept { return this->_type != tt._type;};

        static const TensorType<float> float32;
        static const TensorType<int8_t> int8;
        static const TensorType<uint8_t> uint8;
    };
}

namespace infer{
    template<typename T>
    class Tensor{
    private:
        std::vector<T> _data;
        infer::Shape _shape;
    public:
        Tensor(const Shape& shape);
    };
}

#endif //YOLO_INFER_TENSOR_H
