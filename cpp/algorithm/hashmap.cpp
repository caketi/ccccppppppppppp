#include <stdio.h>
#include <string>
using namespace std;
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){}
};
int hash_func(int key, int table_len){
    return key % table_len;
}
void insert(ListNode *hash_table[], ListNode *node, int table_len){
    int hash_key = hash_func(node->val, table_len);
    node->next = hash_table[hash_key];
    hash_table[hash_key] = node;
}
bool search(ListNode* hash_table[], int value, int table_len){
    int hash_key = hash_func(value, table_len);
    ListNode *head = hash_table[hash_key];
    while(head){
        if(head->val == value){
            return true;
        }
        head=head->next;
    }
    return false;
}
int main(){
    // hash sort 哈希表的长度超过待排序元素的最大值，正整数
    int random[10] = {999, 1, 444, 7, 20,9,1,3,7,7};
    int hash_map[1000] = {0};
    for(int i = 0; i < 10; i++){
        hash_map[random[i]]++;
    }
    for(int i = 0; i <1000; i++){
        for(int j = 0; j < hash_map[i]; j++){
            printf("%d\n", i);
        }
    }
    int char_map[128] = {0};
    string str = "abcdefgaaCAKETIaketi";
    for (int i = 0; i < str.length(); i++){
        char_map[str[i]]++;
    }
    for(int i = 0; i < 128; i++){
        if(char_map[i] > 0){
            printf("[%c][%d] : %d\n", i, i, char_map[i]);
        }
    }
    return 0;
}