# Papildoma uzduotis

Programa skirta darbui su `std::string` ir asociatyviais konteineriais. Ji nuskaito tekstą is failo `tekstas.txt`, suskaiciuoja pasikartojancius zodzius, sukuria cross-reference lentele ir suranda URL adresus.

## Ka programa padaro

- Suskaiciuoja, kiek kartu tekste pasikartoja kiekvienas skirtingas zodis.
- I faila `zodziu_pasikartojimai.txt` isveda tik tuos zodzius, kurie pasikartojo daugiau negu viena karta.
- I faila `cross_reference.txt` isveda zodzius ir eiluciu numerius, kuriose tie zodziai buvo pamineti.
- I faila `url_adresai.txt` isveda rastus URL adresus.

## Naudojami konteineriai

- `std::map<std::string, int>` - zodziams ir ju pasikartojimu kiekiui saugoti.
- `std::map<std::string, std::set<int>>` - zodziams ir eiluciu numeriams saugoti.
- `std::set<int>` - kad tas pats eilutes numeris nebutu kartojamas kelis kartus.
- `std::vector<std::string>` - rastiems URL adresams saugoti tokia tvarka, kokia jie buvo rasti.

## Failai

- `EgzaminoUzd.cpp` - pagrindinis programos kodas.
- `tekstas.txt` - tekstas is https://lt.wikipedia.org/wiki/Vilnius, kuriame yra daugiau nei 1000 zodziu ir keli URL adresai.
- `zodziu_pasikartojimai.txt` - sugeneruotas zodziu pasikartojimu failas.
- `cross_reference.txt` - sugeneruota cross-reference lentele.
- `url_adresai.txt` - sugeneruotas URL adresu sarasas.

## Paleidimas

Projektą galima paleisti per Visual Studio kaip Console Application.

Taip pat galima kompiliuoti komandu eiluteje, jeigu yra C++ kompiliatorius:

```bash
g++ EgzaminoUzd.cpp -o EgzaminoUzd
./EgzaminoUzd
```

Naudojant CMake:

```bash
cmake -S . -B build
cmake --build build
```

Paleidus programa, `tekstas.txt` turi buti tame paciame kataloge, is kurio paleidziama programa.

## URL formatai

Programa iesko pilnu ir sutrumpintu URL formu, pvz.:

- `https://www.vu.lt/`
- `https://vu.lt/`
- `www.vu.lt`
- `vu.lt`

Skyrybos zenklai, esantys salia zodziu arba URL adresu, nera laikomi zodzio ar URL dalimi.
