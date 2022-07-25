
/*The method recieves an integer number and converts it into binary 

*/

char *convert_decimal_Binary(int num)
{
  int n, c, k;
  for (c = 31; c >= 0; c--)
  {
    k = n >> c;

    if (k & 1)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  return 0;
}