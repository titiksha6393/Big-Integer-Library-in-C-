#pragma once
#include<string>

class bigInteger{
    public:
        std::string curr;
        bool negative=false;
        bigInteger();
        bigInteger(std::string& str);
        bigInteger(const char* ch);
        bigInteger(int n);
        bigInteger(long long n);
        // bigInteger(long long n){ curr=std::to_string(n); }
        void push_back(char ch);
        void push_back(std::string& str);
        void operator=(std::string& str);
        void operator=(int n);
        char& operator[](int i);
        int size();
        void reverse();
        bigInteger operator /(bigInteger&div);
        bigInteger operator %(bigInteger& b);
        bigInteger operator *(bigInteger& b);
        bigInteger operator +(bigInteger& b);
        bigInteger operator -(bigInteger& b);
        bigInteger& operator +=(bigInteger& b);
        bigInteger& operator -=(bigInteger& b);
        bigInteger& operator *=(bigInteger& b);
        bigInteger& operator /=(bigInteger& b);
        bigInteger& operator %=(bigInteger& b);
        bool operator ==(bigInteger&b);
        bool operator >(bigInteger&b);
        bool operator >=(bigInteger&b);
        bool operator <(bigInteger&b);
        bool operator <=(bigInteger&b);
        bool operator !=(bigInteger&b);
        void validate();
    private:
        void addAB(bigInteger&a, bigInteger&b);
        void subAB(bigInteger&a, bigInteger&b);
        void subBA(bigInteger&a, bigInteger&b);
};
std::ostream& operator <<(std::ostream& os,bigInteger a);
