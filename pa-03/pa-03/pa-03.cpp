#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000			// 최대 데이터 개수

int Random_1000[1001];
int Random_10000[10001];
int Random_100000[MAX+1];
int Reverse_1000[1001];	
int Reverse_10000[10001];
int Reverse_100000[MAX+1];
int mer[MAX];				// 합병정렬시 추가배열
clock_t start, finish, timer = 0;	// 시간측정 변수

double TimeArr[9][6];			// 시간 출력 테이블

void Bubble_AllTime();
void Select_AllTime();
void Insert_AllTime();
void Merge_AllTime();
void Quick1_AllTime();
void Quick2_AllTime();
void Quick3_AllTime();
void Heap_AllTime();
void SortLibrary_AllTime();
void push(int *arr, int data);

double TimePrint()					// 시간 측정값 반환
{
	timer = finish - start;
	return (double)timer/CLOCKS_PER_SEC;
}

void Swap(int *arr, int a, int b)		// 스왑
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void BubbleSort(int *arr, int n)		// 버블정렬 : 완
{
	int i, temp = 0, count = 0;
	while (1)
	{
		for (i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				Swap(arr, i, i + 1);
			}
		}
		count++;
		if (count == n)
			break;
	}
}

void SelectionSort(int *arr, int n)		// 선택정렬 : 완
{
	int last = n;
	int i, temp = 0, max;

	while (1)
	{
		max = 0;
		for (i = 0; i < last; i++)
		{
			if (arr[max] <= arr[i])
				max = i;
		}
		Swap(arr, max, last - 1);
		last--;
		if (last == 0)
			break;
	}
}

void InsertionSort(int *arr, int n)			// 삽입정렬 :완
{
	int i, temp = 0;

	for (i = 1; i < n; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[i] < arr[j])
			{
				Swap(arr, i, j);
				i--;
			}
		}
	}
}

void Merge(int *arr, int p, int q, int r)
{
	int first = p;
	int mid = q + 1;
	int mer_pointer = p;		// 추가배열의 인덱스 포인터

	while (first <= q && mid <= r)
	{
		if (arr[first] < arr[mid])
		{
			mer[mer_pointer++] = arr[first++];
		}
		else if (arr[first] >= arr[mid])
		{
			mer[mer_pointer++] = arr[mid++];
		}
	}
	if (mid >= r)			// 오른쪽 영역 끝
	{
		while (first <= q)
		{
			mer[mer_pointer++] = arr[first++];
		}
	}
	if (first >= q)			// 왼쪽 영역 끝
	{
		while (mid <= r)
		{
			mer[mer_pointer++] = arr[mid++];
		}
	}
	for (int i = p; i <= r; i++)		// 합병된 배열을 기존 배열에 복사
	{
		arr[i] = mer[i];
	}
}

void MergeSort(int *arr, int p, int r)		// 합병정렬 : 완
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;
		MergeSort(arr, p, q);
		MergeSort(arr, q + 1, r);
		Merge(arr, p, q, r);
	}
}

int Partition_Last(int *arr, int p, int r)
{
	int pivot = arr[r];		// 마지막 값이 pivot
	int left = p;			// 왼쪽 끝
	int right = r - 1;		// pivot을 제외한 오른쪽 끝

	while (left <= right)
	{
		while (pivot >= arr[left] && left <= r - 1)
		{
			left++;
		}		// 현재 인덱스 값이 pivot 값보다 작으면 다음 인덱스로
		while (pivot <= arr[right] && right >= p)
		{
			right--;
		}		// 현재 인덱스 값이 pivot 값보다 크면 이전 인덱스로
		if (left <= right)		// 인덱스가 교차되지 않은 상태라면 스왑
			Swap(arr, left, right);
	}
	Swap(arr, left, r);		// pivot과 left의 인덱스 값과 교환
	return left;			// 옮겨진 pivot 위치정보 반환
}

void QuickSort_Last(int *arr, int p, int r)		// 퀵소트_Last : 완
{
	if (p < r)
	{
		int q = Partition_Last(arr, p, r);
		QuickSort_Last(arr, p, q - 1);
		QuickSort_Last(arr, q + 1, r);
	}		
}

