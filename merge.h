#pragma once

struct Merge
{
  bool useThreads = false;
  Merge() = default;
  ~Merge() = default;
  void MergeSort(int *arr, long first, long last, size_t thCoef);
  void Merger(int *arr, long first, long average, 
    long last);
};