#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    DynFibonacci(int capacity) : cache(new size_t[capacity]{}), cached(0) {
        // 初始化前两个斐波那契数
        if (capacity > 0) {
            cache[0] = 0;// F(0)
            cached++;
        }
        if (capacity > 1) {
            cache[1] = 1;// F(1)
            cached++;
        }
    }

    // 实现复制构造器，进行深拷贝
    DynFibonacci(DynFibonacci const &other) : cache(new size_t[other.cached]), cached(other.cached) {
        // 复制缓存数据
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;// 释放动态分配的缓存
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
      // 判断缓存是否已经计算过
        if (i < cached) {
            return cache[i];// 返回缓存的值
        }

        // 计算并填充缓存
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];// 填充缓存
        }

        // 更新已缓存的最大索引
        cached = i + 1;// 因为我们需要包括 i

        return cache[i];// 返回计算出的值
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
