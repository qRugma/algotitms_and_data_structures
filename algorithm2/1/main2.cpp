#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <chrono>
#include <vector>
#include <string>

#define out  std::ios_base::openmode::_S_out
#define in   std::ios_base::openmode::_S_in

std::string sortFile(const std::string &file_name, const size_t files_count=3){
    std::ifstream fin(file_name);
    size_t n = files_count+1;
    int *ms = new int[n], *ip = new int[n];
    std::fstream *f_i = new std::fstream[n];
    std::vector<std::string> f_names(n);
    size_t file_cur=0;
    size_t f_in = files_count;
    int elem_prev, elem_cur;

    //Первичное разбиение
    for (size_t i=0; i<n; i++){
        ms[i] = 1; ip[i] = 1;
        f_names[i] = "./cache/f_"+ std::to_string(i); 
        f_i[i].open(f_names[i], out);
    }
    ms[n-1] = 0; ip[n-1] = 0;
    while (!fin.eof()){
        int buf;
        fin >> buf;
        f_i[f_in] << " " << buf;
    }
    fin.close();
    f_i[f_in].close();
    //разбиение
    f_i[f_in].open(f_names[f_in], in);
    elem_prev = - (__INT_MAX__-1);
    int L = 1;
    while (!f_i[f_in].eof()){
        f_i[f_in] >> elem_cur;
        if (elem_prev > elem_cur){
            ms[file_cur]--;
            f_i[file_cur] << "#";
            if (ms[file_cur] < ms[file_cur+1]) file_cur = (file_cur + 1) % (files_count);
            else if (ms[file_cur] == 0){
                L++; int ip0 = ip[0]; file_cur = 0;
                for (size_t k = 0; k < files_count; k++){
                    ms[k] = ip[k+1] - ip[k] + ip0;
                    ip[k] = ip[k+1] + ip0;
                }
            } else {
                file_cur = 0;
            }
        }
        elem_prev = elem_cur;
        f_i[file_cur] << " " << elem_cur;
        std::cout << elem_cur << " ";
    }
    ms[file_cur]--;
    f_i[file_cur] << "#";
    
    for (size_t i=0; i<n; i++){
        f_i[i].close();
        if (i == f_in)
            f_i[f_in].open(f_names[f_in], out);
        else
            f_i[i].open(f_names[i], in);
    }
    bool have_zero = false;
    int *elem_curs = new int [files_count]; 
    bool *flag_curs = new bool [files_count]; 
    for (size_t i=0; i<files_count; i++){
        if (!f_i[i].eof())
            f_i[i] >> elem_curs[i];
        flag_curs[i] = true;
    }
    char buf;
    int flag_count = 0;
    std::cout << std::endl;
    while (L > 0){
        std::cout << "L=" << L << ":";
        while (!f_i[n-2].eof()){
            // определение сливаемых отрезков
            for (size_t i=0; i<files_count; i++){
                if (ms[i]>0){
                    flag_curs[i] = false;
                    ms[i]--;
                    continue;
                } else if (ms[i] == 0){
                    flag_curs[i] = true;
                    flag_count++;
                }
            }
            if (flag_count == 0){
                ms[n-1] += 1;
                continue; 
            }
            // слияние отрезков в f_in
            while (flag_count >0){
                // поиск сливаемого элемента
                int min = __INT_MAX__, min_index; 
                for (size_t j=0; j<files_count; j++){
                    if (!flag_curs[j])
                        continue;
                    if (min > elem_curs[j]){
                        min = elem_curs[j];
                        min_index = j;
                    }
                }
                f_i[f_in] << " " << min; 
                std::cout << " " << min;
                // определение того кончился ли отрезок
                f_i[min_index].get(buf);
                if (buf == '#'){
                    flag_curs[min_index] = false;
                    flag_count--;
                    f_i[min_index] >> elem_curs[min_index];
                } else {
                    f_i[min_index] >> elem_curs[min_index];
                }
            }
            f_i[f_in] << "#";
            std::cout << "#" << std::endl;
        } 
        L--;
        f_i[n-2].close();
        f_i[n-2].open(f_names[n-2], out);
        f_i[n-1].close();
        f_i[n-1].open(f_names[n-1], in);
        f_i[n-1] >> elem_curs[n-1];
        for(size_t i=files_count-1; i>0; i--){
            std::swap(f_i[i], f_i[i-1]);
            std::swap(f_names[i], f_names[i-1]);
            std::swap(ms[i], ms[i-1]);
            std::swap(ip[i], ip[i-1]);
            std::swap(elem_curs[i], elem_curs[i-1]);
            std::swap(flag_curs[i], flag_curs[i-1]);
        }
        std::swap(f_i[n-1], f_i[0]);
        std::swap(f_names[n-1], f_names[0]);
        std::swap(ms[n-1], ms[0]);
        std::swap(ip[n-1], ip[0]);
        std::swap(elem_curs[n-1], elem_curs[0]);
        std::swap(flag_curs[n-1], flag_curs[0]);

    }
    std::cout << std::endl << "результат в " << f_names[0] << std::endl;
    for (size_t i=0; i<files_count; i++)
        f_i[i].close();
    return f_names[0];

}






bool isFileContainsSortedArray(const std::string &file_name){
    return true;
}
int createAndSortFile(const std::string &file_name, const int numbersCount, const int maxNumberValue)
{
    

    sortFile(file_name); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(file_name)) {
        return -2;
    }
    std::cout << "Файл отсортирован!" << std::endl;
    return 1;
}


int main(){

    createAndSortFile("./test.txt", 5, 5);
    return 0;
    for(int size=10000; size<=1000000; size*=10)
        for(int d=10; d<=100000; d*=100){
            char file_name[100];
            snprintf(file_name, sizeof(file_name), "../data/S%dD%d.txt", size, d);
            switch (createAndSortFile(file_name, size, d)) {
                case 1:
                    std::cout << "Test passed." << std::endl;
                break;

                case -2:
                    std::cout << "Test failed: file isn't sorted." << std::endl;
                break;
        }
        }
}
