// MyVector.h
#pragma once

#include <initializer_list>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>

template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    

    void reallocate(size_t new_cap); // 내부 재할당 도우미 함수

public:
    // 생성자, 소멸자
    MyVector(std::initializer_list<T> init);
    MyVector();
    ~MyVector();

    // 복사/이동 시맨틱 (R-A-I-I 규칙에 따라 명시적으로 선언)
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    // 1. 요소 추가 및 제거
    void push_back(const T& val);   // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void pop_back();                // Vector의 마지막 항목을 제거하는 함수 구현
    
    // 2. 접근
    size_t size() const;            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](size_t i) ;       // [] 연산자 구현
    const T& operator[](size_t i) const; 

    T& at(size_t i);                // at: 범위 체크 후, i번째 항목 접근 함수 구현
    const T& at(size_t i) const;    // const at

    T& front() ;                    // 첫번째 항목 리턴 함수 구현
    const T& front() const;         // const front

    T& back() ;                     // 마지막 항목 리턴 함수 구현
    const T& back() const;          // const back
    
    // 3. 크기 관련
    size_t capacity() const ;       // cap 값 리턴하는 함수 구현
    bool empty() const ;            // 현재 vector가 empty인지 확인하는 함수 구현
    
    // 4. 반복자 
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*() const; // 역참조 연산자 구현 

        Iterator& operator++();   // 전위 증가 연산자 구현
        Iterator operator++(int); // 후위 증가 연산자

        Iterator& operator--();   // 전위 감소 연산자 구현
        Iterator operator--(int); // 후위 감소 연산자

        Iterator operator+(difference_type n) const ;   // 산술 연산자 구현
        Iterator operator-(difference_type n) const ;   // 산술 연산자 구현

        Iterator& operator+=(difference_type n);
        Iterator& operator-=(difference_type n);

        bool operator==(const Iterator& other) const ;
        bool operator!=(const Iterator& other) const ;

        difference_type operator-(const Iterator& other) const ; // 거리 계산

        // 비교 연산자
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;

        friend class MyVector;
    };
    
    using reverse_iterator = std::reverse_iterator<Iterator>;

    // 순방향 반복자
    Iterator begin() ;
    Iterator end() ;
    const Iterator begin() const; 
    const Iterator end() const;   

    // 역방향 반복자 (예시 코드에서 사용됨)
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const reverse_iterator rbegin() const { return reverse_iterator(end()); }
    const reverse_iterator rend() const { return reverse_iterator(begin()); }


    // 5. 삽입/제거
    Iterator insert(Iterator pos, const T& value); // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator erase(Iterator pos);                  // erase: 지정 위치 요소 제거 함수 구현
    void clear() ;                                 // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)


    // 6. 비교 연산자
    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;
    bool operator<(const MyVector& other) const;
    bool operator>(const MyVector& other) const;
    bool operator<=(const MyVector& other) const;
    bool operator>=(const MyVector& other) const;
};