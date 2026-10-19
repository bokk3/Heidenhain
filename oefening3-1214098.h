0 BEGIN PGM 1214098 MM
1 BLK FORM 0.1 Z X+0 Y+0 Z-16
2 BLK FORM 0.2 X+100 Y+100 Z+0
3 TOOL CALL 8 Z S5600 F1600
4 L Z+100 R0 FMAX M3
5 L X-20 Y-20 R0 FMAX
6 L Z+5 R0 FMAX M8
7 L Z-5 R0 F1600
8 APPR LT X+10 Y+0 LEN20 RL F1600
9 L Y+14
10 CC X+25 Y+25
11 C X+10 Y+36 DR+
12 L Y+100
13 DEP LT LEN20 F2000
14 L Z+5 R0 F2000 M9
15 L X+150 Y+150 Z+100 R0 FMAX M30
16 END PGM 1214098 MM

------------------------------------------------------

Het programma voor tekening **D1214098** hoeft helemaal niet rond de hele plaat van 100×100 mm te varen en laat bij het juiste gereedschap ook geen middenpuntje staan.

---

### 1. Wat ging er precies mis in de vorige versie?

1. **Het onnodige rondje rond het werkstuk:**
De contour eindigt gewoon bovenaan de rand op **`X+10 Y+100`**. De drie extra regels naar `(100,100)`, `(100,0)` en `(10,0)` freesden alleen maar lucht langs de ruwe buitenkant van het blok en horen helemaal niet in het programma.


2. **Waarom bleef dat eilandje/middenpuntje staan in je simulatie?**
* Het cirkelmiddelpunt ligt op `X+25 Y+25` en de cirkel sluit aan op `X+10 Y+14`. Via de stelling van Pythagoras is de straal ($R$) van die cirkel dus:



$$R = \sqrt{(25 - 10)^2 + (25 - 14)^2} = \sqrt{15^2 + 11^2} = \sqrt{346} \approx \mathbf{18,6\text{ mm}}$$


* Met de gevraagde frees **T8 ($\varnothing 16\text{ mm}$, dus $R=8\text{ mm}$)** ligt de binnenkant van de frees tijdens het volgen van de cirkelboog op $18,6 - 16 = \mathbf{2,6\text{ mm}}$ van het middelpunt. Er blijft bij een zuivere contourbaan met een $\varnothing 16\text{ mm}$ frees dus wiskundig gezien altijd een rond pilaretje van $\varnothing 5,2\text{ mm}$ staan (en had je in je `TOOL.T` per ongeluk een frees van $\varnothing 10\text{ mm}$ staan, dan is dat eilandje zelfs $\varnothing 17,2\text{ mm}$!).


* **Is dat een fout in jouw code?** Nee! Dit hoofdstuk heet *Ronde baanfuncties (Cirkelbaan met cirkelmiddelpunt `CC` + `C`)*. Het doel van deze HEIDENHAIN-oefening is puur het aanleren van `CC` en `C` in één doorlopende contourlijn van `X+10 Y+0` naar `X+10 Y+100`. In dit hoofdstuk hoort dat puntje in de 3D-simulatie te blijven staan (of je haalt het met één extra voorpositionering/freesbeweging weg als je het visueel strak wilt hebben).





---

### 2. Het gecorrigeerde, strakke `.h`-programma (Officiële HEIDENHAIN-oplossing)

Dit programma volgt exact je tabel: start op `X+10 Y+0`, meelopend (`RL`), de cirkelboog tegen de klok in (`DR+`), en direct bovenaan bij `X+10 Y+100` tangentieel verlaten met `DEP LT LEN20`:


*(Bonus-tip: Wil je dat kleine middenpilaartje op `(X+25, Y+25)` in je simulatie tóch even meepakken zodat het werkstuk 100% schoon is? Voeg dan tussen regel 12 en 13 simpelweg een korte uitsteek naar het midden toe, of frees eerst even naar het hart voordat je omhoog gaat).*

---

### 3. Uitleg voor je leerkracht (Waarom zit dit zo in elkaar?)

1. **Waarom `RL` (Meelopend frezen) én `DR+`?**
> "We beginnen onderaan bij `X+10 Y+0` en lopen omhoog langs het werkstuk. Het materiaal dat moet blijven staan bevindt zich aan de rechterkant van onze looprichting, en de frees loopt aan de linkerkant langs de wand: daarom kiezen we **`RL` (Radius Left)** voor meelopend frezen.
> 
> 
> Bij punt `X+10 Y+14` buigen we de ronde kamer in. Om vanuit `(10, 14)` rechtsom door de buik van de cirkel naar `(10, 36)` te draaien, maken we een draaibeweging **tegen de klok in**: in HEIDENHAIN is tegen de klok in altijd **`DR+` (Direction of Rotation +)**."
> 
> 


2. **Waarom hoeven we de straal van de cirkel niet uit te rekenen?**
> "Op de tekening staat geen radius (`R`) bij de cirkel vermeld, maar wel het exacte middelpunt (`X+25 Y+25`), het startpunt van de boog (`X+10 Y+14`) en het eindpunt van de boog (`X+10 Y+36`). Door eerst de pool/het cirkelmiddelpunt vast te leggen met **`CC X+25 Y+25`** en daarna **`C X+10 Y+36 DR+`** te programmeren, berekent de besturing zelf de exacte cirkelboog van start- naar eindpunt."
> 
> 


3. **Waarom stoppen we bij `Y+100` met `DEP LT LEN20`?**
> "Zodra de frees op regel 12 het eindpunt `X+10 Y+100` (de bovenrand van de plaat) bereikt, is de hele afstap aan de linkerkant klaar. Met **`DEP LT LEN20 F2000`** loopt de frees in het verlengde van de laatste lijn nog 20 mm rechtdoor het vrije luchtledige in (tot `Y+120`) en schakelt daarbij automatisch de radiuscorrectie weer uit naar `R0`. Daarna trekken we eerst veilig vrij in de Z-as (`Z+5` en `Z+100`) voordat we naar de parkeerpositie `X+150 Y+150` gaan."
> 
>
