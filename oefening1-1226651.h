0 BEGIN PGM 1226651 MM
1 BLK FORM 0.1 Z X+0 Y+0 Z-16
2 BLK FORM 0.2 X+100 Y+100 Z+0
3 TOOL CALL 5 Z S8900 F1100
4 L Z+100 R0 FMAX M3
5 L X+50 Y+20 R0 FMAX
6 L Z+5 R0 FMAX M8
7 L Z-5 R0 F1100
8 L X+30 Y+20 R0 F1100
9 CC
10 LP PR+40 PA+108 R0
11 CC
12 LP PR+40 PA+36 R0
13 CC
14 LP PR+40 PA-36 R0
15 CC
16 LP PR+40 PA-108 R0
17 L X+50 Y+20 R0
18 L Z+5 R0 F2000 M9
19 L X+150 Y+150 Z+100 R0 FMAX M30
20 END PGM 1226651 MM


----------------------------------------------------------------


  Mooi dat de simulatie draait! Als je dit aan je leerkracht moet uitleggen, wil die vooral horen dat je **begrijpt wát je aan het doen bent** en **waarom je bepaalde keuzes hebt gemaakt** (strategie, veiligheid en wiskunde).

Je kunt je uitleg opbouwen in 4 heldere stappen:

---

### 1. Waarom frezen we met `R0` (ongecorrigeerd)?

> "Meneer/mevrouw, op de tekening is de sleuf 10 mm breed en de maatvoering staat aangegeven op de hartlijn van de sleuf. Omdat we een vingerfrees van precies $\varnothing 10\text{ mm}$ (gereedschap T5) gebruiken, valt het hart van het gereedschap exact samen met de hartlijn van de tekening. We hebben daarom geen radiuscorrectie (`RL` of `RR`) nodig, maar programmeren met `R0` direct op de lijn."
> 
> 

---

### 2. Waarom polaire coördinaten (`CC` + `LP`) in plaats van gewoon `X` en `Y`?

> "Als je een schuine vijfhoek met normale $X$- en $Y$-coördinaten zou programmeren, moet je voor elk schuin hoekpunt sinus en cosinus gaan uitrekenen op je rekenmachine. Dat kost veel tijd en is foutgevoelig.
> 
> 
> Een regelmatige vijfhoek heeft echter twee vaste eigenschappen:
> 
> 
> 1. Alle 5 zijden zijn even lang, namelijk **40 mm** (want de onderste zijde loopt van $X+30$ tot $X+70$).
> 
> 
> 2. De binnenhoek van een regelmatige vijfhoek is altijd **$108^\circ$**.
> 
> 
> Daarom hebben we gekozen voor **polaire coördinaten**: je geeft telkens een lengte (`PR`) en een hoek (`PA`) op."
> 
> 
> 
> 

---

### 3. De "Pool-verplaatsingstruc" (De lege `CC`)

Dit is het slimste stukje van je programma waar leerkrachten van houden:

> "Normaal gesproken zet je één pool (`CC`) in het midden van een cirkel. Maar door na elk hoekpunt een **`CC` zonder coördinaten** te programmeren, zeg je tegen de besturing: **'Maak het punt waar de frees nú staat de nieuwe pool'**.
> 
> 
> Vanaf dat nieuwe hoekpunt varen we met `LP PR+40` weer 40 mm weg onder de juiste hoek. Omdat we **met de klok mee** frezen (zoals de opdracht vroeg), draaien we bij elke hoek $72^\circ$ naar rechts (want $180^\circ - 108^\circ = 72^\circ$). Vandaar dat de hoeken telkens met 72 afnemen: eerst $108^\circ$, dan $36^\circ$, dan $-36^\circ$, enzovoort."
> 
> 

---

### 4. De veilige programmeeropbouw

> "Tot slot hebben we een veilige standaard machinestructuur aangehouden:
> 
> 
> * Eerst `BLK FORM` aangemaakt voor de 3D-simulatie.
> 
> 
> * Bij het voorpositioneren eerst in Z naar veilige hoogte (`Z+100`) en de spil gestart (`M3`), daarna pas in het vlak naar het startpunt (`X+50 Y+20`) bewogen. Nooit tegelijk schuin naar beneden duiken om botsingen met klemmen te voorkomen!
> 
> 
> * Op veilige afstand (`Z+5`) de koeling aangezet (`M8`), rustig met bewerkingsvoeding ingezakt naar `Z-5`, de hele lus gefreesd, en weer vrijgetrokken naar `Z+100` voordat de spil en het programma stoppen (`M30`)."
> 
> 
> 
> 

Als je het zó vertelt, laat je zien dat je niet zomaar nummertjes hebt overgetypt, maar dat je de wiskunde, de HEIDENHAIN-logica en de veiligheid van de machine volledig begrijpt!
