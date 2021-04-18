#include "studatabase.h"
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;


// 查找
Institute::grade_pos Institute::find(int year) {
    // 查找年级
    auto p = grades.head();
    for (; p->next && p->next->element.year <= year; p = p->next);
    return p;
}

Institute::major_pos Institute::find(grade_pos pg, const string &name) {
    // 在年级中查找专业
    auto p = pg->element.majors.head();
    for (; p->next && p->next->element.name <= name; p = p->next);
    return p;
}

Institute::class_pos Institute::find(major_pos pm, int id) {
    // 在专业中查找班级
    auto p = pm->element.classes.head();
    for (; p->next && p->next->element.id <= id; p = p->next);
    return p;
}

Institute::stu_pos Institute::find(class_pos pc, const string &id) {
    // 在班级中查找学生
    auto p = pc->element.students.head();
    for (; p->next && p->next->element.id <= id; p = p->next);
    return p;
}

Institute::sub_pos Institute::find(stu_pos ps, const std::string &name) {
    // 在学生中查找课程
    auto p = ps->element.subjects.head();
    for (; p->next && p->next->element.name <= name; p = p->next);
    return p;
}

void *Institute::findPos(int year,
                         const std::string &majorName,
                         int classId,
                         const std::string &stuId,
                         const std::string &subName) {
    // 通用查找方法
    auto pg = find(year);
    if (pg->element.year != year) return nullptr;
    if (!majorName.empty()) {
        auto pm = find(pg, majorName);
        if (pm->element.name != majorName) return nullptr;
        if (classId != 0) {
            auto pc = find(pm, classId);
            if (pc->element.id != classId) return nullptr;
            if (!stuId.empty()) {
                auto pStu = find(pc, stuId);
                if (pStu->element.id != stuId) return nullptr;
                if (!subName.empty()) {
                    auto pSub = find(pStu, subName);
                    if (pSub->element.name != subName) return nullptr;
                    return pSub;
                } else {
                    return pStu;
                }
            } else {
                return pc;
            }
        } else {
            return pm;
        }
    } else {
        return pg;
    }
}


// 插入
void Institute::insert(Grade &gradeStruct) {
    // 插入年级
    auto p = find(gradeStruct.year);
    grades.insert(p, gradeStruct);
}

void Institute::insert(int year, Major &majorStruct) {
    // 在年级中插入专业
    auto pg = find(year);
    if (pg->element.year != year) {
        Grade temp;
        temp.year = year;
        insert(temp);
        pg = pg->next;
    }
    auto pm = find(pg, majorStruct.name);
    pg->element.majors.insert(pm, majorStruct);
}

void Institute::insert(int year, const std::string &majorName, Class &classStruct) {
    // 在专业中插入班级
    auto pg = find(year);
    if (pg->element.year != year) {
        Grade temp;
        temp.year = year;
        insert(temp);
        pg = pg->next;
    }
    auto pm = find(pg, majorName);
    if (pm->element.name != majorName) {
        Major temp;
        temp.name = majorName;
        insert(year, temp);
        pm = pm->next;
    }
    auto pc = find(pm, classStruct.id);
    pm->element.classes.insert(pc, classStruct);
}

void Institute::insert(int year,
                       const std::string &majorName,
                       int classId,
                       Student &stuStruct) {
    // 在班级中插入学生
    auto pg = find(year);
    if (pg->element.year != year) {
        Grade temp;
        temp.year = year;
        insert(temp);
        pg = pg->next;
    }
    auto pm = find(pg, majorName);
    if (pm->element.name != majorName) {
        Major temp;
        temp.name = majorName;
        insert(year, temp);
        pm = pm->next;
    }
    auto pc = find(pm, classId);
    if (pc->element.id != classId) {
        Class temp;
        temp.id = classId;
        insert(year, majorName, temp);
        pc = pc->next;
    }
    auto ps = find(pc, stuStruct.id);
    pc->element.students.insert(ps, stuStruct);
}

void Institute::insert(int year,
                       const std::string &majorName,
                       int classId,
                       const string &stuId,
                       Subject &subStruct) {
    // 在学生中插入课程
    auto pg = find(year);
    if (pg->element.year != year) {
        Grade temp;
        temp.year = year;
        insert(temp);
        pg = pg->next;
    }
    auto pm = find(pg, majorName);
    if (pm->element.name != majorName) {
        Major temp;
        temp.name = majorName;
        insert(year, temp);
        pm = pm->next;
    }
    auto pc = find(pm, classId);
    if (pc->element.id != classId) {
        Class temp;
        temp.id = classId;
        insert(year, majorName, temp);
        pc = pc->next;
    }
    auto pStu = find(pc, stuId);
    if (pStu->element.id != stuId) {
        Student temp;
        temp.id = stuId;
        insert(year, majorName, classId, temp);
        pStu = pStu->next;
    }
    auto pSub = find(pStu, subStruct.name);
    pStu->element.subjects.insert(pSub, subStruct);
}


// 删除
void Institute::del(int year) {
    // 删除年级
    auto pg = find(year);
    if (pg->element.year != year) {
        cerr << "Del position doesn't exist!\n";
        terminate();
    }
    grades.del(pg);
}

void Institute::del(grade_pos pg, const std::string &name) {
    // 在年级中删除专业
    auto pm = find(pg, name);
    if (pm->element.name != name) {
        cerr << "Del position doesn't exist!\n";
        terminate();
    }
    pg->element.majors.del(pm);
}

void Institute::del(major_pos pm, int id) {
    // 在专业中删除班级
    auto pc = find(pm, id);
    if (pc->element.id != id) {
        cerr << "Del position doesn't exist!\n";
        terminate();
    }
    pm->element.classes.del(pc);
}

void Institute::del(class_pos pc, const std::string &id) {
    // 在班级中删除学生
    auto ps = find(pc, id);
    if (ps->element.id != id) {
        cerr << "Del position doesn't exist!\n";
        terminate();
    }
    pc->element.students.del(ps);
}

void Institute::del(stu_pos ps, const std::string &name) {
    // 在学生中删除课程
    auto pSub = find(ps, name);
    if (pSub->element.name != name) {
        cerr << "Del position doesn't exist!\n";
        terminate();
    }
    ps->element.subjects.del(pSub);
}

void Institute::delItem(int year,
                        const std::string &majorName,
                        int classId,
                        const std::string &stuId,
                        const std::string &subName) {
    // 通用删除方法
    if (!majorName.empty()) {
        auto pg = find(year);
        if (classId != 0) {
            auto pm = find(pg, majorName);
            if (!stuId.empty()) {
                auto pc = find(pm, classId);
                if (!subName.empty()) {
                    auto pStu = find(pc, stuId);
                    del(pStu, subName);
                } else {
                    del(pc, stuId);
                }
            } else {
                del(pm, classId);
            }
        } else {
            del(pg, majorName);
        }
    } else {
        del(year);
    }
}

void Institute::clear(int year,
           const std::string &majorName,
           int classId,
           const std::string &stuId) {
    // 通用清空方法
    if (year != 0) {
        auto pg = find(year);
        if (!majorName.empty()) {
            auto pm = find(pg, majorName);
            if (classId != 0) {
                auto pc = find(pm, classId);
                if (!stuId.empty()) {
                    auto pStu = find(pc, stuId);
                    pStu->element.subjects.clear();
                } else {
                    pc->element.students.clear();
                }
            } else {
                pm->element.classes.clear();
            }
        } else {
            pg->element.majors.clear();
        }
    } else {
        grades.clear();
    }
}
