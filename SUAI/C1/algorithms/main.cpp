#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

void reverse_c_string(char *str) {
  char *end = str;
  char tmp;
  if (str) {
    while (*end) {
      ++end;
    }
    --end;
    while (str < end) {
      tmp = *str;
      *str++ = *end;
      *end-- = tmp;
    }
  }
}

void turn90(int** matr, int n) {
    int tmp;
    for (int i = 0; i < n / 2; i++) {
      for (int j = i; j < n - 1 - i; j++) {
        tmp = matr[i][j];
        matr[i][j] = matr[n - j - 1][i];
        matr[n - j - 1][i] = matr[n - i - 1][n - j - 1];
        matr[n - i - 1][n - j - 1] = matr[j][n - i - 1];
        matr[j][n - i - 1] = tmp;
      }
    }
}

struct list_node {
    int data;
    list_node* next;
};

void push(list_node* start, int data){
    list_node* newnode = new list_node;
    newnode->data = data;

    while(start->next){
        start++;
    }
    start->next = newnode;
}

int list_to_num (list_node* list){
    list_node* tmp = list;
    int size = 1;
    while(tmp->next) {
        size++;
        tmp = tmp->next;
    }
    tmp = list;
    int sum = 0;
    for(int i = size - 1; i >= 0; --i){
        sum += tmp->data * pow(10, size - i - 1);
        tmp = tmp->next;
    }
    return sum;
}

list_node* num_to_list(int num){
    char buff[100];
    sprintf(buff, "%i", num);
    string line = buff;
    int size = line.length();

    list_node* tmp = new list_node;
    list_node* root_node = tmp;

    for(int i = size-1; i >= 0; --i){
        string part;
        part.push_back(line.at(i));
        tmp->data = atoi(part.c_str());
        if(i > 0){
            tmp->next = new list_node;
            tmp = tmp->next;
        }
    }

    return root_node;
}

void list_ariphmetics() {
    list_node* list1 = new list_node;
    list1->data = 5;
    push(list1, 9);
    push(list1, 2);

    list_node* list2 = new list_node;
    list2->data = 3;
    push(list2, 1);
    push(list2, 5);

    int num1 = list_to_num(list1);
    int num2 = list_to_num(list2);

    int sum = num1 + num2;

    list_node *result = num_to_list(sum);

    int res =  list_to_num(result);

    printf("%i + %i = %i\n", num1, num2, res);
}

int main() {
    std::vector<int> v;
    srand(clock());
    for (int i = 0; i < 15; i++){
        v.push_back(rand() % 20);
        cout << v[i] << " ";
    }
    std::sort(v.begin(), v.end());

    cout << endl;
    for (int i = 0; i < 15; i++){
        cout << v[i] << " ";
    }

    return 0;
}
