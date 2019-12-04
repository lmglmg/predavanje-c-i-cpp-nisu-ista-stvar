---
marp: true
theme: gaia
backgroundColor: black
color: white
paginate: false
style: |
    p {
        font-family: 'Avenir Next';
        font-size: x-large;
    }
    a {
        color: white;
        font-size: x-large;
    }
    h1, h3, h4, h5, h6 {
        color: #48b2e8;
        font-family: 'Avenir Next';
        font-weight: 600;
    }
    h2 {
        color: #48b2e8;
        font-family: 'Avenir Next';
        font-weight: 400;
    }
    code, code[class*='language'] {
        background: #222;
        font-family: 'Fira Code';
        font-size: large;
    }
    section.lead h2 {
        color: #48b2e8;
        text-align: left;
        font-size: x-large;

        position: relative;
        top: 6em
    }
    section.lead h3 {
        color: #48b2e8;
        text-align: right;
        font-size: xx-large;

        position: relative;
        top: 2em
    }
    section>table {
        font-family: 'Avenir Next';
        font-size: x-large;
    }
---

<!-- _class: lead -->

# C i C++ nisu ista stvar

## Luka Mate Granić
## C++ software developer @ Microblink

---

<!-- paginate: true -->

## Zašto ovo predavanje?

- "C/C++"
- Predrasude [FILL]

---

## C++

- "C++ is a general-purpose programming language emphasizing the design and use of type-rich,lightweight  abstractions."
  - _The C++ Programming Language (4th Edition) - Bjarne Stroustrup_
- Zero-overhead principle
  - "What you don’t use, you don’t pay for. And further: What you do use, you couldn’t hand code any better."

---

## Primjer 1

```txt
zapamtiti trenutak
spavanje 100 milisekundi
zapamtiti trenutak
prikazati provedeno vrijeme u sekundama
```

---

## Usporedba: kôd

__C__
```c
usleep( 100  * SECONDS_TO_MICROSECONDS / SECONDS_TO_MILLISECONDS );
// ...
float seconds = ( t2.tv_sec - t1.tv_sec ) + ( float )( t2.tv_nsec - t1.tv_nsec ) / SECONDS_TO_NANOSECONDS;
```
__C++__
```cpp
std::this_thread::sleep_for( milliseconds( 100 ) );
// ...
float seconds = duration_cast< duration< float, seconds::period > >( end - start ).count();
```

---

## Usporedba: kôd

__C 1__
```c
typedef long long milliseconds;
typedef long long nanoseconds;
//...
milliseconds total_time = time1 + time2;
```

---

## Usporedba: kôd

```c
typedef struct { long long value; } Milliseconds;
Milliseconds add_milliseconds(Milliseconds a, Milliseconds b) {
    Milliseconds r = { .value = a.value + b.value };
    return r;
}
typedef struct { long long value; } Nanoseconds;
Nanoseconds add_nanoseconds(Nanoseconds a, Nanoseconds b) {
    Nanoseconds r = { .value = a.value + b.value };
    return r;
}
// ...
add_milliseconds(t1, t2);
// passing 'Nanoseconds' to parameter of incompatible type 'Milliseconds'
```

https://godbolt.org/z/EufDY-

---

## Usporedba: kôd

__C++__
```cpp
milliseconds time1;
nanoseconds time2;
// ...
milliseconds total_tome = time1 + time2;
// no viable conversion from 'duration<[...], ratio<[...], 1000000000>>'
// to
// 'duration<[...], ratio<[...], 1000>>
```

https://godbolt.org/z/ej-EXR

---

## Usporedba: strojni kôd

```cpp
#include <chrono>
using namespace std::chrono;
using TP = high_resolution_clock::time_point;
float convert( TP const a,TP const b ) {
    return duration_cast< duration< float, seconds::period > >( a - b ).count();
}
```

```masm
.LCPI0_0:
        .long   1315859240              # float 1.0E+9
convert(..., ...)
        sub     rdi, rsi
        cvtsi2ss        xmm0, rdi
        divss   xmm0, dword ptr [rip + .LCPI0_0]
        ret
```

https://godbolt.org/z/xnDcxg

---

## Usporedba: strojni kôd
- Veličina strukture
  - https://godbolt.org/z/bNA2Z5

---

## Primjer 2

```txt
generiraj niz nasumičnih brojeva
izmjeri vrijeme
sortiraj niz
izmjeri vrijeme
provjeri da je niz sortiran
prikaži vrijeme
```

---

## Usporedba: kôd

__C__

```c
int intLess( void const * a, void const * b )
{
    int const ia = * ( int const * )( a );
    int const ib = * ( int const * )( b );
    return ia - ib;
}
// ...
qsort( arr, ARRAY_SIZE, sizeof( int ), intLess );
```

__C++__

```cpp
std::sort( begin( v ), end( v ), []( int const a, int const b ){ return a < b; } );
```

---

## Usporedba: performanse

| | Vrijeme (veliki raspon \*\*) [ms] | Vrijeme (mali raspon \*\*\*) [ms] |
|:-- | --: | --: |
| qsort | 1199 | 628 |
| std::sort | 764 | 415 |
| quick_sort\* | 799 | 412 |

Sistem: Intel Core i7 (I7-8850H), 256 GiB RAM

_\* vlastita implementacija_
_\*\* veliki raspon: (-1e6, 1e6)_
_\*\*\* mali raspon: (-1e3, 1e3)_

---

## Zaključak

- Izbjegavanje indirekcije
  - Metoda usporedbe se ekpandira na mjestu poziva
- Dupliciranje strojnog koda
- Ograničenje jezika a ne algoritma
- Jasan kôd bez degradacije performansi

---

## STL algorithmi

all_of, any_of, none_of, for_each, for_each_n, count, count_if, mismatch, find, find_if, find_if_not, find_end, find_first_of, adjacent_find, search, search_n, copy, copy_if, copy_n, copy_backward, move, move_backward, fill, fill_n, transform, generate, generate_n, remove, remove_if, remove_copy, remove_copy_if, replace, replace_if, replace_copy, replace_copy_if, swap, swap_ranges, iter_swap, reverse, reverse_copy, rotate, rotate_copy, shift_left, shift_right, shuffle, sample, unique, unique_copy, is_partitioned, partition, partition_copy, stable_partition, partition_point, is_sorted, is_sorted_until, sort, partial_sort, partial_sort_copy, stable_sort, nth_element, lower_bound, upper_bound, binary_search, equal_range, merge, inplace_merge, includes, set_difference, set_intersection, set_symmetric_difference, set_union, is_heap, is_heap_until, make_heap, push_heap, pop_heap, sort_heap, max, max_element, min, min_element, minmax, minmax_element, clamp, equal, lexicographical_compare, lexicographical_compare_three_way, is_permutation, next_permutation, prev_permutation, iota, accumulate, inner_product, adjacent_difference, partial_sum, reduce, exclusive_scan, inclusive_scan, transform_reduce, transform_exclusive_scan, transform_inclusive_scan

---

# Pauza

---

## Primjer 3

---

<!-- _class: lead -->

# Hvala!

---

## Izvori

- https://en.cppreference.com/w/cpp/algorithm
