module top
  (
  input  logic   clk,

  input  logic   tms,
  input  logic   tck,
  input  logic   trstn,
  input  logic   tdi,
  output logic   tdo
  );

  jtag u0( .* );

endmodule : top

