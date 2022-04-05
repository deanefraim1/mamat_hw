#!/bin/bash

chmod +x news_scrape

website=https://www.ynetnews.com/article/

wget https://www.ynetnews.com/category/3082 

cat 3082 | grep -E -o "$website[a-zA-Z0-9]{9}" \
| sort | uniq > uniq_art

rm 3082

cat uniq_art | wc -l | sed 's/^ *//g' > results.csv

while IFS= read -r line; do

	wget -O curr_website $line 

	bibi_times=$(grep -o Netanyahu curr_website \
	| wc -w | sed 's/^ *//g')

	bennett_times=$(grep -o Bennett curr_website \
	| wc -w | sed 's/^ *//g')
		
	if (( (($bibi_times==0)) && (($bennett_times==0)) )); then

		echo "$line, -"  >> results.csv
	else 

		echo "$line, Netanyahu, $bibi_times, Bennett, $bennett_times" \
		>> results.csv

	fi
	
	rm curr_website

done < uniq_art

rm uniq_art


