FILE="${1%.*}"

bdp $FILE.py -o $FILE.png -p -c -r 300
# CONVERT OPTIONS: -density 600x600 -resize 1080x800
# convert -density 300 $FILE.png -quality 90  $FILE.png
convert $FILE.png -bordercolor white -border 0x0 $FILE.png
subl $FILE.png
# zathura $FILE.pdf
# display $FILE.png