0 BEGIN PGM 1206129 MM
1 BLK FORM 0.1 Z X+0 Y+0 Z-20
2 BLK FORM 0.2 X+100 Y+100 Z+0
3 TOOL CALL 10 Z S4500 F1100
4 L Z+100 R0 FMAX M3
5 L X-20 Y+20 R0 FMAX
6 L Z+5 R0 FMAX M8
7 L Z-5 R0 F1100
8 APPR LT X+0 Y+25 LEN20 RL F1100
9 L X+25 Y+100
10 L X+100 Y+75
11 L X+75 Y+0
12 L X+0 Y+25
13 DEP LT LEN20 F2000
14 L Z+5 R0 F2000 M9
15 L X+150 Y+150 Z+100 R0 FMAX M30
16 END PGM 1206129 MM

-------------------------------------------------------------------

  Dit programma kun je in vier logische punten uitleggen aan je leerkracht:

---

### 1. Waarom gebruiken we hier wél radiuscorrectie (`RL`)?

> "In tegenstelling tot de vorige oefening (waar we een sleuf freesden op de hartlijn), frezen we nu een **buitencontour** (een opstaand eiland). We programmeren gewoon de exacte maten van de tekening, en laten de besturing zelf uitrekenen dat het hart van onze $\varnothing 20\text{ mm}$ frees (radius $10\text{ mm}$) netjes $10\text{ mm}$ naast de lijn moet blijven lopen.
> 
> 
> Omdat de opdracht vraagt om **meelopend** te frezen en we met de klok mee om het blok heen lopen, bevindt de frees zich aan de linkerkant van de looprichting: vandaar **`RL` (Radius Left)**."
> 
> 

---

### 2. Waarom gebruiken we `APPR LT` en `DEP LT` met `LEN20`?

Dit is de kern van dit hoofdstuk (*Contour benaderen en verlaten*):

> "Als je met een draaiende frees rechtstreeks op het contourpunt `(X+0, Y+25)` afstapt of daar stopt, krijg je een lelijke aanzetmarkering (een deukje) in je werkstuk en riskeer je dat je de hoek van het materiaal beschadigt.
> 
> 
> Daarom gebruiken we **`APPR LT`** (Approach Line Tangential) en **`DEP LT`** (Departure Line Tangential):
> 
> 
> * We positioneren de frees eerst veilig buiten het werkstuk op het hulppunt `X-20 Y+20` met `R0` en zakken daar in het luchtledige naar de diepte `Z-5`.
> 
> 
> * Met `APPR LT ... LEN20 RL` berekent de besturing automatisch een aanlooppunt dat precies $20\text{ mm}$ in het verlengde vóór de eerste schuine lijn ligt. De frees schakelt `RL` in en glijdt vloeiend (tangentieel) de eerste zijde in.
> 
> 
> * Belangrijke veiligheidsregel: De aanlooplengte `LEN` moet altijd groter zijn dan de radius van de frees. Onze frees is $\varnothing 20\text{ mm}$ (dus $R=10\text{ mm}$), dus `LEN20` is ruim voldoende.
> 
> 
> * Aan het einde zorgt `DEP LT LEN20` ervoor dat de frees nog $20\text{ mm}$ rechtdoor uitloopt van het werkstuk weg én dat de radiuscorrectie automatisch weer veilig wordt uitgeschakeld naar `R0`."
> 
> 
> 
> 

---

### 3. Hoe hebben we de 4 hoekpunten uit de tekening gehaald?

> "Op de tekening staan maar twee maten bij het gedraaide vierkant: $25\text{ mm}$ en $75\text{ mm}$ op een blok van $100 \times 100\text{ mm}$. Omdat er twee hartlijnen (symmetrielijnen) door het midden lopen, weten we dat het figuur volledig symmetrisch is. Elke zijde van het buitenblok wordt op exact dezelfde verhouding ($25\text{ mm}$ vanaf de hoek, $75\text{ mm}$ vanaf de andere hoek) geraakt:
> 
> 
> 1. Links (start): `X+0 Y+25`
> 
> 2. Boven: `X+25 Y+100`
> 
> 3. Rechts: `X+100 Y+75`
> 
> 4. Onder: `X+75 Y+0`
> 
> 5. En weer terug naar start: `X+0 Y+25` om het vierkant helemaal te sluiten."
> 
> 
> 
> 

---

### 4. Waarom verandert er verder niets tussen regel 9 en 12?

> "Omdat coördinaten, de voeding (`F1100`) en de radiuscorrectie (`RL`) bij HEIDENHAIN **modaal** werken (ze blijven actief tot je iets anders zegt), hoeven we op regel 9 t/m 12 alleen nog maar de vier $X/Y$-hoekpunten op te geven. De besturing berekent bij elke buitenhoek zelf de overgangsboog van de frees zodat de puntjes van het vierkant mooi scherp blijven."
> 
>
