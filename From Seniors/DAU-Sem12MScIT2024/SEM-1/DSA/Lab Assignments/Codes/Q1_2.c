#include <stdio.h>

#define MAX_SIZE 100

void insertFirst(int arr[], int *size, int num) {
    for (int i = *size; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = num;  
    (*size)++;     
}

void insertLast(int arr[], int *size, int num) {
    arr[*size] = num;  
    (*size)++;         
}

void deleteFirst(int arr[], int *size) {
    if (*size == 0) {
        printf("Array is empty, nothing to delete.\n");
        return;
    }
    for (int i = 0; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;  // Update the size of the array
    printf("Element at the first position deleted.\n");
}

void deleteLast(int arr[], int *size) {
    if (*size == 0) {
        printf("Array is empty, nothing to delete.\n");
        return;
    }
    (*size)--;  // Update the size of the array
    printf("Element at the last position deleted.\n");
}

int main() {
    int arr[MAX_SIZE];  
    int size = 0;       
    int num, baseSize, choice;

    
    printf("Enter the number of initial elements in the array (0 or 5): ");
    scanf("%d", &baseSize);

    if (baseSize != 0 && baseSize != 5) {
        printf("Invalid initial size. Please enter either 0 or 5.\n");
        return -1;
    }

    
    if (baseSize > 0) {
        printf("Enter %d initial elements: ", baseSize);
        for (int i = 0; i < baseSize; i++) {
            scanf("%d", &arr[i]);
        }
        size = baseSize;
    }

    
    while (1) {
        printf("\nChoose the operation:\n");
        printf("1. Insert at the first position\n");
        printf("2. Insert at the last position\n");
        printf("3. Delete at the first position\n");
        printf("4. Delete at the last position\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the num to insert at the first position: ");
                scanf("%d", &num);
                insertFirst(arr, &size, num);
                break;
            case 2:
                printf("Enter the num to insert at the last position: ");
                scanf("%d", &num);
                insertLast(arr, &size, num);
                break;
            case 3:
                deleteFirst(arr, &size);
                break;
            case 4:
                deleteLast(arr, &size);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please choose either 1, 2, or 3.\n");
        }

        
        printf("Array after operation: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}
