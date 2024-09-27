import struct
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

order=3
subdivision_time=0
subdivision_mode=2
para=str(order)+"_"+str(subdivision_time)+"_"+str(subdivision_mode)
draw_time=1
# 文件路径
file_path1 = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\my_collision_time.txt"
file_path2 = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\ho_collision_time.txt"
file_path3 = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\my_collision_step.txt"
file_path4 = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\ho_collision_step.txt"
file_path5 = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\collision_step_" + str(order) + ".txt"
time_path = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\time.png"
step_path = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\" + para + "\\step.png"


batch_size = 10000  # 设定 batch_size

# 读取两组数据
def read_data(file_path, batch_size):
    with open(file_path, "rb") as f:
        data = f.read()
    return struct.unpack(f'{batch_size}d', data)

if draw_time:
    step_vals1 = read_data(file_path1, batch_size)
    step_vals2 = read_data(file_path2, batch_size)
else:
    step_vals1 = read_data(file_path3, batch_size)
    step_vals2 = read_data(file_path4, batch_size)
step_vals3 = read_data(file_path5, batch_size)


# 计算第三组数据：第二组数据除以第一组数据，然后取自然对数
# 需要注意避免除以0的情况
step_vals1 = np.array(step_vals1)
step_vals2 = np.array(step_vals2)
step_vals3 = np.array(step_vals3)

# indices = np.where(step_vals1 > step_vals2)[0]
# print(indices.size)
# with open("C:/Git Code/HighOrderDeformation/src/test_data/exp1/1_2/indice.txt", "w") as f:
#     for index in indices:
#         f.write(f"{index}\n")

# ratios = step_vals1 / step_vals2
# top_10_indices = np.argsort(ratios)[-10:]  # 找到排序后最大的10个值的索引
# top_10_values = ratios[top_10_indices]     # 获取对应的比值

# # 输出最大的10个比值及其索引
# for i in range(10):
#     print(f"Index: {top_10_indices[i]}, Value: {top_10_values[i]}")


eps = 1e-10  # 防止除以0的微小数值
if draw_time:
    #np.log(step_vals1)#
    step_vals = np.log(step_vals2 / (step_vals1 + eps))
    rate = np.sum(step_vals2)/np.sum(step_vals1)
else:
    #(step_vals2-step_vals1) / step_vals3#
    step_vals = step_vals1/step_vals3
    rate=np.sum(step_vals1)/np.sum(step_vals3)

# 绘制第三组数据的密度图
plt.figure(figsize=(8, 6))
sns.histplot(step_vals, kde=False, bins=100, stat="count", color="purple")

# 添加标签和标题
if draw_time:
    plt.xlabel('Log(Time2/Time1)')
    plt.ylabel('Count')
    plt.text(0.95, 0.95, f'Sum(Time2)/Sum(Time1) = {rate}', horizontalalignment='right', verticalalignment='top', 
         transform=plt.gca().transAxes, fontsize=12, color='black')
    plt.grid(True)
    plt.savefig(time_path)
else:
    plt.xlabel('Step1/Step3')
    plt.ylabel('Count')
    plt.text(0.95, 0.95, f'Sum(Step1)/Sum(Step3) = {rate}', horizontalalignment='right', verticalalignment='top', 
         transform=plt.gca().transAxes, fontsize=12, color='black')
    plt.grid(True)
    plt.savefig(step_path)


# rate = np.sum(step_vals2-step_vals1)/np.sum(step_vals3)
# plt.xlabel('Log((Time2-Time1)/Time3)')
# plt.ylabel('Count')
# plt.text(0.95, 0.95, f'Sum(Time3-Time2)/Sum(Time3) = {rate}', horizontalalignment='right', verticalalignment='top', 
#          transform=plt.gca().transAxes, fontsize=12, color='black')
# plt.grid(True)
# plt.savefig("C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\step_compare.png")

plt.show()
