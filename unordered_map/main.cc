#include<unordered_map>
#include<iostream>
#include<string>
#include<memory>

template<typename T>
class Parameter {
private:
    std::shared_ptr<T> ptr;
    size_t len;
    std::string name;
public:
    Parameter() : ptr(nullptr), len(0), name("") {
        std::cout << "\n默认 Parameter 构造函数" << std::endl;
    }

    Parameter(const std::string& _name) : len(10), name(_name) {
        std::cout << "\nParameter Constructor : " + _name << std::endl;
        ptr.reset(new float[10]);
        for(int i = 0; i < len; i++)
            ptr.get()[i] = i + 20;
    }

    // 拷贝构造函数
    Parameter(const Parameter& other) {
        std::cout << "\n拷贝构造函数被调用: " << other.name << std::endl;
        ptr  = other.ptr;
        len  = other.len;
        name = other.name;
    }

    // 移动构造函数
    Parameter(Parameter&& other) noexcept : ptr(std::move(other.ptr)), len(other.len), name(std::move(other.name)) {
        std::cout << "\n移动构造函数被调用: " << name << std::endl;
    }

    // 拷贝赋值运算符
    Parameter& operator=(const Parameter& other) {
        if(this != &other){
            std::cout << "\n拷贝赋值运算符被调用: " << other.name << std::endl;
            ptr  = other.ptr;
            len  = other.len;
            name = other.name;
        }
        return *this;
    }

    // 移动赋值运算符
    Parameter& operator=(Parameter&& other) noexcept {
        if(this != &other){
            std::cout << "\n移动赋值运算符被调用: " << other.name << std::endl;
            ptr  = std::move(other.ptr);
            len  = other.len;
            name = std::move(other.name);
        }
        return *this;
    }

    ~Parameter() {
        std::cout << "\nParameter 析构 " + name << std::endl;
    }

    inline void print() {
        std::cout << "\nPrint() Parameter " + name << std::endl;
        for(int i = 0; i < len; i++)
            std::cout << ptr.get()[i] << " ";
        std::cout << std::endl;
        std::cout << "ptr's use_count = " << ptr.use_count() << std::endl;
    }

    inline std::shared_ptr<T> Ptr() { return ptr; }
};

int main() {
    // std::unordered_map 要求 Parameter<float> 类型是可默认构造的。
    std::unordered_map<std::string, Parameter<float>> params;
    params["param3"];   // 只是这样就会调用默认构造函数
    // 默认 Parameter 构造函数

    std::cout << "\n+++\n";

    params["param1"] = Parameter<float>("param1");
    // 【Parameter<float>("param1")】                       Parameter Constructor : param1
    // 【params["param1"]】                                 默认 Parameter 构造函数
    // 【params["param1"] = Parameter<float>("param1")】    移动赋值运算符被调用: param1
    //                                                      Parameter 析构 param1

    std::cout << "\n+++\n";

    params.emplace("param2", Parameter<float>("param2"));
    // 【Parameter<float>("param2")】                           Parameter Constructor : param2
    // 【params.emplace("param2", Parameter<float>("param2"))】 移动构造函数被调用: param2
    //                                                          Parameter 析构

    std::cout << "\n+++\n";

    std::unordered_map<std::string, Parameter<float>> params1 = params;
    // 拷贝构造函数被调用: param2
    // 拷贝构造函数被调用: param1
    // 拷贝构造函数被调用:

    params1["param1"].print();

}
