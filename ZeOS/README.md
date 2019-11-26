# README

## instruccions git

1. Descarregar el codi al teu pc:

```git clone https://github.com/nilquera/SOA.git```

2. Fer els canvis que vulguis als fitxers

3. Un cop fets els canvis s'ha de fer commit. Es fa en dos passos: add + commit:

```git add .``` --> Prepara tots(.) els fitxers canviats per a ser commitejats.

```git commit -m "missatge"``` --> Fa commit d'allò que previament li has fet add.

4. El commit del punt 3 està fet al teu PC, per tant jo no puc veure el canvis fins que no facis "upload" dels canvis a github. Fer upload és fer un push.

```git push origin master``` --> origin és el nom que identifica al repositori de github i master és la branca

(Abans et demanarà que facis `git --global user.name "nom"` i `git --global user.email "email"`)