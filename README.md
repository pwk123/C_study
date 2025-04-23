2025.04.23
word: 1、format 格式
function:
1、scanf("",&a);键盘输入函数 将参数传到变量a中
  键盘输入的内容" "要100%满足，包括大小写等
  EG:scnaf("ARM:%d %d");则输入为ARM:num1 num2
2、sscanf(str,"str想要提取出来的参数",name,&num1,&num2);
  EG:
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
  3、
