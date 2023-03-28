import torch
from SH_diff import PolygonClipper

subject_polygon = torch.tensor([[-1.,1.],[1.,1.],[1.,-1.],[-1.,-1.]])
clipping_polygon = torch.tensor([[0.,0.],[0.,2.],[2.,2.],[2.,0.]],requires_grad=True)

clip = PolygonClipper(warn_if_empty = False)
clipped_polygon = clip(subject_polygon, clipping_polygon)

print(clipped_polygon)