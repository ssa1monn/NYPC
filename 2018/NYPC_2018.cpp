#include < iostream >
 
using namespace std;
 
int main()
{
    // 체력 물약 : p, 마나물약 : q, 총액 : w
    int p = 0, q = 0, w = 0;
 
    // 공백으로 3가지 대입 받기(체력, 마나, 총액)
    cin >> p >> q >> w;
 
    // y에 대한 방정식
    // 1. ax + by = c 
    // 2. by = c-ax
    // 3. y = (c-ax)/b
 
    for (int i = 1; i * p <= w; i++) 
    {  
         if ((w - (i * p)) % q == 0)
         {
             cout << i << " " << (w - (i * p)) / q << endl;
             break;
         }
    }
     return 0;
}