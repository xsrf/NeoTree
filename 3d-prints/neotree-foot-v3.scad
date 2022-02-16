$usbh = 4.7;
$pcbt = 1.6;
difference() {
    translate([0,1.5,0]) hull() {
        cylinder(r=10,h=2,$fn=64);
        cylinder(r=9,h=3,$fn=64);
    }
    //translate([0,0,10/2+0.25])cube([16,$pcbt,10],center=true);
    cube([16,$pcbt,20],center=true);
    #translate([0,$usbh/2-$pcbt/2])cube([8.5,$usbh,20],center=true);
    translate([0,-0.5,0]) difference() {
        cube([16,$pcbt,20],center=true);
        cube([2,2,20],center=true);
    }
    
    // Flex split
    translate([0,-2.5,0]) cube([15,0.5,20],center=true);
    
    // Battery Case Stand Cutout
    translate([0,$pcbt/2+5.5,20/2+0.25]) cube([9,2.4,20],center=true);
}

translate([0,0,0.25/2]) difference() {
    cube([16,3,0.25],center=true);
    cube([13,3,5],center=true);
}