// $ iverilog -g2012 test_module1.sv
// $ ./a.out
//

module tb;

  reg  a, b;
  wire c;

  test_module1 u0( a, b, c );

  initial begin
    $monitor("%t : a(%b), b(%b) => c(%b)", 
             $time, a, b, c);

    a <= 0;
    b <= 0;
    #10;
    a <= 1;
    #10;
    a <= 0;
    b <= 1;
    #10;
    a <= 1;
    #10;
    $finish(2);
  end

endmodule : tb

module test_module1(
  input  wire a,
  input  wire b,
  output wire c
);

  assign c = a & b;

endmodule : test_module1
