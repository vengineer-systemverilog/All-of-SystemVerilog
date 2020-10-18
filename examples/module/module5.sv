// $ iverilog -g2012 test_module5.sv
// $ ./a.out
//

package my_pkg;
  parameter N = 8;
endpackage : my_pkg

module tb;

  import my_pkg::*;

  logic [N-1:0] a, b, c;

  test_module5 #(.N(N)) u0( .* );

  initial begin
    $monitor("%t : a(%b), b(%b) => c(%b)", 
             $time, a, b, c);

    a <= 0;
    b <= 0;
    #10;
    a <= {N{1'b1}};
    #10;
    a <= 0;
    b <= {N{1'b1}};
    #10;
    a <= {N{1'b1}};
    #10;
    $finish(2);
  end

endmodule : tb

module test_module5
#(
  parameter N = 1
)
(
  input  logic [N-1:0] a, b,
  output logic [N-1:0] c
);

  assign c = a & b;

endmodule : test_module5
