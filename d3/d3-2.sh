cat shakespeare.txt | sed -nE 's/^.*\b([A-Z]{3,16})\..*$/\1/p'
