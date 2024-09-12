from pathlib import Path
import numpy as np
import onnx
import onnxruntime as ort

path = Path(__file__).parent.absolute()
save_path = str(path / "test_model.onnx")

def make_tensor(name, weights):
    return onnx.helper.make_tensor(
        name=name,
        data_type=onnx.TensorProto.FLOAT,
        dims=weights.shape,
        vals=weights.flatten().tolist(),
    )

def create_test_onnx(input_name: str = "test_input", output_name: str = "test_output", opset_version: str = 21):
    # 包含两个全连接层
    # 第一层输入形状为 (batch_size, 1, 28)，输出形状为 (1, 12)
    # 第二层输入形状为 (1, 12)，输出形状为 (1)
    model = onnx.ModelProto()  
    model.producer_name = 'test_model'  
    opset_import = onnx.helper.make_opsetid('', opset_version)  
    model.opset_import.extend([opset_import])  
    model.ir_version = 7
    
    # 定义输入    
    input_tensor = onnx.helper.make_tensor_value_info(input_name, onnx.TensorProto.FLOAT, [1, 28])  
    model.graph.input.extend([input_tensor])  
    
    # 定义权重和偏置  
    # 第一层权重和偏置  
    weights1 = np.random.randn(12, 28).astype(np.float32)  
    bias1 = np.random.randn(12).astype(np.float32)  
    # 第二层权重和偏置  
    weights2 = np.random.randn(1, 12).astype(np.float32)  
    bias2 = np.random.randn(1).astype(np.float32)  
    
    # 添加权重和偏置到模型  
    weights_tensors = [  
        make_tensor('weights1', weights1),  
        make_tensor('bias1', bias1),  
        make_tensor('weights2', weights2),  
        make_tensor('bias2', bias2),  
    ]  
    model.graph.initializer.extend(weights_tensors)  
    
    # 添加第一层全连接  
    node_def1 = onnx.helper.make_node(  
        op_type='Gemm',
        inputs=[input_name, 'weights1', 'bias1'],  
        outputs=['fc1_output'],
        alpha=1.0, 
        beta=1.0,
        transA=0, 
        transB=1, 
        name='node_def1'
    )  
    # 添加第二层全连接  
    node_def2 = onnx.helper.make_node(  
        op_type='Gemm',  
        inputs=['fc1_output', 'weights2', 'bias2'],  
        outputs=[output_name],  
        alpha=1.0, 
        beta=1.0,
        transA=0, 
        transB=1, 
        name='node_def2'
    )  
    # 将节点添加到图中  
    model.graph.node.extend([node_def1, node_def2])  
    # 定义输出
    output_tensor = onnx.helper.make_tensor_value_info(output_name, onnx.TensorProto.FLOAT, [None, 1])  
    model.graph.output.extend([output_tensor])  

    # 保存ONNX模型
    onnx.save(model, save_path)


if __name__ == "__main__":
    create_test_onnx()
    # 验证onnx模型是否正常推理
    session = ort.InferenceSession(save_path)

    input_name = session.get_inputs()[0].name
    output_name = session.get_outputs()[0].name
    input_shape = session.get_inputs()[0].shape
    output_shape = session.get_outputs()[0].shape

    print(f'{input_name}:  {input_shape}')
    print(f'{output_name}:  {output_shape}')
    
    input_data = np.random.randn(1, 28).astype(np.float32)
    output_data = session.run([output_name], {input_name: input_data})[0]
