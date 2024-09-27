from graphviz import Digraph
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np

def bright_color(index):
    """Generate a bright color for the edges."""
    colors = [
        "#FF5733", "#33FF57", "#3357FF", "#FF33A0", "#A0FF33", "#33A0FF",
        "#FF8C00", "#8CFF00", "#00FF8C", "#8C00FF", "#FF00A0", "#A000FF",
        "#00A0FF", "#FF00A0", "#A0FF00", "#00FF33", "#33FF00", "#FF5733",
        "#33FF57", "#3357FF"
    ]
    return colors[index % len(colors)]

# Create the decision tree object
dot = Digraph("MinPositiveRootDecision", format="png")

# Set background color to gradient (Graphviz does not support true gradients, so use a solid color)
dot.attr(bgcolor='lightblue')  # Background color

# Style settings
dot.attr("node", style="filled", color="lightyellow", fontname="Kaiten", fontsize="16", shape="box", fontcolor="darkblue")
dot.attr("edge", fontname="Kaiten", fontsize="14")  # Set font to Kaiten for edges

# Create a list of bright colors for edges
edge_colors = [bright_color(i) for i in range(20)]

# Create nodes and edges
dot.node("start", "f(x)=ax^3+bx^2+cx+d")

# a > 0 branch
dot.node("a_pos", "a > 0")
dot.edge("start", "a_pos", label="a > 0", color=edge_colors[0], fontcolor=edge_colors[0], fontsize="14")

# a > 0 - delta branch
dot.node("delta", "delta = b^2 - 3ac")
dot.edge("a_pos", "delta", color=edge_colors[1], fontcolor=edge_colors[1], fontsize="14")

dot.node("delta_leq_0", "No Collision")
dot.edge("delta", "delta_leq_0", label="delta <= 0", color=edge_colors[2], fontcolor=edge_colors[2], fontsize="14")

# delta > 0, branch into two
#dot.node("delta_pos", "delta > 0")
#dot.edge("delta", "delta_pos", color=edge_colors[3], fontcolor=edge_colors[3], fontsize="14")

dot.node("x_calc", "Calculate x1 and x0")
dot.edge("delta", "x_calc", label="delta > 0", color=edge_colors[4], fontcolor=edge_colors[4], fontsize="14")

# Case for fx1.inf() > 0
dot.node("fx1_inf_pos", "No Collision")
dot.edge("x_calc", "fx1_inf_pos", label="fx1.inf() > 0", color=edge_colors[5], fontcolor=edge_colors[5], fontsize="14")

# Case for x1 < 0
dot.node("x1_neg", "No Collision")
dot.edge("x_calc", "x1_neg", label="x1 < 0", color=edge_colors[6], fontcolor=edge_colors[6], fontsize="14")

# Case for time.sup() < x1.inf() and eval(time).inf() > 0
dot.node("time_check", "No Collision")
dot.edge("x_calc", "time_check", label="time.sup() < x1.inf() and\neval(time).inf() > 0", color=edge_colors[7], fontcolor=edge_colors[7], fontsize="14")

# General Collision Case
dot.node("collision", "Newton Iteration")
dot.edge("x_calc", "collision", label="Other Cases", color=edge_colors[8], fontcolor=edge_colors[8], fontsize="14")

# a == 0 branch
dot.node("a_zero", "a == 0")
dot.edge("start", "a_zero", label="a == 0", color=edge_colors[9], fontcolor=edge_colors[9], fontsize="14")

# a == 0, b == 0
dot.node("b_zero", "b == 0")
dot.edge("a_zero", "b_zero", color=edge_colors[10], fontcolor=edge_colors[10], fontsize="14")

# Case for c >= 0
dot.node("c_pos", "No Collision")
dot.edge("b_zero", "c_pos", label="c >= 0", color=edge_colors[11], fontcolor=edge_colors[11], fontsize="14")

# Case for c < 0
dot.node("c_neg", "Solve Linear Equation")
dot.edge("b_zero", "c_neg", label="c < 0", color=edge_colors[12], fontcolor=edge_colors[12], fontsize="14")

# a == 0 and b != 0
dot.node("b_not_zero", "b != 0")
dot.edge("a_zero", "b_not_zero", color=edge_colors[13], fontcolor=edge_colors[13], fontsize="14")

