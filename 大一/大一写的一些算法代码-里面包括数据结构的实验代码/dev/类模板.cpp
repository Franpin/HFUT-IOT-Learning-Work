template <class T>
class Complex{
    
public:
    //���캯��
   	
    Complex(T a,T b);
    //���������
    Complex<T> operator+(Complex &c)
    {
        Complex<T> tmp(this->a+c.a, this->b+c.b);
        return tmp;
    }
        
private:
    T a;
    T b;
};
template <class T>
Complex<T>::Complex(T a, T b)
    {
        this->a = a;
        this->b = b;
    }
int main()
{
    //����Ķ��壬��������ģ�����ͣ���ΪҪ��������
    Complex<int> a(10,20);  
    Complex<int> b(20,30);
    Complex<int> c = a + b;
    
    return 0;
}

