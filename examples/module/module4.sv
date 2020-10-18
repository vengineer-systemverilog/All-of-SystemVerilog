// $ iverilog -g2012 test_module4.sv
// $ ./a.out
//

module tb;
  localparam N = 4;

  logic [N-1:0] a, b, c;

  test_module4 #(.N(N)) u0( .* );

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

module test_module4
#(
  parameter N = 1
)
(
  input  logic [N-1:0] a, b,
  output logic [N-1:0] c
);

  assign c = a & b;

endmodule : test_module4
