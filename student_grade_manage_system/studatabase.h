#ifndef STUDATABASE_H
#define STUDATABASE_H

#include "dulinklist.h"
#include <string>

struct Subject {
    // 课程
    std::string name; // 课程名
    int credit; // 学分数
    int score; // 成绩
};

struct Student {
    // 学生
    std::string id; // 学号
    std::string name; // 姓名
    bool sex; // 性别，true为男性，false为女性
    int age; // 年龄
    std::string telephone; // 电话
    DuLinkList<Subject> subjects; // 课程列表
    node<Subject> *firstSubject() { return subjects.head()->next; } // 返回第一门课程的指针
};

struct Class {
    // 班级
    int id; // 班级编号
    DuLinkList<Student> students; // 学生列表
    node<Student> *firstStudent() { return students.head()->next; } // 返回第一名学生的指针
};

struct Major {
    // 专业
    std::string name; // 专业名称
    DuLinkList<Class> classes; // 班级列表
    node<Class> *firstClass() { return classes.head()->next; } // 返回第一个班级的指针
};

struct Grade {
    // 年级
    int year; // 年级编号
    DuLinkList<Major> majors; // 专业列表
    node<Major> *firstMajor() { return majors.head()->next; } // 返回第一个专业的指针
};

class Institute {
    // 学院
public:
    typedef node<Grade> *grade_pos;
    typedef node<Major> *major_pos;
    typedef node<Class> *class_pos;
    typedef node<Student> *stu_pos;
    typedef node<Subject> *sub_pos;

    std::string name() { return na; } // 返回学院名称

    // 通用查找
    void *findPos(int year,
                  const std::string &majorName = "",
                  int classId = 0,
                  const std::string &stuId = "",
                  const std::string &subName = "");

    // 通用删除
    void delItem(int year,
                 const std::string &majorName = "",
                 int classId = 0,
                 const std::string &stuId = "",
                 const std::string &subName = "");

    // 清空
    void clear(int year = 0,
               const std::string &majorName = "",
               int classId = 0,
               const std::string &stuId = "");

    // 插入
    void insert(Grade &gradeStruct);
    void insert(int year, Major &majorStruct);
    void insert(int year, const std::string &majorName, Class &classStruct);
    void insert(int year,
                const std::string &majorName,
                int classId,
                Student &stuStruct);
    void insert(int year,
                const std::string &majorName,
                int classId,
                const std::string &stuId,
                Subject &subStruct);

    // 返回第一个年级的指针
    grade_pos firstGrade() { return grades.head()->next; }

protected:
    // 查找
    grade_pos find(int year);
    major_pos find(grade_pos pg, const std::string &name);
    class_pos find(major_pos pm, int id);
    stu_pos find(class_pos pc, const std::string &id);
    sub_pos find(stu_pos ps, const std::string &name);

    // 删除
    void del(int year);
    void del(grade_pos pg, const std::string &name);
    void del(major_pos pm, int id);
    void del(class_pos pc, const std::string &id);
    void del(stu_pos ps, const std::string &name);

    std::string na; // 学院名称
    DuLinkList<Grade> grades; // 年级列表
};

#endif // STUDATABASE_H