int Partition_FML_Middle(int *arr, int p, int r)
{
	int mid = (p + r) / 2;

	if (arr[p] <= arr[mid] && arr[p] >= arr[r] || arr[p] >= arr[mid] && arr[p] <= arr[r])
		Swap(arr, p, r);			// p가 중간값, 마지막과 스왑
	if (arr[mid] <= arr[r] && arr[mid] >= arr[p] || arr[mid] >= arr[r] && arr[mid] <= arr[p])
		Swap(arr, mid, r);			// mid가 중간값, 마지막과 스왑
	
	// r이 중간값이면, Last가 pivot인 것과 같음
	// 이 후 Partition_Last와 같은 수행

	int pivot = arr[r];		// 마지막 값이 pivot
	int left = p;			// 왼쪽 끝
	int right = r - 1;		// pivot을 제외한 오른쪽 끝

	while (left <= right)
	{
		while (pivot >= arr[left] && left <= r - 1)
		{
			left++;
		}		// 현재 인덱스 값이 pivot 값보다 작으면 다음 인덱스로
		while (pivot <= arr[right] && right >= p)
		{
			right--;
		}		// 현재 인덱스 값이 pivot 값보다 크면 이전 인덱스로
		if (left <= right)		// 인덱스가 교차되지 않은 상태라면 스왑
			Swap(arr, left, right);
	}
	Swap(arr, left, r);		// pivot과 left의 인덱스 값과 교환
	return left;			// 옮겨진 pivot 위치정보 반환
}

void QuickSort_FML_Middle(int *arr, int p, int r)	// 퀵소트_FML : 완
{
	if (p < r)
	{
		int q = Partition_FML_Middle(arr, p, r);
		QuickSort_FML_Middle(arr, p, q - 1);
		QuickSort_FML_Middle(arr, q + 1, r);
	}
}

int Partition_Random(int *arr, int p, int r)
{
	int ran_num = rand() % (r - p + 1) + p;
	Swap(arr, ran_num, r);		// 랜덤 설정된 pivot을 마지막 인덱스와 스왑

	// 이 후 Partition_Last와 같은 수행

	int pivot = arr[r];		// 마지막 값이 pivot
	int left = p;			// 왼쪽 끝
	int right = r - 1;		// pivot을 제외한 오른쪽 끝

	while (left <= right)
	{
		while (pivot >= arr[left] && left <= r - 1)
		{
			left++;
		}		// 현재 인덱스 값이 pivot 값보다 작으면 다음 인덱스로
		while (pivot <= arr[right] && right >= p)
		{
			right--;
		}		// 현재 인덱스 값이 pivot 값보다 크면 이전 인덱스로
		if (left <= right)		// 인덱스가 교차되지 않은 상태라면 스왑
			Swap(arr, left, right);
	}
	Swap(arr, left, r);		// pivot과 left의 인덱스 값과 교환
	return left;			// 옮겨진 pivot 위치정보 반환
}

void QuickSort_Random(int *arr, int p, int r)	// 퀵소트_RANDOM : 완
{
	if (p < r)
	{
		int q = Partition_Random(arr, p, r);
		QuickSort_Random(arr, p, q - 1);
		QuickSort_Random(arr, q + 1, r);
	}
}

void MAX_Heapify(int *arr, int index, int i)
{
	int LeftChild = 2 * i;
	int RightChild = (2 * i) + 1;
	int k = 0;
	if (arr[LeftChild] == NULL && arr[RightChild] == NULL)
		return;
	else
	{
		if (LeftChild < index && arr[LeftChild] >= arr[RightChild])
		{
			k = LeftChild;
		}
		else if (RightChild < index && arr[LeftChild] < arr[RightChild])
		{
			k = RightChild;
		}
	}
	if (k != i)
	{
		if (arr[i] >= arr[k])
			return;
		Swap(arr, k, i);
		MAX_Heapify(arr, index, k);
	}
}

void Build_MAX_Heap(int *arr, int data)
{
	for (int i = data / 2; i >= 0; i--)
	{
		MAX_Heapify(arr, data, i);
	}
}

void HeapSort(int *arr, int data)			// 힙 정렬 :미완
{
	Build_MAX_Heap(arr, data);
	for (int i = data - 1; i >= 0; i--)
	{
		Swap(arr, 0, i);
		MAX_Heapify(arr, i, 0);
	}
}

int compare(const void *a, const void *b)	// 배열의 앞뒤 인덱스 비교
{
	int first = *(int*)a;
	int second = *(int*)b;
	
	if (first < second)
		return -1;
	else if (first > second)
		return 1;
	// 현재 오름차순 정렬, 내림차순으로 바꾸려면 return값을 바꿔주면 된다.
	return 0;
}

void Data_1000()
{
	for (int i = 0; i < 1000; i++)
	{
		Random_1000[i] = rand() % 1000 + 1;
		Reverse_1000[i] = 1000 - i;
	}
}
void Data_10000()
{
	for (int i = 0; i < 10000; i++)
	{
		Random_10000[i] = rand() % 10000 + 1;
		Reverse_10000[i] = 10000 - i;
	}
}
void Data_100000()
{
	for (int i = 0; i < MAX; i++)
	{
		Random_100000[i] = rand() % MAX + 1;
		Reverse_100000[i] = MAX - i;
	}
}

