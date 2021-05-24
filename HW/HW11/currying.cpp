#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;
using namespace std::placeholders;

/* 求导数函数，对某个函数f在点x0处求得导数
* f'(x0) = (f(x0)-f(x0-d))/d
* params:
* x: x0
* d: d
* f: f
*/
double derivative(double x, double d, double (*f)(double)){
    return (f(x) - f(x-d))/d;
}

function<double (double (*)(double))> bind_derivative(double x, double d){
    return bind(derivative, x, d, _1);
}

function<function<double(double(*)(double))>(double)> bind_derivative(double x){
    return [x](double d)->function<double(double(*)(double))>{return bind(derivative,x,d,_1);};
}

int main() {
    vector<double (*)(double)> funcs = {sin, cos, tan, exp, sqrt, log, log10};
    auto d1 = bind_derivative(1, 0.000001); // 在x=1处求导数的函数d1
    auto d2 = bind_derivative(1)(0.000001); // 在x=1处求导数的函数d2
    vector<double> result1, result2;
    transform(funcs.begin(), funcs.end(), back_inserter(result1), d1);
    transform(funcs.begin(), funcs.end(), back_inserter(result2), d2);
    for(int i=0;i<result1.size();i++){
        if(result1[i]!=result2[i])
            assert(0);
    }
    return 0;
}