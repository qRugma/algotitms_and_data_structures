#include <iostream>
#include <string>
#include <vector>

#define string std::wstring


int BM_search(string S, string P){
    int i, j, k, n=S.length(), m=P.length();

    std::vector<int> Alph(1200, m);
    for(int g=0; g<m-1; g++)
        Alph[P[g]] = m-1-g; 
    // for(int g=0; g<m; g++)
    //     std::wcout << Alph[P[g]];
    // std::wcout << std::endl;
    
    i = j = m-1;

    while(i < n and j >= 0){
        k = i; j = m-1;
        while(j>=0){
            if (S[k] == P[j]){
                j--; k--;
            } else {
                i = i + Alph[S[i]];
                j = m-1;
                break;
            }
        }
    }
    if (j>=0)
        return -1;
    return i + 1 - m;
}

std::vector<int> findAll(int s, int e, string S, string P){
    int i, j, k, n=S.length(), m=P.length();
    std::vector<int> answer;
    std::vector<int> Alph(1200, m);
    for(int g=0; g<m-1; g++)
        Alph[P[g]] = m-1-g; 
    // for(int g=0; g<m; g++)
    //     std::wcout << Alph[P[g]];
    // std::wcout << std::endl;
    
    i = s + m - 1;
    j = m-1;
    while (true){
        while(i < e and j >= 0){
            k = i; j = m-1;
            while(j>=0){
                if (S[k] == P[j]){
                    j--; k--;
                } else {
                    i = i + Alph[S[i]];
                    j = m-1;
                    break;
                }
            }
        }
        if (i > e)
            return answer;
        answer.push_back(i + 1 - m);
        i = i + Alph[S[i]];
        j = m-1;
    }
}


void autoTest(){
    string S1 = L"во дворе трава на траве дрова";
    string P1 = L"дрова";
    string S = L"std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    string P = L"tor";

    int Ianswer = BM_search(S1, P1);
    std::wcout << Ianswer << std::endl;
    for(int i=Ianswer; i<Ianswer+P1.length(); i++)
        std::wcout << S1[i];
    std::wcout << std::endl;

    std::wcout << "not in S: ";
    std::vector<int> answer = findAll(0, 91, S, L"stdasd");
    for(auto i : answer)
        std::wcout << i << L" ";
    std::wcout << std::endl;

    std::wcout << "0  91: ";
    answer = findAll(0, 91, S, P);
    for(auto i : answer)
        std::wcout << i << L" ";
    std::wcout << std::endl;
    
    
    std::wcout << "17 91: ";
    answer = findAll(17, 91, S, P);
    for(auto i : answer)
        std::wcout << i << L" ";
    std::wcout << std::endl;
    
    std::wcout << "28 36: ";
    answer = findAll(28, 36, S, P);
    for(auto i : answer)
        std::wcout << i << L" ";
    std::wcout << std::endl;

}


int main(){
    setlocale(LC_ALL,"");
    
    std::wstring S;
    std::wstring P;
    int choise;
    std::wcin >> choise;
    if (choise == 0){
        autoTest();
        return 0;
    }
    std::wcin.get();
    std::getline(std::wcin, S);
    std::getline(std::wcin, P);
    if (choise == 1){
        int Ianswer = BM_search(S, P);
        std::wcout << Ianswer << std::endl;
        for(int i=Ianswer; i<Ianswer+P.length(); i++)
            std::wcout << S[i];
        std::wcout << std::endl;
    }
    else if(choise == 2){
        int s, e;
        std::wcin >> s >> e;    
        std::vector<int> answer = findAll(s, e, S, P);
        for(auto i : answer)
            std::wcout << i << L" ";
        std::wcout << std::endl;
    }
    

}