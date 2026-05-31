# Papildoma_uzduotis

Ši programa skirta tekstinių duomenų analizei. Ji apdoroja įvestą tekstą, suskaido jį į žodžius ir atlieka kelias užduotis: skaičiuoja žodžių pasikartojimus, nustato, kuriose teksto eilutėse jie pasirodo, bei išrenka URL adresus.

Programa taip pat pašalina skyrybos ženklus, suvienodina žodžių rašybą (pvz., pirmą raidę paverčia didžiąja), ir ignoruoja skaičius bei netinkamus simbolius.

Papildomai, naudojant ICU biblioteką, programa teisingai apdoroja Unicode simbolius, todėl veikia su įvairiomis kalbomis (ne tik anglų).

## Naudojimosi instrukcija
### 1. Paruošk failus

Projekto aplanke turi būti šie failai:
- *tekstas.txt* - pagrindinis analizuojamas tekstas
- *domenai.txt* - domenų sąrašas URL atpažinimui
- *CMakelists.txt* - projekto kompiliavimo failas
- *run.bat* - paleidimo skriptas

### 2. Įrašyk tekstą

Į *tekstas.txt* įkelk norimą analizuoti tekstą.

### 3. Paleidimas

1. Įsitikinkite, jog jūsų įrenginyje yra įdiegta CMake
- Atsidarykite Command Prompt arba PowerShell
- Įveskite: **cmake --version**
- Jei terminalas parodo versiją, viskas gerai. Jei ne, reikia įsidiegti CMake
2. Raskite **run.bat** failą (jis turi būti pagrindiniame projekto kataloge)
3. Paleiskite **run.bat** failą
- *1 variantas:* dukart spustelėkite failą
- *2 variantas:* atidarykite PowerShell arba Command Prompt, nueikite į projekto katalogą ir įveskite **.\run.bat**

Programa automatiškai:
- sukompiliuos projektą
- paleis programą
- sugeneruos rezultatus

### 4. Rezultatų failai

Po programos įvykdymo bus sukurti šie failai:

#### **zodziai.txt**:
- Žodžiai, kurie pasikartoja daugiau negu 1 kartą
- Šalia nurodytas jų pasikartojimo skaičius

#### **cross_reference_lentele.txt**:
- Žodžiai, kurie pasikartoja daugiau negu 1 kartą
- Eilutės, kuriose jis pasirodo

#### **url.txt**:
- Visi rasto URL adresai, pašalinant pasikartojančius
- Įskaitant pilnus ir sutrumpintus domenus