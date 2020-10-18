//  inside 演算子
//  動作確認したシミュレータ
//    * Aldec Riviera Pro
//    * Cadence Xcelium
//    * Mentor Questa
//    * Synopsys VCS
module top;
  logic [3:0] v;
  logic [3:0] result;

  initial begin
    for (int i = 0;i < 16;++i) begin
      v         = i;
      result[0] = v inside {0, 1, 2, 3, 8, 9, 10, 11};  //  複数の比較値
      result[1] = v inside {4'b00??, 4'b10??};          //  ワイルドカード
      result[2] = v inside {[0:3], [8:11]};             //  範囲比較
      result[3] = v inside {0, 1, 4'b001?, [8:11]};     //  合わせ技
      $display("v = %b result = %b", v, result);
    end
    $finish;
  end
endmodule
