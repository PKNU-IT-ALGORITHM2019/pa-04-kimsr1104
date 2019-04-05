#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 배열정렬 퀵소트 라이브러리
	qsort (void *base, int num, int width, int compare)
		base : 정렬을 수행 할 배열
		num : 배열의 크기 (갯수)
		width : 정렬할 각 원소의 크기 바이트의 수 (동적할당 sizeof()), 배열 / 자료형 ex) int width = sizeof(a) / sizeof(int);
		compare : 두 배열요소를 비교, 서로의 관계를 지정하는 값을 반환하는 포인터
*/
int compare(const void *a, const void *b)
{
	
}

int compareStr(const void *a, const void *b)	// 문자열 비교
{
	char const **aa = (char const**)a;
	char const **bb = (char const**)b;

	return strcmp(*aa, *bb);
}

int main()
{
	FILE *file = fopen("C:\Users\사용자\source\repos\pa-04\pa-04\webLog.csv", "rt");
	
}