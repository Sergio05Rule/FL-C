//Inserire elementi pari e dispari in distinti vettori

void printarray(int a[20], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
      printf("%d \t ", a[i]);
    }
    printf("\n");
}


int main()
{
 int size, i, a[10], even[10], odd[10];
 int even_count = 0, odd_count = 0;

 printf("\n Please Enter the Size of an Array :  ");
 scanf("%d", &size);

 printf("\n Please Enter the Array Elements  :   ");
 for(i = 0; i < size; i++)
 {
      scanf("%d", &a[i]);
 }

 for(i = 0; i < size; i ++)
 {
 	if(a[i] % 2 == 0)
 	{
 		even[even_count] = a[i];
 		even_count++;
	}
	else
	{
		odd[odd_count] = a[i];
	 	odd_count++;
	}
 }

 printf("\n Total Number of Even Numbers in this Array = %d ", even_count);
 printf("\n Array Elements in Even Array  :  ");
 printarray(even, even_count);

 printf("\n Total Number of Odd Numbers in this Array = %d ", odd_count);
 printf("\n Array Elements in Odd Array  : ");
 printarray(odd, odd_count);
 return 0;
}

