#include <bits/stdc++.h>
using namespace std;
struct City {
    int id;
    double x;
    double y;
};

vector <City> ReadCities (const string &file_name) {
    vector <City> cities;
    ifstream file (file_name); //打开文件
    string line;
    //跳过文件头
    while (getline (file,line)) {
        if (line.find("NODE_COORD_SECTION")!=string::npos)
            break;
        //npos是字符串的表达，表示没找到
    }
    while (getline (file,line)) {
        if (line == "EOF") break;

        std::istringstream iss (line); //创建一个一行的变量iss
        City c;
        iss >> c.id >> c.x >> c.y;

        cities.push_back(c);
    }
    return cities;
}

double Distance (int a, int b, vector <City> &cities) {
    double d=pow((cities[a].x-cities[b].x),2) + pow((cities[a].y-cities[b].y),2); //离散数学学中毒了
    return sqrt(d);
}

//领域界定
//交换策略
//1. 2—Opt 与 best- improve
vector <int> Opt_2_best_improve (vector <int> &con,vector<City> &cities) {
    vector <int> temp_ans;
    double mini=numeric_limits<double>::max();
    for (int i=1;i<con.size()-2;i++) {
        for (int j=2;j<con.size()-1;j++) {
            if (i==1 && j==con.size()-2) continue;
            vector <int> temp=con;
            reverse(temp.begin()+i,temp.begin()+j);
            double dis_increase=Distance (temp[i],temp[i-1],cities)+Distance(temp[j],temp[j+1],cities)
            -Distance(con[i],con[i-1],cities)-Distance(con[j],con[j+1],cities);
            if (dis_increase<0) {
                if (dis_increase<mini) {
                    mini=dis_increase;
                    temp_ans=temp;
                }
            }
        }
    }
    //这里是我设置的终止条件，但大家可以看到这个算法找到的是局部最优解
    if (temp_ans==con) {
        con=temp_ans;
        return {};
    }
    return temp_ans;
}
vector <int> Opt_2_first_improve (vector <int> &con,vector<City> &cities) {

    for (int i=1;i<con.size()-2;i++) {
        for (int j=2;j<con.size()-1;j++) {
            if (i==1 && j==con.size()-2) continue;
            vector <int> temp=con;
            reverse(temp.begin()+i,temp.begin()+j);
            double dis_increase=Distance (temp[i],temp[i-1],cities)+Distance(temp[j],temp[j+1],cities)
            -Distance(con[i],con[i-1],cities)-Distance(con[j],con[j+1],cities);
            if (dis_increase<0) {
                return temp;
            }

        }
    }
    //这里是我设置的终止条件，但大家可以看到这个算法找到的是局部最优解
    return {};

}
vector <int> Exchange_2_best_improve (vector <int> &con,vector<City> &cities) {
    vector <int> temp_ans;
    double mini=numeric_limits<double>::max();
    for (int i=1;i<con.size()-2;i++) {
        for (int j=2;j<con.size()-1;j++) {
            if (i==1 && j==con.size()-2) continue;
            vector <int> temp=con;
            reverse(temp.begin()+i,temp.begin()+j);
            double dis_increase=Distance (temp[i],temp[j+1],cities)+Distance(temp[j],temp[i-1],cities)
            -Distance(temp[i],temp[i-1],cities)-Distance (temp[j],temp[j+1],cities);
            if (dis_increase<0) {
                if (dis_increase<mini) {
                    mini=dis_increase;
                    temp_ans=temp;
                }
            }
        }
    }
    //这里是我设置的终止条件，但大家可以看到这个算法找到的是局部最优解
    if (temp_ans==con) return {};
    return temp_ans;
}
//2-Exchange
vector <int> Exchange_2_first_improve (vector <int> &con,vector <City> &cities) {
    for (int i=1;i<con.size()-2;i++) {
        for (int j=2;j<con.size()-1;j++) {
            vector <int> temp=con;
            swap(temp[i],temp[j]);
            double dis_increase=Distance (temp[i],temp[j+1],cities)+Distance(temp[j],temp[i-1],cities)
            -Distance(temp[i],temp[i-1],cities)-Distance (temp[j],temp[j+1],cities);
            if (dis_increase<0) {
                return temp;
            }
        }
    }
    return {};

}



