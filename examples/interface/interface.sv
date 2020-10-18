//  interface 使用例
//  動作確認したシミュレータ
//    * Aldec Riviera Pro
//    * Cadence Xcelium
//    * Mentor Questa
//    * Synopsys VCS
interface foo_if #(parameter int W = 1);
  typedef logic [W-1:0] foo_type;

  logic     valid;
  logic     ready;
  foo_type  foo;

  function automatic logic ack();
    return valid && ready;
  endfunction

  modport master (
    output  valid,
    input   ready,
    output  foo,
    import  ack
  );

  modport slave (
    input   valid,
    output  ready,
    input   foo,
    import  ack
  );

  modport monitor (
    input   valid,
    input   ready,
    input   foo,
    import  ack
  );
endinterface

module foo_master (
  input var     i_clk,
  input var     i_rst_n,
  foo_if.master master_if
);
  typedef master_if.foo_type  foo_type;

  logic     valid;
  foo_type  foo;

  always_comb begin
    master_if.valid = valid;
    master_if.foo   = foo;
  end

  always_ff @(posedge i_clk, negedge i_rst_n) begin
    if (!i_rst_n) begin
      valid <= '0;
      foo   <= '0;
    end
    else if ((!valid) || master_if.ack()) begin
      valid <= $urandom_range(0, 1);
      foo   <= $urandom_range(0, (2**$bits(foo_type) - 1));
    end
  end
endmodule

module foo_slave (
  input var     i_clk,
  input var     i_rst_n,
  foo_if.slave  slave_if
);
  logic ready;

  always_comb begin
    slave_if.ready  = ready;
  end

  always_ff @(posedge i_clk, negedge i_rst_n) begin
    if (!i_rst_n) begin
      ready <= '0;
    end
    else begin
      ready <= $urandom_range(0, 1);
    end
  end
endmodule

module foo_monitor (
  foo_if.monitor  monitor_if
);
  timeunit  1ns;

  always_comb begin
    if (monitor_if.ack()) begin
      $display("%t foo: %b", $time, monitor_if.foo);
    end
  end
endmodule

module top;
  timeunit  1ns/1ps;

  logic clk;
  initial begin
    clk = 0;
    forever #(500ps) begin
      clk ^= 1;
    end
  end

  logic rst_n;
  initial begin
    rst_n = 0;
    repeat (10) @(posedge clk);
    rst_n = 1;
  end

  foo_if #(4) fooif();

  foo_master u_master (clk, rst_n, fooif);
  foo_slave u_slave (clk, rst_n, fooif);
  foo_monitor u_monitor (fooif);

  initial begin
    repeat (10) begin
      do begin
        @(posedge clk);
      end while (!fooif.ack());
    end
    $finish;
  end
endmodule
