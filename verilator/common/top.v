// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2003 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
// ======================================================================

// This is intended to be a complex example of several features, please also
// see the simpler examples/make_hello_c.

`timescale 100ps/1ps

module top
  (
   // Declare some signals so we can see how I/O works
   input  logic        clk,
   input  logic        reset_l,

   output logic [7:0]  out_data,
   input  logic        load,
   input  logic [7:0]  in_data
   );

   always_ff @(posedge clk) begin
      if(reset_l == 1'b0)
         out_data <= 8'h00;
      else if(load) begin
         out_data <= in_data;
      end 
      else begin
         out_data <= out_data + 1'b1;
      end
   end

endmodule
