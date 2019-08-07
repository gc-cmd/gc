#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<assert.h>
void Merge(int *arr,int len,int gap)
{
	int *brr = (int *)malloc(sizeof(int) * len);
	assert(brr != NULL);
	int i = 0;//brr���±�
	int start1 = 0;
	int end1 = start1+gap-1;
	int start2 = end1+1;
	int end2 = start2+gap-1 < len-1 ? start2+gap-1 : len-1;

	//���������鲢�ε�ʱ��
	while(start2 < len)
	{
		//�������鲢�λ�û�бȽ����ʱ��
		while(start1 <= end1 && start2<=end2)
		{
			if(arr[start1] <= arr[start2])
			{
				brr[i++] = arr[start1++];
			}
			else
			{
				brr[i++] = arr[start2++];
			}
		}
		while(start1 <= end1)
		{
			brr[i++] = arr[start1++];
		}

		while(start2 <= end2)
		{
			brr[i++] = arr[start2++];
		}
		//�������µĹ鲢��

		start1 = end2+1;
		end1 = start1+gap-1;
		start2 = end1+1;
		end2 = start2+gap-1 < len-1?start2+gap-1:len-1;
	}
	while(start1 < len)
	{
		brr[i++] = arr[start1++];
	}

	for(int i = 0;i < len;i++)
	{
		arr[i] = brr[i];
	}

}
void MergeSort(int *arr,int len)
{
	for(int i = 1;i < len;i *= 2)
	{
		Merge(arr,len,i);
	}
}

void Show(int *arr,int len)
{
	for(int i = 0;i < len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
//������ǰK����С������

//���ִ����������鳤��һ������֣�
//�磺{1,2,3,2,2,2,5,4,2} ����2Ϊ
//�������鳤��һ������֡� 
int main()
{
	int arr[10000] = {};
	int len = sizeof(arr)/sizeof(arr[0]);
	srand(time(NULL));
	for(int i = 0;i < len;i++)
	{
		arr[i] = rand()%10000;
	}
	MergeSort(arr,len);
	Show(arr,len);
	return 0;
}

#if 0
int Partion(int *arr,int low,int high)
{
	int tmp = arr[low];
	while(low < high)
	{
		while(low < high && arr[high] >= tmp)
		{
			high--;
		}
		if(low >= high)
		{
			break;
		}
		else
		{
			arr[low] = arr[high];
		}
		while(low < high && arr[low] <= tmp)
		{
			low++;
		}
		if(low >= high)
		{
			break;
		}
		else
		{
			arr[high] = arr[low];
		}
	}
	arr[low] = tmp;
	return low;
}
void Swap(int *arr,int start,int end)
{
	int tmp = arr[start];
	arr[start] = arr[end];
	arr[end] = tmp;
}
//1 2 3 4 5 6
void SelectPivotMedianOfThree(int *arr,int low,int high) 
{
	int mid = (high-low)/2+low;//(high+low)>>1;
	//arr[mid]<=arr[low]<=arr[high];
	if(arr[mid] > arr[low])
	{
		Swap(arr,mid,low);
	}//arr[mid] <= arr[low]
	if(arr[low] > arr[high]) 
	{
		Swap(arr,low,high);
	}//arr[low] <= arr[high]
	if(arr[mid] > arr[high])
	{
		Swap(arr,mid,high);
	}//arr[mid] <= arr[high]

}
//�Ż���ʽһ����������������У�������ĸ���С��ĳһ��
//��������ʱ��ʹ�ò������򣨲�������Խ����Խ�죬���Դﵽ��
//O(n)��ʱ�临�Ӷ�
void InsertSort(int *arr,int low,int high)
{
	for(int i = low+1;i <= high;i++)
	{
		int tmp = arr[i];
		int j = 0;
		for(j = i-1;j >= low;j--)
		{
			if(arr[j] > tmp)
			{
				arr[j+1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j+1] = tmp;
	}
}
//�ۼ���ͬԪ�ػ�׼��
void FocusNumPar(int *arr,int low,int par,int high,int *left,
				 int *right)
{
	if(low < high)
	{
		int parLeft = par-1;
		for(int i = par-1;i >= low;i--)
		{
			if(arr[i] == arr[par])
			{
				if(i != parLeft)
				{
					Swap(arr,i,parLeft);
					parLeft--;
				}
				else
				{
					parLeft--;
				}
			}
		}
		*left = parLeft;

		int parRight = par+1;
		for(int i = par+1;i <= high;i++)
		{
			if(arr[i] == arr[par])
			{
				if(i != parRight)
				{
					Swap(arr,i,parRight);
					parRight++;
				}
				else
				{
					parRight++;
				}
			}
		}
		*right = parRight;
	}
}

void Quick(int *arr, int low, int high)
{
	/*if((high-low)+1 < 100)
	{
		InsertSort(arr,low,high);
		return;
	}*/
	//����ʽ2�����ѡȡ��׼��
	//srand((unsigned int)time(NULL));
	//Swap(arr,low,rand() % (high-low)+low);
	//����ʽ3������ȡ�з�
	SelectPivotMedianOfThree(arr,low,high);
    int par = Partion(arr,low,high);
	int left = 0;
	int right = 0;
	//�Ż���ʽ2��
	FocusNumPar(arr,low,par,high,&left,&right);

	if(left >= low+1)//˵�������������������
	{
		//Quick(arr,low,par-1);
		Quick(arr,low,left);
	}
	if(right <= high-1)
	{
		//Quick(arr,par+1,high);
		Quick(arr,right,high);
	}
}
void QuickSort(int *arr,int len)
{
	Quick(arr,0,len-1);
}
#endif
