module top
  (
   input  logic        clk,
   input  logic        reset_l,

   output logic [7:0]  out_data,
   input  logic        load,
   input  logic [7:0]  in_data
   );

   always_ff @(posedge clk) begin
      if(reset_l == 1'b0)
         out_data <= 8'h00;
      else if(load)
         out_data <= in_data;
      else
         out_data <= out_data + 1'b1;
   end

endmodule