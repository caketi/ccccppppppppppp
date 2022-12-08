#include <iostream>

using namespace std;
struct Array {

  static int length;
  int size;
  int a[199999];
};

void Display(struct Array arr) {
  int i;
  printf("\nElements are \n");
  for (i = 0; i < arr.length; i++) {
    printf("%d ", arr.a[i]);
  }
}
void Append(struct Array *arr, int x) {
  if (arr->length < arr->size) {
    arr->a[arr->length++] = x;
  }
}
void Insert(struct Array *arr, int index, int x) {
  int i;
  if (index >= 0 && index <= arr->length) {
    for (i = arr->length; i > index; i--) {
      arr->a[i] = arr->a[i - 1];
    }
    arr->a[index] = x;
    arr->length++;
  }
}
int Delete(struct Array *arr, int index) {
  int x = 0;
  if (index >= 0 && index < arr->length) {
    x = arr->a[index];
    for (int i = index; i < arr->length - 1; i++) {
      arr->a[i] = arr->a[i + 1];
    }
    arr->length--;
    return x;
  }
  return 0;
}
void swap(int *x, int *y) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

int LinearSearch(struct Array *arr, int key) {
  int i;
  for (i = 0; i < arr->length; i++) {
    if (key == arr->a[i]) {
      swap(&arr->a[i], &arr->a[i - 1]);
      return i;
    }
  }
  return -1;
}
