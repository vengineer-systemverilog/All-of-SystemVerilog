//  bind 構文
//  動作確認したシミュレータ
//    * Aldec Riviera Pro
//        * インスタンスを指定する場合の bind はバグを踏む模様
//    * Cadence Xcelium
//    * Mentor Questa
//    * Synopsys VCS
module sub_0 #(
  parameter int W = 1
)(
  input var i_clk,
  input var i_rst_n
);
  logic [W-1:0] v;

  always_ff @(posedge i_clk, negedge i_rst_n) begin
    if (!i_rst_n) v <= 0;
    else          v <= v + 1;
  end
endmodule

module sub_1 #(
  parameter int W = 1
)(
  input var i_clk,
  input var i_rst_n
);
  logic [W-1:0] v;

  always_ff @(posedge i_clk, negedge i_rst_n) begin
    if (!i_rst_n) v <= 0;
    else          v <= v - 1;
  end
endmodule

module monitor #(
  parameter int W = 1
)(
  input var [W-1:0] i_v
);
  always_comb begin
    $display("%t %m v = %0d", $time, i_v);
  end
endmodule

module top;
  timeunit  1ns/1ps;

  bit clk;
  initial begin
    clk = 0;
    forever #(500ps) begin
      clk ^= 1;
    end
  end

  bit rst_n;
  initial begin
    rst_n = 0;
    repeat (10) @(posedge clk);
    rst_n = 1;
  end

  sub_0 #(2)  u_sub_0_0 (clk, rst_n);
  sub_0 #(4)  u_sub_0_1 (clk, rst_n);
  sub_1 #(2)  u_sub_1_0 (clk, rst_n);
  sub_1 #(4)  u_sub_1_1 (clk, rst_n);

  //  module 一括で bind
  bind sub_0
  monitor #(W) u_monitor (v);

  //  instnace を指定して bind
  bind u_sub_1_0
  monitor #(W) u_monitor (v);

  initial begin
    repeat (32) @(posedge clk);
    $finish;
  end
endmodule
