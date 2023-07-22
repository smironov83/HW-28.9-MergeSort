#include <iostream>
#include <iomanip>
#include <thread>
#include "merge.h"

long const arrSize = 10000000;
size_t const thQuant = 20;
size_t const thCoef = arrSize / thQuant;

void CreateArray(int *arr, long partBeg, long partEnd)
{
  srand((unsigned int) time(NULL) + partBeg);
  for (long i = partBeg; i < partEnd; ++i)
    arr[i] = static_cast<int>(rand() % 10000);
}

auto main() -> int
{
  system("chcp 1251");
  system("cls");
  std::cout<<std::setiosflags(std::ios::left);
  int *arr = new int[arrSize] {};
  std::thread threads[thQuant] {};
  for (size_t i = 0; i < thQuant; ++i)
    threads[i] = std::thread(CreateArray, std::ref(arr), arrSize / 
      thQuant * i, arrSize / thQuant * (i + 1));
  for (auto &th : threads)
    if (th.joinable())
      th.join();
  //std::cout << "Несортированный массив:" << std::endl;
  //for (long i = 0; i < arrSize; ++i)
    //std::cout << std::setw(5) << arr[i];
  //std::cout << std::endl;
  //system("pause");
  int *arrCopy = new int[arrSize] {};
  for (size_t i = 0; i < arrSize; ++i)
    arrCopy[i] = arr[i];
  Merge merge;
  auto timeStart = std::chrono::system_clock::now();
  merge.MergeSort(arr, 0, arrSize - 1, thCoef);
  auto timeFinish = std::chrono::system_clock::now();
  auto timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>
    (timeFinish - timeStart).count();
  //std::cout << std::endl;
  //std::cout << std::endl << "Отсортированный массив:" << std::endl;
  //for (long i = 0; i < arrSize; ++i)
    //std::cout << std::setw(5) << arr[i];
  //std::cout << std::endl;
  std::cout << "Сортировка в однопоточном режиме выполнена за " << timeSpent
    << " мс." << std::endl;
  delete[]arr;
  //system("pause");
  merge.useThreads = true;
  timeStart = std::chrono::system_clock::now();
  merge.MergeSort(arrCopy, 0, arrSize - 1, thCoef);
  timeFinish = std::chrono::system_clock::now();
  timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>
    (timeFinish - timeStart).count();
  //std::cout << std::endl;
  //std::cout << std::endl << "Отсортированный массив:" << std::endl;
  //for (long i = 0; i < arrSize; ++i)
    //std::cout << std::setw(5) << arrCopy[i];
  //std::cout << std::endl;
  std::cout << "Сортировка во многопоточном режиме выполнена за " << timeSpent
    << " мс." << std::endl;
  delete[]arrCopy;
  return 0;
}