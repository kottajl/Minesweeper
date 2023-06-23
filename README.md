# Minesweeper (Saper)

Popularna gra Saper zrobiona jako mini-projekt z przedmiotu C++ w roku akademickim 2022/23.  
Gra została stworzona przy użyciu biblioteki ***Raylib*** (https://www.raylib.com).

## Zasady gry i sterowanie

Gra polega na odkryciu wszystkich pól na planszy, które nie zostały uzbrojone w miny, w jak najkrótszym czasie. Sam rozkład ominowanych pól jest losowany przy pierwszym odkryciu pola przez gracza (przez co m.in. nie da się trafić na minę w pierwszym ruchu).  

W menu głównym gry możliwe są do wyboru trzy poziomy trudności:

* **Easy (poziom łatwy)** - plansza 9 x 9, 10 ukrytych min
* **Normal (poziom średni)** - plansza 16 x 16, 40 ukrytych min
* **Hard (poziom trudny)** - plansza 30 x 16, 99 ukrytych min

W lewym dolnym rogu aplikacji znajdować się będzie również przycisk ***Sound fx***, za pomocą którego można wyłączyć efekty dźwiękowe w grze.  

Po wyborze poziomu wyświetli się plansza o odpowiednich wymiarach. Z widoku planszy można zrestartować rozgrywkę (używając przycisku ***Restart***), a także powrócić do menu głównego (przycisk ***Main manu***).

Samo sterowanie w trakcie rozgrywki nie różni się szczególnie od tego w innych, bardziej znanych odsłonach tej gry, a więc:

* **LPM (Lewy przycisk myszy)**: odkrywa wybrane pole (pod warunkiem że nie zostało już odkryte oraz nie zostało oznaczone flagą)
* **PPM (Prawy przycisk myszy)**: oznacza wybrane pole flagą (jeśli było nieodkryte i nieoznaczone) albo usuwa flagę z danego pola
* **LPM + PPM (wciśnięcie obu przycisków naraz)**: odkrywa wszystkie sąsiadujące i nieodkryte jeszcze pola, o ile nie zostały one oznaczone flagami (tego mechanizmu można użyć tylko na już odkrytym polu, gdy w jego sąsiedztwie znajduje się tyle samo oflagowanych pól co pól faktycznie zawierających miny - użycie tego mechanizmu wraz z błędnym oflagowaniem sąsiadujących pól skutkować będzie przegraną rozgrywką).

Pod planszą znajdować się będzie informacja o aktualnym czasie rozgrywki (timer rusza od momentu pierszego odkrycia pola) oraz o pozostałej liczbie nieoznaczonych bomb.
