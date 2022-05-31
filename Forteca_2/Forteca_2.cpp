#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <iomanip>

using namespace std;
int current_size = 0;

struct Value {

    int x;
    int y;
    double alfa;
    double r;
};
void alfaAndR(vector <Value>& value, Value p, int n) {
    for (int i = 0; i < n; i++) {
        value[i].alfa = double(atan2(value[i].y - p.y, value[i].x - p.x));
        value[i].r = double(sqrt(((value[i].x - p.x) * (value[i].x - p.x)) + ((value[i].y - p.y) * (value[i].y - p.y))));
    }
}
bool function(Value a, Value b) {
    if (a.alfa > b.alfa) return true;
    if (a.alfa < b.alfa) return false;
    if (a.r > b.r) return true;
    if (a.r < b.r) return false;
    return false;

}
bool function_uni(Value a, Value b) {
    return a.alfa == b.alfa;
}
void sortAndClear(vector <Value>& value, int n) {
    sort(value.begin(), value.end(), function);
    value.erase(unique(value.begin(), value.end(), function_uni), value.end());
}
double det(int x1, int x2, int x3, int y1, int y2, int y3) {
    double result = (1 * x2 * y3) + (1 * x3 * y1) + (1 * x1 * y2) - (1 * x2 * y1) - (1 * x1 * y3) - (1 * x3 * y2);
    return result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N;
    cin >> N;
    vector <Value> value;
    Value P;
    Value tmp;
    int x, y;
    cin >> x >> y;
    P.y = y;
    P.x = x;
    for (int i = 0; i < N - 1; i++) {
        cin >> x >> y;
        if (y < P.y) {
            value.push_back(P);
            P.y = y;
            P.x = x;

        }
        else if (y == P.y) {
            if (x < P.x) {
                value.push_back(P);
                P.y = y;
                P.x = x;
            }
            else {
                tmp.x = x;
                tmp.y = y;
                value.push_back(tmp);

            }
        }
        else {
            tmp.x = x;
            tmp.y = y;
            value.push_back(tmp);
        }
    }
    alfaAndR(value, P, N - 1);
   
    sortAndClear(value, N - 1);

    stack<Value> stack;
    stack.push(P);
    double d;
    Value tmp_det;
    stack.push(value.back());
    value.pop_back();
    stack.push(value.back());
    value.pop_back();  
    while (!value.empty()) {
        if (stack.size() >= 2) {
            tmp_det = stack.top();
            stack.pop();
            d = det(stack.top().x, tmp_det.x, value.back().x, stack.top().y, tmp_det.y, value.back().y);
            if (d > 0) {
                stack.push(tmp_det);
                stack.push(value.back());
                value.pop_back();
            }
            
        }
        else {
            stack.push(value.back());
        }

        //value.pop_back();


    }
    Value point_1, point_2;
    double side;
    double p;
    double result = 0.00;
    while (stack.size() >= 3) {
        point_1 = stack.top();
        stack.pop();
        point_2 = stack.top();
        side = sqrt(((point_1.x - point_2.x) * (point_1.x - point_2.x)) + ((point_1.y - point_2.y) * (point_1.y - point_2.y)));      
        p = (point_1.r + point_2.r + side) / 2;      
        result += sqrt(p * (p - point_1.r) * (p - point_2.r) * (p - side));
       
    }
    cout <<fixed<<setprecision(3)<<result ;

    return 0;
}