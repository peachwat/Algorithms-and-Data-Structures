# Algorithms and Data Structures

Zbiór projektów zrealizowanych w ramach przedmiotu **Algorytmy i Struktury Danych**. Repozytorium zawiera implementacje zaawansowanych algorytmów obliczeniowych, analizę gier planszowych oraz narzędzia do teorii grafów.

> **Uwaga techniczna**: Zgodnie z wymaganiami projektowymi, wszystkie struktury danych (stosy, kolejki, wektory, listy) zostały zaimplementowane samodzielnie, bez użycia biblioteki standardowej STL.

---

## Projekt 1: Kalkulator ONP (Infix to Postfix)

Zaawansowany kalkulator liczb całkowitych obsługujący notację infiksową oraz konwersję do **Odwrotnej Notacji Polskiej (ONP)**.

### Funkcjonalności:
* **Konwersja i Obliczenia**: Obsługa priorytetów operatorów, nawiasów oraz funkcji matematycznych.
* **Własna Implementacja Stosu**: Silnik oparty na dynamicznej liście wiązanej (`Node.h`, `Stack.h`).
* **Obsługiwane Operacje**:
    * Podstawowe: `+`, `-`, `*`, `/` (dzielenie całkowitoliczbowe z obsługą błędu `ERROR` przy dzieleniu przez 0).
    * Funkcje logiczne: `IF(a, b, c)` (warunek a > 0).
    * Funkcje agregujące: `MIN(...)` oraz `MAX(...)` z nieograniczoną liczbą parametrów.
    * Operatory jednoargumentowe: `N` (negacja).
* **Śledzenie Stanu**: Wypisywanie stanu stosu przed każdą operacją w celu debugowania algorytmu.

---

## Projekt 2: Analiza Gry Hex

Narzędzie do analizy stanów gry planszowej **Hex** na heksagonalnej planszy o rozmiarach od 1x1 do 11x11.

### Funkcjonalności:
* **Parsowanie Planszy**: Wczytywanie i interpretacja wizualnego układu pól (`r` - czerwony, `b` - niebieski).
* **Analiza Stanu**:
    * Wyznaczanie rozmiaru planszy (`BOARD_SIZE`) i liczby pionów (`PAWNS_NUMBER`).
    * Weryfikacja poprawności stanu planszy (`IS_BOARD_CORRECT`).
* **Algorytmy Ścieżkowe (Connectivity)**:
    * Wykrywanie zakończenia gry (`IS_GAME_OVER`) za pomocą algorytmów przeszukiwania grafu (BFS/DFS) w poszukiwaniu nieprzerwanej ścieżki łączącej brzegi planszy.
    * Weryfikacja możliwości wystąpienia danego stanu (`IS_BOARD_POSSIBLE`).
* **Predykcja Wygranej**: Sprawdzanie możliwości wygranej w 1 ruchu przy założeniu naiwnego przeciwnika.

---

## Projekt 3: Teoria Grafów i Algorytmy Kolorowania

Zestaw narzędzi do wyznaczania parametrów strukturalnych grafów oraz optymalizacji kolorowania wierzchołków.

### Funkcjonalności:
* **Parametry Podstawowe**: Wyznaczanie ciągu stopniowego, liczby krawędzi dopełnienia oraz liczby składowych spójności.
* **Charakterystyka Grafu**: Sprawdzanie dwudzielności grafu oraz obliczanie acentryczności wierzchołków wewnątrz składowych.
* **Algorytmy Kolorowania Wierzchołków**:
    * **Greedy**: Kolorowanie zachłanne zgodnie z indeksem wierzchołka.
    * **LF (Largest First)**: Kolorowanie w kolejności malejących stopni wierzchołków.
    * **SLF (Saturation Largest First)**: Zaawansowane kolorowanie uwzględniające stopień nasycenia sąsiedztwa.
* **Struktury Danych**: Wykorzystanie własnych implementacji wektora dynamicznego (`vector.h`) oraz kolejki (`queue.h`).

---

## Technologia

* **Język**: C++ (standard C++11/14).
* **Kompilacja**: Pliki przygotowane pod kompilator GCC/MSVC.
* **Zarządzanie Pamięcią**: Ręczne zarządzanie pamięcią (brak wycieków w strukturach listowych i grafowych).

## Uruchomienie

Każdy projekt znajduje się w osobnym folderze (`AISD_PR_X`). Aby skompilować wybrany projekt (np. Projekt 1):
```bash
cd AISD_PR_1/AISD_PR_1
g++ Source.cpp -o calculator
./calculator < input.txt
