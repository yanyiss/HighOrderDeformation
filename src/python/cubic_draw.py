import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from PIL import Image, ImageDraw
from matplotlib.patches import Rectangle
import os
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
# for Palatino and other serif fonts use:
rc('font',**{'family':'serif','serif':['Palatino']})
rc('text', usetex=True)
plt.switch_backend('agg')


# 输入数据：28组，每组4个系数
data = [
    #[ 0.0941 , 0.425 , -0.911 , -0.629 ],        #0
    [ 0.273 , 1.04 , 1.94 , 1.67 ],              #1
    [0.36, -0.5, -0.3, 1],              #2
    [ 1.91 , 8.08 , 7.92 , 1.19 ],               #3
    [ 0.459 , -0.693 , -1.87 , 2.47 ],              #4
    [ 0.448 , 0.285 , -2.58 , 1.35 ],               #5
    [ 0.881 , -1.38 , -0.58 , 0.623 ],               #6
    [ 0.664 , -2.04 , 0.598 , 0.198 ],              #7
    [ 0.576 , 0.624 , -2.04 , 0.604 ],              #8
    [ 6.29 , -6.21 , -2.07 , 0.75 ],              #9
    [0, 0, 1, 1],              #10
    [0, 0, -0.5, 1],              #11
    [0, 0, -2, 1],              #12
    [0, 1, -1, 1],                #13
    [0, 1, 2, 0.75],                 #14
    [0, 1, -3.5, 3],                 #15
    [0, 1, -2 , 0.75],                 #16
    [0, -1, 0, 2.25],              #17
    [0, -1, 0, 0.25],              #18
    [ -0.254 , 0.366 , -1.24 , 2.63 ],               #19
    [ -1.99 , 2.24 , -3.39 , 2.06 ],               #20
    [ -0.968 , 2.19 , -0.611 , 0.552 ],             #21
    [ -0.692 , -0.354 , 0.747 , 0.746 ],            #22
    [ -2.0 , -1.6 , 0.746 , 0.806 ],             #23
    [ -6.34 , 37.0 , -67.6 , 38.8 ],             #24
    [ -3.09 , 16.0 , -24.1 , 10.0 ],             #25
    [ -0.277 , 0.322 , 1.36 , 0.457 ],            #26
    [ -5.34 , -2.41 , 3.31 , 0.66 ],            #27
    [ -1.67 , 7.7 , -9.28 , 2.72 ]             #28
]
# 1,1 a  
# 1,2 e
# 1,3 f(x1)
# 1,4 x1 
# 1,5 x1-t
# 1,6 f(t)
# 2,1 i
# 2,2 i-t
# 2,3 b
# 2,4 c
# 2,5 ct+d
# 2,6 g
# 3,1 x2
# 3,2 x2-t
# 3,3 x3-t
# 3,4 f(x0)
# 3,5 x0-t
# 3,6 x0


