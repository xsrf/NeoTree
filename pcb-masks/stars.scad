variant = 1;
sc = 0.5;
scale([sc,sc]) {
    if(variant==1) star1(4,5,0.2);
    if(variant==2) star1(4,5,0.4);
    if(variant==3) star1(4,4,0.2);
    if(variant==4) star1(4,4,0.17);
    if(variant==4) star1(3,8,0.17);
    if(variant==5) star1(4,8,0.15);
}



module star1($r = 10, $n = 5, $s = 0.5) {
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