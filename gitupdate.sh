#!/bin/bash
now="$(date +'%d/%m/%Y')"
now2="$(date +'%r')"
cd /home/coldragon/Documents/Programmation/Bobs_tower
git add .
git commit -m "Commit le $now a $now2"
git push -u origin master