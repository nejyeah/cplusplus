template <class numtype> //声明一个模板，虚拟类型名为numtype
class Compare //类模板名为Compare
{
    public :
        Compare(numtype a,numtype b)
        {
            x=a;y=b;
        }
        numtype max( )
        {
            return (x>y)?x:y;
        }
        numtype min( )
        {
            return (x<y)?x:y;
        }
    private :
        numtype x,y;
};
