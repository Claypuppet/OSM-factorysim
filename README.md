# Productiestraat simulatie

mooie project samenvatting!

## Build

Installeer cmake (minimum version 3.5) en zorg er voor dat deze werkt in
de terminal.

### Maak bin directory

Maak een bin directory (of linux, mingw) in de source files folder waar
je de gecompiled binaries worden opgeslagen.

`mkdir bin`
`cd bin`

### Build & Make

Bouw de makefile dingen, gebruik de extra args voor het instellen van
(niet-standaard) boost en wxwidget directories. (TODO: exacte args opzoeken)

`cmake ../ [--extra args]`

Bouw de applicatie(s)

`make`

Nu staan de binaries in de bin folder.

