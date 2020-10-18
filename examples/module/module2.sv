// $ iverilog -g2012 test_module2.sv
// $ ./a.out
//

module tb;

  logic a, b, c;

  test_module2 u0( .a, .b, .c );

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

module test_module2(
  input  logic a, 
  input  logic b,
  output logic c
);

  assign c = a & b;

endmodule : test_module2
