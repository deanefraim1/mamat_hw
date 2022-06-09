#!/bin/bash
chmod +x firewall.sh

if [ "$#" -ne 1 ]; then
    exit
fi

cat > packets.txt

cat $1 | grep -E -o '^[^#]*' | sort -u > rules.txt

while read -r curr_line; do

    IFS=',' read -r -a sub_rules <<< "$curr_line"
    
    cat packets.txt | \
    ./firewall.exe "${sub_rules[0]}" | \
    ./firewall.exe "${sub_rules[1]}" | \
    ./firewall.exe "${sub_rules[2]}" | \
    ./firewall.exe "${sub_rules[3]}" >> passed_packets.txt

done < rules.txt

cat passed_packets.txt | sort -u | grep -v "^[[:space:]]*$" | tr -d " \t"

rm passed_packets.txt rules.txt
