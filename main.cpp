#include <iostream>
#include "proto/hello.pb.h"

int main() {
    hello::Student student;
    student.set_age(12);
    student.set_name("markus");
    student.set_sex("boy");
    student.set_id("1234567");
    std::string res{};
    bool tag{student.SerializeToString(&res)};
    if (!tag) {
        std::cout << "student object serialize to string error!";
        return -1;
    }
    hello::Student student_clone{};
    student_clone.ParseFromArray(res.data(), res.size());
    std::cout << std::boolalpha << "age  is equal:" << (student_clone.age() == student.age()) << std::endl;
    std::cout << std::boolalpha << "name is equal:" << (student_clone.name() == student.name()) << std::endl;
    std::cout << std::boolalpha << "sex  is equal:" << (student_clone.sex() == student.sex()) << std::endl;
    std::cout << std::boolalpha << "id   is equal:" << (student_clone.id() == student.id()) << std::endl;
    return 0;
}