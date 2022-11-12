


int strlen(char *, int size);
int main(){


    int num = 65;
    int length = strlen((char *) &num, num);
    printf("length = %d\n", length);
    return 0;
}