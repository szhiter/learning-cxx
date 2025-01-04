#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>
static unsigned long long fibonacci(int i) {
    // 初始化缓存数组（缓存大小为96，因为要支持至少fib(90)）
    static unsigned long long cache[96] = {0, 1}; // 初始值：cache[0] = 0, cache[1] = 1
    static bool initialized = false;

    // 如果缓存没有完全计算过（即缓存尚未初始化），进行计算
    if (!initialized) {
        for (int j = 2; j <= 90; ++j) {  // 计算并填充缓存
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        initialized = true; // 标记缓存已初始化
    }

    return cache[i]; // 返回缓存中的结果
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