int main()
{
	srand(time(NULL));

	Bubble_AllTime();				// 작동
	Select_AllTime();				// 작동
	Insert_AllTime();				// 작동
	Merge_AllTime();				// 작동
//	Quick1_AllTime();				// 미작동
//	Quick2_AllTime();				// 미작동
	Quick3_AllTime();				// 작동
//	Heap_AllTime();					// 미작동
	SortLibrary_AllTime();			// 작동

	printf("\n==============================================================================================================\n");
	printf("\t\tRandom1000\tReverse1000\tRandom10000\tReverse10000\tRandom100000\tReverse100000\n");
	printf("==============================================================================================================\n");
	printf("Bubble\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[0][i]);
	printf("\n");

	printf("Selection\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[1][i]);
	printf("\n");

	printf("Insertion\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[2][i]);
	printf("\n");

	printf("Merge\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[3][i]);
	printf("\n");

	printf("Quick1\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[4][i]);
	printf("\n");

	printf("Quick2\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t",TimeArr[5][i]);
	printf("\n");

	printf("Quick3\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[6][i]);
	printf("\n");

	printf("Heap\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[7][i]);
	printf("\n");

	printf("Library\t\t");
	for (int i = 0; i < 6; i++)
		printf("%f\t", TimeArr[8][i]);
	printf("\n");

	printf("==============================================================================================================\n");

	return 0;
}

void Bubble_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		BubbleSort(Random_1000, 1000);
	}
	finish = clock();
	TimeArr[0][0] = TimePrint();

	start = clock();
	BubbleSort(Reverse_1000, 1000);
	finish = clock();
	TimeArr[0][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		BubbleSort(Random_10000, 10000);
	}
	finish = clock();
	TimeArr[0][2] = TimePrint();

	start = clock();
	BubbleSort(Reverse_10000, 10000);
	finish = clock();
	TimeArr[0][3] = TimePrint();

/*	// 10만 파트 너무 느려 확인 어려움
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		BubbleSort(Random_100000, 100000);
	}
	finish = clock();
	TimeArr[0][4] = TimePrint();

	start = clock();
	BubbleSort(Reverse_100000, 100000);
	finish = clock();
	TimeArr[0][5] = TimePrint();
	*/
}

void Select_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		SelectionSort(Random_1000, 1000);
	}
	finish = clock();
	TimeArr[1][0] = TimePrint();

	start = clock();
	SelectionSort(Reverse_1000, 1000);
	finish = clock();
	TimeArr[1][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		SelectionSort(Random_10000, 10000);
	}
	finish = clock();
	TimeArr[1][2] = TimePrint();

	start = clock();
	SelectionSort(Reverse_10000, 10000);
	finish = clock();
	TimeArr[1][3] = TimePrint();

/*	// 10만 파트 너무 느려 확인 어려움
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		SelectionSort(Random_100000, 100000);
	}
	finish = clock();
	TimeArr[1][4] = TimePrint();

	start = clock();
	SelectionSort(Reverse_100000, 100000);
	finish = clock();
	TimeArr[1][5] = TimePrint();
	*/
}

void Insert_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		InsertionSort(Random_1000, 1000);
	}
	finish = clock();
	TimeArr[2][0] = TimePrint();

	start = clock();
	InsertionSort(Reverse_1000, 1000);
	finish = clock();
	TimeArr[2][1] = TimePrint();
/*  // 랜덤 1만 파트 느려 확인 어려움
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		InsertionSort(Random_10000, 10000);
	}
	finish = clock();
	TimeArr[2][2] = TimePrint(); 
*/
	start = clock();
	InsertionSort(Reverse_10000, 10000);
	finish = clock();
	TimeArr[2][3] = TimePrint(); 

/*	// 10만 파트 너무 느려 확인 어려움
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		InsertionSort(Random_100000, 100000);
	}
	finish = clock();
	TimeArr[2][4] = TimePrint();

	start = clock();
	InsertionSort(Reverse_100000, 100000);
	finish = clock();
	TimeArr[2][5] = TimePrint();
	*/
}

void Merge_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		MergeSort(Random_1000, 0, 999);
	}
	finish = clock();
	TimeArr[3][0] = TimePrint();

	start = clock();
	MergeSort(Reverse_1000, 0, 999);
	finish = clock();
	TimeArr[3][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		MergeSort(Random_10000, 0, 9999);
	}
	finish = clock();
	TimeArr[3][2] = TimePrint();

	start = clock();
	MergeSort(Reverse_10000, 0, 9999);
	finish = clock();
	TimeArr[3][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		MergeSort(Random_100000, 0, 99999);
	}
	finish = clock();
	TimeArr[3][4] = TimePrint();

	start = clock();
	MergeSort(Reverse_100000, 0, 99999);
	finish = clock();
	TimeArr[3][5] = TimePrint();
}

