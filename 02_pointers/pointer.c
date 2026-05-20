#include<stdio.h>
#include<stdint.h>
int main(void) {
    
    printf("================= Memory Inspector =================\n\n");
    
    char    a  = 'J';
    int     b   = 1234;
    float   c = 3.141;
    long    d  = 123456;
    printf("%-12s %-12s %-16s %s\n",
           "Variable", "Value", "Address", "Size");
    printf("------------------------------------------------\n");
    printf("%-12s %-12d %-16p %zu bytes\n",
           "char a",  a,  &a,  sizeof(a));
    printf("%-12s %-12d %-16p %zu bytes\n",
           "int b",  b,  &b,  sizeof(b));
    printf("%-12s %-12f %-16p %zu bytes\n",
           "float c",  c,  &c,  sizeof(c));
    printf("%-12s %-12ld %-16p %zu bytes\n",
           "long d",  d,  &d,  sizeof(d));
    printf("------------------------------------------------\n\n\n");
    printf("=== Memory addresses of an integer array elements ===\n\n");
    
    int arr[5] = {10,20,30,40,50};
    printf("%-12s %-12s %-16s %s\n",
           "Index", "Value", "Address", "Size");
    printf("------------------------------------------------\n");       
    for(int i = 0; i<5; i++){
        printf("%-12d %-12d %-16p %zu bytes\n",
                   i, arr[i],  &arr[i],  sizeof(arr[i]));
      
    }
    printf("------------------------------------------------\n\n\n");
printf("======Relation Between Pointer and Variable======\n\n");
int x   = 42;
int *ptr = &x;
    printf("x value              :%d\n",  x);
    printf("x address (&x)       :%p\n",  &x);
    printf("ptr contains         :%p\n",  ptr);    
    printf("value ptr points to  :%d\n",  *ptr);   
    printf("address of ptr       :%p\n",  &ptr);
    printf("------------------------------------------------\n\n\n");
    
printf("===========Sizeof different Datatypes===========\n\n");
printf("%-12s %s\n","Datatype","Size");
 printf("-----------------\n");
printf("%-12s %zu\n","char", sizeof(char));
printf("%-12s %zu\n","int", sizeof(int));
printf("%-12s %zu\n","float", sizeof(float));
printf("%-12s %zu\n","double", sizeof(double));
printf("%-12s %zu\n","long", sizeof(long));
printf("%-12s %zu\n","uint8_t", sizeof(uint8_t));
printf("%-12s %zu\n","uint16_t", sizeof(uint16_t));
printf("%-12s %zu\n","uint32_t", sizeof(uint32_t));
printf("------------------------------------------------\n\n\n");
return 0;
    
}

