#include<stdio.h>
#include<conio.h>

int main(){

    int arr[] = {5,10,50,84,200,1,6,99,65,50,1,99};
    int max,min,tmp,j=0;

    int n = sizeof(arr) / sizeof(arr[0]);
    max = arr[0];
    min = arr[0];
    int rev[n];

    //Original Array
    for(int i=0;i<n;i++){
        printf("%d \t",arr[i]);
    }


    //Q-7 Reverse an array
    for(int i=n-1;i>=0;i--){
        rev[j] = arr[i];
        j++;
    }
    printf("\nREVERSE\t");
    for(int i=0;i<n;i++){
        
        printf("%d ",rev[i]);
    }

    //Q-3 Minimum and maximum in an array 
    for(int i=0;i<n;i++){
        if(max<arr[i]){
            max = arr[i];
        }
        if(min > arr[i]){
            min = arr[i];
        }
        
    }
        printf("\n%d is maximum\n",max);
        printf("%d is minimum",min);

    //Q-4 Write a program to find duplicate elements in an array in O(n) times.
    printf("\n------------ARRAY ELEMENTS-----------\n"); 
    for(int i = 0; i < n; i++)
    { 
        printf("%d ",arr[i]); 
    } 
    printf("\n------------DUPLICATE ELEMENTS-----------\n");
     for(int i = 0; i < n-1; i++)
     { 
        for(j = i+1; j < n; j++)
        { 
            if(arr[i] == arr[j])
            { 
                printf("%d ",arr[i]); 
                break;
            } 
        }
    }
    
    
    //Q-5 Array in increasing order
    for(int i=0 ; i<n ; i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                tmp=arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    printf("\nIncreasing order array \t");
    for(int i=0;i<n;i++){
        
        printf("%d ",arr[i]);
    }

    //Q-6 Largest and the second largest Value of an array
    printf("\nLargest No. = %d",arr[n-1]);
    printf("\nSecond Largest No. = %d",arr[n-2]);

    
    return 0;
}