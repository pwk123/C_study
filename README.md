> remenber word: 1、format 格式 2、function 函数

1、scanf("",&a);键盘输入函数 将参数传到变量a中键盘输入的内容" "要100%满足，包括大小写等  
	**scanf_s("%s", 数组名, 缓冲区长度)**
  
>1、 scnaf("ARM:%d %d");则输入为ARM:num1 num2
> 2、想要传递的参数前的空格可以省略，但是固定格式空格不能省略
> 3、%d/%d 输入可以是··3/··6但不能是··3··/··6
> 4、输入25foo，有效值是25，foo被放入隐藏缓存区中，给下个scanf使用

  
2、**sscanf(str,"str想要提取出来的参数",name,&num1,&num2);**
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
sprintf_s在**Microsoft**中：int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);
      1、数组作为参数来传递时，实际上传递的是指针，也就是数组的首地址。
      2、const char *format的优势：提高代码安全性，防止意外修改；（只读）
      3、return (int)strlen(buf)​ 的潜在风险：若 sprintf_s 失败（如缓冲区太小），buf 可能未正确以** \0** 结尾，导致 strlen 越界访问。
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

## 数组：数组是相同类型元素的集合
arr[5] = { 0 }
> sizeof(arr) 1、计算数组大小size*n  2、子函数内计算指针大小
> 指针大小一般为8
```
#include <stdio.h>
void test(int arr[5])
{
	int sz1 = sizeof(arr) / sizeof(arr[0]);
	printf("%d ", sz1);
}
int main()
{
	int arr[5] = { 0 };
	int sz2 = sizeof(arr) / sizeof(arr[0]);
	test(arr);
	printf("%d ", sz2);
	return 0;
}
输出： 2 5
```
上述arr代表数组的**首地址**
数组名在大多数表达式中会**退化**为指向首元素的**指针**
- **核心规则**​：在大多数表达式中，​**数组名会隐式转换为指向其首元素的指针**​（例外：`sizeof(arr)` 和 `&arr`）。

>int arr[5] = {1,2,3,4,5};
>int *p = arr;  // arr退化为 &arr[0]

## printf(""),格式化输出
1、%m.nX 其中m控制变量最小输出宽度，输入小于m会自动补充空格，输入大于m不产生影响，-m在后面补充空格，m在前面补充空格
	.n指小数点后几位，常与浮点数一起使用
	%02d当输入为3时，2作为最小输出宽度，补充一位0，输出03
2、不同类型的字符要对应输出，不能混淆 reason：不同数据编码格式不同
3、\* = * 如：\\ = \ ; \" = "；%%输出%；
4、%i可以用于整数读写，包含八进制、十进制、十六进制，如果用户输入056，则默认为八进制；如果用户输入0x··则默认输入十六进制数，这种情况下容易产生错误，故%i很少使用

### ✅ `%g` 的含义：

-   `%g` 会根据**值的大小和精度**，**自动选择**使用 **普通小数格式（%f）** 或 **科学计数法（%e）** 来输出浮点数。
    
-   它会去掉多余的尾部 **零和小数点**。
    
-   常用于需要“智能格式化”浮点数的场景。
![输入图片说明](/imgs/2025-05-03/1xWysiOTj1Uptc9e.png)


字符串：
char str[] = "hello";// 实际上是：{'h', 'e', 'l', 'l', 'o', '\0'}
sizeof(str) ->输出为6

# 运算符
i%j的值的符号与i相同，因此-9%7的值为-2
`` 赋值“=”表达式``有返回值，**​返回值​**​ = 右操作数的值（转换后）
