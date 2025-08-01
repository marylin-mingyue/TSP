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
path = [16, 15, 13, 12, 11, 9, 8, 10, 4, 5, 6, 14, 7, 3, 1, 2,16]
for i in range (len(path)-1):

    start=df[df['ID']==path[i]].iloc[0]#筛选结果的第一行
    end=df[df['ID']==path[i+1]].iloc[0]
    if not start.empty and not end.empty:
        plt.arrow(start['x'],start['y'],end['x']-start['x']-0.2,end['y']-start['y']-0.2,color='b',head_width=0.3,length_includes_head=True)
plt.title ('TSP Visualization')
plt.grid(True)


desktop_path = os.path.join(os.path.expanduser('~'), 'Desktop')
save_path = os.path.join(desktop_path, 'tsp_solution.svg')
plt.savefig(save_path, format='svg', dpi=150)
plt.show()