# FIT-PA2-Polymorphism

This is a project created as a homework for subject Programming and algorithmic 2 (BI-PA2 - Programování a algoritmizace 2) at FIT CTU.

Full assignment in Czech language is below.

Summary of the assignment: Create program that will help you with packing suitcases for a holiday.

---

The point of this assignment is create good object-oriented design based on assignment.

My solution is in file `solution.cpp`, function main of this file contains test data for basic scenarios.

My solution has received 5 points out of 5, which is maximum.

# Assignment

Blíží se doba prázdnin a po dvou semestrech programování na oblíbeném automatickém vyhodnocovacím systému je potřeba změna. Na prázdniny je potřeba se připravit a sbalit. Jako poslední domácí úlohu z programování proto realizujete program, který Vám s balením na dovolenou pomůže.

Předpokládáme, že na dovolenou s sebou balíme do kufru nebo do batohu následující věci:

- **`CClothes`** - oblečení, hmotnost 500g/ks. Samozřejmě je potřeba mít evidovaný i jeho stručný popis (řetězec).
- **`CShoes`** - boty, hmotnost 750g/ks.
- **`CKnife`** - nůž o hmotnosti 100g/ks. Poznamenáme si délku jeho čepele (v cm).
- **`CMobile`** - naprostá nezbytnost, hmotnost 150g/ks, samozřejmě si pamatujeme značku a model.

Veškeré nezbytnosti si balíme do kufru `CSuitcase` nebo do batohu `CBackpack`. Obě zavazadla mají obrovskou výhodu - vejde se do něj naprosto cokoliv, a to při hmotnosti pouze 2000g (kufr) resp. 1000g (batoh). Navíc v naší implementaci bude schopen poskytovat cenné výstupy díky svému rozhraní:

- **Konstruktor `CSuitcase(w,h,d)`** ma 3 celočíselné parametry, které udávají max. velikost kufru. Tyto údaje je potřeba uložit a zobrazovat. Konstruktor `CBackpack` nemá parametry žádné. Zbytek rozhraní je pak pro obě třídy shodný.
- **Metodou `Add`** půjde do kufru/batohu přidat libovolné vybavení výše.
- **Metodou `Weight`** půjde zjistit hmotnost celého kufru/batohu (včetně obsahu). Metoda vrací celé číslo - hmotnost v gramech.
- **Metodou `Danger`** nám kufr/batoh zjistí, zda se v něm nenachází nebezpečná věc (to se hodí např. při kontrole na letišti). Za nebezpečnou věc v naší implementaci považujeme nůž s čepelí delší než 7 cm a mobilní telefon Samsung Galaxy Note S7. Pokud je v zavazadle nebezpečná věc, metoda vrátí `true`.
- **Metodu `Count`**, která nám zjistí počet věcí v kufru (vrací celé číslo).
- **Metodu `IdenticalContents (x)`**, která zjistí, zda je obsah dvou zavazadel stejný. Porovnává se pouze obsah (tedy ne zavazadlo samotné), navíc nás nezajímá pořadí věcí v zavazadle. Metoda vrací `true` pro shodný obsah, `false` pro odlišný.
- **Operátor <<**, kterým půjde zobrazit obsah celého kufru/batohu (viz ukázka níže).
- Dále od našeho kufru/batohu požadujeme standardní vlastnosti (aby se sám dokázal správně zničit, aby se dokázal správně zkopírovat - to se hodí jako prevence ztráty, ...).

Vaším úkolem je navrhnout vhodné rozhraní tříd `CKnife`, `CMobile`, `CShoes`, `CClothes`, `CSuitcase` a `CBackpack`. Při realizaci se zaměřte zejména na čistotu objektového návrhu. Implementace vyžaduje, abyste využili dědění a polymorfismu a dále vyžaduje, abyste atributy (členské proměnné) umístili právě jen do těch tříd, které je potřebují. Rozhodně nebude fungovat pokud všechny atributy umístíte do základní třídy.

Odevzdávejte zdrojový soubor, který obsahuje implementaci všech požadovaných tříd. Do odevzdávaného souboru nepřidávejte vkládání hlavičkových souborů a funkci main. Pokud vkládání hlavičkových souborů nebo funkci main v odevzdávaném souboru necháte, umístěte je do bloku podmíněného překladu (`#ifndef __PROGTEST__` / `#endif`). Využijte přiložený archiv jako základ Vaší implementace.

Poznámky:
- Prvním řádkem ve výpisu je označení zavazadla Suitcase se zadanými rozměry nebo Backpack (bez rozměrů, rozměry si udržujeme pouze pro kufr).
- Poslední prvek ve výpisu nemá značku +-, ale značku \-.
- Pořadí věcí ve výpisu je shodné jako pořadí vkládání pomocí metody Add.
- Výstupy operátorů jsou porovnávány řetězcově, dodržte formátování včetně bílých znaků.
- Nepoužívejte typeid operátor. Pro vyřešení této úlohy není potřeba (jeho použití zde svědčí o nesprávném návrhu). V testovacím prostředí úmyslně není vložen hlavičkový soubor typeinfo, použití typeid tedy povede k chybě při kompilaci.
- Místo pracné kaskády `if`/`if else` použijte pro kopírování věcí v kufru polymorfismus.
