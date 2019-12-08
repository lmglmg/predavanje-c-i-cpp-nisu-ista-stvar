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
    li {
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
    section>image {
        font-family: 'Avenir Next';
        font-size: x-large;
    }
---

<!-- _class: lead -->

# C i C++ nisu ista stvar

## Luka Mate Granić
## C++ senior software developer @ Microblink

---

<!-- paginate: true -->

## Zašto ovo predavanje?

- "C/C++"
- Predrasude:
  - Prvo treba naučiti C a onda C++
  - C++ je objektno orijentiran jezik
  - Potreban je programski jezik niske razine da se ostvare dobre performanse

---

## C++

- "C++ is a general-purpose programming language emphasizing the design and use of type-rich, lightweight abstractions."
  - _The C++ Programming Language (4th Edition) - Bjarne Stroustrup_
- Zero-overhead principle
  - "What you don’t use, you don’t pay for. And further: What you do use, you couldn’t hand code any better." - _Foundations of C++, Bjarne Stroustrup_

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

__C 2__

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
- [Veličina strukture](https://godbolt.org/z/bNA2Z5)
  - timespec: 128 bitova
  - std::duration: u prinicpu proizvnoljna veličina
  - std::chrono::high_resolution_clock::duration: 64 bita

---

## Zaključak

- Apstrakcija iznad samo jednog broja
  - Jasno izražavanje namjere
  - Izbjegavanje grešaka
- Generirani strojni kôd je optimalan

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

Sistem: Intel Core i7 (I7-8850H), 16 GiB RAM

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

<!-- _class: lead -->

# Pauza

---

## Primjer 3

```txt
izračunati magnetsko polje idealnog Hertzovog dipola

prikazati to polje s ASCII znakovima
```

$$ H = \frac{ I_0 \Delta z }{ 4 \pi } \left( 1 + \frac{ 1 }{ j k r } \right) \frac{ e^{ - j k r } }{ r } sin( \Theta ) \pmb{ \hat{ \phi } } $$

---

## Postava

```c
#define TABLE_SIZE 50
typedef struct
{
    float data[ TABLE_SIZE ][ TABLE_SIZE ];
} FieldImage;
```

- Velika struktura ( 1kB )
- Pri računanju, možemo birati kut

---


## Ispis

```c
void printTable( FieldImage const * image )  // C
{
    if ( !image ) return;
    // ...
}
```

```cpp
void printTable( FieldImage const & image )  // C++
{
    // ...
}
```

- Nije moguće prikazati "prazni" parametar

---

## Povratna vrijednost: 1

```c
FieldImage const * generateImage_01()  // C
{
    // ...
}
```

```cpp
FieldImage const & generateImage_01()  // C++
{
    // ...
}
```

| const T * | const T & |
|---|---|
| nullptr ili vrijednost | vrijednost |

___

## Digresija

__Tony Hoare__ ([QCon London 2009](https://www.infoq.com/presentations/Null-References-The-Billion-Dollar-Mistake-Tony-Hoare/)): "I call it my billion-dollar mistake. It was the invention of the null reference in 1965. At that time, I was designing the first comprehensive type system for references in an object oriented language (ALGOL W). My goal was to ensure that all use of references should be absolutely safe, with checking performed automatically by the compiler. But I couldn't resist the temptation to put in a null reference, simply because it was so easy to implement. This has led to innumerable errors, vulnerabilities, and system crashes, which have probably caused a billion dollars of pain and damage in the last forty years."

---

## Povratna vrijednost: 2

```c
FieldImage * generateImage_02( float const rot )  // C
{
    // ...
}
// ...
FieldImage * image = generateImage_02( rot );
//...
free( image );
```

```cpp
std::unique_ptr< FieldImage > generateImage_02( float const rot ) {  // C++
    // ...
}
// ...
std::unique_ptr< FieldImage > = generateImage_02( rot );
```

- Jasna poruka da pozivatelju funkcije dajemo vlasništvo objekta.

---

## Povratna vrijednost: 3 [ C ]

```c
void generateImage_03( FieldImage * image, float const rot ) {
    // ...
}

void main_03() {
    FieldImage image;
    generateImage_03( &image, M_PI * 0.75f );
    printTable( &image );
}

void printAndClean( FieldImage * image ) {
    printTable( image );
    free( image );
}

void main_04() {
    FieldImage * image = malloc( sizeof( FieldImage ) );
    generateImage_03( image, M_PI );
    printAndClean( image );
}
```

---

## Povratna vrijednost: 3 [ C++ ]

```c
void generateImage_03( FieldImage & image, float const rot ) {
    // ...
}

void main_03() {
    FieldImage image;
    generateImage_03( image, M_PI * 0.75f );
    printTable( image );
}

void printAndClean( std::unique_ptr< FieldImage > image ) {
    printTable( *image );
}

void main_04() {
    std::unique_ptr< FieldImage > image = std::make_unique< FieldImage >();
    generateImage_03( *image, M_PI );
    printAndClean( std::move ( image ) );
}
```

---

## Zaključak

- Jasna komunikacija
  - Postoji li vrijednost?
  - Tko je vlasnik?
- Sigurno korištenje
  - Dvostruko oslobađanje memorije
  - Memory leak
- `unique_ptr` ima istu veličinu kao i normalni pokazivač
- `shared_ptr` i `weak_ptr`: Brojanje referenci

---

## Za kraj

- Apstraktni kôd bez gubitka performansi
- Velika standardna biblioteka
- Sigurnije upravljanje memorijom

___

<!-- _class: lead -->

# Hvala!

---

## Izvori

- [The C++ Programming Language (4th Edition), Bjarne Stroustrup](http://www.stroustrup.com/4th.html)
- https://en.cppreference.com/w/cpp/algorithm
- http://www.waves.utoronto.ca/prof/svhum/ece422/notes/05-dipole.pdf
- http://www.stroustrup.com/ETAPS-corrected-draft.pdf
- https://www.gnu.org/software/libc/manual/pdf/libc.pdf

---

## Zajednica u Zagrebu

- [Zagreb C/C++ User Group](https://www.meetup.com/Zagreb-C-C-User-Group/)
-  cpplang.slack.com \#ug-hr-zagreb
