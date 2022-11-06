/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedQueue.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedQueue<T>::LinkedQueue() {
  this->Queue_list = new STLList<T>();
}

template <typename T> LinkedQueue<T>::~LinkedQueue() {
  delete this->Queue_list;
}

template <typename T> int LinkedQueue<T>::getSize() {
  return this->Queue_list->getSize();
}

template <typename T> bool LinkedQueue<T>::isEmpty() {
  return this->Queue_list->isEmpty();
}

template <typename T> T LinkedQueue<T>::peek() {
  if (this->Queue_list->isEmpty()) {
    throw runtime_error("Queue is empty!");
  } else{
    return this->Queue_list->getFirst();
  }
}

template <typename T> void LinkedQueue<T>::enqueue(T element) {
  this->Queue_list->insertLast(element);
}

template <typename T> T LinkedQueue<T>::dequeue() {
  return this->Queue_list->removeFirst();
}

template <typename T> void LinkedQueue<T>::insert(T element) {
  this->enqueue(element);
}

template <typename T> T LinkedQueue<T>::remove() {
  return this->dequeue();
}

