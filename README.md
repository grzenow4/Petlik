# Petlik
Realization of programming language "Petlik". Programme reads the code and generate code on virtual machine which optimises and executes it.

Grammar of "Petlik":
```
Program → CiągInstrukcji
CiągInstrukcji → ε | CiągInstrukcji Instrukcja
Instrukcja → Zwiększ | Powtarzaj
Zwiększ → Zmienna
Powtarzaj → '(' Zmienna CiągInstrukcji ')'
Zmienna → 'a' | .. | 'z'
```
The machine can only do instructions listed below:
```
INC Zmienna (increment)
zwiększ o jeden wartość zmiennej Zmienna,
ADD Zmienna0 Zmienna1 (add)
dodaj do zmiennej Zmienna0 wartość zmiennej Zmienna1,
CLR Zmienna (clear)
wyzeruj zmienną Zmienna,
JMP Adres (jump)
skocz do instrukcji o adresie Adres,
DJZ Zmienna Adres (decrement or jump if zero)
jeśli Zmienna ma wartość 0 to skocz do instrukcji o adresie Adres, w przeciwnym przypadku zmniejsz o jeden wartość zmiennej Zmienna,
HLT (halt)
zakończ wykonywanie programu.
```
