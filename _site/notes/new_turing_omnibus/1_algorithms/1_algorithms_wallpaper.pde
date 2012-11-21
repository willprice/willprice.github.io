float i, j, c;
int s = 5;
float corna = 22;
float cornb = 37;


size(200,200);



for (int x = 0; x < width; x+=s) {
  for (int y = 0; y < height; y+=s) {
    i = corna + x * width/100;
    j = cornb + y * height/100;
    c = i*i + j*j;
    noStroke();
    
    println("i is " + i + " and j is " + j + "i^2  + j^2 is "+c);
    println("i^2 + ^2 mod 2 is: " + c%2);

    if (int(c)%2 == 0) {
      fill(255, 50, 1);
    } 
    else {
      fill(0);
    }

    rect(x, y, x+s, y+s);
  }
}

