#!/bin/bash

chmod +x news_scrape

wget https://www.ynetnews.com/category/3082

grep -E -o "https://www.ynetnews.com/article/[a-zA-Z0-9]{9}" 3082>articles_urls

rm 3082

uniq articles_urls articles_urls_uniq

rm articles_urls

articles_num=$(wc -l < articles_urls_uniq)

echo "Total articles: "$articles_num > results.csv

while IFS= read -r line; do

    wget -O curr_website $line

    grep -o "Netanyahu" curr_website > bibi_freq

    bibi_times=$(wc -w < bibi_freq)

    grep -o "Bennett" curr_website > bennett_freq

    bennett_times=$(wc -w < bennett_freq)
    
    if [ $bibi_times == 0 ] && [ $bibi_times == 0 ]; then
        echo ",,,-," $line >> results.csv
    else
echo $bennett_times ",Bennett," $bibi_times ",Netanyahu," $line >> results.csv
    fi
    
    rm curr_website
    rm bibi_freq
    rm bennett_freq

done < articles_urls_uniq

rm articles_urls_uniq
