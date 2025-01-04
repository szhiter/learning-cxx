#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        /*
            所以为什么原始代码中ref的改变会影响vec[30]？
            这说明vec[30]返回的实际上是一个引用类型。这种情况通常发生在：
            vec很可能是一个vector<bool>类型
            vector<bool>是标准库的一个特殊实现，它的operator[]返回的不是bool&，而是一个特殊的代理对象（proxy object）：vector<bool>::reference
            这是因为：
            vector<bool>为了节省内存，在内部将8个bool值打包存储在一个字节中
            因此不能直接返回bool的引用（因为无法引用到比特位）
            所以返回一个特殊的代理对象，这个对象会自动处理对单个位的读写操作
            这就是为什么即使auto ref = vec[30]看起来像是在进行值复制，但ref的改变仍然会影响到vec[30]的值 - 因为ref实际上得到的是这个特殊的代理对象。
            这也是为什么vector<bool>在C++中被认为是一个有争议的设计 - 它的行为与其他vector类型不一致，可能导致一些反直觉的结果。
        */
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
