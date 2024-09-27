import numpy as np
from PIL import Image, ImageDraw, ImageFont
import matplotlib.pyplot as plt
from io import BytesIO

# 生成包含 LaTeX 文本的图像
def create_latex_image(latex_text, font_size=30, image_size=(100, 100)):
    fig, ax = plt.subplots(figsize=(image_size[0] / 100, image_size[1] / 100), dpi=100)
    ax.text(0.5, 0.5, latex_text, fontsize=font_size, va='center', ha='center', usetex=True)
    ax.axis('off')
    
    # 保存到内存中的一个缓冲区
    buf = BytesIO()
    plt.savefig(buf, format='png', bbox_inches='tight', pad_inches=0.1, transparent=True)
    buf.seek(0)
    
    # 将图像加载到Pillow中，不关闭BytesIO对象
    img = Image.open(buf).convert("RGBA")
    
    plt.close(fig)
    return img

# 打开图像
image_path = "cubic_figure/blank.png"  # 替换为你的图片路径
image = Image.open(image_path)

# 获取图像的宽度和高度
width, height = image.size

# 计算每个格子的宽度和高度
grid_width = width // 4
grid_height = height // 4

# 创建一个绘图对象
draw = ImageDraw.Draw(image)

# 画出外围线框，将边界框稍微往里面缩进1个像素，避免绘制时越界
draw.rectangle([(3, 3), (width-1, height-1)], outline="black", width=2)

# 画出网格线
for i in range(1, 4):
    # 画竖线
    draw.line([(i * grid_width, 0), (i * grid_width, height)], fill="black", width=2)
    # 画横线
    draw.line([(0, i * grid_height), (width, i * grid_height)], fill="black", width=2)

# 在每个格子中插入LaTeX文本
latex_texts = [
    r"$a$", r"$b$", r"$c$", r"$\Delta _1$",
    r"$i-1$", r"$x_0$", r"$f(x_0)$", r"$f(x_1)$",
    r"$f(1)$", r"$x_0-1$", r"$x_1-1$", r"$a*b$",
    r"$c+d$", r"$\Delta _2$", r"$x_3$", r"$x_3-1$"
]

# 加载每个格子的 LaTeX 图片，并将其插入到图像中
for row in range(4):
    for col in range(4):
        latex_text = latex_texts[row * 4 + col]
        
        # 生成包含 LaTeX 的图像
        latex_img = create_latex_image(latex_text, font_size=50, image_size=(grid_width, grid_height))
        latex_width,latex_height=latex_img.size
        
        # 计算插入的位置
        x = col * grid_width + (grid_width - latex_width) // 2
        y = row * grid_height + (grid_height - latex_height) // 2
        
        # 将 LaTeX 图片粘贴到原图像的对应格子中
        image.paste(latex_img, (x, y), latex_img)  # latex_img 为透明图层

# 显示结果
plt.imshow(image)
plt.axis('off')  # 隐藏坐标轴
# 保存包含 LaTeX 文本的图像
output_path = "cubic_figure/28.png"
image.save(output_path)
plt.show()


print(f"Image with LaTeX texts saved as {output_path}")
