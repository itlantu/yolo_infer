#include "onnx_test.h"
#include "infer/model/onnx_model.h"

using namespace std;

static const auto dir_path = std::filesystem::path(__FILE__).parent_path();
static const auto onnx_path = dir_path / "test_model.onnx";

int main(){
    cout << "onnx_path: " << onnx_path << endl;
    if(!filesystem::exists(onnx_path)){
        cerr << "onnx file not exists, path: " << onnx_path << endl;
        return -1;
    }

    try{
        infer::ONNXModel model(onnx_path.wstring());
        const auto& input_info = model.get_input_node_info();
        const auto& output_info = model.get_output_node_info();

        cout << input_info.to_string() << endl;
        cout << output_info.to_string() << endl;

        if(input_info.shapes[0] != infer::Shape(vector<int64_t>{1, 28})){
            cerr << "onnx/info.cpp: input shape error, shape != {1, 28}" << endl;
            return -3;
        }
        if(output_info.shapes[0] != infer::Shape(vector<int64_t>{1, 1})){
            cerr << "onnx/info.cpp: output shape error, shape != {1, 1}" << endl;
            return -4;
        }

    }catch(const Ort::Exception& error){
        cerr << error.what() <<  endl;
        return -2;
    }
    return 0;
}
