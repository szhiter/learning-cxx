#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    constexpr int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // 这行代码试图创建一个 constexpr 对象 FIB，这意味着 FIB 必须是一个编译时常量
    // 为了让这个对象成为编译时常量，Fibonacci 结构体的所有成员和构造函数都必须是 constexpr
    constexpr Fibonacci FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
