#include <stdio.h>
#include <stdlib.h>
#define MAX 50

int binary_search(int a[],int key,int min,int max) {
	int i,mid;
	while(max >= min) {
		mid = (min + max)/2;
		if(a[mid] == key)
			return mid;
		else if(a[mid] < key)
			min = mid + 1;
		else
			max = mid - 1;
	}
	return -1;
}

int main(int argc,char *argv[]) {
	int i,res,key,arr[MAX];
	for(i = 0;i < argc;i++)
		arr[i] = atoi(argv[i]);
	printf("\nIN CHILD PROCESS | ARRAY : ");
	for(i = 0;i < argc;i++)
		printf("%d ",arr[i]);
	printf("\nENTER ELEMENT TO SEARCH : ");
	scanf("%d",&key);
	res = binary_search(arr,key,0,i-1);
	if(res == -1)
		printf("\nELEMENT NOT FOUND!\n");
	else
		printf("ELEMENT FOUND AT %d POSITION!\n",res);
	return 0;
}