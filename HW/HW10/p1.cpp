#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<string>
using namespace std;

enum Sex {MALE, FEMALE};
enum Major {MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY,
            ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY};

class Date{
    int year;
    int month;
    int day;
public:
    Date(){}
    Date(int y, int m, int d){
        year = y;
        month = m;
        day = d;
    }
    int get_year() { return year; }
    int get_month() { return month; }
    int get_day() { return day; }
};

class Student{
    int no;
    string name;
    Sex sex;
    Date birth_date;
    string birth_place;
    Major major; 
public:
    Student(int no1, char *name1, Sex sex1, Date birth_date1, char *birth_place1, Major major1){
        birth_place = birth_place1;
        name = name1,
        birth_date = birth_date1,
        no = no1;
        sex = sex1;
        major = major1;          
    }
    int get_no() { return no; }
    string get_name() { return name; }
    string get_birth_place() {return birth_place; }
    int get_sex() { return sex; }
    Major get_major() { return major; }
    int get_age(){ return 2021-birth_date.get_year(); }
};


int main(){
    vector<Student> students;
    students.push_back(Student(2,(char*)"zhang",FEMALE,Date(1990,10,1),(char*)"nanjing",COMPUTER));
    students.push_back(Student(5,(char*)"li",MALE,Date(1990,10,1),(char*)"beijing",PHILOSOPHY));
    students.push_back(Student(1,(char*)"wang",MALE,Date(1991,10,1),(char*)"nanjing",COMPUTER));
    students.push_back(Student(4,(char*)"qian",FEMALE,Date(1991,11,1),(char*)"shanghai",PHILOSOPHY));
    students.push_back(Student(3,(char*)"zhao",MALE,Date(1993,10,1),(char*)"nanjing",COMPUTER));
    students.push_back(Student(7,(char*)"shao",MALE,Date(1993,10,1),(char*)"nanjing",MATHEMATICS));
    students.push_back(Student(6,(char*)"hao",MALE,Date(1993,10,1),(char*)"nanjing",PHILOSOPHY));
    students.push_back(Student(8,(char*)"hong",MALE,Date(2003,10,1),(char*)"nanjing",PHILOSOPHY));
    students.push_back(Student(9,(char*)"hou",MALE,Date(2005,10,1),(char*)"nanjing",PHILOSOPHY));

    //q1
    vector<Student> q1;
    copy_if(students.begin(), students.end(), back_inserter(q1),
            [](Student &st){ return st.get_major()==COMPUTER && st.get_sex()==MALE;});
    sort(q1.begin(), q1.end(), [](Student &st1, Student &st2){ return st1.get_no()<st2.get_no();});
    cout<<"================q1================"<<endl;
    for_each(q1.begin(), q1.end(), [](Student &st){ cout<<st.get_no()<<", "<<st.get_name()<<endl;});
    
    //q2
    vector<Student> q2;
    copy_if(students.begin(), students.end(), back_inserter(q2),[](Student &st){return
        st.get_birth_place()=="nanjing" && (st.get_major()==PHILOSOPHY || st.get_major()==MATHEMATICS);});
    sort(q2.begin(), q2.end(), [](Student &st1, Student &st2){ return st1.get_no()<st2.get_no();});
    cout<<"================q2================"<<endl;
    for_each(q2.begin(), q2.end(), [](Student &st){ cout<<st.get_no()<<", "<<st.get_name()<<", "<<st.get_age()<<endl;});

    //q3
    vector<Student> q3;
    copy_if(students.begin(), students.end(), back_inserter(q3),[](Student &st){return st.get_sex()==FEMALE;});
    double mean_age_q3 = (double)accumulate(q3.begin(), q3.end(), 0, [](int partial, Student &st)->int{ return partial+st.get_age();})/q3.size();
    cout<<"================q3================"<<endl;
    cout<<mean_age_q3<<endl;

    //q4
    vector<Student> q4;
    copy_if(students.begin(), students.end(), back_inserter(q4),[](Student &st){return st.get_birth_place()=="nanjing" && st.get_major()==COMPUTER;});
    double mean_age_q4 = (double)accumulate(q4.begin(), q4.end(), 0, [](int partial, Student &st)->int{ return partial+st.get_age();})/q4.size();
    cout<<"================q4================"<<endl;
    cout<<mean_age_q4<<endl;

    //q5
    vector<Student> q5;
    copy_if(students.begin(), students.end(), back_inserter(q5),[](Student &st){return st.get_major()!=COMPUTER && st.get_age()<20;});
    double mean_age_q5 = (double)accumulate(q5.begin(), q5.end(), 0, [](int partial, Student &st)->int{ return partial+st.get_age();})/q5.size();
    cout<<"================q5================"<<endl;
    cout<<mean_age_q5<<endl;
    return 0;
}

