> remember word: 1、format 格式 2、function 函数
## 输入输出
### scanf("",&a);
键盘输入函数 将参数传到变量a中键盘输入的内容" "要100%满足，包括大小写等  
	**scanf_s("%s", 数组名, 缓冲区长度)**
  
> 1、 scanf_s("ARM:%d %d");则输入为ARM:num1 num2
> 2、想要传递的参数前的空格可以省略，但是固定格式空格不能省略
> 3、%d/%d 输入可以是··3/··6但不能是··3··/··6
> 4、输入25foo，有效值是25，foo被放入隐藏缓存区中，给下个scanf使用
> 5、输入字符串需要写缓冲区长度用sizeof
> 6、读取double类型用%lf，读取float用%f
> 7、给数组元素赋值scanf("%d", &a[i]);
```
/**sum.c 输入0截止**/
#include <stdio.h>

int main(void)
{
	int n ,sum = 0;
	printf("This program sums a series of integers.\n");
	printf("Enter integers (0 to terminate):");
	scanf("%d",&n);
	while(n != 0)
	{
		sum += n;
		scanf("%d" ,&n);
	}
	printf("The sum is: %d\n" ,sum);
	return 0;
}
```
### fgets(char *str, int n, FILE *stream);
**安全读取用户输入的推荐函数**
- ​**参数**​：
    - `str`：目标字符数组（存储输入的缓冲区）。
    - `n`：最大读取字符数（**包含结尾的 `\0`**）。
    - `stream`：输入流，通常为 `stdin`（标准输入）。
- ​**返回值**​：
    - 成功时返回 `str` 的地址。
    - 失败或到达文件末尾时返回 `NULL`

### **sscanf**
**sscanf(str,"str想要提取出来的参数",name,&num1,&num2);**
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
  ```
  输出：Name: Alice, Age: 25, Height: 165.5

### sprintf
  sprintf(buffer,"想要规定的格式",传参);将数据转化为字符串
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

```
输出：Year: 2023, Pi: 3.14
写入字符数：20

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
```
输出:你好世界：3
返回值为11

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

### 数组：数组是相同类型元素的集合
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
```
输出： 2 5

上述arr代表数组的**首地址**
数组名在大多数表达式中会**退化**为指向首元素的**指针**
- **核心规则**​：在大多数表达式中，​**数组名会隐式转换为指向其首元素的指针**​（例外：`sizeof(arr)` 和 `&arr`）。

>int arr[5] = {1,2,3,4,5};
>int *p = arr;  // arr退化为 & arr[0]

### printf(""),格式化输出
1、%m.nX 其中m控制变量最小输出宽度，输入小于m会自动补充空格，输入大于m不产生影响，-m在后面补充空格，m在前面补充空格
	.n指小数点后几位，常与浮点数一起使用
	%02d当输入为3时，2作为最小输出宽度，补充一位0，输出03
2、不同类型的字符要对应输出，不能混淆 reason：不同数据编码格式不同
3、
```
\* = * 如：\\ = \ ; \" = "；%%输出%；
```

4、%i可以用于整数读写，包含八进制、十进制、十六进制，如果用户输入056，则默认为八进制；如果用户输入0x··则默认输入十六进制数，这种情况下容易产生错误，故%i很少使用

### ✅ `%g` 的含义：

-   `%g` 会根据**值的大小和精度**，**自动选择**使用 **普通小数格式（%f）** 或 **科学计数法（%e）** 来输出浮点数。
    
-   它会去掉多余的尾部 **零和小数点**。
    
-   常用于需要“智能格式化”浮点数的场景。
![[Pasted image 20250507174153.png]]
字符串：
char str[] = "hello";// 实际上是：{'h', 'e', 'l', 'l', 'o', '\0'}
sizeof(str) ->输出为6

## 运算符
i%j的值的符号与i相同，因此-9%7的值为-2
`` 赋值“=”表达式``有返回值，**​返回值​**​ = 右操作数的值（转换后）
i += 2;  	/* same as i = i + 2; */

复合运算符和赋值运算符一样都是右结合的，i+=j+=k;等同于i+=(j+=k);

### 运算符的左结合、右结合：
>等式右侧的式子从左到右计算为左结合
>从右到左计算为右结合
>优先级
>![[Pasted image 20250507174220.png]]而且>= , <=同样为左结合


