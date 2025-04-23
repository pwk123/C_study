#include <stdio.h>

int main() {
    const char* str = "Name: Alice, Age: 25, Height: 165.5";
    char name[20];
    int age;
    float height;

    // 关键修复点：
    // 1. 格式符 %19[^,] 匹配 name 数组大小（19字符 + \0）
    // 2. 添加缓冲区大小参数 sizeof(name)
    int parsed = sscanf_s(str, "Name: %19[^,], Age: %d, Height: %f",
        name, (unsigned)sizeof(name), &age, &height);
    /*1. ?**sscanf_s 的安全参数要求**?
sscanf_s 是 C11 标准中定义的“安全版本”输入函数（遵循 Annex K），其核心改进是 ?强制要求指定缓冲区大小，以防止缓冲区溢出。具体规则如下：

对于涉及写入缓冲区的格式符（如 %s、%[ ]、%c），?必须额外传递缓冲区大小参数。
该参数的类型需为 unsigned int（微软的 sscanf_s 实现严格遵循此类型要求）。
2. ?**sizeof(name) 的作用**?
sizeof(name) 返回字符数组 name 的 ?总字节数?（例如 char name[20]，则 sizeof(name) = 20）。
它用于告知 sscanf_s 缓冲区的实际容量，确保写入时不会越界。
3. ?**(unsigned) 强制转换的必要性**?
sizeof 运算符的返回值类型是 size_t（一种平台相关的无符号整数类型，如在 64 位系统中可能是 unsigned long long）。
微软的 sscanf_s 实现要求缓冲区大小参数为 unsigned int，而 size_t 可能与 unsigned int ?类型不兼容?（尤其在 64 位系统上，size_t 可能为 64 位，而 unsigned int 为 32 位）。
?**强制转换 (unsigned)**? 将 size_t 转换为 unsigned int，以匹配 sscanf_s 的参数类型要求。*/


    if (parsed == 3) {
        printf("Name: %s, Age: %d, Height: %.1f\n", name, age, height);
    }
    else {
        printf("解析失败！\n");
    }
    return 0;
}