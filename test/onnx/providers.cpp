#include "onnx_test.h"

using namespace std;

int main(){
    const auto& providers = Ort::GetAvailableProviders();
    cout << "number of available providers: " << providers.size() << endl;
    for(const auto& provider: providers){
        cout << " " << provider << endl;
    }
}