### 布尔型数值
下划线Bool {变量名}

## 循环：while、for、do while
while循环

do{
	语句;
} while();
```
#include <stdio.h>

int main(void)
{
	int input_num, output_num = 0;
	printf("Enter a nonnegative integer:");
	scanf_s("%d", &input_num);
	do
	{
		input_num /= 10;
		output_num++;
	} while (input_num != 0);
	printf("The number has %d digit{s}", output_num);
	return 0;
}
```
函数可以作为判断条件，需要返回值传出


### for(表达式1 ;表达式2 ;表达式3) 语句
> 表达式1 作为声明，如 int i = 0；
> 表达式2 作为判断，如 i < 10;
> 表达式3 作为执行，如 i++;

第一次执行表达式1->表达式2的判断->执行语句->语句执行完毕之后，执行表达式3->再回去判断表达式2
向上加/减非常适合用for
for表达式可以省略但“；”不能掉。当省略第1、3表达式之后，与while没有差别
for( ; ; )……可作为无限循环 等同于 while(1)
如果变量i不需要在该语句前进行声明。事实上,如果变量i在之前已经进行了声明,这个语句将创建一个新的i且该值仅用于循环内。
向下计数-- 一般和>、>=同时出现；向上计数++ 一般和<、<=同时出现
### 逗号运算符
- 优先级低于所有其他运算符，左结合
	for(int i = 0, j = 0; i < n; i++)
- `,` 是一个运算符，只返回最后一个表达式的值
- 问:当for (i = 5, j = i - 1; i > 0, j > 0; --i, j = i - 1)表达式2中同时出现两个判断条件，循环是否能够进行下去由谁来决定？答：**由最后一个判断来决定，即j > 0**

### continue
- **有效性测试**
```
for(;;){
	读入数据;
	if(数据的第一条测试失败)
		continue;
	if(数据的第二条测试失败)
		continue;
	·
	·
	·
	if(数据的最后一条测试失败)
		continue;
	处理数据;
}
```
跳过本次循环剩下部分，进入下一次循环

## break
```
for(; ;){
	提示用户录入命令;
	读入命令;
	switch(命令){
		case 命令1;执行操作1;break;
		case 命令2;执行操作2;break;
		···
		case 命令n-1;执行操作n-1;break;
		case 命令n;执行操作n;break;
		default:显示错误消息;break;		
	}
}
```

立即==终止整个循环==，运行循环后面的程序

---
### goto
```
goto 标签名;

...

标签名:
    语句;
```
从一个语句跳到其他语句中，但不能跨函数使用

---

### 空语句
用法一：for(表达式1;表达式2;表达式3) 空语句；
事实上程序员为了使空语句更加明显，可以用continue;代替空语句
用法二：
```
···
goto end_of_stmt;
···
end_of_stmt: ;
```
用法三：for

在C语言中main()和main(void)相比较后者更加规范
  C++中main()更加符合书写习惯

---

十六位的最大整数 0111 1111 1111 1111 （2^15 - 1 = 32767）
十六位无符号最大整数 1111 1111 1111 1111 （2^16 - 1 = 2147483647）

在64位计算机int类型为32位，为了满足实际需要衍生出short int ; long int  ——> 在编译器中写成 short a ; long a; 即可，unsigned可以进一步增加长度范围
八进制以0（零）开头，十六进制以0x开头，可以混合使用:10 + 015 +0x20
强制编译器把常量作为`长整数`(long int)来处理:15L 0377L 0x7fffL
指明无符号常量，在常量后边加上U：15U 0377U 0x7fffU
LL -> long long int
LLU -> unsigned long long int 
当数据类型发生改变，需要同时检查printf、scanf中的数据类型
数据的读写d表示十进制，o表示八进制，x表示十六进制
读写短整数需要在d、o、x前面加h，变为hd、ho、hx
读写长整数则加l
- 标准浮点类型有三种：float、double、long double 
十六进制浮点数转化为十进制浮点数：
```
指数部分 `pN` 始终以 2 为底
1.B为十六进制数值部分
0x1.Bp3 -> (1 * 16^0 + 11 * 16^-1) * 2^3 = 13.5
```

