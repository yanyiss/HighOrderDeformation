import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

# 初始四个点
x_points = np.array([0, 1, 2, 3], dtype=float)
y_points = np.array([1, 2, 0, 3], dtype=float)

# 创建三次插值多项式函数
def cubic_interpolation(x_vals, y_vals):
    return np.polyfit(x_vals, y_vals, 3)

# 更新曲线和多项式系数
def update_curve():
    # 重新计算三次插值多项式
    coeffs = cubic_interpolation(x_points, y_points)
    poly = np.poly1d(coeffs)

    # 绘制新的多项式曲线
    x_curve = np.linspace(min(x_points) - 1, max(x_points) + 1, 500)
    y_curve = poly(x_curve)

    line.set_xdata(x_curve)
    line.set_ydata(y_curve)

    # 更新拖动的点位置
    scatter.set_offsets(np.c_[x_points, y_points])

    # 更新右上角的系数显示
    text.set_text(f'Coeffs: a={coeffs[0]:.2f}, b={coeffs[1]:.2f}, c={coeffs[2]:.2f}, d={coeffs[3]:.2f}')

    c0="{:.3}".format(coeffs[0])
    c1="{:.3}".format(coeffs[1])
    c2="{:.3}".format(coeffs[2])
    c3="{:.3}".format(coeffs[3])
    print('[',c0,',',c1,',',c2,',',c3,']')

    # 更新图形
    fig.canvas.draw_idle()

# 拖动点时更新点的坐标
def on_click(event):
    if event.inaxes != ax:
        return
    # 获取点击位置最近的点索引
    distances = np.hypot(x_points - event.xdata, y_points - event.ydata)
    closest_point_idx = np.argmin(distances)

    # 如果按住并拖动，则更新点的坐标
    if event.button == 1 and event.inaxes == ax:
        def on_motion(event):
            if event.inaxes != ax:
                return
            x_points[closest_point_idx] = event.xdata
            y_points[closest_point_idx] = event.ydata
            update_curve()

        # 绑定鼠标移动事件来拖动点
        cid_motion = fig.canvas.mpl_connect('motion_notify_event', on_motion)

        # 当释放鼠标按钮时，停止拖动
        def on_release(event):
            fig.canvas.mpl_disconnect(cid_motion)
            fig.canvas.mpl_disconnect(cid_release)
            update_curve()

        cid_release = fig.canvas.mpl_connect('button_release_event', on_release)

# 创建图形和轴
fig, ax = plt.subplots()
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.2)

# 绘制初始的多项式曲线
coeffs = cubic_interpolation(x_points, y_points)
poly = np.poly1d(coeffs)
x_curve = np.linspace(min(x_points) - 1, max(x_points) + 1, 500)
y_curve = poly(x_curve)
line, = ax.plot(x_curve, y_curve, label='Cubic Polynomial')

# 绘制初始点
scatter = ax.scatter(x_points, y_points, color='red', s=100, label='Control Points')

# 设置轴范围
ax.set_xlim([-3, 10])
ax.set_ylim([min(y_points) - 10, max(y_points) + 2])

# 标记 x 和 y 轴，并添加箭头
ax.axhline(0, color='black',linewidth=0.5)
ax.axvline(0, color='black',linewidth=0.5)
ax.annotate('', xy=(1, 0), xytext=(0, 0), arrowprops=dict(facecolor='black', shrink=0.05))
ax.annotate('', xy=(0, 1), xytext=(0, 0), arrowprops=dict(facecolor='black', shrink=0.05))

# 显示多项式的系数在右上角
text = ax.text(0.95, 0.95, f'Coeffs: a={coeffs[0]:.2f}, b={coeffs[1]:.2f}, c={coeffs[2]:.2f}, d={coeffs[3]:.2f}',
               transform=ax.transAxes, ha='right', va='top', fontsize=10, bbox=dict(facecolor='white', alpha=0.6))

# 鼠标点击事件
fig.canvas.mpl_connect('button_press_event', on_click)

plt.legend()
plt.show()