void Quick1_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		QuickSort_Last(Random_1000, 0, 999);
	}
	finish = clock();
	TimeArr[4][0] = TimePrint();

	start = clock();
	QuickSort_Last(Reverse_1000, 0, 999);
	finish = clock();
	TimeArr[4][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		QuickSort_Last(Random_10000, 0, 9999);
	}
	finish = clock();
	TimeArr[4][2] = TimePrint();

	start = clock();
	QuickSort_Last(Reverse_10000, 0, 9999);
	finish = clock();
	TimeArr[4][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		QuickSort_Last(Random_100000, 0, 99999);
	}
	finish = clock();
	TimeArr[4][4] = TimePrint();

	start = clock();
	QuickSort_Last(Reverse_100000, 0, 99999);
	finish = clock();
	TimeArr[4][5] = TimePrint();
}

void Quick2_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		QuickSort_FML_Middle(Random_1000, 0, 999);
	}
	finish = clock();
	TimeArr[5][0] = TimePrint();

	start = clock();
	QuickSort_FML_Middle(Reverse_1000, 0, 999);
	finish = clock();
	TimeArr[5][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		QuickSort_FML_Middle(Random_10000, 0, 9999);
	}
	finish = clock();
	TimeArr[5][2] = TimePrint();

	start = clock();
	QuickSort_FML_Middle(Reverse_10000, 0, 9999);
	finish = clock();
	TimeArr[5][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		QuickSort_FML_Middle(Random_100000, 0, 99999);
	}
	finish = clock();
	TimeArr[5][4] = TimePrint();

	start = clock();
	QuickSort_FML_Middle(Reverse_100000, 0, 99999);
	finish = clock();
	TimeArr[5][5] = TimePrint();
}

void Quick3_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		QuickSort_Random(Random_1000, 0, 999);
	}
	finish = clock();
	TimeArr[6][0] = TimePrint();

	start = clock();
	QuickSort_Random(Reverse_1000, 0, 999);
	finish = clock();
	TimeArr[6][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		QuickSort_Random(Random_10000, 0, 9999);
	}
	finish = clock();
	TimeArr[6][2] = TimePrint();

	start = clock();
	QuickSort_Random(Reverse_10000, 0, 9999);
	finish = clock();
	TimeArr[6][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		QuickSort_Random(Random_100000, 0, 99999);
	}
	finish = clock();
	TimeArr[6][4] = TimePrint();

	start = clock();
	QuickSort_Random(Reverse_100000, 0, 99999);
	finish = clock();
	TimeArr[6][5] = TimePrint();
}

void Heap_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		push(Random_1000, 1000);	// 0~999 배열을 1~1000배열로 변환
		HeapSort(Random_1000, 1000);
	}
	finish = clock();
	TimeArr[7][0] = TimePrint();

	push(Reverse_1000, 1000);
	start = clock();
	HeapSort(Reverse_1000, 1000);
	finish = clock();
	TimeArr[7][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		push(Random_10000, 10000);
		HeapSort(Random_10000, 10000);
	}
	finish = clock();
	TimeArr[7][2] = TimePrint();

	push(Reverse_10000, 10000);
	start = clock();
	HeapSort(Reverse_10000, 10000);
	finish = clock();
	TimeArr[7][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		push(Random_100000, 100000);
		HeapSort(Random_10000, 10000);
	}
	finish = clock();
	TimeArr[7][4] = TimePrint();

	push(Reverse_100000, 100000);
	start = clock();
	HeapSort(Reverse_100000, 100000);
	finish = clock();
	TimeArr[7][5] = TimePrint();
}

void SortLibrary_AllTime()
{
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_1000();
		qsort(Random_1000, 1000, sizeof(int), compare);
	}
	finish = clock();
	TimeArr[8][0] = TimePrint();

	start = clock();
	qsort(Reverse_1000, 1000, sizeof(int), compare);
	finish = clock();
	TimeArr[8][1] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_10000();
		qsort(Random_10000, 10000, sizeof(int), compare);
	}
	finish = clock();
	TimeArr[8][2] = TimePrint();

	start = clock();
	qsort(Reverse_10000, 10000, sizeof(int), compare);
	finish = clock();
	TimeArr[8][3] = TimePrint();

	start = clock();
	for (int i = 0; i < 10; i++)
	{
		Data_100000();
		qsort(Random_100000, 100000, sizeof(int), compare);
	}
	finish = clock();
	TimeArr[8][4] = TimePrint();

	start = clock();
	qsort(Reverse_100000, 100000, sizeof(int), compare);
	finish = clock();
	TimeArr[8][5] = TimePrint();
}

void push(int *arr, int data)	// 인덱스 한칸씩 밀어주기
{
	for (int i = data+1; i >= 1; i--)
	{
		arr[i] = arr[i - 1];
	}
}