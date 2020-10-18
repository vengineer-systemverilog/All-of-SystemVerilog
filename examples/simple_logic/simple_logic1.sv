// $ iverilog -g2012 simple_logic1.sv
// $ ./a.out
//
module simple_logic1;

  logic a, b, c_and, c_or, c_nand, c_nor, c_xor, c_xnor, a_not;

  assign c_and  = a & b;
  assign c_or   = a | b;
  assign c_nand = ~(a & b);
  assign c_nor  = ~(a | b);
  assign c_xor  = a ^ b;
  assign c_xnor = ~(a ^ b);
  assign a_not  = ~a;

  initial begin
    $monitor("%t : a(%b), b(%b) => c_and(%b), c_or(%b), c_nand(%b), c_nor(%b), c_xor(%b), c_xnor(%b), a_not(%b)", 
             $time, a, b, c_and, c_or, c_nand, c_nor, c_xor, c_xnor, a_not);

    a <= 0;
    b <= 1;
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

endmodule : simple_logic1
