0 BEGIN PGM 1214155 MM
1 BLK FORM 0.1 Z X+0 Y+0 Z-16
2 BLK FORM 0.2 X+100 Y+100 Z+0
3 TOOL CALL 5 Z S8900 F1100
4 L Z+100 R0 FMAX M3
5 L X+150 Y+150 R0 FMAX
6 CYCL DEF 251 RECHTHOEKIGE KAMER ~
    Q215=+0    ;BEWERKINGSOMVANG ~
    Q218=+70   ;1E ZIJDELENGTE ~
    Q219=+20   ;2E ZIJDELENGTE ~
    Q220=+6    ;HOEKRADIUS ~
    Q368=+0.2  ;OVERMAAT ZIJKANT ~
    Q224=+90   ;ROTATIEPOSITIE ~
    Q367=+0    ;KAMERPOSITIE ~
    Q207=+1100 ;AANZET FREZEN ~
    Q351=+1    ;FREESWIJZE ~
    Q201=-5    ;DIEPTE ~
    Q202=+5    ;DIEPTEVERPLAATSING ~
    Q369=+0.1  ;OVERMAAT DIEPTE ~
    Q206=+1100 ;AANZET DIEPTEVERPL. ~
    Q338=+5    ;VERPLAATSING NABEW. ~
    Q200=+5    ;VEILIGHEIDSAFSTAND ~
    Q203=+0    ;COORD. OPPERVLAK ~
    Q204=+50   ;2E VEILIGHEIDSAFST. ~
    Q370=+0.7  ;BAANOVERLAPPING ~
    Q366=+1    ;INSTEKEN ~
    Q385=+1100 ;AANZET NABEWERKEN ~
    Q439=+0    ;REF. AANZET
7 L X+30 Y+50 R0 FMAX M8 M99
8 CYCL DEF 252 RONDE KAMER ~
    Q215=+0    ;BEWERKINGSOMVANG ~
    Q223=+30   ;CIRKELDIAMETER ~
    Q368=+0.2  ;OVERMAAT ZIJKANT ~
    Q207=+1100 ;AANZET FREZEN ~
    Q351=+1    ;FREESWIJZE ~
    Q201=-5    ;DIEPTE ~
    Q202=+5    ;DIEPTEVERPLAATSING ~
    Q369=+0.1  ;OVERMAAT DIEPTE ~
    Q206=+1100 ;AANZET DIEPTEVERPL. ~
    Q338=+5    ;VERPLAATSING NABEW. ~
    Q200=+5    ;VEILIGHEIDSAFSTAND ~
    Q203=+0    ;COORD. OPPERVLAK ~
    Q204=+50   ;2E VEILIGHEIDSAFST. ~
    Q370=+0.7  ;BAANOVERLAPPING ~
    Q366=+1    ;INSTEKEN ~
    Q385=+1100 ;AANZET NABEWERKEN ~
    Q439=+0    ;REF. AANZET
9 L X+75 Y+60 R0 FMAX M99
10 CYCL DEF 253 SLEUFFREZEN ~
    Q215=+0    ;BEWERKINGSOMVANG ~
    Q218=+50   ;SLEUFLENGTE ~
    Q219=+12   ;SLEUFBREEDTE ~
    Q368=+0.2  ;OVERMAAT ZIJKANT ~
    Q374=+20   ;ROTATIEPOSITIE ~
    Q367=+0    ;SLEUF POSITIE ~
    Q207=+1100 ;AANZET FREZEN ~
    Q351=+1    ;FREESWIJZE ~
    Q201=-5    ;DIEPTE ~
    Q202=+5    ;DIEPTEVERPLAATSING ~
    Q369=+0.1  ;OVERMAAT DIEPTE ~
    Q206=+1100 ;AANZET DIEPTEVERPL. ~
    Q338=+5    ;VERPLAATSING NABEW. ~
    Q200=+5    ;VEILIGHEIDSAFSTAND ~
    Q203=+0    ;COORD. OPPERVLAK ~
    Q204=+50   ;2E VEILIGHEIDSAFST. ~
    Q366=+2    ;INSTEKEN ~
    Q385=+1100 ;AANZET NABEWERKEN ~
    Q439=+0    ;REF. AANZET
11 L X+70 Y+22 R0 FMAX M99
12 L Z+100 R0 FMAX M9
13 L X+150 Y+150 R0 FMAX M30
14 END PGM 1214155 MM


-------------------------------------------------------------------------------------



  Dit programma voor tekening **D1214155** laat zien hoe je met vaste bewerkingscycli en één gereedschap drie compleet verschillende geometrieën (een rechthoekige kamer, een ronde kamer en een gedraaid slobgat) uitruimt én nabewerkt.

---

### 1. Uitleg voor je leerkracht (De CNC- en wiskundige logica)

* **Waarom 3 verschillende cycli (`251`, `252` en `253`)?**
> "Op de tekening staan drie vormen die op het eerste gezicht op elkaar lijken, maar geometrisch verschillen:
> 
> 
> 1. De verticale uitsparing links is $70 \times 20\text{ mm}$, maar heeft **geen** volledig ronde uiteinden van $R10$; er staat expliciet **`R6`** bij de hoeken. Daarom moeten we hier **Cyclus 251 (Rechthoekige kamer)** gebruiken, waarin we met `Q220=+6` exact die hoekradius van $6\text{ mm}$ kunnen opgeven (en omdat onze frees $\varnothing 10\text{ mm}$ oftewel $R5$ is, kan hij die $R6$ makkelijk halen). Omdat de lange zijde ($70\text{ mm}$) verticaal langs de $Y$-as staat, roteren we de kamer met `Q224=+90` graden.
> 
> 
> 2. De cirkel rechtsboven ($\varnothing 30\text{ mm}$) frezen we met **Cyclus 252 (Ronde kamer)**. De besturing steekt spiraalvormig (`Q366=+1`) in het midden in en pelt de cirkel met een baanoverlapping van $70\%$ (`Q370=+0.7`) naar buiten toe open, zodat er — in tegenstelling tot puur contourfrezen — geen eilandje in het midden blijft staan.
> 
> 
> 3. De schuine gleuf rechtsonder ($50 \times 12\text{ mm}$) heeft wél volledig halfronde uiteinden ($R6$ bij een breedte van $12\text{ mm}$). Dat is een echt slobgat, waarvoor we **Cyclus 253 (Sleuffrezen)** gebruiken met een pendelende invalbeweging (`Q366=+2`) omdat de sleuf ($12\text{ mm}$) nauwelijks breder is dan de frees ($\varnothing 10\text{ mm}$)."
> 
> 
> 
> 


