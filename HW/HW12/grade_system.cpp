#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
using namespace std;


class Grade{
    int id;
    char name[32];
    char sex[3];
    double grade;
public:
    double get_grade(){
        return grade;
    }
    void change_grade(double a){
        grade = a;
    }
    string get_sex(){
        return sex;
    }
    friend ostream &operator<<(ostream &output, const Grade &G){
        output<<G.id<<" "<<G.name<<" "<<G.sex<<" "<<G.grade;
        return output;
    }
    friend istream &operator>>(istream &input, Grade &G){
        input>>G.id>>G.name>>G.sex>>G.grade;
        return input;
    }
};

int main(){
    //1
    ofstream out_file("./a.txt",ios::out);
    if(out_file.fail()) exit(-1);
    Grade g;
    cout<<"输入成绩，每条以两个空格分隔："<<endl;
    while(true){
        cin>>g;
        out_file<<g;
        if(cin.get() == '\n') break;
        else out_file<<endl;
    }
    out_file.close();
    //2
    ifstream in_file("./a.txt",ios::in);
    if(in_file.fail()) exit(-1);
    vector<Grade> grades;
    cout<<"Load Grades from a.txt"<<endl;
    while(!in_file.eof()){
        in_file>>g;
        grades.push_back(g);
    }
    in_file.close();
    //3
    sort(grades.begin(), grades.end(), [](Grade &g1, Grade &g2){return g1.get_grade()>g2.get_grade();});
    cout<<"Write to b.txt"<<endl;
    ofstream b("./b.txt", ios::out);
    if(b.fail()) exit(-1);
    for_each(grades.begin(), grades.size()>3?grades.begin()+3:grades.end(), [&](Grade &g){b<<g<<endl;});
    b.close();
    //4
    vector<Grade> male, female;
    copy_if(grades.begin(), grades.end(), back_inserter(male), [](Grade &g){return g.get_sex()=="男";});
    copy_if(grades.begin(), grades.end(), back_inserter(female), [](Grade &g){return g.get_sex()=="女";});
    double mean_male = (double)accumulate(male.begin(), male.end(), 0, [](double partial, Grade &g)->double{ return partial+g.get_grade();})/male.size();
    double mean_female = (double)accumulate(female.begin(), female.end(), 0, [](double partial, Grade &g)->double{ return partial+g.get_grade();})/female.size();
    cout<<"Write to c.txt"<<endl;
    ofstream c("./c.txt", ios::out);
    if(c.fail()) exit(-1);
    for_each(male.begin(), male.end(), [&](Grade &g){if(g.get_grade()<mean_male) c<<g<<endl;});
    for_each(female.begin(), female.end(), [&](Grade &g){if(g.get_grade()<mean_female) c<<g<<endl;});
    c.close();
    //5
    vector<Grade> makeup;
    cout<<"输入补考成绩，每条以两个空格分隔："<<endl;
    while(true){
        cin>>g;
        makeup.push_back(g);
        if(cin.get() == '\n') break;
    }
    for_each(makeup.begin(), makeup.end(), [](Grade &g){g.change_grade(g.get_grade()*0.9);});
    //6
    cout<<"Write to a.txt"<<endl;
    ofstream a("./a.txt",ios::app);
    if(a.fail()) exit(-1);
    for_each(makeup.begin(), makeup.end(), [&](Grade &g){a<<endl<<g;});
    a.close();
    return 0;
}