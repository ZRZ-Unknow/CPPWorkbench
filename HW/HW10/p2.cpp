#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<string>
#include<math.h>
using namespace std;


class Point{
    int x, y;
public:
    Point(int _x, int _y) : x(_x), y(_y) {}
    int get_x() { return x; }
    int get_y() { return y; }
};

bool lessthan(Point &pt1, Point &pt2){
    if(pt1.get_x() == pt2.get_x()){
        return pt1.get_y() < pt2.get_y();
    }
    return pt1.get_x() < pt2.get_x();
}

int main(){
    vector<Point> p, q;
    p.push_back(Point(-1, -1));
    p.push_back(Point(-2, -2));
    p.push_back(Point(1, 1));
    p.push_back(Point(6, 9));
    q.push_back(Point(1, 1));
    q.push_back(Point(-3, -3));
    q.push_back(Point(4, 3));
    q.push_back(Point(-2, -2));

    //q1
    sort(p.begin(), p.end(), lessthan);
    sort(q.begin(), q.end(), lessthan);
    cout<<"================q1================"<<endl;
    cout<<"p: ";
    for_each(p.begin(), p.end(), [](Point &pt){ cout<<"("<<pt.get_x()<<","<<pt.get_y()<<") ";});
    cout<<endl<<"q: ";
    for_each(q.begin(), q.end(), [](Point &pt){ cout<<"("<<pt.get_x()<<","<<pt.get_y()<<") ";});
    cout<<endl;

    //q2
    vector<Point> q2;
    copy_if(p.begin(), p.end(), back_inserter(q2), [](Point &pt){ return pt.get_x()>0 && pt.get_y()>0;});
    cout<<"================q2================"<<endl;
    sort(q2.begin(), q2.end(), lessthan);
    for_each(q2.begin(), q2.end(), [](Point &pt){ cout<<pow(pt.get_x(),2)+pow(pt.get_y(),2)<<" ";});
    cout<<endl;
    
    //q3
    vector<Point> q3;
    copy_if(p.begin(), p.end(), back_inserter(q3), [](Point &pt){ return pt.get_x()>0 && pt.get_y()>0;});
    cout<<"================q3================"<<endl;
    int dist_q3 = 0;
    for(vector<Point>::iterator curr=q3.begin(); curr!=q3.end();curr++){
        if(next(curr) != q3.end()){
            dist_q3 += pow(curr->get_x() - next(curr)->get_x(), 2) + pow(curr->get_y() - next(curr)->get_y(), 2);
        }
    }
    cout<<dist_q3<<endl;

    //q4
    vector<Point> q4;
    copy_if(p.begin(), p.end(), back_inserter(q4), [](Point &pt){ return pt.get_x()>0 && pt.get_y()>0;});
    cout<<"================q4================"<<endl;
    int q4_sum = accumulate(q4.begin(), q4.end(), 0, [](int partial, Point &pt){return partial+pow(pt.get_x(),2)+pow(pt.get_y(),2);});
    cout<<q4_sum<<endl;

    //q5
    vector<Point> q5_p, q5_q;
    copy_if(p.begin(), p.end(), back_inserter(q5_p), [](Point &pt){ return pt.get_x()<0 && pt.get_y()<0;});
    copy_if(q.begin(), q.end(), back_inserter(q5_q), [](Point &pt){ return pt.get_x()<0 && pt.get_y()<0;});
    cout<<"================q5================"<<endl;
    int cnt = 0;
    vector<Point>::iterator curr_p=q5_p.begin();
    vector<Point>::iterator curr_q=q5_q.begin();
    for(;
        curr_p!=q5_p.end() && curr_q!=q5_q.end(); curr_p++, curr_q++){
        int dist = pow(curr_p->get_x() - curr_q->get_x(), 2) + pow(curr_p->get_y() - curr_q->get_y(), 2);
        if(dist == 2) cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}