## 字符串
/*自动填充\\0字符*/
定义空字符串 char str[20] = ""; 
## 字符
- char a = “可以直接进行赋值，0-127对应ACSii码”
	'a' - 'b' == -1
- 当需要区分**有符号字符**和**无符号字符时**，定义变量要清楚的写明signed char 、unsigned char，不能笼统的全部写成char
	char类型范围：-128 - 127 ；unsigned char范围:0 - 255
	char ch = '\xdb'; 这时ch溢出转换为-37

#### **putchar()**——输出单个字符
```
/*打印结果：hello world*/
	#include <stdio.h>
	
	int main(void)
	{
		char str[] = "hello world!";
		for (int i = 0; str[i] != 0; i++) /* 0 == '\0' */
		{
			putchar(str[i]);
		}
		return 0;
	}
```
#### getchar()——读取单个字符
	参数：无
	返回值：
	- 成功时：返回读取的字符(以int形式)
	- 失败或输入结束：返回EOF（通常为-1）
```
/*输入后，原样打印*/
//方法一：逐个回显打印
#include <stdio.h>

int main() {
    printf("请输入一行文字（按回车结束）：");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        putchar(c);  // 逐个回显字符
    }
    putchar('\n');
    return 0;
}
```

```
/*输入后，原样打印*/
//方法二：一次性打印
#include <stdio.h>

int main() 
{
    char str[10] = " ";
    for (int ch ,num = 0; ch = getchar(), ch != EOF && ch != '\n' && ch != ' '; num++)
    {
        str[num] = ch;
    }
    printf("%s\n", str);

    return 0;
}
```
*返回输入数据的长度*
```
/*返回输入数据的长度*/
#include <stdio.h>

int main(void)
{
	int c,num;
	printf("Enter a message:");
	for (int i = 1; c = getchar(), c != '.'; i++)
		num = i;
		
	printf("Your message was %d character(s) long.\n", num);
	
	return 0;
}
```
**if(a == '1') return 0;为什么输入了字符1之后不能直接跳出程序**
> 答：**输入缓冲机制​****​；默认行为​**​：键盘输入的字符会先存储在系统缓冲区中，直到用户按下 ​**​回车键（`\n`）​**​，才会将整行内容一次性提交给程序。
- getchar是可以判断输入为空格
- isdigit()判断输入是否为'0'-'9'，true：返回值为1，false：返回值为0

##### 手动清空缓冲区
`getchar()` 会读取输入缓冲区中的字符（包括换行符 `\n`）
```
	int c;
	while ((c = getchar()) != '\n' && c != EOF);  // 清空输入缓冲区
```

**当输入类型为字符，scanf()输入不会跳过空字符
在包含头文件#include  <ctype.h> 的情况下:
	toupper(int ch) 函数能够将小写字符（a-z）转换为大写字符（A-Z）
	isalpha(int ch) 输入为'a-z' 或'A - Z'时，返回整数1，否则返回整数0


## 数据转换
### 隐式转换（自动转换）

编译器自动完成，通常发生在以下场景：
#### 1. ​**​算术运算中的类型提升​**​

