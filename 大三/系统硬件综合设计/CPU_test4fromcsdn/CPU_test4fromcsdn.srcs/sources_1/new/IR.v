// 用于临时存储指令的二进制形式
// @param i_data 输入的数据
// @param clk 时钟信号
// @param IRWre 输入IR的控制信号
// @param o_data 输出的数据
module IR(i_data, clk, IRWre, o_data);
  input clk, IRWre;
  input [31:0] i_data;
  output reg[31:0] o_data;
  always @(negedge clk) begin // 存在延迟的问题，所以用下降沿触发，对数据传输没有什么影响
    if (IRWre) begin
        o_data = i_data;
     end
  end
endmodule
