import meshio

# 读取 .msh 文件
mesh = meshio.read("beam.msh")

# 获取网格顶点坐标
points = mesh.points

# 输出顶点坐标
for i, point in enumerate(points):
    print(f"Vertex {i}: {point}")
