#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* �迭���� ����Ʈ ���̺귯��
	qsort (void *base, int num, int width, int compare)
		base : ������ ���� �� �迭
		num : �迭�� ũ�� (����)
		width : ������ �� ������ ũ�� ����Ʈ�� �� (�����Ҵ� sizeof()), �迭 / �ڷ��� ex) int width = sizeof(a) / sizeof(int);
		compare : �� �迭��Ҹ� ��, ������ ���踦 �����ϴ� ���� ��ȯ�ϴ� ������
*/
int compare(const void *a, const void *b)
{
	
}

int compareStr(const void *a, const void *b)	// ���ڿ� ��
{
	char const **aa = (char const**)a;
	char const **bb = (char const**)b;

	return strcmp(*aa, *bb);
}

int main()
{
	FILE *file = fopen("C:\Users\�����\source\repos\pa-04\pa-04\webLog.csv", "rt");
	
}