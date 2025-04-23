#include <stdio.h>

int main() {
    const char* str = "Name: Alice, Age: 25, Height: 165.5";
    char name[20];
    int age;
    float height;

    // �ؼ��޸��㣺
    // 1. ��ʽ�� %19[^,] ƥ�� name �����С��19�ַ� + \0��
    // 2. ��ӻ�������С���� sizeof(name)
    int parsed = sscanf_s(str, "Name: %19[^,], Age: %d, Height: %f",
        name, (unsigned)sizeof(name), &age, &height);
    /*1. ?**sscanf_s �İ�ȫ����Ҫ��**?
sscanf_s �� C11 ��׼�ж���ġ���ȫ�汾�����뺯������ѭ Annex K��������ĸĽ��� ?ǿ��Ҫ��ָ����������С���Է�ֹ���������������������£�

�����漰д�뻺�����ĸ�ʽ������ %s��%[ ]��%c����?������⴫�ݻ�������С������
�ò�����������Ϊ unsigned int��΢��� sscanf_s ʵ���ϸ���ѭ������Ҫ�󣩡�
2. ?**sizeof(name) ������**?
sizeof(name) �����ַ����� name �� ?���ֽ���?������ char name[20]���� sizeof(name) = 20����
�����ڸ�֪ sscanf_s ��������ʵ��������ȷ��д��ʱ����Խ�硣
3. ?**(unsigned) ǿ��ת���ı�Ҫ��**?
sizeof ������ķ���ֵ������ size_t��һ��ƽ̨��ص��޷����������ͣ����� 64 λϵͳ�п����� unsigned long long����
΢��� sscanf_s ʵ��Ҫ�󻺳�����С����Ϊ unsigned int���� size_t ������ unsigned int ?���Ͳ�����?�������� 64 λϵͳ�ϣ�size_t ����Ϊ 64 λ���� unsigned int Ϊ 32 λ����
?**ǿ��ת�� (unsigned)**? �� size_t ת��Ϊ unsigned int����ƥ�� sscanf_s �Ĳ�������Ҫ��*/


    if (parsed == 3) {
        printf("Name: %s, Age: %d, Height: %.1f\n", name, age, height);
    }
    else {
        printf("����ʧ�ܣ�\n");
    }
    return 0;
}