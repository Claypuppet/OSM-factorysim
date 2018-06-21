# Productiestraat simulatie

## Installatie

1. Installeer cmake (minimum version 3.5) en zorg er voor dat deze werkt in
de terminal.

2. Maak een directory voor de gecompileerde binaries, standaard 'bin' en navigeer hierheen.
`mkdir bin`
`cd bin`

3. Genereer de makefiles, gebruik de extra args voor het instellen van
(niet-standaard) boost en wxwidget directories. (TODO: exacte args opzoeken)
`cmake .. [--extra args]`

4. Build de applicatie(s)
`make`

Nu staan de binaries in de bin directory.

## Applicaties

Elke applicatie en testapplicatie staat in een eigen subdirectory (Machine Control, Production Control en Visualiser).

Voor het uitvoeren van een simulatie over TCP/IP dient Production Control als eerste te worden opgestart.

## Argumenten

### Machine Control

De argumenten voor Machine Control zijn alleen van toepassing op een simulatie via TCP/IP.

2. **-machine_id**
Het ID van de door Machine Control aangestuurde machine.
Voorbeeld: ./app_machine_control -machine_id=3

1. **-pcip** (optional)
IPv4-adres van Production Control. Deze staat standaard op 'localhost'
Voorbeeld: ./app_machine_control -pcip=192.168.1.42


### Production Control

1. **Argument 0: Configuratielocatie**
Locatie van de configuratie om in te stellen.
Voorbeeld: ./app_production_control ./config_files/example.yaml

## Scripts

### Gebruikerscripts

1. **Config generator**
Gebruik het configgenerator script, script.py, om via de machines ingesteld in configs.yaml
een configuratiebestand te genereren. Om machines toe te voegen, aan te passen of te verwijderen,
bewerk het configs.yaml bestand.

### Developmentscripts

1. **adviesrapport**
Script voor het berekenen van resultaten die gebruikt worden in adviesrapport hoofdstuk 7.
Maakt gebruik van de statistics.json en used_config.yaml die gegenereerd worden door het uitvoeren
van een simulatie.

2. **simulations.sh**
Een shellscript voor het uitvoeren van meerdere configuraties achter elkaar.
