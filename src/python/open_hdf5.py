import meshio

# 读取 .msh 文件
file_path = "beam.msh"
mesh = meshio.read(file_path)

# 1. 顶点数（点的数量）
num_vertices = len(mesh.points)
print(f"Number of vertices (points): {num_vertices}")

# 2. 单元数（包括所有类型的单元）
num_cells = sum(len(cells_block.data) for cells_block in mesh.cells)
print(f"Total number of cells (elements): {num_cells}")

# 3. 边数和面数
# 需要根据单元的类型（如线单元表示边，面单元如三角形表示面）来统计
num_edges = 0
num_faces = 0

# 统计不同单元类型
for cells_block in mesh.cells:
    cell_type = cells_block.type
    num_elements = len(cells_block.data)
    
    # 线单元（边）
    if cell_type in ["line"]:
        num_edges += num_elements
    # 面单元（如三角形或四边形）
    elif cell_type in ["triangle", "quad"]:
        num_faces += num_elements

# 输出边数和面数
print(f"Number of edges: {num_edges}")
print(f"Number of faces: {num_faces}")
