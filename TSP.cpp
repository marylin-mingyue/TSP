//这些header能够转化为.so
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <limits>
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
    double d=pow((cities[a-1].x-cities[b-1].x),2) + pow((cities[a-1].y-cities[b-1].y),2); //离散数学学中毒了
    return sqrt(d);
}

//领域界定
//交换策略
//1. 2—Opt 与 best- improve
vector<int> Opt_2_best_improve(vector<int>& con, vector<City>& cities) {
    vector<int> temp_ans;
    double mini = numeric_limits<double>::max();

    for (int i = 0; i < con.size() - 2; i++) {
        for (int j = i + 1; j < con.size() - 1; j++) {
            if (i == 0 && j == con.size() - 1) continue;

            double dis_increase = numeric_limits<double>::infinity();
            if (i == 0) {
                dis_increase = Distance(con[j], con.back(), cities) +
                               Distance(con[0], con[j + 1], cities) -
                               Distance(con[0], con.back(), cities) -
                               Distance(con[j], con[j + 1], cities);
            } else if (j == con.size() - 1) {
                dis_increase = Distance(con[j], con[i - 1], cities) +
                               Distance(con[i], con[0], cities) -
                               Distance(con[i], con[i - 1], cities) -
                               Distance(con[j], con[0], cities);
            } else {
                dis_increase = Distance(con[i - 1], con[j], cities) +
                               Distance(con[i], con[j + 1], cities) -
                               Distance(con[i], con[i - 1], cities) -
                               Distance(con[j], con[j + 1], cities);
            }

            // 计算更优解
            if (dis_increase < 0) {
                vector<int> temp = con; // 复制当前路径
                reverse(temp.begin() + i, temp.begin() + j + 1); // 反转区间
                if (dis_increase < mini) {
                    mini = dis_increase;
                    temp_ans = temp; // 更新临时答案
                }
            }
        }
    }

    // 如果没有找到更优解，返回空向量
    if (temp_ans.empty()) return {};
    return temp_ans; // 返回找到的最佳路径
}
vector <int> Opt_2_first_improve (vector <int> &con,vector<City> &cities) {

    for (int i = 0; i < con.size() - 2; i++) {
        for (int j = i + 1; j < con.size() - 1; j++) {
            if (i == 0 && j == con.size() - 1) continue;

            double dis_increase = numeric_limits<double>::infinity();
            if (i == 0) {
                dis_increase = Distance(con[j], con.back(), cities) +
                               Distance(con[0], con[j + 1], cities) -
                               Distance(con[0], con.back(), cities) -
                               Distance(con[j], con[j + 1], cities);
            } else if (j == con.size() - 1) {
                dis_increase = Distance(con[j], con[i - 1], cities) +
                               Distance(con[i], con[0], cities) -
                               Distance(con[i], con[i - 1], cities) -
                               Distance(con[j], con[0], cities);
            } else {
                dis_increase = Distance(con[i - 1], con[j], cities) +
                               Distance(con[i], con[j + 1], cities) -
                               Distance(con[i], con[i - 1], cities) -
                               Distance(con[j], con[j + 1], cities);
            }

            // 计算更优解
            if (dis_increase < 0) {
                vector<int> temp = con; // 复制当前路径
                reverse(temp.begin() + i, temp.begin() + j + 1); // 反转区间
                return temp;
            }

        }
    }
    //局部最优解
    return {};
}
vector <int> Exchange_2_best_improve (vector <int> &con,vector<City> &cities) {
    vector <int> temp_ans;
    double mini=numeric_limits<double>::max();
    for (int i=1;i<con.size()-2;i++) {
        for (int j=i+1;j<con.size()-1;j++) {
            vector <int> temp=con;
            swap (temp[i],temp[j]);
            double dis_increase=Distance (temp[i],temp[i+1],cities)+Distance(temp[i],temp[i-1],cities)+
                Distance(temp[j],temp[j+1],cities)+ Distance(temp[j],temp[j-1],cities)
            -Distance(con[i],con[i-1],cities)-Distance (con[j],con[j+1],cities)
            -Distance(con[j],con[j-1],cities)-Distance(con[i],con[i+1],cities);
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
        for (int j=i+1;j<con.size()-1;j++) {
            vector <int> temp=con;
            swap(temp[i],temp[j]);
            double dis_increase=Distance (temp[i],temp[i+1],cities)+Distance(temp[i],temp[i-1],cities)+
                Distance(temp[j],temp[j+1],cities)+ Distance(temp[j],temp[j-1],cities)
            -Distance(con[i],con[i-1],cities)-Distance (con[j],con[j+1],cities)
            -Distance(con[j],con[j-1],cities)-Distance(con[i],con[i+1],cities);
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
    for (int i=0;i<cities.size();i++) {
        con.push_back(cities[i].id);
    }
    //C++ 11 new requirement  equals to srand(time(0));
    random_device rd;
    mt19937 g (rd());
    shuffle (con.begin(),con.end(),g);
    return con;
}

//构造初始解
//插入启发式
//谁敢想底层是greedy
//参考文献reference： Implementation of Cheapest Insertion Heuristic Algorithm in Determining Shortest Delivery Route
vector<int> Constructor_insert(vector<City> &cities) {
    vector<int> path;
    vector<int> visited(cities.size()+1, 0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, cities.size());
    int start = dis(gen);
    path.push_back(start);

    visited[0]=-1;
    visited[start] = 1;


    for (int i = 0; i < cities.size(); i++) {
        double minIncrease = numeric_limits<double>::max();
        int bestCity = -1;
        int bestPosition = -1;
        for (int j = 1; j < cities.size()+1; j++) {
            if (!visited[j]) {
                for (int k = 0; k <= path.size(); k++) {


                    int city_a, city_b;
                    if (k==0) {
                        city_a=path[path.size()-1];
                        city_b=path[0];
                    }

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
        if (bestCity==-1) continue;

        if (bestPosition == path.size()) {
            path.push_back(bestCity);
        } else {
            path.insert(path.begin() + bestPosition, bestCity);
        }

        visited[bestCity] = 1;
    }
    return path;
}
void Interactive_Improvement (vector <City> &cities) {
    vector <int> tmp;
    tmp=Constructor(cities);


    vector <int> start=tmp;
    vector <int> temp=tmp;
    vector <int> p=tmp;
    int count=0;
    vector <int> path_final;
    double temp_ans=0;
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


    ans+=Distance(path_final[path_final.size()-1],path_final[0],cities);
    cout<<ans<<endl;
    cout<<"------------------------------------"<<endl;

    while (!start.empty()) {

        temp_ans=0;
        path_final=start;
        start=Opt_2_best_improve(start,cities);
        count++;


    }
    cout<< "初始选点是用了启发式插入法"<<endl;
    cout<<"这里采用的是 Opt_2 策略，使用first- improve 接收解"<<endl;
    cout<< "共进行了"<< count << "轮，找到最优解"<<endl;
    cout<<"最优路径是："<<endl;
    for (int i=0;i<path_final.size();i++) {
        cout<<path_final[i]<<" ";
    }
    cout<<endl;
    cout<<"总路程是："<<endl;
    ans=0;
    for (int i=0;i<path_final.size()-1;i++) {
        ans+=Distance(path_final[i],path_final[i+1],cities);

    }
    ans+=Distance(path_final[path_final.size()-1],path_final[0],cities);
    cout<<ans<<endl;

}


int main() {
    string file_name="ulysses16.tsp";

    vector <City> cities= ReadCities(file_name);

    //我也不知道为什么 反正处理后多出来俩0
    cities.pop_back();
    cities.pop_back();

    //for (int i=0;i<cities.size();i++) {
    //    cout<<cities[i].id<<" ";
    //}
    //cout<<endl;
    //把原点也加上会不会清楚一点

    //Interactive_Improvement(cities);
    //vector <int> con=Constructor_insert(cities);
    //for (int i=0;i<con.size();i++) {
    //    cout<<con[i]<<" ";
    //}
    Interactive_Improvement(cities);

    //vector <int> tmp=Opt_2_best_improve(con,cities);
    //for (int num:tmp) {cout<<num<<" ";}

}