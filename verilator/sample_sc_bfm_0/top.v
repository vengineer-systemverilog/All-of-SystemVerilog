`ifdef VERILATOR
module top
`else
module Vtop
`endif
(
    input  logic        clk,
    input  logic        reset,

    /* verilator lint_off UNUSED */
    input  logic [15:0] addr,
    /* verilator lint_on UNUSED */
    input  logic        cs,
    input  logic        rw,
    input  logic [31:0] data_in,
    output logic        ready,
    output logic [31:0] data_out
    );

    localparam ram_size = (17'h10000>>2);
    /* verilator lint_off WIDTH */
    logic [31:0] ram[ram_size];
    /* verilator lint_on WIDTH */

    enum {STATE_IDLE, STATE_RUN, STATE_DONE} state;

    always_ff @(posedge clk) begin
        if(reset == 1'b1)
            state <= STATE_IDLE;
        else if(cs == 1'b1 && state == STATE_IDLE)
            state <= STATE_RUN;
        else if(cs == 1'b1 && state == STATE_RUN)
            state <= STATE_DONE;
        else if(cs == 1'b0)
            state <= STATE_IDLE;
    end

    always_ff @(posedge clk) begin
        if(reset == 1'b1) begin
            data_out <= 32'h0000_0000;
            ready    <= 1'b0;
        end
        else if(state == STATE_RUN) begin
            if(rw == 1'b1)
                data_out <= ram[addr[15:2]];
            else
                ram[addr[15:2]] <= data_in;
            ready    <= 1'b1;
        end 
        else begin
            data_out <= 32'h0000_0000;
            ready    <= 1'b0;
        end
    end

endmodule
