


int memcmp(void * v1);
int main(){


   int n = 17;
   int m = memcmp(&n);
   printf("%d\n",m);
    return 0;
}