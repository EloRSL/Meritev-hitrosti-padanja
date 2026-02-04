# Meritev hitrosti padanja frnikole

Projektna naloga za maturo, pri kateri smo izdelali sistem za merjenje hitrosti padanja frnikole. Uporabili smo Arduino Uno, dva laserska modula (KY-008) in dva LDR svetlobna senzorja.

**Avtor:** Rok Studen Levstek  
**Mentor:** mag. Milan Setničar, prof.  
**Kraj in datum:** Ljubljana, april 2024

## Opis delovanja
Sistem meri čas, ki preteče med prekinitvijo dveh laserskih snopov. Laserja sta postavljena eden nad drugim v znani razdalji. Ko frnikola pade mimo prvega laserja, LDR senzor zazna spremembo in Arduino sproži štetje časa. Ko frnikola prekine spodnji snop, se meritev zaključi.

Iz izmerjenega časa in znane razdalje mikrokrmilnik izračuna hitrost padanja, jo pretvori v metre na sekundo in izpiše na računalnik preko serijske povezave. Izmeril sem na treh različnih točkah, katerih meritve so podane v `docs/mere.txt`.

## Uporabljena oprema
*   Arduino Uno (ATmega328P)
*   2x Laserski modul KY-008
*   2x LDR senzor (z LM393 komparatorjem)
*   Leseno ohišje za stabilno pritrditev

## Povezava in koda
Senzorja sta povezana na digitalna vhoda, ki podpirata zunanje prekinitve (interrupts), kar omogoča natančnejše merjenje časa kot navadno preverjanje stanja v zanki. Rezultati se izpisujejo na računalnik preko serijske povezave.

## Ugotovitve
Pri testiranju smo ugotovili, da je uporaba senzorjev za svetlobo LDR s čipom LM393 in Arduino Uno zanesljiva metoda za detekcijo gibanja in merjenje časa med prekinitvama laserskega snopa.

