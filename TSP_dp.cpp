#include <bits/stdc++.h>
using namespace std;
//这里为了保险起见开了20个状态的空间，但实际针对这个问题 16 个状态就够 开到2^16就够
//还是开16个吧
const int MAXN=16;
double dp [1<<16][MAXN];
double graph [MAXN][MAXN];
int n;
struct City {
    int id;
    double x;
    double y;
};
//测试点领取
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

        std::istringstream iss (line);
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

//临接表构建
void BuildGraph (vector <City> &cities) {


    for (int i=0;i<cities.size();i++) {
        for (int j=0;j<cities.size();j++) {
            graph[i][j]=Distance (cities[i].id,cities[j].id,cities);
        }
    }
    for (int i=0;i<(1<<16);i++) {
        for (int j=0;j<n;j++) dp[i][j]=-1;
    }
}
//状态压缩dp,主算法
double f (int status,int cur) {
    double ans=numeric_limits<double>::max();;
    if (status==((1<<n)-1)) return graph[cur][0];
    if (dp[status][cur]!=-1) return dp[status][cur];

    for (int i=0;i<n;i++) {

        if ((status & (1<<i))==0) {
            ans=min(ans,graph[cur][i]+f(status|(1<<i),i));
        }
    }
    dp[status][cur]=ans;
    return ans;
}
int main() {
    vector <City> cities;
    cities = ReadCities("ulysses16.tsp");

    cities.pop_back();
    cities.pop_back();
    n=cities.size();
    cout<<n<<endl;
    //for (int i=0;i<cities.size();i++) {cout<<cities[i].id<<" ";}
    BuildGraph(cities);

    /*for (int i=0;i<cities.size();i++) {
        for (int j=0;j<cities.size();j++) {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }*/
    double mini_ans=f(1,0);
    cout<<mini_ans<<endl;
}