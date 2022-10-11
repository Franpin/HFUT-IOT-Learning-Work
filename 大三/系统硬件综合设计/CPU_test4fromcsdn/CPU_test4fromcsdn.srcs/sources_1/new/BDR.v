// 切割数据通路
// @param i_data 输入的数据
// @param o_data 输出的数据
// @param clk 时钟信号
module BDR(i_data, clk, o_data);
  input clk;
  input [31:0] i_data;
  output reg[31:0] o_data;
  always @(posedge clk) begin
    o_data = i_data;
  end
endmodule