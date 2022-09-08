#include<iostream>
#include "bigInteger.h"

bigInteger::bigInteger(){ curr="0"; validate(); }
bigInteger::bigInteger(std::string& str){ curr=str; validate(); }
bigInteger::bigInteger(const char* ch){ curr=ch; validate(); }
bigInteger::bigInteger(int n){
    if(n<0){
        negative=true;
        n*=-1;
    }
    curr=std::to_string(n);
}
bigInteger::bigInteger(long long n){
    if(n<0){
        negative=true;
        n*=-1;
    }
    curr=std::to_string(n);
}
void bigInteger::push_back(char ch){ curr+=ch; }
void bigInteger::push_back(std::string& str){ curr+=str; }
void bigInteger::operator=(std::string& str){ curr=str; validate(); }
void bigInteger::operator=(int n){ curr=std::to_string(n); validate(); }
char& bigInteger::operator[](int i){ return curr[i]; }
int bigInteger::size(){ return curr.size(); }
void bigInteger::reverse(){
    for(int i=0;i<curr.size()/2;i++)
        std::swap(curr[i],curr[curr.size()-i-1]);
}
//COMPARISON OPERATORS
bool bigInteger::operator ==(bigInteger&b){
    if(curr[0]=='0'&&b[0]=='0'&&curr.size()==1&&b.size()==1)
        return true;
    if(negative!=b.negative||curr.size()!=b.size())
        return false;
    for(int i=0;i<curr.size();i++){
        if(curr[i]!=b[i])
            return false;
    }
    return true;
}
bool bigInteger::operator >(bigInteger&b){
    if(!b.negative&&negative)
        return false;
    if(!negative&&b.negative)
        return true;
    if(curr.size()>b.size()){
        if(negative&&b.negative)
            return false;
        return true;
    }
    if(curr.size()<b.size()){
        if(negative&&b.negative)
            return true;
        return false;
    }
    bool ab=false,ba=false;
    for(int i=0;i<curr.size();i++){
        if(curr[i]>b[i]){
            ab=true;
            break;
        }
        if(curr[i]<b[i]){
            ba=true;
            break;
        }
    }
    if(ab){
        if(negative&&b.negative)
            return false;
        return true;
    }
    if(ba){
        if(negative&&b.negative)
            return true;
        return false;
    }
    return false;
}
bool bigInteger::operator >=(bigInteger&b){
    if(*this==b||*this>b)
        return true;
    return false;
}
bool bigInteger::operator <(bigInteger&b){
    if(*this>=b)
        return false;
    return true;
}
bool bigInteger::operator <=(bigInteger&b){
    if(*this>b)
        return false;
    return true;
}
bool bigInteger::operator !=(bigInteger&b){
    if(*this==b)
        return false;
    return true;
}
//ARITHEMATIC OPERATORS
bigInteger& bigInteger::operator +=(bigInteger&b){
    if(negative){
        if(b.negative){
            addAB(*this,b);
        }
        else{
            if((curr).size()>(b.curr).size()||((curr).size()==(b.curr).size()&&curr>b.curr)){
                subAB(*this,b);
            }
            else{
                subBA(*this,b);
                negative=false;
            }
        }
    }
    else{
        if(b.negative){
            if((curr).size()>(b.curr).size()||((curr).size()==(b.curr).size()&&curr>b.curr)){
                subAB(*this,b);
            }
            else{
                subBA(*this,b);
                negative=true;
            }
        }
        else{
            addAB(*this,b);
        }
    }
    validate();
}
bigInteger& bigInteger::operator -=(bigInteger&b){
    if(b.negative)
        b.negative=false;
    else
        b.negative=true;
    *this+=b;
    if(b.negative)
        b.negative=false;
    else
        b.negative=true;
}
bigInteger& bigInteger::operator *=(bigInteger&b){
    bigInteger ans=(*this)*b;
    *this=ans;
}
bigInteger& bigInteger::operator /=(bigInteger&b){
    (*this)=(*this)/b;
}
bigInteger& bigInteger::operator %=(bigInteger&b){
    *this=(*this)%b;
}
bigInteger bigInteger::operator +(bigInteger& b){
    bigInteger ans;
    ans+=(*this);
    ans+=b;
    return ans;
}
bigInteger bigInteger::operator -(bigInteger& b){
    bigInteger ans;
    ans+=(*this);
    ans-=b;
    return ans;
}
bigInteger bigInteger::operator *(bigInteger&b){
    bigInteger ans;
    if((curr[0]=='0'&&curr.size()==1)||(b[0]=='0'&&b.size()==1)){
        ans.curr="0";
        ans.negative=false;
        return ans;
    }
    if(negative!=b.negative)
        ans.negative=true;
    else
        ans.negative=false;
    for(int i=curr.size()-1,x=0;i>=0;i--,x++){
        int carry=0,ansCarry=0;
        for(int j=b.size()-1,y=0;j>=0;j--,y++){
            carry+=(b[j]-'0')*(curr[i]-'0');
            if(x+y<ans.size()){
                ansCarry+=(ans[x+y]-'0')+(carry%10);
                ans[x+y]=(char)(ansCarry%10 + '0');
            }
            else{
                ansCarry+=carry%10;
                ans.push_back((char)(ansCarry%10 + '0'));
            }
            ansCarry/=10;
            carry/=10;
        }
        if(carry>0)
            ansCarry+=carry;
        if(ansCarry>0)
            ans.push_back((char)(ansCarry+'0'));
    }
    ans.reverse();
    return ans;
}
bigInteger bigInteger::operator /(bigInteger&div){
    bigInteger ans,b;
    b.curr=div.curr;
    if(b[0]=='0'&&b.size()==1){
        ans.curr="0";
        return ans;
    }
    if(curr[0]=='0'&&curr.size()==1){
        return ans;
    }
    ans.curr="";
    bigInteger d;
    for(int i=0;i<b.size()-1;i++)
        d.push_back(curr[i]);
    for(int i=b.size()-1;i<curr.size();i++){
        d.push_back(curr[i]);
        d.validate();
        bigInteger diff;
        int l=0,r=9,x=0;
        while(l<=r){
            bigInteger mid=(l+r)/2;
            mid*=b;
            if(mid<=d){
                x=(l+r)/2;
                l=x+1;
                diff=mid;
            }
            else
                r=(l+r)/2 - 1;
        }
        ans.push_back((char)(x+'0'));
        d-=diff;
    }
    ans.validate();
    if(negative&&div.negative)
        ans.negative=false;
    else if(negative||div.negative)
        ans.negative=true;
    return ans;
}
bigInteger bigInteger::operator %(bigInteger&b){
    bigInteger quotient= (*this)/b;
    quotient*=b;
    return (*this)-quotient;
}
//OVERLOADING COUT OPERATOR
std::ostream& operator <<(std::ostream& os,bigInteger a){
    if(a.negative)
        os<<'-';
    os<<a.curr;
    return os;
}
//NECESSARY METHOD DEFINITION
void bigInteger::validate(){
    if(curr.size()==0){
        curr="0";
        negative=false;
    }
    if(curr[0]=='-')
        negative=true;
    int i=0;
    if(curr[0]=='-'||curr[0]=='+')
        i=1;
    while(i<curr.size()&&curr[i]=='0')
        i++;
    if(i==curr.size()){
        curr="0";
        negative=false;
        i=0;
    }
    int j=i;
    while(i<curr.size()&&curr[i]>='0'&&curr[i]<='9')
        i++;
    if(i==curr.size())
        i--;
    curr=curr.substr(j,i-j+1);
}
void bigInteger::addAB(bigInteger&a, bigInteger&b){
    a.reverse(); b.reverse();
    int i=0,carry=0;
    for(;i<a.size()&&i<b.size();i++){
        carry=(a[i]-'0')+(b[i]-'0')+carry;
        a[i]=(char)(carry%10 + '0');
        carry/=10;
    }
    while(i<a.size()){
        carry=(a[i]-'0')+carry;
        a[i]=(char)(carry%10 + '0');
        carry/=10;
        i++;
    }
    while(i<b.size()){
        carry=(b[i]-'0')+carry;
        a.push_back((char)(carry%10 + '0'));
        carry/=10;
        i++;
    }
    if(carry>0)
        a.push_back((char)(carry + '0'));
    a.reverse(); b.reverse();
}
void bigInteger::subAB(bigInteger&a, bigInteger&b){//Assuming a>=b
    a.reverse(); b.reverse();
    int i=0;
    bool carry=false;
    for(;i<b.size();i++){
        int A=(int)(a[i]-'0'), B=(int)(b[i]-'0');
        if(carry){
            carry=false;
            A--;
        }
        if(B>A){
            carry=true;
            A+=10;
        }
        a[i]=(char)((A-B)%10 + '0');
    }
    if(carry){
        while(a[i]=='0')
            i++;
        a[i]--;
    }
    a.reverse(); b.reverse();
    a.validate();
}
void bigInteger::subBA(bigInteger&a, bigInteger&b){//Assuming a<=b
    a.reverse(); b.reverse();
    int i=0;
    bool carry=false;
    for(;i<a.size();i++){
        int A=(int)(a[i]-'0'), B=(int)(b[i]-'0');
        if(carry){
            carry=false;
            B--;
        }
        if(A>B){
            carry=true;
            A+=10;
        }
        a[i]=(char)((B-A)%10 + '0');
    }
    for(int j=i;j<b.size();j++)
        a.push_back(b[i]);
    if(carry){
        while(a[i]=='0')
            i++;
        a[i]--;
    }
    a.reverse(); b.reverse();
    a.validate();
}
