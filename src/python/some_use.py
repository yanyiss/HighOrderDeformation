# from PIL import Image, ImageDraw
# import matplotlib.pyplot as plt

# # 打开图像
# image_path = "cubic_figure/29.png"  # 替换为你的图片路径
# image = Image.open(image_path)

# # 获取图像的宽度和高度
# width, height = image.size

# # 计算每个格子的宽度和高度
# grid_width = width // 4
# grid_height = height // 4

# # 创建一个绘图对象
# draw = ImageDraw.Draw(image)

# # 画出外围线框
# draw.rectangle([(3, 3), (width-1, height-1)], outline="black", width=2)

# # 画出网格线
# for i in range(1, 4):
#     # 画竖线
#     draw.line([(i * grid_width, 0), (i * grid_width, height)], fill="black", width=2)
#     # 画横线
#     draw.line([(0, i * grid_height), (width, i * grid_height)], fill="black", width=2)

# # 使用Matplotlib显示图像
# plt.imshow(image)
# plt.axis('off')  # 隐藏坐标轴
# plt.show()

# # 保存带网格线和外围线框的图像
# output_path = "cubic_figure/28.png"
# image.save(output_path)

# print(f"Image with grid and outer frame saved as {output_path}")

import numpy as np
import matplotlib.pyplot as plt

xinf=-3
xsup=10
yinf=-10
ysup=2
x = np.linspace(xinf, xsup, 400)
y = 0.29*x**3  -2.8*x**2 + 0.1254*x + 1.1
plt.plot(x, y, linewidth=1.0, label=f'f',color='black')
plt.arrow(xinf, 0, xsup-xinf, 0, head_width=0.1, head_length=0.1, fc='k', ec='k', linewidth=1)
plt.arrow(0, yinf, 0, ysup-yinf, head_width=0.1, head_length=0.4, fc='k', ec='k', linewidth=1)
plt.show()