//构造初始解
//随机
vector <int> Constructor (vector <City> &cities) {
    vector <int> con;
    for (int i=1;i<cities.size();i++) {
        con.push_back(cities[i].id);
    }

    //C++ 11 new requirement  equals to srand(time(0));
    random_device rd;
    mt19937 g (rd());
    shuffle (con.begin(),con.end(),g);
    vector <int> tmp;
    tmp.push_back(0);
    for (int i=0;i<con.size();i++) {
        tmp.push_back(con[i]);
    }

    tmp.push_back(0);
    return tmp;
}

//构造初始解
//插入启发式
//谁敢想底层是greedy
//参考文献reference： Implementation of Cheapest Insertion Heuristic Algorithm in Determining Shortest Delivery Route
vector<int> Constructor_insert(vector<City> &cities) {
    vector<int> path;
    vector<int> visited(cities.size(), 0);
    path.push_back(0);
    visited[0] = 1;

    for (int i = 1; i < cities.size(); i++) {
        double minIncrease = numeric_limits<double>::max();
        int bestCity = -1;
        int bestPosition = -1;
        for (int j = 0; j < cities.size(); j++) {
            if (!visited[j]) {
                for (int k = 0; k <= path.size(); k++) {
                    // 跳过在起点0之前插入（保持0固定）
                    if (k == 0) continue;

                    int city_a, city_b;

                    if (k == path.size()) {
                        // 末尾插入：最后城市 -> j -> 0
                        city_a = path.back();
                        city_b = 0;
                    } else {
                        // 中间插入：path[k-1] -> j -> path[k]
                        city_a = path[k-1];
                        city_b = path[k];
                    }

                    double increase = Distance(city_a, j, cities)
                                   + Distance(j, city_b, cities)
                                   - Distance(city_a, city_b, cities);

                    if (increase < minIncrease) {
                        minIncrease = increase;
                        bestCity = j;
                        bestPosition = k;
                    }
                }
            }
        }

        if (bestPosition == path.size()) {
            path.push_back(bestCity);
        } else {
            path.insert(path.begin() + bestPosition, bestCity);
        }
        visited[bestCity] = 1;
    }
    path.push_back(0);
    return path;
}
void Interactive_Improvement (vector <City> &cities) {
    vector <int> tmp;
    tmp=Constructor_insert(cities);
    vector <int> start=tmp;
    int count=0;
    vector <int> path_final;
    while (!tmp.empty()) {
        path_final=tmp;
        tmp=Opt_2_best_improve(tmp,cities);
        count++;
    }
    cout<< "初始选点是用了启发式插入法"<<endl;
    cout<<"这里采用的是 Opt_2 策略，使用best- improve 接收解"<<endl;
    cout<< "共进行了"<< count << "轮，找到最优解"<<endl;
    cout<<"最优路径是："<<endl;
    for (int i=0;i<path_final.size();i++) {
        cout<<path_final[i]<<" ";
    }
    cout<<endl;
    cout<<"总路程是："<<endl;
    double ans=0;

    for (int i=0;i<path_final.size()-1;i++) {
        ans+=Distance(path_final[i],path_final[i+1],cities);
    }
    cout<<ans<<endl;
    cout<<"-------------------------------------------"<<endl;
    count=0;
    //cout<<"HA"<<endl;
    while (!start.empty()) {
        //cout<<"HAHA"<<endl;
        //通过调试我们可以知道这里是死循环了
        path_final=start;
        start=Opt_2_first_improve(start,cities);
        count++;
    }
    cout<<"Opt_2 first-improve"<<endl;
    cout<<"共进行了"<<count<<"轮"<<endl;
    cout<<"最优路径"<<endl;
    for (int i=0;i<path_final.size();i++) {
        cout<<path_final[i]<<" ";
    }
    cout<<endl;
    cout<<"总路程是："<<endl;
    ans=0;
    for (int i=0;i<path_final.size()-1;i++) {
        ans+=Distance(path_final[i],path_final[i+1],cities);
    }
    cout<<ans<<endl;
}


int main() {
    string file_name="ulysses16.tsp";

    vector <City> temp= ReadCities(file_name);
    //我也不知道为什么 反正处理后多出来俩0
    temp.pop_back();
    temp.pop_back();
    vector <City> cities;
    //把原点也加上会不会清楚一点
    cities.push_back({0,0,0});
    for (int i=0;i<temp.size();i++) {
        cities.push_back(temp[i]);
    }
    Interactive_Improvement(cities);
}