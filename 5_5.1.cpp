#include <locale.h>
#include <iostream>


int direct_search(const wchar_t *str, const int len_str, const wchar_t *sample, int len_sam){
    for(int i=0; i<len_str-len_sam; i++){
        for(int j=0; j<len_sam; j++){
            if (str[i+j]!=sample[j])
                break;
            else if (j==len_sam-1)
                return i;
        }
    }
    return -1;
}
int BM_find(const wchar_t *str, const int len_str, const wchar_t *sample, int len_sam){
    int TAB[1104]={0};
    for (int i=0; i<len_sam-1; i++){
        TAB[sample[i]] = -i-1;
    }
    // вывод таблицы сдвигов
    for (int i=0; i<len_sam; i++){
        printf("%lc %d ",sample[i], TAB[sample[i]]+len_sam);
    }
    for(int i=len_sam-1, j=len_sam-1, k=i;i<len_str;){
        k=i; j=len_sam-1;
        while(j>=0){
            printf("str:%lc sample:%lc\n", str[k], sample[j]);
            getchar();
            if (str[k] != sample[j]){
                i += (TAB[str[i]] + len_sam);
                break;
            }
            k--; j--;
        } if (j==-1){
            return k+1;
        }
    }

    return -1;
}

// int bin_search(int* nums, int len_nums, int target) {
//     int mid, index, left=0, right=len_nums-1;
//     while(left<=right){
//         index = left + (right - left)/2;
//         mid = nums[index];
//         if (mid==target)
//             return index;
//         else if (mid < target)
//             left=index+1;
//         else if (mid > target)
//             right=index-1;
//     }
//     return -1;
// }

int bin_search(int* nums, int len_nums, int target) {
    int mid, index, left=0, right=len_nums-1;
    while(left<right){
        index = left + (right - left)/2;
        mid = nums[index];
        if (target > mid)
            left=index+1;
        else 
            right=index;
    }
    if (nums[left]==target)
        return left;
    return -1;
}

int main(){
    setlocale(LC_ALL,"ru_RU.utf8");
    int nums[16]={1, 5, 9, 11, 16, 17, 20, 24, 30, 34, 43, 45, 49, 52, 57, 59}, len_nums = 16;
    // const wchar_t str[] = L"на дворе трава, на траве дрова", sample[] = L"траве";
    // int len_str=30, len_sam=5;
    const wchar_t str[] = L"privit", sample[] = L"ivi";
    int len_str=6, len_sam=3;
    int x = BM_find(str, len_str, sample, len_sam);
    int y = direct_search(str, len_str, sample, len_sam);
    printf("\nx=%d ", x);
    for(int i=x; i<x+len_sam; i++)
        printf("%lc", str[i]);
    printf("\n");
    printf("y=%d ", y);
    for(int i=y; i<y+len_sam; i++)
        printf("%lc", str[i]);

    int z = bin_search(nums, len_nums, 34);
    printf("\nz=%d target=%d", z, nums[z]);

}