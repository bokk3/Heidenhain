0 BEGIN PGM 1226642 MM
1 BLK FORM 0.1 Z X+0 Y+0 Z-16
2 BLK FORM 0.2 X+100 Y+100 Z+0
3 * - VOORBOREN Ø6.8 (T229)
4 TOOL CALL 229 Z S6000
5 L Z+100 R0 FMAX M3 M8
6 CYCL DEF 200 BOREN ~
    Q200=+5    ;VEILIGHEIDSAFSTAND ~
    Q201=-17   ;DIEPTE ~
    Q206=+840  ;AANZET DIEPTEVERPL. ~
    Q202=+17   ;DIEPTEVERPLAATSING ~
    Q210=+0    ;STILSTANDSTIJD BOVEN ~
    Q203=+0    ;COORD. OPPERVLAK ~
    Q204=+50   ;2E VEILIGHEIDSAFST. ~
    Q211=+0    ;STILSTANDSTIJD ONDER ~
    Q395=+0    ;REF. DIEPTE
7 CALL LBL 10
8 CALL LBL 11
9 CALL LBL 12
10 * - TAPPEN M8 (T264)
11 L Z+100 R0 FMAX M5 M9
12 L X+150 Y+150 R0 FMAX
13 TOOL CALL 264 Z S200
14 L Z+100 R0 FMAX M3 M8
15 CYCL DEF 206 SCHROEFDRAAD TAPPEN ~
    Q200=+5    ;VEILIGHEIDSAFSTAND ~
    Q201=-17   ;SCHROEFDRAADDIEPTE ~
    Q206=+250  ;AANZET (200 x 1.25) ~
    Q211=+0    ;STILSTANDSTIJD ONDER ~
    Q203=+0    ;COORD. OPPERVLAK ~
    Q204=+50   ;2E VEILIGHEIDSAFST.
16 CALL LBL 10
17 CALL LBL 11
18 CALL LBL 12
19 L Z+100 R0 FMAX M5 M9
20 L X+150 Y+150 R0 FMAX
21 M30
22 * - SUBPROGRAMMA'S
23 LBL 10
24 * - RIJ 1 (8 GATEN)
25 L X+30 Y+15 R0 FMAX
26 LBL 1
27 CYCL CALL
28 L IX+3.420 IY+9.397 FMAX
29 CALL LBL 1 REP 7
30 LBL 0
31 LBL 11
32 * - RIJ 2 (8 GATEN)
33 L X+11.206 Y+21.840 R0 FMAX
34 LBL 2
35 CYCL CALL
36 L IX+3.420 IY+9.397 FMAX
37 CALL LBL 2 REP 7
38 LBL 0
39 LBL 12
40 * - CIRKEL 6x60 R15
41 CC X+70 Y+30
42 LP PR+15 PA+30 R0 FMAX
43 LBL 3
44 CYCL CALL
45 LP IPA+60 FMAX
46 CALL LBL 3 REP 5
47 LBL 0
48 END PGM 1226642 MM


--------------------------------------------- UITLEG:


# Uitleg van het programma in gewone woorden

Het programma maakt in een vierkante plaat (100 × 100 × 16 mm) **22 gaten**. Eerst boort het ze voor met een boor van 6,8 mm. Daarna tapt het er M8-schroefdraad in. Het verloop is hetzelfde als wat je met de hand zou doen, alleen schrijf je het op voor de machine.

## 1. De voorbereiding (regel 0 t/m 2)

- **BEGIN PGM**: de naam van het programma. Het is het onderdeelnummer, 1226642.
- **BLK FORM**: hiermee vertel je de machine hoe groot het ruwe stuk materiaal is. Het is een blok van 100 × 100 mm, met de bovenkant op Z0 en de onderkant op Z-16. Het nulpunt ligt dus linksonder op de bovenkant van de plaat. Alle maten in het programma gaan vanaf dat punt.

## 2. Voorboren (regel 3 t/m 9)