# Case for delta < 0
dot.node("delta_neg", "No Collision")
dot.edge("b_not_zero", "delta_neg", label="delta < 0", color=edge_colors[14], fontcolor=edge_colors[14], fontsize="14")

# Case for delta >= 0, branch into two
dot.node("delta_pos_quad", "delta >= 0")
dot.edge("b_not_zero", "delta_pos_quad", color=edge_colors[15], fontcolor=edge_colors[15], fontsize="14")

dot.node("x0_x1_calc", "Calculate x0 and x1")
dot.edge("delta_pos_quad", "x0_x1_calc", color=edge_colors[16], fontcolor=edge_colors[16], fontsize="14")

# Cases for x0 and x1
dot.node("x0_pos", "Check x0")
dot.edge("x0_x1_calc", "x0_pos", label="x0.inf() > 0 and\nx0.inf() < toi.inf()", color=edge_colors[17], fontcolor=edge_colors[17], fontsize="14")

dot.node("x1_pos", "Check x1")
dot.edge("x0_x1_calc", "x1_pos", label="x1.inf() > 0 and\nx1.inf() < toi.inf()", color=edge_colors[18], fontcolor=edge_colors[18], fontsize="14")

# Case for No Collision in both x0 and x1
dot.node("no_collision_quad", "No Collision")
dot.edge("x0_x1_calc", "no_collision_quad", label="(x0.sup() < 0 or x0.inf() > toi.inf()) and\n(x1.sup() < 0 or x1.inf() > toi.inf())", color=edge_colors[19], fontcolor=edge_colors[19], fontsize="14")

# Case for Numerical Failure
dot.node("num_fail", "Numerical Failure")
dot.edge("x0_x1_calc", "num_fail", label="(x0.inf() < 0 and 0 < x0.sup())\nor (x1.inf() < 0 and 0 < x1.sup())", color=edge_colors[0], fontcolor=edge_colors[0], fontsize="14")

# a < 0 branch
dot.node("a_neg", "a < 0")
dot.edge("start", "a_neg", label="a < 0", color=edge_colors[1], fontcolor=edge_colors[1], fontsize="14")

# a < 0 - delta branch
dot.node("delta_neg2", "delta = b^2 - 3ac")
dot.edge("a_neg", "delta_neg2", color=edge_colors[2], fontcolor=edge_colors[2], fontsize="14")

dot.node("ft","ft=f(t).inf()")
dot.edge("delta_neg2", "ft", label="delta < 0", color=edge_colors[3], fontcolor=edge_colors[3], fontsize="14")

dot.node("a1","No Collision")
dot.edge("ft", "a1", label="ft > 0", color=edge_colors[3], fontcolor=edge_colors[3], fontsize="14")

dot.node("delta_lt_0", "Newton Iteration")
dot.edge("ft", "delta_lt_0", label="ft <= 0", color=edge_colors[3], fontcolor=edge_colors[3], fontsize="14")

dot.node("x0_x1_calc2", "Calculate x0 and x1")
dot.edge("delta_neg2", "x0_x1_calc2", label = "delta > 0", color=edge_colors[6], fontcolor=edge_colors[6], fontsize="14")

dot.node("temp","Temp")
dot.edge("x0_x1_calc2","temp",label="fx0>0")

dot.node("a3","No Collision")
dot.edge("temp","a3",label="t<x1")

dot.node("a4","No Collision")
dot.edge("temp","a4",label="ft>0")

dot.node("a5","Newton Iteration")
dot.edge("temp","a5",label="Other Cases")

dot.node("b1","Temp")
dot.edge("x0_x1_calc2","b1",label="else")

dot.node("b2","temp")
dot.edge("b1","b2","0<x0")

dot.node("b3","temp")
dot.edge("b2","b3","t<x0 and f(t)>0")

dot.node("b4","Newton Iteration")
dot.edge("b2","b4",label="else")

dot.node("b5","No Collision")
dot.edge("b1","b5","f(t)>0")

dot.node("b6","Newton Iteration")
dot.edge("b1","b6","Newton Iteration")


output_path = "C:\\Git Code\\HighOrderDeformation\\src\\python\\rr"
dot.render(output_path + "\\detailed_decision_tree")

print(f"Detailed flowchart saved to: {output_path}\\detailed_decision_tree.png")

I=mpimg.imread('C:\\Git Code\\HighOrderDeformation\\src\\python\\rr\\detailed_decision_tree.png')
plt.imshow(I)
plt.show()
