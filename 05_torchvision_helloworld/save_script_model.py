import sys

if len(sys.argv) != 2:
    print(f"Wrong number of arguments: {len(sys.argv)}")
    exit(1)

import torch
import torchvision

model = torchvision.models.resnet18()
model.eval()

traced_model = torch.jit.script(model)
traced_model.save(sys.argv[1])  # "../models/resnet18.pt"
