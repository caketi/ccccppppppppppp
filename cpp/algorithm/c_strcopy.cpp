#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <objidlbase.h>
#include <playsoundapi.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include <winnt.h>
using namespace std;

bool readBinFile(const char fileName[], char** bufPtr){
  if(FILE* fp = fopen(fileName, "rb")){
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    *bufPtr = new char[length + 1];
    fseek(fp, 0, SEEK_SET);
    fread(*bufPtr, sizeof(char), length, fp);
    return  true;
  }else{
    return false;
  }
}

int main(int argc, char** argv){
  char* buf;
  // if(!readBinFile(argv[1], &buf)){
  //   puts("failure to open COFF file.");
  //   return 0;
  // }
  readBinFile("test.o", &buf);
  IMAGE_FILE_HEADER* fileHdr = (IMAGE_FILE_HEADER*)buf;
  IMAGE_SECTION_HEADER* sectionHdr = (IMAGE_SECTION_HEADER*)(buf + sizeof(IMAGE_FILE_HEADER));
  for(int i = 0; i < (fileHdr->NumberOfSections); ++i){
    printf("%s: %p\n",
    sectionHdr[i].Name,
    sectionHdr[i].PointerToRawData);
  }

}

int strToInt(char *strNum) {
  int v = 0;
  while (*strNum) {
    v = (10 * v + *strNum++ - '0');
  }
  return v;
}

// The result of the postfix ++ operator is the value of the operand. As a side
// effect,the value of the operand object is incremented
void Mystrcpy(char *des, char *src) {
  assert(des != NULL && src != NULL);

  if (des == NULL || src == NULL) {
    return;
  }

  while (*src != '\0') {
    *des = *src;
    des++;
    src++;
  }
  *des = '\0';
}

void Mystrcpy1(char *des, char *src) {
  int i = 0;
  while (src[i] != '\0') {
    des[i] = src[i];
    ++i;
  }
  des[i] = '\0';
}

void Mystrcpy2(char *des, char *src) {
  int i = 0;
  while (*(src + i) != '\0') {
    *(des + i) = *(src + i);
    i++;
  }
  *(des + i) = '\0';
}

// 进阶三，利用符号优先级，*和++的优先级相同，且高于赋值。优先级相同时看结合性，*和++结合性自右向左，所以先++后解引用，但是后置++会先使用当前值再自加：
void Mystrcpy3(char *des, char *src) {

  while (*src != '\0') {
    *des++ = *src++;
  }
  *des = '\0';
}
// 利用字符串末尾带'/0'的特性
void Mystrcpy4(char *des, char *src) {
  while (*des++ == *src++)
    return;
}

int main1() {
  int i = 7;
  printf("%d\n", i++);
  printf("%d\n", i);
  char str2[10];
  char str3[] = "abcd";
  Mystrcpy4(str2, str3);
  printf("dest: str2=%s, source: str3=%s\n", str2, str3);

  return 0;
}

uint32_t reverseBits(uint32_t n) {
  uint32_t ret = 0;
  for (uint32_t i = 0, j = 1, k = (1 << 31); i < 32; i++, j <<= 1, k >>= 1) {
    if (n & j)
      ret |= k;
  }
  return ret;
}
int longestSubstring(string s, int k) {
  unordered_map<char, int> cnt;
  vector<int> splits;
  for (auto x : s)
    cnt[x] += 1;
  for (int i = 0; s[i]; ++i) {
    if (cnt[s[i]] < k)
      splits.push_back(i);
  }
  splits.push_back(s.size());
  if (splits.size() == 1)
    return s.size();
  int pre = 0, ans = 0;
  for (auto p : splits) {
    int len = p - pre;
    if (len >= k) {
      ans = max(ans, longestSubstring(s.substr(pre, len), k));
    }
    pre = p + 1;
  }
  return ans;
}

int myAtoi(string s) {
  int flag = 1, max_pre = INT32_MAX / 10, d = INT32_MAX % 10, ind = 0, num = 0;
  if (s[0] == '-')
    flag = -1, ind += 1;
  else if (s[0] == '+')
    ind += 1;
  for (; s[ind]; ++ind) {
    if (s[ind] < '0' || s[ind] > '9')
      break;
    if (num > max_pre || (num == max_pre && (s[ind] - '0') > d)) {
      if (flag > 0)
        return INT32_MAX;
      return INT32_MIN;
    }
    num = num * 10 + (s[ind] - '0');
  }
  return 0;
}