- **TOOL CALL 229**: de machine haalt boor nummer 229 (Ø6,8) en draait met 6000 toeren per minuut.
- **Z+100 en M3 M8**: de boor gaat omhoog naar een veilige hoogte van 100 mm boven het werkstuk. M3 laat de spindel draaien en M8 zet de koeling aan.
- **Cyclus 200 (boren)**: dit is een kant-en-klaar boorprogramma van de machine. Je vult alleen de gegevens in:
  - de boor stopt op 5 mm boven het oppervlak (veiligheidsafstand) en gaat dan het materiaal in met 840 mm/min;
  - de boordiepte is 17 mm (de plaat is 16 mm dik, dus de boor gaat er helemaal doorheen);
  - na het boren gaat de boor terug omhoog naar 50 mm boven de plaat, zodat hij nergens tegenaan botst.
- **CALL LBL 10, 11, 12**: dit zijn de drie gatenpatronen. De uitleg staat hieronder bij de subprogramma's.

## 3. Tappen (regel 10 t/m 18)

- Eerst gaat de boor omhoog, de spindel en de koeling gaan uit, en de machine rijdt naar een veilige wisselplek.
- **TOOL CALL 264**: nu komt de tap (M8) erin. Draaisnelheid is maar 200 toeren per minuut, want schroefdraad maken moet langzaam.
- **Cyclus 206 (tappen)**: dezelfde opzet als bij het boren. De tap gaat 17 mm diep, dus door de hele plaat. De voortgang is **250 mm/min**. Dat komt van toeren × spoed: 200 × 1,25 mm (de spoed van M8). Zo draait de tap precies één draadgang per omwenteling en snijdt hij een mooie draad.
- Daarna worden dezelfde drie patronen nog een keer afgewerkt. De tap komt dus precies in de gaten die net geboord zijn.

## 4. Het einde (regel 19 t/m 21)

Alles omhoog, spindel en koeling uit, de machine rijdt naar een vrije hoek (X150 Y150) en **M30** beëindigt het programma.

## 5. De subprogramma's (regel 22 t/m 47)

Dit is het slimme deel. Je schrijft de posities **één keer** op en roept ze twee keer aan, bij het boren en bij het tappen. Zo hoef je ze niet te kopiëren en maak je minder fouten. Een subprogramma begint met `LBL` (label, een soort naamplaatje) en eindigt met `LBL 0`.

**Rij 1 en rij 2 (LBL 10 en 11)**
De twee rijen staan schuin, onder een hoek van 70°. In elke rij zitten 8 gaten, op 10 mm van elkaar.
- Eerst gaat de machine naar het eerste gat van de rij (rij 1 op X30 Y15, rij 2 op X11,206 Y21,84).
- Dan boort of tapt hij een gat (`CYCL CALL`).
- Dan schuift hij 10 mm verder langs de schuine lijn. Omdat de rij schuin loopt, is dat 3,42 mm opzij (X) en 9,397 mm omhoog (Y). Die getallen komen uit de driehoeksrekening (sinus en cosinus van 70°).
- `CALL LBL 1 REP 7` betekent: "doe dit stukje nog 7 keer opnieuw". Eén keer plus 7 herhalingen geeft 8 gaten.

**De cirkel (LBL 12)**
Zes gaten in een cirkel, met de middelpunten op een straal van 15 mm.
- `CC X70 Y30` zet het middelpunt van de cirkel (de "pool").
- Daarna werk je met **poolcoördinaten**: een afstand (15 mm) en een hoek. Het eerste gat zit op 30°.
- Na elk gat draait de machine 60° verder (`IPA+60`). Zes keer 60° is een hele cirkel van 360°.
- `REP 5` geeft één keer plus 5 herhalingen, dus 6 gaten.

## Waarom het eerst fout was (korte samenvatting)

Als je het aan je leerkracht uitlegt, zijn dit de hoofdpunten:

1. De rijen waren als **verticaal** gezien, maar ze lopen **schuin onder 70°**.
2. Het aantal gaten klopte niet: er moesten er **8 per rij** zijn, geen 7.
3. De **tweede rij** begon op de verkeerde plek.
4. Er stonden **verkeerde commando's** in (`ICA`, `L` in plaats van `LP`, absoluut en incrementeel door elkaar).
5. Bij de boorcyclus waren een paar waarden **anders dan in de tabel** (veiligheidsafstand, aanzet).
6. Bij het tappen werd er **helemaal niet getapt**: er stond geen positie en geen oproep, alleen commentaar.
