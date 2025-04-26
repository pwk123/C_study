> remenber word: 1、format 格式 2、function 函数

1、scanf("",&a);键盘输入函数 将参数传到变量a中键盘输入的内容" "要100%满足，包括大小写等  
  
> scnaf("ARM:%d %d");则输入为ARM:num1 num2
  
2、sscanf(str,"str想要提取出来的参数",name,&num1,&num2);
```
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
  
      if (parsed == 3) {
          printf("Name: %s, Age: %d, Height: %.1f\n", name, age, height);
      } else {
          printf("解析失败！\n");
      }
      return 0;
  }
  /*************** scanf or sscnaf 的返回值 = 提取参数个数  ***********************/
  输出：Name: Alice, Age: 25, Height: 165.5
  ```
  3、sprintf(buffer,"想要规定的格式",传参);将数据转化为字符串
```
#include <stdio.h>
int main() 
{
    char buffer[50];
    int year = 2023;
    float pi = 3.14159;

    // 将数据格式化到 buffer
    int len = sprintf(buffer,sizeof(buffer), "Year: %d, Pi: %.2f", year, pi);
    
    printf("%s\n", buffer);  // 输出：Year: 2023, Pi: 3.14
    printf("写入字符数：%d\n", len);  // 输出：21（不包括 \0）
    return 0;
}
输出：Year: 2023, Pi: 3.14
写入字符数：20
```

```
#include <stdio.h>
#include <string.h>  // 添加 strlen 所需的头文件      
int main() 
{
     int num = 3;
     char buf[20];
     // 正确调用 sprintf_s，传入缓冲区大小
     sprintf_s(buf, sizeof(buf), "你好世界：%d",3);
     printf("%s", buf);
     // 返回字符串实际长度（不包括 \0）
     return (int)strlen(buf);  // 输出：12（"holle world!" 的长度）
}
输出:你好世界：3
返回值为11
```
sprintf_s在Microsoft中：int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);
      1、数组作为参数来传递时，实际上传递的是指针，也就是数组的首地址。
      2、const char *format的优势：提高代码安全性，防止意外修改；（只读）
      3、return (int)strlen(buf)​ 的潜在风险：若 sprintf_s 失败（如缓冲区太小），buf 可能未正确以 \0 结尾，导致 strlen 越界访问。
> strlen 返回 size_t，强制转换为 int 可能丢失精度（极长字符串时）。
解决方法是检查 sprintf_s 的返回值，确保写入成功：
 ```

EG、int len = sprintf_s(buf, sizeof(buf), "你好世界：%d", 3);
    if (len == -1) {
        printf("写入失败！");
        return -1;
    }
    return len;  // 直接返回 sprintf_s 的结果（已包含字符串长度）
```

## 数组
arr[5] = { 0 }
> sizeof(arr) 1、计算数组大小size*n  2、子函数内计算指针大小
