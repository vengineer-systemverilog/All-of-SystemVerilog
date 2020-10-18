module jtag(

  input  logic tms,
  input  logic tck,
  input  logic trstn,
  input  logic tdi,
  output logic tdo
  
);

  assign tdo = tdi;

endmodule : jtag