// $ iverilog -g2012 test_module3.sv
// $ ./a.out
//

module tb;

  logic a, b, c;

  test_module3 u0( .* );

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

module test_module3(
  input  logic a, b,
  output logic c
);

  assign c = a & b;

endmodule : test_module3
