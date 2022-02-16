/* 
    Print: 
    0.25 layer height
    0.42 extrusion width
*/

$bw = 21;
$bl = 53.5;
$ch = 6; // case height (4mm battery + LEDs)
$w = 0.8; // case wall width
$f = 0.5; // case floor thickness


translate([0,19,6]) rotate([0,180,0]) scale([0.254,0.254,0.254]) %import("OBJ_NeoTree PCB.stl");

difference() {
    battery_case();
    battery_case_cutouts();
}

translate([0,-($bl/2+$w),0]) case_foot();

module battery_case() {
    translate([0,0,$ch/2-$f/2]) difference() {
        cube([$bw+2*$w, $bl+2*$w, $ch+$f],center=true);
        translate([0,0,$f]) cube([$bw, $bl, $ch+$f],center=true);
    }
}

module battery_case_cutouts() {
    translate([$bw/2,$bl/2-3.75,$ch]) cube([4,4,$ch],center=true);
    translate([$bw/2,3,$ch]) cube([4,4,$ch],center=true);
    translate([$bw/2,-$bl/2+8,$ch]) cube([4,16,$ch],center=true);

    translate([-$bw/2,$bl/2-5.5,$ch]) cube([4,4,$ch],center=true);
    translate([-$bw/2,2.5,$ch]) cube([4,4,$ch],center=true);
    translate([-$bw/2,-10,$ch]) cube([4,4,$ch],center=true);
    translate([-$bw/2,-19.5,$ch]) cube([4,4,$ch],center=true);

    translate([0,-$bl/2,$ch]) cube([15,4,$ch],center=true);

}

module case_foot() {
    $l = 7.7;
    hull() {
        translate([-4,-$l+1,-$f]) cube([8,$l-1,2]);
        translate([-3,-$l,-$f]) cube([6,$l,2]);
    }
    translate([-2.5,-$l+3,-$f]) cube([5,3,4]);
}