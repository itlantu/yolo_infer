#ifndef YOLO_INFER_SHAPE_H
#define YOLO_INFER_SHAPE_H

#include <cstdint>
#include <array>
#include <vector>
#include <string>

namespace infer{
    class Shape{
    private:
        // 索引从0到3表示维度的顺序, 维度顺序按照NCHW排列, 其中索引0表示最外层维度(4维), 索引3表示最内层维度(1维)
        // 当某个索引的维度值为0, 则表示当前维度未使用
        int64_t _dim[4]{};
    public:
        explicit Shape();
        Shape(int n, int c, int h, int w);
        explicit Shape(const std::array<int64_t, 4>& arr);
        explicit Shape(const std::vector<int64_t>& vec);
        Shape(const Shape& shape);

        [[nodiscard]] std::string to_string() const;
        constexpr int64_t operator[](int index) const noexcept;
        [[nodiscard]] int ndim() const noexcept;
        int64_t total() const noexcept;
    };
}

#endif //YOLO_INFER_SHAPE_H