- ​**​规则​**​：低精度类型向高精度类型提升。
- ​**​优先级顺序​**​：`char < short < int < long < float < double`
```
`int a = 10; float b = 3.14; 
float c = a + b;  // a自动转为float再相加`
```
#### 2. ​**​赋值时的类型转换​**​

- ​**​右值自动转为左值类型​**​：

```
int num = 3.14;    // 3.14被截断为int类型3 
float x = 10;       // 10自动转为float类型10.0`
```
#### 3. ​**​函数传参和返回值​**​

- 参数类型不匹配时自动转换：

```
void print_float(float x) { /* ... */ } 
int main() {     
	print_float(5); // 5自动转为float 5.0     
	return 0; 
}
```
### 显式转换（强制转换）
通过强制类型转换运算符 `(type)` 手动指定目标类型。
#### 1. ​**​基本语法​**​
`(目标类型) 表达式`
```
double pi = 3.1415926; 
int int_pi = (int)pi; // 结果为3（直接截断）
```
#### 2. ​**​常见应用场景​**
- ​**​浮点数转整数​**​：
```
float x = 5.8; 
int a = (int)x; // a = 5（丢失小数部分）
```
- ​**​整数转字符​**​：
```
int num = 65; 
char c = (char)num; // c = 'A'（ASCII码65）
```
- ​**​指针类型转换​**​：
```
int *p; 
void *vp = (void*)p; // 转为void指针
```
### 常见转换场景及示例

#### 1. ​**​整数与浮点数互转​**​
```
int num = 42; 
double d = (double)num; // 42.0 
int back = (int)d;       // 42
```
#### 2. ​**​字符与整数互转​**​
```
char c = 'A'; 
int ascii = (int)c;     // 65 
char c2 = (char)97;     // 'a'
```
#### 3. ​**​指类型转换​**​
```
int x = 100; 
int *p = &x; 
char *cp = (char*)p;    // 按字节解析内存
```
#### 4. ​**​不同长度的整数类型转换​**​
```
long big_num = 1000; 
short small = (short)big_num; // 可能溢出（取决于值范围）
```
#### 5. ​**​字符串与数值互转​**​
 - **​字符串转数值​**​：    
```
#include <stdlib.h> 
char str[] = "123"; 
int num = atoi(str);      // 123 
double d = atof("3.14");  // 3.14
```
- ​**​数值转字符串​**​：
```
#include <stdio.h> 
char buffer[20]; 
sprintf(buffer, "%d", 100); // "100"
```
### 注意事项

1. ​**​数据丢失风险​**​：    
    - 浮点转整数时直接截断小数部分（非四舍五入）。
    - 超出目标类型范围时可能导致溢出（未定义行为）。
2. ​**​指针转换的安全性​**​：    
    - 不同类型的指针强制转换可能导致未对齐访问（如 `int*` 转 `char*` 是安全的，反之可能崩溃）。
3. ​**​隐式转换的陷阱​**​：    
```
int a = 300; 
char c = a; // 隐式转换，若char为有符号则c=44（溢出）
```
4. ​**​布尔转换​**​：    
    - C语言中，`0` 为假，非 `0` 为真：
```
	int x = 5; 
	if (x) { /* 执行 */ } // x被隐式转为布尔值
```

---
#### 转义序列
- **字符型**转义序列
![[Pasted image 20250513153458.png]]

- **数值型**的转义序列
	```
	char a = 27        /*ESC*/
	char b = '\33';    /*八进制*/
	char c = '0x1b';   /*十六进制，大小写没影响*/
	char d = '0x1B'
	```
*上面定义都是一样的效果*

### ASCii码
![[ASCii.png]]
**扩展资料**
在ASCII码中，0～31及127(共33个)是控制字符或通信专用字符，如控制符：LF（换行）、CR（回车）、FF（换页）、DEL（删除）、BS（退格)、BEL（响铃）等。
通信专用字符：SOH（文头）、EOT（文尾）、ACK（确认）等。
ASCII值为8、9、10 和13 分别转换为退格、制表、换行和回车字符。它们并没有特定的图形显示，但会依不同的应用程序，而对文本显示有不同的影响。
32～126(共95个)是字符(32是空格），其中48～57为0到9十个阿拉伯数字。
65～90为26个大写英文字母，97～122号为26个小写英文字母，其余为一些标点符号、运算符号等。
同时还要注意，在标准ASCII中，其最高位(b7)用作奇偶校验位。
所谓奇偶校验，是指在代码传送过程中用来检验是否出现错误的一种方法，一般分奇校验和偶校验两种。

### 类型定义
> #define BOOL int  -> BOOL == int
> typedef int Bool;     Bool == int
- **typedef不易出错，在结构体、联合体、函数指针中优先使用**，提高代码的可读性和可维护性



### sizeof 运算符
- [sizeof表达式] sizeof(类型名)
- size_t 代表无符号整型，在类型**输出统一用%zu**，以确保代码的跨平台兼容性和类型安全。​
- sizeof i + j  -> sizeof( i ) + j 原因：sizeof为**一元运算符**优先级高于二元运算符'+'

## 数组
- 数组传入自定义函数中，自动退化为指针
### 一维数组
#### 数组下标
- a[i+j] = 0 这样子写没问题

	```
	int i = 0 , N =5;
	while(i < N)
		a[i++] = 0
	```
- 这样子写导致第一次进入循环体等价于执行了a[1] = 0;
- 结论：在数组下标内不要使用++、--操作符

### 多维数组


