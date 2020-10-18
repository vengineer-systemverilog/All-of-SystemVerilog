// $ iverilog -g2012 prog1.sv
// $ ./a.out
//

module tb ;

  parameter N = 4;

  logic [N-1:0] a, b, c;

  assign_and #( .N(N) ) u0( .* );

  prog1 #( .N(N) ) u1( .* );

endmodule : tb

program prog1
#(
  parameter N = 1
)
(
  output logic [N-1:0] a, b,
  input  logic [N-1:0] c
);

  initial begin
    $monitor("%t : a(%b), b(%b) => c(%b)", 
             $time, a, b, c);

    a = 0;
    b = 0;
    #10;
    a = {N{1'b1}};
    #10;
    a = 0;
    b = {N{1'b1}};
    #10;
    a = {N{1'b1}};
    #10;
    $finish(2);
  end

  final begin
    $display("finish final");
  end

endprogram : prog1

module assign_and
#(
  parameter N = 1
)
(
  input  logic [N-1:0] a, b,
  output logic [N-1:0] c
);

  assign c = a & b;

endmodule : assign_and
