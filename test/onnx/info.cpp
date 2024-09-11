#include "onnx_test.h"
#include "infer/model/onnx_model.h"

using namespace std;

static const filesystem::path onnx_path = std::filesystem::current_path() / "test_model.onnx";

int main(){
    if(!filesystem::exists(onnx_path)){
        cerr << "onnx file not exists, path: " << onnx_path << endl;
        return -1;
    }

    infer::ONNXModel model(onnx_path.wstring());
    cout << model.get_input_node_info().to_string() << endl;
    cout << model.get_output_node_info().to_string() << endl;
    return 0;
}
