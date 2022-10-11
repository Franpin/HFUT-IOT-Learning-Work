// PC模块的实现
// @param clk 时钟信号
// @param pcWre信号
// @param reset信号
// @param i_pc 输入的pc值
// @param o_pc 输出的pc值
// @param outside_pc ???
module PC(clk, i_pc, pcWre, reset, outside_pc, o_pc);
  input wire clk, pcWre, reset;
  input wire [31:0] i_pc, outside_pc;
  output reg [31:0] o_pc;
  always @(pcWre or reset) begin // 这里和单周期不太一样，存在延迟的问题，只有当pcWre改变的时候或者reset改变的时候再检测
   // reset
    if (reset) begin
      o_pc = outside_pc;
    end else if (pcWre) begin
      o_pc = i_pc;
    end else if (!pcWre) begin 
        o_pc = o_pc;
     end
  end
endmodule
