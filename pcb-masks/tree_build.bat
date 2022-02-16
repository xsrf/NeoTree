openscad -D "layer=\"outline\"" -o tree_outline.svg tree.scad
openscad -D "layer=\"mask\"" -o tree_mask.svg tree.scad
openscad -D "layer=\"keepout\"" -o tree_keepout.svg tree.scad