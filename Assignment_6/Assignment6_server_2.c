// gcc -fPIC -shared -o Assignment6_server_1.so Assignment6_server_1.c
int Addition(int A,int B)
{
    int ans = 0;
    ans = A + B;
    return ans;
}

int Substraction(int A,int B)
{
    int ans = 0;
    ans = A - B;
    return ans;
}