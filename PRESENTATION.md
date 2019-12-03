---
marp: true
theme: gaia
backgroundColor: black
color: white
paginate: false
style: |
    p {
        font-family: 'Avenir Next'
    }
    a {
        color: white
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
        font-size: xx-large;

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
---

<!-- _class: lead -->

# C i C++ nisu ista stvar

## Luka Mate Granić
## C++ senior developer @ Microblink

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

## Usporedba: Kôd

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

## Usporedba: Kôd

__C 1__
```c
typedef long long milliseconds;
typedef long long nanoseconds;
//...
milliseconds total_time = time1 + time2;
```

---

## Usporedba: Kôd

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

## Usporedba: Kôd

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

## Usporedba: Strojni kôd


- Veličina strukture
  - https://godbolt.org/z/bNA2Z5

---

## Usporedba: Strojni kôd


---