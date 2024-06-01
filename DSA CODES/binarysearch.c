#include<stdio.h>
#include<conio.h>
int main()
{
    int i, low, high, mid, n, key, array[100];
    printf("Enter Numbers of Elements");
    scanf("%d",&n);
    printf("Enter %d Integers", n);
    for(i=0;i<n;i++)
    scanf("%d",&array[i]);
    printf("Enter Value to Find");
    scanf("%d",&key);
    low=0;
    high=n-1;
    mid=(low+high)/2;
    while(low<=high)
    {
        if(array[mid]<key)
            low=mid+1;
        else if(array[mid]==key)
        {
            printf("%d found at location %d.n", key, mid);
            break;
        }
        else
            high=mid-1;
            mid=(low+high)/2;
    }
    if(low>high)
        printf("Not Found! %d is not present in the list.n", key);
    return 0;
}
