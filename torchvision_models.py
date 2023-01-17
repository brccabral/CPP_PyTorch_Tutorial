import torch
import torchvision

# https://pytorch.org/tutorials/advanced/cpp_export.html#converting-to-torch-script-via-tracing
# An instance of your model.
model = torchvision.models.resnet18()

# An example input you would normally provide to your model's forward() method.
example = torch.rand(1, 3, 224, 224)

# Use torch.jit.trace to generate a torch.jit.ScriptModule via tracing.
traced_script_module = torch.jit.trace(model, example)
torch.jit.save(traced_script_module, "models/resnet18_example.pt")

# https://github.com/pytorch/vision
# pytorch-vision-0.14.1/examples/cpp/hello_world/traced_model.py
model = torchvision.models.resnet18()
model.eval()

traced_model = torch.jit.script(model)
traced_model.save("models/resnet18.pt")
