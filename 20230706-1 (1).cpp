
// 20230706-1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 50
#define c_size 100
void set_Array(int array[]) {

	for (int i = 0; i < size; i++) {
		array[i] = rand() % 100;
	}



}

void setC_sort(int array1234[]) {
	int temp;

	for (int i = 0; i < c_size; i++) {
		for (int j = 0; j < (c_size - 1) - i; j++) {
			if (array1234[j] > array1234[j + 1]) {	// 버블 정렬 사용
				temp = array1234[j];
				array1234[j] = array1234[j + 1];
				array1234[j + 1] = temp;
			}

		}
	}
	for (int p = 0; p < c_size; p++) {
		printf("%d    ", array1234[p]);
	}
	printf("\n");



}
void set_sort(int array234[]) {

	int temp;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < (size - 1) - i; j++) {
			if (array234[j] > array234[j + 1]) {	// 버블 정렬 사용
				temp = array234[j];
				array234[j] = array234[j + 1];
				array234[j + 1] = temp;
			}

		}
	}

	
		for (int k = 0; k < size; k++) {
			printf("%d  ", array234[k]);
		}
	

}// 배열의 크기가 달라가지고 
void concat(int array1[size], int array2[size], int array3[100]) { //배열 두개를 합쳐라 !
	for (int i = 0; i < size; i++) {
		array3[i] = array1[i];

	}

	int num = 50;
	int num2 = 0;
	while (num <= 99) {
		array3[num] = array2[num2];
		num++;
		num2++;

	}


	for (int k = 0; k < c_size; k++) {
		printf(" %d  ", array3[k]);
	}
	printf("%d\n");

}
int main(void)
{
	srand((unsigned int)time(NULL));
	int arr_a[size];
	int arr_b[size];
	int arr_c[c_size];

	set_Array(arr_a);

	set_sort(arr_a);

	set_Array(arr_b);

	set_sort(arr_b);


	printf("배열합침");
	concat(arr_a, arr_b, arr_c);
	printf("배열합친 배열을 sort 함");
	setC_sort(arr_c);
	

	printf("\n");




	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