background_colors = ['#80A0FF', '#FA983A', '#6DFA95']
backgroundbar=[
    0,0,0,0,1,
    1,1,1,1,0,
    0,2,0,0,0,
    2,0,2,0,1,
    0,0,1,0,1,
    0,1,1
]
color_sign=['#E2F42E', '#FFFFFF', '#BFBFBF', '#808080', '#404040', '#000000']
colorbar=[
    [1,5,0,0,0,0,  0,0,0,0,0,0,  0,0,0,0,0,0],      #1
    [1,2,1,0,0,0,  0,0,0,0,0,0,  0,0,0,0,0,0],      #2
    [1,2,4,5,0,0,  0,0,0,0,0,0,  0,0,0,0,0,0],      #3
    [1,2,4,0,1,1,  0,0,0,0,0,0,  0,0,0,0,0,0],      #4
    [1,2,4,0,1,4,  4,0,0,0,0,0,  0,0,0,0,0,0],      #5
    [1,2,4,0,1,4,  1,5,0,0,0,0,  0,0,0,0,0,0],      #6
    [1,2,4,0,1,4,  0,2,0,0,0,0,  0,0,0,0,0,0],      #7
    [1,2,4,2,4,0,  5,0,0,0,0,0,  0,0,0,0,0,0],      #8
    [1,2,4,2,4,0,  2,0,0,0,0,0,  0,0,0,0,0,0],      #9
    [3,0,0,0,0,0,  0,0,3,2,0,0,  0,0,0,0,0,0],      #10
    [3,0,0,0,0,0,  0,0,3,0,1,0,  0,0,0,0,0,0],      #11
    [3,0,0,0,0,0,  0,0,3,0,4,0,  0,0,0,0,0,0],      #12
    [3,0,0,0,0,0,  0,0,1,0,0,5,  0,0,0,0,0,0],      #13
    [3,0,0,0,0,0,  0,0,1,0,0,2,  5,0,0,0,0,0],      #14
    [3,0,0,0,0,0,  0,0,1,0,0,2,  0,1,0,0,0,0],      #15
    [3,0,0,0,0,0,  0,0,1,0,0,2,  2,4,0,0,0,0],      #16
    [3,0,0,0,0,0,  0,0,5,0,0,0,  0,0,1,0,0,0],      #17
    [3,0,0,0,0,0,  0,0,5,0,0,0,  0,0,4,0,0,0],      #18
    [5,5,0,0,0,1,  0,0,0,0,0,0,  0,0,0,0,0,0],      #19
    [5,5,0,0,0,4,  0,0,0,0,0,0,  0,0,0,0,0,0],      #20
    [5,2,0,0,1,0,  0,0,0,0,0,0,  0,0,0,1,0,0],      #21
    [5,2,0,0,4,1,  0,0,0,0,0,0,  0,0,0,1,0,0],      #22
    [5,2,0,0,4,4,  0,0,0,0,0,0,  0,0,0,1,0,0],      #23
    [5,2,0,0,0,1,  0,0,0,0,0,0,  0,0,0,4,0,1],      #24
    [5,2,0,0,0,4,  0,0,0,0,0,0,  0,0,0,4,0,1],      #25
    [5,2,0,0,0,1,  0,0,0,0,0,0,  0,0,0,4,5,0],      #26
    [5,2,0,0,0,4,  0,0,0,0,0,0,  0,0,0,4,5,0],      #27
    [5,2,0,0,0,0,  0,0,0,0,0,0,  0,0,0,4,2,4]       #28
]
# message=[                                                        
#     0["d<0: Subdivisio Info"]                                                           
#     1["a>0, e<0: NoCollision"],                                                           
#     2["a>0, e>=0, f(x1)>0: NoCollision"],                                                    
#     3["a>0, e>=0, f(x1)<=0, x1<0: NoCollision"],                                           
#     4["a>0, e>=0, f(x1)<=0, x1>t, f(t)>0: NoCollision"],                              
#     5["a>0, e>=0, f(x1)<=0, x1>t, f(t)<=0, i<=0: Newton"],                     
#     6["a>0, e>=0, f(x1)<=0, x1>t, f(t)<=0, i>0, i<t: Newton"],                 
#     7["a>0, e>=0, f(x1)<=0, x1>t, f(t)<=0, i>=t: Newton"],                
#     8["a>0, e>=0, f(x1)<=0, x1>=0, x1<=t, i<0: Newton"],                             
#     9["a>0, e>=0, f(x1)<=0, x1>=0, x1<=t, i>=0: Newton"],                              
#     10["a=0, b=0, c>=0: NoCollision"],                                                      
#     11["a=0, b=0, ct+d>0: NoCollision"],                                                        
#     12["a=0, b=0, ct+d<=0: LinearSolve"],                                                       
#     13["a=0, b>0, g<0: NoCollision"],        
#     14["a=0, b>0, g>=0, x2<0: NoCollision"]
#     15["a=0, b>0, g>=0, x2>t: NoCollision"]
#     16["a=0, b>0, g>=0, x2>=0, x2<=t: QuatriSolve"]
#     17["a=0, b<0, x3>t: NoCollision"],   
#     18["a=0, b<0, x3<=t: QuatricSolve"],                                                         
#     19["a<0, e<0, f(t)>0: NoCollision"],                                                       
#     20["a<0, e<0, f(t)<=0: Newton"],                                                          
#     21["a<0, e>=0, f(x0)>0, x1>t: NoCollision"],                                                    
#     22["a<0, e>=0, f(x0)>0, x1<=t, f(t)>0: NoCollision"],                                         
#     23["a<0, e>=0, f(x0)>0, x1<=t, f(t)<=0: Newton"],                                               
#     24["a<0, e>=0, f(x0)<=0, x0>t, f(t)>0： NoCollision"]                                 
#     25["a<0, e>=0, f(x0)<=0, x0>t, f(t)<=0: Newton"]                                      
#     26["a<0, e>=0, f(x0)<=0, x0<0, f(t)>0: NoCollision"],                                         
#     27["a<0, e>=0, f(x0)<=0, x0<0, f(t)<=0: Newton"]   
#     28["a<0, e>=0, f(x0)<=0, x0>=0, x0<=t: Newton"]                                          
#]

# 保存路径
output_dir = "cubic_figure"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# 设置x范围
xinf=-3
xsup=3
yinf=-2
ysup=5
x = np.linspace(xinf, xsup, 400)

def draw_colored_grid(ax, id, rows=3, cols=6, width=0.05, height=0.05):
    x_start = 0.7  # 方格左下角的x坐标 (相对于整个图的百分比)
    y_start = 0.85  # 方格左下角的y坐标
    for i in range(rows):
        for j in range(cols):
            rect = Rectangle(
                (x_start + j * width, y_start + (rows - i - 1) * height), width, height, 
                color=color_sign[colorbar[id][i*cols + j]], transform=ax.transAxes, clip_on=False
            )
            ax.add_patch(rect)

