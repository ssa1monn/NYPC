#include < iostream >
 
using namespace std;
 
int main()
{
    // ü�� ���� : p, �������� : q, �Ѿ� : w
    int p = 0, q = 0, w = 0;
 
    // �������� 3���� ���� �ޱ�(ü��, ����, �Ѿ�)
    cin >> p >> q >> w;
 
    // y�� ���� ������
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