* **De wiskunde achter de hoek van $20^\circ$ (`Q374=+20`) bij de schuine sleuf:**
> "Op de tekening staat een hoek van **$70^\circ$** aangegeven vanaf de **verticale hartlijn** ($Y$-as) naar rechts gekanteld. HEIDENHAIN meet rotatiehoeken echter altijd vanaf de **positieve horizontale $X$-as ($0^\circ$)** tegen de klok in. Omdat de positieve $Y$-as op $90^\circ$ ligt, is de hoek ten opzichte van de $X$-as dus: $90^\circ - 70^\circ = \mathbf{+20^\circ}$."
> 
> 


* **Voorbewerken én nabewerken in één cyclus (`Q215=+0`):**
> "Volgens de opdracht moeten we voor- én nabewerken. Door `Q215=+0` te kiezen, ruimt de cyclus de kamer eerst ruw uit, maar laat daarbij een overmaat van **$0.2\text{ mm}$ aan de wanden (`Q368=+0.2`)** en **$0.1\text{ mm}$ op de bodem (`Q369=+0.1`)** staan. Daarna freest dezelfde cyclus direct de bodem en de zijwanden op de exacte eindmaat van `Z-5` schoon."
> 
> 


* **Positioneren vanuit het hart (`Q367=+0` en `M99`):**
> "Omdat alle drie de vormen op de tekening bemaat zijn vanuit hun symmetrische middelpunt (`X+30 Y+50`, `X+75 Y+60` en `X+70 Y+22`), zetten we de positieparameter `Q367` op `+0` (referentiepunt = midden van de kamer/sleuf). Met een simpele `L X... Y... R0 FMAX M99` sturen we de frees boven het hart en voert `M99` de cyclus direct op die plek uit."
> 
> 



---

### 2. Wat was er fout aan ons "Design 1"?

In de eerste poging zaten vier fouten die je in de simulatie meteen terugziet of die een error geven:

1. **Verkeerde cyclus én verkeerde lengte voor de linker kamer:**
Design 1 gebruikte `CYCL DEF 253` (Sleuffrezen) met een lengte van `50 mm` in plaats van `70 mm`. Een sleufcyclus maakt van een $20\text{ mm}$ brede sleuf automatisch halfronde uiteinden met radius $R10$, terwijl de tekening een rechthoekige kamer van $70\text{ mm}$ lang met kleine hoekradii van **`R6`** vraagt (`CYCL DEF 251`).


2. **Verkeerde coördinaat en rotatie voor de schuine sleuf:**
Design 1 riep de schuine sleuf op bij `X+55 Y+22` met `ROT70`, terwijl de tekening het middelpunt op **`X+70 Y+22`** legt en de hoek van $70^\circ$ vanaf de $Y$-as meet (dus **`Q374=+20`** ten opzichte van de $X$-as).


3. **Ontbrekende Q-parameters voor jouw TNC 640-versie:**
In Design 1 ontbraken `Q374` (rotatiepositie), `Q367` (sleufpositie) en `Q439` (referentie aanzet) binnen de cyclusdefinitie.



---

### 3. Knip- & Plak-regels voor `.h`-bestanden (Voor jouw Toolchain / VS Code)

Als software developer die `.h`-bestanden buiten de machine om genereert of plakt, zijn dit de gouden syntaxisregels van de TNC 640 parser:

* **Verplichte tilde (`~`) bij meerregelige commando's:**
In een `.h`-bestand is een `CYCL DEF` eigenlijk één enkel regelnummer (bijv. regel `6`). Elke regel binnen die cyclus **moet** eindigen op een spatie gevolgd door een tilde (` ~`), behalve de allerlaatste Q-parameter van die cyclus (`Q439`). Vergeet je één tilde of zet je een tilde achter de laatste parameter, dan crasht de parser bij het inladen.


* **Exacte volgorde en volledigheid van Q-parameters:**
De TNC 640 verwacht bij het inlezen van een plat tekstbestand *alle* Q-parameters die bij die specifieke software-release horen, in de **exacte vaste volgorde**. Je mag geen "ongebruikte" Q-parameters weglaten in een `.h`-bestand.


* **Expliciete voortekens (`+` of `-`):**
Elke numerieke waarde achter een `X`, `Y`, `Z` of `Q`-parameter in Klaartekst moet altijd een expliciet `+` of `-` teken hebben (bijv. `Q215=+0`, nooit `Q215=0`).


* **Pas op met `AUTO` in platte tekst:**
Waar je op het paneel op de softkey `F AUTO` drukt, schrijft de besturing intern afhankelijk van de taalversie of software-update een specifieke string weg. Door in je geautomatiseerde `.h`-templates direct de numerieke waarde uit je tabel te zetten (`Q207=+1100` in plaats van `AUTO`), voorkom je taal- en versie-errors bij het inladen.
