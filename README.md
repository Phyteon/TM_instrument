# Temat projektu:
Instrument muzyczny stworzony na podstawie mikrokontrolera i modułu głośnika.


# Autorzy
Pawelec Filip
Skomiał Krzysztof

# Opis projektu:

Celem projektu jest wykonanie układu pełniącego funkcję prostego instrumentu muzycznego. Poszczególne tony są zadawane za pomocą zewnętrznej klawiatury posługując się portem komunikacyjnym PS/2, które następnie podlegają edycji z wykorzystaniem potencjometrów oraz slidera. Końcowy efekt jest przekazywany na wyjście dołączonego modułu (głośniczek).

# Analiza problemu:

Moduł Waveshare 3972 zawiera dwa potencjometry o wysokiej precyzji służące do regulacji napięcia w zakresie 0V - 3.3V, z których jeden będzie odpowiadał za zmianę głośności melodii wychodzącej z głośniczka. Jego zadaniem jest generacja odpowiedniego napięcia, które zostanie przekazane do przetwornika A/C na płytce. Obecny w module głośniczek emitujący dźwięk jest zasilany za pomocą bloku TPM obecnego w mikrokontrolerze.

Obecny na płytce ewaluacyjnej slider jest wykorzystywany jako modulator przekazywanego do głośniczka dźwięku. Przesuwając palcem po powierzchni slidera będzie można dokonać modyfikacji dźwięku.

W projekcie zostanie także wykorzystana klawiatura komputerowa z wejściem PS/2, której zadaniem będzie zadawanie określonych tonów o określonych wartościach częstotliwości. Złącze tego typu jest portem szeregowym posiadającym sześć pinów (w przypadku tego projektu wymagane jest podłączenie czterech z nich: dwóch pinów zasilania oraz dwóch pinów służącym do przesyłu danych).

# Plan realizacji:

Do użytych w projekcie komponentów możemy zaliczyć: płytkę ewaluacyjną FRDM - KL05Z wyposażoną w mikroprocesor ARM Cortex M0, klawiaturę komputerową wykorzystującą port komunikacyjny PS/2, moduł z głośnikiem do testowania przetworników A/C i C/A Waveshare 3972.

W ramach projektu zostaną utworzone dodatkowe pliki do obsługi klawiatury komputerowej i dopasowywania do zadanych wartości poszczególnych tonów muzycznych.
# Link do filmiku:
https://youtu.be/J6HUxXaTPOU
