#include "merge.h"
#include <future>

void Merge::MergeSort(int *arr, long first, long last, size_t thCoef)
{
  if (first >= last)
    return;
  long average = (last + first - 1) / 2;
  if (static_cast<unsigned long long>(last) - first >= thCoef && useThreads)
  {
    auto f1 = std::async(std::launch::async, [&] () 
      {MergeSort(arr, first, average, thCoef); });
    auto f2 = std::async(std::launch::async, [&] () 
      {MergeSort(arr, average + 1, last, thCoef); });
  }
  else
  {
    MergeSort(arr, first, average, thCoef);
    MergeSort(arr, average + 1, last, thCoef);
  }
  Merger(arr, first, average, last);
}

void Merge::Merger(int *arr, long first, long average, 
  long last)
{
  long nLeft = average - first + 1;
  long nRight = last - average;
  int *arrLeft = new int[nLeft] {};
  int *arrRight = new int[nRight] {};
  for (long i = 0; i < nLeft; ++i)
    arrLeft[i] = arr[first + i];
  for (long j = 0; j < nRight; ++j)
    arrRight[j] = arr[average + 1 + j];
  long i = 0, j = 0;
  long k = first;
  while (i < nLeft && j < nRight) 
    if (arrLeft[i] <= arrRight[j]) 
      arr[k++] = arrLeft[i++];
    else
      arr[k++] = arrRight[j++];
  while (i < nLeft) 
    arr[k++] = arrLeft[i++];
  while (j < nRight) 
    arr[k++] = arrRight[j++];
  delete[]arrLeft;
  delete[]arrRight;
}
