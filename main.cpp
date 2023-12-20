#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class BigNum{
public:
    BigNum(){
        str = '0';
        flag = '+';
        num_len = 1;
    }
    BigNum(string s){
        str = s;
        if (s[0]=='+'){
            flag = '+';
            num_len = s.length() - 1;}
        else if (s[0]=='-'){
            flag = '-';
            num_len = s.length() - 1;}
        else{
            flag = '+';
            num_len = s.length();}
    }
    string str;
    char flag;
    int num_len;

    friend std::ostream& operator<<(std::ostream& s, BigNum& num);

    bool operator>(BigNum& theSecondNum){
        if (((this->flag)=='+')&&((theSecondNum.flag)=='-'))
            return true;
        else if (((this->flag)=='-')&&((theSecondNum.flag)=='+'))
            return false;
        else{
            if ((this->flag)=='+'){
                if ((this->num_len)>(theSecondNum.num_len))
                    return true;
                else if ((this->num_len)<(theSecondNum.num_len))
                    return false;
                else{
                    for(int i=0; i<(this->num_len); i++){
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')>(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return true;
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')<(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return false;}
                }
            }
            if ((this->flag)=='-'){
                if ((this->num_len)<(theSecondNum.num_len))
                    return true;
                else if ((this->num_len)>(theSecondNum.num_len))
                    return false;
                else{
                    for(int i=0; i<(this->num_len); i++){
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')<(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return true;
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')>(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return false;}
                }
            }
        }
        return false;
    }

    bool operator<(BigNum& theSecondNum){
        if (((this->flag)=='+')&&((theSecondNum.flag)=='-'))
            return false;
        else if (((this->flag)=='-')&&((theSecondNum.flag)=='+'))
            return true;
        else{
            if ((this->flag)=='+'){
                if ((this->num_len)>(theSecondNum.num_len))
                    return false;
                else if ((this->num_len)<(theSecondNum.num_len))
                    return true;
                else{
                    for(int i=0; i<(this->num_len); i++){
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')>(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return false;
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')<(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return true;}
                }
            }
            if ((this->flag)=='-'){
                if ((this->num_len)<(theSecondNum.num_len))
                    return false;
                else if ((this->num_len)>(theSecondNum.num_len))
                    return true;
                else{
                    for(int i=0; i<(this->num_len); i++){
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')<(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return false;
                        if ((((this->str)[i+(this->str).length()-(this->num_len)])-'0')>(((theSecondNum.str)[i+(theSecondNum.str).length()-(theSecondNum.num_len)]-'0')))
                            return true;}
                }
            }
        }
        return false;
    }

    BigNum operator+(BigNum& theSecondNum){
        BigNum tmp, tmp1 = *this, high, low, tmp2 = theSecondNum, tmp3, tmp4;

        tmp3 = *this;
        tmp3.flag = '+';
        tmp4 = theSecondNum;
        tmp4.flag = '+';
        if (tmp3 > tmp4)
            tmp.flag = tmp1.flag;
        else
            tmp.flag = theSecondNum.flag;

        if ((this->flag)==(theSecondNum.flag)){
            int x = this->num_len;
            int y = theSecondNum.num_len;
            int res_len = max(x,y)+1;
            int* res = new int[res_len];
            int* x_arrey = new int[res_len-1];
            for(int i=0; i<res_len-1; i++)
                x_arrey[i] = 0;
            for(int i=0; i<x; i++)
                x_arrey[res_len-i-2] = (this->str)[(this->str).length()-i-1]-'0';
            int* y_arrey = new int[res_len-1];
            for(int i=0; i<res_len-1; i++)
                y_arrey[i] = 0;
            for(int i=0; i<y; i++)
                y_arrey[res_len-i-2] = (theSecondNum.str)[(theSecondNum.str).length()-i-1]-'0';

            int carry=0, res_tmp;
            for (int i=0; i<res_len-1; i++){
                res_tmp = x_arrey[res_len-2-i] + y_arrey[res_len-2-i] + carry;
                if (res_tmp < 10){
                    res[res_len-1-i] = res_tmp;
                    carry = 0;
                }
                else{
                    res[res_len-1-i] = res_tmp-10;
                    carry = 1;
                }
            }
            res[0] = carry;
            if (tmp.flag=='+'){
                int sp=-1;
                for(int i=0;i<res_len ;i++){
                        if (res[i] > 0){
                            tmp.str = (char)(res[i]+48);
                            sp = i;
                            break;}
                }
                if (sp==-1){
                    tmp.str = '0';
                }
                else{
                    for (int i=sp+1; i<res_len; i++)
                        (tmp.str).push_back((char)(res[i]+48));
                }
                tmp.num_len = (tmp.str).length();
                delete[] res;
                delete[] x_arrey;
                delete[] y_arrey;
                return tmp;}
            else{
                int sp=-1;
                for(int i=0; i<res_len;i++){
                        if (res[i] > 0){
                            tmp.str = '-';
                            (tmp.str).push_back((char)(res[i]+48));
                            sp = i;
                            break;}
                }
                if (sp==-1){
                    tmp.str = '0';
                    tmp.flag = '+';
                }
                else{
                    for (int i=sp+1; i<res_len; i++)
                        (tmp.str).push_back((char)(res[i]+48));
                }
                tmp.num_len = (tmp.str).length() - 1;
                delete[] res;
                delete[] x_arrey;
                delete[] y_arrey;
                return tmp;}

        }
        else{
            if ((tmp1.str)[0]=='-'){
                (tmp1.str)[0]='+';
                tmp1.flag = '+';}
            if ((tmp2.str)[0]=='-'){
                (tmp2.str)[0]='-';
                tmp2.flag ='+';}
            if (tmp1 > tmp2){
                high = tmp1;
                low = tmp2;
            }
            else{
                high = tmp2;
                low = tmp1;
            }
            int x = high.num_len;
            int y = low.num_len;
            int res_len = max(x,y);
            int* res = new int[res_len];
            int* x_array = new int[x];
            int* y_array = new int[x];
            for(int i=0; i<x; i++)
                y_array[i]=0;
            for(int i=0; i<x; i++)
                x_array[x-i-1] = high.str[(high.str).length()-i-1]-'0';
            for(int i=0; i<y; i++)
                y_array[x-i-1] = low.str[(low.str).length()-i-1]-'0';
            int index,hindex;
            for(int i=0; i<x; i++){
                index = x-i-1;
                if ((x_array[index])>=(y_array[index]))
                    res[index] =  x_array[index] - y_array[index];
                else{
                    for (int i=1; ;i++){
                        if (x_array[index-i]>0){
                            hindex = index-i;
                            x_array[hindex] -= 1;
                            break;}
                    }
                    for (int i=1; ;i++){
                        if (hindex+i<index)
                            x_array[hindex+i] = 9;
                        else if ((hindex+i)== index){
                            x_array[index] += 10;
                            break;}
                    }
                    res[index] =  x_array[index] - y_array[index];
                }
            }
            if (tmp.flag=='+'){
                int sp=-1;
                for(int i=0;i<res_len ;i++){
                        if (res[i] > 0){
                            tmp.str = (char)(res[i]+48);
                            sp = i;
                            break;}
                }
                if (sp==-1){
                    tmp.str = '0';
                }
                else{
                    for (int i=sp+1; i<res_len; i++)
                        (tmp.str).push_back((char)(res[i]+48));
                }
                tmp.num_len = (tmp.str).length();
                delete[] res;
                delete[] x_array;
                delete[] y_array;
                return tmp;}
            else{
                int sp=-1;
                for(int i=0; i<res_len;i++){
                        if (res[i] > 0){
                            tmp.str = '-';
                            (tmp.str).push_back((char)(res[i]+48));
                            sp = i;
                            break;}
                }
                if (sp==-1){
                    tmp.str = '0';
                    tmp.flag = '+';
                }
                else{
                    for (int i=sp+1; i<res_len; i++)
                        (tmp.str).push_back((char)(res[i]+48));
                }
                tmp.num_len = (tmp.str).length() - 1;
                delete[] res;
                delete[] x_array;
                delete[] y_array;
                return tmp;}
        }
    }
    BigNum& operator-=(string s){
        BigNum tmp1, tmp2;
        int s_size = s.length();
        if (s[0]=='+'){
            tmp1.flag = '-';
            tmp1.str = '-';
            for(int i=1; i<s_size; i++)
                (tmp1.str).push_back(s[i]);
            tmp1.num_len = s.length()-1;
        }
        else if (s[0]=='-'){
            tmp1.flag = '+';
            tmp1.str = s[1];
            for(int i=2; i<s_size; i++)
                (tmp1.str).push_back(s[i]);
            tmp1.num_len = s.length()-1;
        }
        else{
            tmp1.flag = '-';
            tmp1.str = '-';
            for(int i=0; i<s_size; i++)
                (tmp1.str).push_back(s[i]);
            tmp1.num_len = s.length();
        }
        *this = *this + tmp1;

        return *this;
    }
};

std::ostream& operator<<(std::ostream& s, BigNum& num){
    s << num.str;
    return s;
}

template<typename T>
void bubble_sort(T arrey[], int array_size);

int main()
{
    BigNum x[5] = {BigNum("432"), BigNum("-12"), BigNum("-543"), BigNum("12"), BigNum("10")};
    //double x[5] = {432, -12.1, -543.2, 12.3, 10.4};
    //int x[5] = {432, -12, -543, 12, 10};
    bubble_sort(x, 5);
    for (int i=0; i<5; i++)
        cout << x[i] << endl;
    return 0;
}


template<typename T>
void bubble_sort(T arrey[], int array_size){
        for (int pass=1; pass<array_size; pass++) {
        for (int i=0; i<array_size-1; i++) {
            if (arrey[i] > arrey[i+1]) {
                T hold = arrey[i];
                arrey[i] = arrey[i+1];
                arrey[i+1] = hold;
            }
        }
    }
}
