interface parameterized_mux #(
  parameter type  DATA    = logic,
  parameter int   ENTRIES = 2,
  parameter bit   ONEHOT  = 1
);
  localparam  int SELECT_WIDTH  = (ONEHOT) ? ENTRIES : $clog2(ENTRIES);

  if (ONEHOT) begin : g
    function automatic DATA __mux(
      logic [ENTRIES-1:0] select,
      DATA  [ENTRIES-1:0] data
    );
      DATA  out;

      for (int i = 0;i < $bits(DATA);++i) begin
        logic [ENTRIES-1:0] temp;

        for (int j = 0;j < ENTRIES;++j) begin
          temp[j] = select[j] & data[j][i];
        end

        out[i]  = |temp;
      end

      return out;
    endfunction
  end
  else begin : g
    function automatic DATA __mux(
      logic [$clog2(ENTRIES)-1:0] select,
      DATA  [ENTRIES-1:0]         data
    );
      return data[select];
    endfunction
  end

  function automatic DATA mux(
    logic [SELECT_WIDTH-1:0]  select,
    DATA  [ENTRIES-1:0]       data
  );
    return g.__mux(select, data);
  endfunction
endinterface

module top;
  logic [3:0][1:0]  data;
  logic [3:0]       onehot_select;
  logic [1:0]       onehot_out;
  logic [1:0]       binary_select;
  logic [1:0]       binary_out;

  parameterized_mux #(logic [1:0], 4, 1)  u_onehot_mux();
  parameterized_mux #(logic [1:0], 4, 0)  u_binary_mux();

  initial begin
    data[0] = 3;
    data[1] = 2;
    data[2] = 1;
    data[3] = 0;

    for (int i = 0;i < 4;++i) begin
      onehot_select = 1 << i;
      onehot_out    = u_onehot_mux.mux(onehot_select, data);
      $display("onehot_select: %b, onehot_out: %0d", onehot_select, onehot_out);
    end

    for (int i = 0;i < 4;++i) begin
      binary_select = i;
      binary_out    = u_binary_mux.mux(binary_select, data);
      $display("binary_select: %b, binary_out: %0d", binary_select, binary_out);
    end

    $finish;
  end
endmodule
