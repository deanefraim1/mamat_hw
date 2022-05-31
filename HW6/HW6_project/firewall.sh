#!/bin/bash
chmod +x firewall.sh

if [ "$#" -ne 1 ]; then
    exit
fi

packets="$(</dev/stdin)"

cat $1 | grep -o '^[^#]*' | sort -u > rules.txt

while read -r curr_line; do

    IFS=',' read -r -a field <<< "$curr_line"
    
    
    
    echo "$packets" | ./firewall.exe "${curr_line[0]}" | \
    ./firewall.exe "${curr_line[1]}" | \
    ./firewall.exe "${curr_line[2]}" | \
    ./firewall.exe "${curr_line[4]}" > passed_packets.txt

done < rules

cat passed_packets.txt | sort -u

rm rules.txt passed_packets.txt

