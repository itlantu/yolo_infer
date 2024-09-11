from pathlib import Path
import numpy as np
import onnx

path = Path(__file__).parent.absolute()
save_path = str(path / "test_model.onnx")

def make_tensor(name, weights):
    return onnx.helper.make_tensor(
        name=name,
        data_type=onnx.TensorProto.FLOAT,
        dims=weights.shape,
        vals=weights.flatten().tolist(),
    )

def create_test_onnx(input_name: str = "test_input", output_name: str = "test_output"):
    # 包含两个全连接层
    # 第一层输入形状为 (batch_size, 10, 10, 1)，输出形状为 (batch_size, 20)
    # 第二层输入形状为 (batch_size, 20)，输出形状为 (batch_size, 1)
    model = onnx.ModelProto()
    model.producer_name = "onnx_test_model"

    # 添加输入层
    input_tensor = onnx.helper.make_tensor_value_info(
        input_name, onnx.TensorProto.FLOAT, [None, 10, 10, 1]
    )
    model.graph.input.extend([input_tensor])

    # 初始化权重和偏置
    weights1 = np.random.randn(10, 20).astype(np.float32)
    bias1 = np.random.randn(20).astype(np.float32)
    weights2 = np.random.randn(20, 1).astype(np.float32)
    bias2 = np.random.randn(1).astype(np.float32)

    # 第一个全连接层
    node_def1 = onnx.helper.make_node("MatMul", inputs=[input_name, "weights1"], outputs=["matmul1"])
    node_def1_bias = onnx.helper.make_node("Add", inputs=["matmul1", "bias1"], outputs=["add1"])

    # 第二个全连接层
    node_def2 = onnx.helper.make_node("MatMul", inputs=["add1", "weights2"], outputs=["matmul2"])
    node_def2_bias = onnx.helper.make_node("Add", inputs=["matmul2", "bias2"], outputs=[output_name])

    # 添加权重和偏置到模型
    weights_tensors = [
        make_tensor("weights1", weights1),
        make_tensor("bias1", bias1),
        make_tensor("weights2", weights2),
        make_tensor("bias2", weights2),
    ]
    model.graph.initializer.extend(weights_tensors)

    # 添加节点到图
    model.graph.node.extend([node_def1, node_def1_bias, node_def2, node_def2_bias])

    # 添加输出层
    output_tensor = onnx.helper.make_tensor_value_info(
        output_name, onnx.TensorProto.FLOAT, [None, 1]
    )
    model.graph.output.extend([output_tensor])

    # 保存ONNX模型
    onnx.save(model, save_path)


if __name__ == "__main__":
    create_test_onnx()
