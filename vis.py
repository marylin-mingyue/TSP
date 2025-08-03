import pandas as pd
import matplotlib.pyplot as plt
import os
file_path ='ulysses16.tsp'
#delim_whitespace=True 代表用空格代替逗号来分隔 但现在变成了 sep='\s+'
#header表示没有列名
#skiprows 跳过前7行
df = pd.read_csv(file_path,sep='\s+',header=None,skiprows=7,names=["ID","x","y"])\
#去掉异常值
df = df.dropna()
df['ID']=df['ID'].astype(int)
x=df["x"]
y=df["y"]

plt.scatter(x,y,color='r',s=100)

plt.xlim(x.min()-1, x.max()+1)
plt.ylim(y.min() - 1, y.max() + 1)
for i,row in df.iterrows():
    plt.text(row["x"],row["y"],str(row["ID"].astype(int)),fontsize=7,ha='center',va='center',color='white')
path = [2,4,8,1,16,12,13,14,7,6,15,5,11,9,10,3,2]
for i in range (len(path)-1):

    start=df[df['ID']==path[i]].iloc[0]#筛选结果的第一行
    end=df[df['ID']==path[i+1]].iloc[0]
    dx,dy=end.x-start.x,end.y-start.y
    #这种会比较丑
    #plt.arrow(start['x'],start['y'],end['x']-start['x']-0.2,end['y']-start['y']-0.2,color='b',head_width=0.3,length_includes_head=True)
    arrow_props=dict(arrowstyle='->',color='royalblue',lw=1.5,connectionstyle="arc3,rad=0.0")
    plt.annotate("",xy=(end.x,end.y),xytext=(start.x,start.y),arrowprops=arrow_props)
    plt.scatter(start.x,start.y,s=60,c='tomato',zorder=3)
    plt.text(start.x,start.y,str(path[i]),ha='center',va='center',color='white')
start_point = df[df['ID'] == path[0]].iloc[0]
plt.scatter(start_point['x'], start_point['y'], s=350, marker='*', c='gold', edgecolors='k', label='Start/End')
plt.title ('TSP Visualization')
plt.grid(True,linestyle='--', alpha=0.3)


desktop_path = os.path.join(os.path.expanduser('~'), 'Desktop')
save_path = os.path.join(desktop_path, 'tsp_solution.svg')
plt.savefig(save_path, format='svg', dpi=150)
plt.show()