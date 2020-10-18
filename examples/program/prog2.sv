// $ iverilog -g2012 prog2.sv
// $ ./a.out
//

interface and_port_if
  #(
    parameter N = 4
  );
  logic [N-1:0] a, b, c;

  modport dut(
    input  a, b,
    output c
  );
  
  modport tb(
    output a, b,
    input  c
  );

endinterface : and_port_if

module tb ;

  parameter N = 4;

  and_port_if port();
  
  assign_and #( .N(N) ) u0( .a(port.a), .b(port.b), .c(port.c) );

  prog1 #( .N(N) ) u1( .a(port.a), .b(port.b), .c(port.c) );

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
