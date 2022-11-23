#include <cstdio>
#include <iostream>

using namespace std;
class Person {
private:
  int id;
  string name;
  string birth;
  int phone;
  string address;

public:
  Person() {
    id = 1;
    name = "1";
    birth = "1";
    phone = 1;
    address = "1";
  }
  Person(int id, string name, string birth, int phone, string address) {
    this->id = id;
    this->name = name;
    this->birth = birth;
    this->phone = phone;
    this->address = address;
  }
  int getId() { return id; }
  string getName() { return name; }
  string getBirth() { return birth; }
  int getPhone() { return phone; }
  string getAddress() { return address; }
  ~Person() {}
  void title() {
    cout << "编号"
         << "\t"
         << "姓名"
         << "\t"
         << "出生日期"
         << "\t"
         << "电话"
         << "\t"
         << "地址"
         << "\t";
  }
  void display() {
    cout << id << "\t" << name << "\t" << birth << "\t" << phone << "\t"
         << address << "\t";
  }
};
class Worker : public Person {
private:
  string indate;

public:
  Worker() : Person(1, "1", "1", 1, "1") { indate = "1"; }
  Worker(int id, string name, string birth, int phone, string address,
         string indate)
      : Person(id, name, birth, phone, address) {
    this->indate = indate;
  }
  ~Worker() {}
  string getIndate() { return indate; }
  void title() {
    title();
    cout << "入职日期" << endl;
  }
  void display() {
    display();
    cout << indate << endl;
  }
};

class Teacher : public virtual Worker {
private:
  string zhicheng;

public:
  Teacher() : Worker(1, "1", "1", 1, "1", "1") { zhicheng = "1"; }
  Teacher(int id, string name, string birth, int phone, string address,
          string indate, string zhicheng)
      : Worker(id, name, birth, phone, address, indate) {
    this->zhicheng = zhicheng;
  }
  ~Teacher() {}
  string getZhicheng() { return zhicheng; }
  void title() {
    title();
    cout << "入职日期" << endl;
  }
  void display() {
    display();
    cout << getZhicheng() << endl;
  }
};

class Xingzheng : public virtual Worker {
private:
  string zhiwu;

public:
  ~Xingzheng() {}
  string getZhiwu() { return zhiwu; }
  Xingzheng() : Worker(1, "1", "1", 1, "1", "1") { zhiwu = "1"; }
  Xingzheng(int id, string name, string birth, int phone, string address,
            string indate, string zhiwu)
      : Worker(id, name, birth, phone, address, indate) {
    this->zhiwu = zhiwu;
  }
    void title() {
    title();
    cout << "入职日期" << endl;
  }
  void display() {
    display();
    cout << getZhiwu() << endl;
  }
};

class Teacheraxz : public Teacher, public Xingzheng {
public:
  Teacheraxz()
      : Teacher(1, "1", "1", 1, "1", "1", "1"),
        Xingzheng(1, "1", "1", 1, "1", "1", "1") {}
  Teacheraxz(int id, string name, string birth, int phone, string address,
             string indate, string zhicheng, string zhiwu)
      : Teacher(id, name, birth, phone, address, indate, zhicheng),
        Xingzheng(id, name, birth, phone, address, indate, zhiwu) {}
  ~Teacheraxz() {}
    void title() {
    title();
    cout << "入职日期" << endl;
  }
  void display() {
    display();
   
  }
};

int main() {
  Worker w1(1, "zhang", "2003.02.02", 136, "三里屯", "2020.02.02");
  w1.title();
  w1.display();
  Teacher t1(2, "wang", "1975.02.02", 137, "四里屯", "2003.02.02", "教授");
  t1.title();
  t1.display();
  Xingzheng x1(3, "li", "1980.02.02", 138, "五里屯", "2010.02.02", "书记");
  x1.title();
  x1.display();
  Teacheraxz ta1(4, "zhao", "1976.02.02", 139, "六里屯", "2011.02.02", "教授",
                 "书记");
  ta1.title();
  ta1.display();
  return 0;
}