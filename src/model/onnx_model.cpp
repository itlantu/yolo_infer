#include "infer/model/onnx_model.h"
#include <filesystem>

using namespace std;

Ort::Env infer::ONNXModel::_env{OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "yolo_infer"};

/*
 * ONNXNodeInfo
 * */
string infer::ONNXNodeInfo::to_string() const {
    string result;
    for(int i = 0; i < this->count; i++){
        result += std::to_string(i) + ": " + this->names[i] + ": " + this->shapes[i].to_string();
    }
    return result;
}

/*
 * ONNXModel
 * */
infer::ONNXModel::ONNXModel(const string &filepath) {
    this->_filepath = wstring(filepath.begin(), filepath.end());
    this->_init();
}

infer::ONNXModel::ONNXModel(const wstring &filepath) {
    this->_filepath = filepath;
    this->_init();
}

void infer::ONNXModel::_init() {
    const auto filepath = filesystem::absolute(filesystem::path(this->_filepath));
    if(!filesystem::exists(filepath)){
        // 文件不存在
        // todo错误处理
    }

    // 加载模型
    this->_session = Ort::Session(infer::ONNXModel::_env, filepath.wstring().c_str(), this->_options);
    // 获得输入节点信息
    this->_input_info.count = this->_session.GetInputCount();
    for(auto i = 0; i < this->_input_info.count; i++){
        const auto& shape = this->_session.GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        const auto& name = this->_session.GetInputNameAllocated(i, this->_allocator);
        this->_input_info.shapes.emplace_back(shape);
        this->_input_info.names.emplace_back(name.get());
    }
    // 获取输出节点信息
    this->_output_info.count = this->_session.GetOutputCount();
    for(auto i = 0; i < this->_input_info.count; i++){
        const auto& shape = this->_session.GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        const auto& name = this->_session.GetOutputNameAllocated(i, this->_allocator);
        this->_output_info.shapes.emplace_back(shape);
        this->_output_info.names.emplace_back(name.get());
    }
}

const infer::ONNXNodeInfo &infer::ONNXModel::get_input_node_info() const noexcept {
    return this->_input_info;
}

const infer::ONNXNodeInfo &infer::ONNXModel::get_output_node_info() const noexcept {
    return this->_output_info;
}