for i, (a, b, c, d) in enumerate(data):
    # 计算三次多项式值
    y = a*x**3 + b*x**2 + c*x + d
    in_range_indices = np.where((y > yinf) & (y < ysup))

    # 获取对应的 x 和 y 值
    x_in_range = x[in_range_indices]
    y_in_range = y[in_range_indices]
    # 创建图像
    plt.figure(dpi=300)
    #plt.axis('off')
    plt.rcParams['axes.facecolor']='#F6FCF4'#F6F1EC
    ax=plt.gca()
    plt.plot(x_in_range, y_in_range, linewidth=10.0, label=f'f(x) = {a}x³ + {b}x² + {c}x + {d}',color=background_colors[backgroundbar[i]])
    #draw_colored_grid(ax,i)
    
    # 标记0和1的位置
    # plt.axhline(0, color='black',linewidth=0.5)
    # plt.axvline(0, color='black',linewidth=0.5)
    
    # 添加箭头
    plt.arrow(xinf, 0, xsup-xinf, 0, head_width=0.1, head_length=0.1, fc='k', ec='k', linewidth=5)
    plt.arrow(0, yinf, 0, ysup-yinf, head_width=0.1, head_length=0.4, fc='k', ec='k', linewidth=5)

    # 标记0和1的位置
    plt.text(0.1, -0.8, '0', color='black', fontsize=30)
    plt.text(1.1, -0.8, 't', color='black', fontsize=30)
    plt.scatter([0, 1], [0, 0], color='red',s=80)  # 标记原点和1的位置
    
    
    # 根据a的值在右上角标记
    # if a > 0:
    #     plt.text(1, ysup - 0.1, "a > 0", fontsize=12, color='blue')
    # elif a < 0:
    #     plt.text(1, ysup - 0.1, "a < 0", fontsize=12, color='red')
    # else:
    #     plt.text(1, ysup - 0.1, "a = 0", fontsize=12, color='green')
    #plt.text(2,ysup-0.1,message[i][1],fontsize=15,color='blue')
    #plt.text(2,ysup-0.7,message[i][2],fontsize=12,color='red')
    
    # 不显示刻度
    plt.xticks([])
    plt.yticks([])

    frame = plt.gca()
    # y 轴不可见
    frame.axes.get_yaxis().set_visible(False)
    # x 轴不可见
    frame.axes.get_xaxis().set_visible(False)

    # 保存图像
    plt.savefig(os.path.join(output_dir, f'{i+1}.png'),bbox_inches='tight', pad_inches=0)
    plt.close()

print(f"All cubic polynomial plots have been saved to {output_dir}.")






combined_image_path = os.path.join(output_dir, "com.png")

# 获取所有生成的图片
image_files = [os.path.join(output_dir, f"{i+1}.png") for i in range(28)]
# 打开所有图片
images = [Image.open(img_file) for img_file in image_files]
cut_size=5
for i in range(0,28):
    w,h=images[i].size
    images[i]=images[i].crop((cut_size,cut_size,w-cut_size,h-cut_size)).copy()

# 假设所有图片大小相同，获取单个图片的宽高
img_width, img_height = images[0].size

# 设置合成图像的列数和行数
columns = 7
rows = (len(images) + columns - 1) // columns

# 创建新的大图片，大小为宽度4倍，高度根据行数变化
combined_image = Image.new('RGB', (columns * img_width, rows * img_height))

# 将每张图片粘贴到对应位置
for i, img in enumerate(images):
    row = i // columns
    col = i % columns
    combined_image.paste(img, (col * img_width, row * img_height))

# 创建绘图对象
draw = ImageDraw.Draw(combined_image)

# 绘制虚线的函数
def draw_dashed_line(draw_obj, start, end, dash_length=15, space_length=20, width=8):
    x1, y1 = start
    x2, y2 = end
    total_length = ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5
    num_dashes = int(total_length // (dash_length + space_length))
    for i in range(num_dashes + 1):
        start_pos = (x1 + (x2 - x1) * i * (dash_length + space_length) / total_length,
                     y1 + (y2 - y1) * i * (dash_length + space_length) / total_length)
        end_pos = (x1 + (x2 - x1) * (i * (dash_length + space_length) + dash_length) / total_length,
                   y1 + (y2 - y1) * (i * (dash_length + space_length) + dash_length) / total_length)
        draw_obj.line([start_pos, end_pos], fill="#FF6E6B", width=width)

# 绘制水平和垂直虚线
for i in range(1, 4):
    # 水平虚线
    y = i * img_height
    draw_dashed_line(draw, (0, y), (columns * img_width, y))

for j in range(1, 7):
    # 垂直虚线
    x = j * img_width
    draw_dashed_line(draw, (x, 0), (x, rows * img_height))

# 保存最终的合并图片
combined_image.save(combined_image_path)

print(f"Combined image saved as {combined_image_path}.")

# a_image = Image.open('cubic_figure/1.png')
# # 获取 a.png 的宽度和高度
# width, height = a_image.size
# # 创建一个全白色的图像，模式为 RGB
# white_image = Image.new("RGB", (width, height), color="white")
# # 保存全白色的图像
# white_image.save("cubic_figure/28.png")