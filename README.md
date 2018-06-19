# Productiestraat simulatie

## Installatie

1. Installeer cmake (minimum version 3.5) en zorg er voor dat deze werkt in
de terminal.

2. Maak een bin directory (of linux, mingw) in de source files folder waar
je de gecompiled binaries worden opgeslagen.
`mkdir bin`
`cd bin`

3. Bouw de makefile dingen, gebruik de extra args voor het instellen van
(niet-standaard) boost en wxwidget directories. (TODO: exacte args opzoeken)
`cmake .. [--extra args]`

4. Bouw de applicatie(s)
`make`

Nu staan de binaries in de bin folder.

## Scripts

### Gebruikerscripts

1. **Configgenerator**
Gebruik het configgenerator script, script.py, om via de machines ingesteld in configs.yaml
een configuratiebestand te genereren. Om machines toe te voegen, aan te passen of te verwijderen,
bewerk het configs.yaml bestand.

### Developmentscripts

1. **adviesrapport**
Script voor het berekenen van resultaten die gebruikt worden in adviesrapport hoofdstuk 7.
Maakt gebruik van de statistics.json en used_config.yaml die gegenereerd worden door het uitvoeren
van een simulatie.

2. **simulations.sh**
Een kort shellscripts voor het uitvoeren van alle configuraties in de configs/adviesrapport_configs/ folder.

## Applicaties

Elke applicatie en testapplicatie staat in zijn subfolder (Machine Control,
Production Control en Visualiser).

Tijdens het uitvoeren van een simulatie over TCP/IP dient Production Control altijd als eerste te worden opgestart.

## Argumenten

De volgende argumenten zijn alleen van toepassing op een simulatie via TCP/IP.

### Machine Control

1. **-pcip**
IPv4-adres van Production Control.

2. **-machine_id**
Het ID van de door Machine Control aangestuurde machine.

### Production Control

1. **Argument 0: Configuratielocatie**
Locatie van de configuratie om in te stellen.
