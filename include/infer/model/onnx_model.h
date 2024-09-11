#ifndef YOLO_INFER_ONNX_MODEL_H
#define YOLO_INFER_ONNX_MODEL_H

#include <vector>
#include <string>
#include <onnxruntime_cxx_api.h>
#include "infer/core/tensor.h"
#include "infer/core/shape.h"

namespace infer{
    using ONNXNodeInfo = struct _ONNXNodeInfo{
        size_t count;
        std::vector<infer::Shape> shapes;
        std::vector<std::string> names;

        [[nodiscard]] std::string to_string() const;
    };

    class ONNXModel{
    private:
        static Ort::Env _env;

        std::wstring _filepath;
        Ort::SessionOptions _options{};
        Ort::Session _session{nullptr};
        Ort::AllocatorWithDefaultOptions _allocator;
        ONNXNodeInfo _input_info;
        ONNXNodeInfo _output_info;

        void _init();
    public:
        explicit ONNXModel(const std::string& filepath);
        explicit ONNXModel(const std::wstring& filepath);

        [[nodiscard]] const ONNXNodeInfo& get_input_node_info() const noexcept;
        [[nodiscard]] const ONNXNodeInfo& get_output_node_info() const noexcept;
    };
}

#endif //YOLO_INFER_ONNX_MODEL_H
