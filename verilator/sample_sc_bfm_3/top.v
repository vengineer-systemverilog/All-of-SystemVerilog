module top
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

    /* verilator lint_off WIDTH */
    logic [31:0] ram[ram_size]; 
    /* verilator lint_on WIDTH */

    export "DPI-C" function direct_read;
    export "DPI-C" function direct_write;
    import "DPI-C" context function void sc_stop_for_hdl();

    function automatic void address_check(input int addr_);
        if((addr_>>2)>ram_size) begin
            $display("write, address range error at %h", addr_);
            sc_stop_for_hdl();
        end

        if((addr_ & 32'h3) != 32'h0) begin
            $display("write, address boundary error at %h", addr_);
            sc_stop_for_hdl();
            
        end
    endfunction : address_check
    
    function int direct_read(input int addr_);
        int data_;
        address_check(addr_);
        data_ = ram[addr_>>2];
        return data_;
    endfunction : direct_read

    function void direct_write(input int addr_, input int data_);
        address_check(addr_);
        ram[addr_>>2] = data_;
    endfunction : direct_write

endmodule
