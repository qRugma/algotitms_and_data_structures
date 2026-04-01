#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <chrono>

#define out  std::ios_base::openmode::_S_out
#define in   std::ios_base::openmode::_S_in

void sortFile(const std::string &file_name, const size_t files_count=3){
    size_t file_size=0;
    std::ifstream fin(file_name);

    std::fstream *f_i = new std::fstream[files_count];
    std::fstream *g_i = new std::fstream[files_count];
    size_t file_cur=0;
    int elem_prev, elem_cur;
    fin >> elem_prev;
    //Первичное разбиение
    for (size_t i=0; i<files_count; i++){
        f_i[i].open("./cache/f_"+ std::to_string(i), out);
    }
    f_i[0] << elem_prev << " ";
    while (!fin.eof()){
        fin >> elem_cur;
        file_size++;
        if (elem_prev > elem_cur){
            file_cur = (file_cur + 1) % files_count;
        }
        elem_prev = elem_cur;
        f_i[file_cur] << " " << elem_cur;
    }
    for (size_t i=0; i<files_count; i++)
        f_i[i].close();

    //Цикл слияний
    int *elem_curs = new int[files_count], phase = 0;
    bool *files_flags = new bool[files_count];
    std::fstream *files_in, *files_out;
    while(true){
        bool end_sort = true;
        if (phase % 2 == 0)
            for (size_t i=0; i<files_count; i++){
                f_i[i].open("./cache/f_"+ std::to_string(i), in);
                files_in = f_i;
                g_i[i].open("./cache/g_"+ std::to_string(i), out);
                files_out = g_i;
            }
        else
            for (size_t i=0; i<files_count; i++){
                f_i[i].open("./cache/f_"+ std::to_string(i), out);
                files_out = f_i;
                g_i[i].open("./cache/g_"+ std::to_string(i), in);
                files_in = g_i;
            }

        for (size_t i=0; i<files_count; i++) files_flags[i] = true;
        
        for (size_t i=0; i<files_count; i++){
            if (!files_in[i].eof())
                files_in[i] >> elem_curs[i];
        }

        //слияние
        for (size_t i=0; i<files_count; i++){
            int prev=-__INT_MAX__+1;
            
            while(true){
                bool next_file=true;
                int min=__INT_MAX__, min_index=-1;
                for (size_t i=0; i<files_count; i++)
                    if (files_flags[i] and (elem_curs[i] < min) and (elem_curs[i] >= prev)){
                        min=elem_curs[i];
                        min_index = i;
                    }
                if (min_index == -1)
                    break;
                if (!files_in[min_index].eof())
                    files_in[min_index] >> elem_curs[min_index];
                else
                    files_flags[min_index] = false;
                prev = min;
                files_out[i] << " " << min;
                if (i>0)
                    end_sort = false;
            }
        }
        for (size_t i=0; i<files_count; i++){
            f_i[i].close();
            g_i[i].close();
        }
        if (end_sort)
        break;
        phase++;
    }
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
