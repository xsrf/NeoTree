$gr = 1.61803398875;
$fn = 20;

$w = 1.0;
$gap = 0.07;
$h1 = 9; // inner height of box
$h2 = 4;
$t = 0.8;

difference() {
    linear_extrude($h1+$t) offset($w) pos();
    translate([0,0,$t]) linear_extrude($h1+$t) pos();
}

scale([1,-1,1]) translate([70,90,0]) difference() {
    linear_extrude($h2+$t) offset($w+$w+$gap) pos();
    translate([0,0,$t]) linear_extrude($h2+$t) offset($w+$gap) pos();
}


module pos() offset(0.4) hull() scale([5,5]) round_edges(0.1) {
    tree();
    star(2,5,0.4);
    stem();
}

module stem() {
    translate([0,-18]) square([3+2,4],center=true);
}

module tree() {
    $fn = 200;
    translate([0,1,0]) {
        branch(10);
        branch(10*$gr);
        branch(10*$gr*$gr);
    }
}

module tree2() {
    branch(10);
    branch(20);
    branch(30);
}

module branch($r = 20) {
    $o = $r/4;
    difference() {
        translate([0,$o]) circle(r=$r);
        translate([+$r,0]) circle(r=$r);
        translate([-$r,0]) circle(r=$r);
        translate([0,$r]) circle(r=$r);
        //translate([0,-$r/1.5]) circle(1);
    }
}



module star($r = 10, $n = 5, $s = 0.5) {
    union() {
        for(i=[0:$n-1]) rotate([0,0,i*(360/$n)]) polygon(points=[[-$r*$s,0],[0,$r],[$r*$s,0]]);
    }
}


module round_edges($r = 0.1) {
    offset(r = -$r) 
        offset(r = 2*$r) 
        offset(r = -$r) 
        children();
}


module stroke_center($t = 1) {
    difference() {
        round_edges(0.5) offset(r = $t/2) children();
        round_edges(0.5) offset(r = -$t/2) children();
    }
}