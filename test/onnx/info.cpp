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
        cout << model.get_input_node_info().to_string() << endl;
        cout << model.get_output_node_info().to_string() << endl;
    }catch(const Ort::Exception& error){
        cerr << error.what() <<  endl;
        return -2;
    }
    return 0;
}
