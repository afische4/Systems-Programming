cat shakespeare.txt | sed -nE 's/^\s+\b([A-Z]{3,16})\..*$/\1/p' | sort | uniq -c | sort -nr | head -n 30

