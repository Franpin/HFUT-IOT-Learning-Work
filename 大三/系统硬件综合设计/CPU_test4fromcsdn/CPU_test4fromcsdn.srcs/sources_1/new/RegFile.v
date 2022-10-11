// 寄存器组的实现
// @param rs 输入数据源1所在的寄存器号
// @param rt 输入数据源2所在的寄存器号
// @param rd 结果存储的寄存器号
// @param i_data 输入的数据
// @param RegWre 输入寄存器组的控制信号
// @param clk 时钟信号
// @param o_data_1 输出数据1
// @param o_data_2 输出数据2
module RegFile (rs, rt, rd, i_data, RegWre, clk, o_data_1, o_data_2);
  input [4:0] rs, rt, rd;
  input [31:0] i_data;
  input RegWre, clk;
  output [31:0] o_data_1, o_data_2;
  reg [31:0] register [0:31];
  initial begin
   // 只需要确定零号寄存器的值就好，$0恒等于0
    register[0] = 0;
  end
  assign o_data_1 = register[rs];
  assign o_data_2 = register[rt];
  always @(i_data or rd) begin
   // rd != 0 是确保零号寄存器不会改变的作用
    if ((rd != 0) && (RegWre == 1)) begin
      register[rd] = i_data;
    end
  end
endmodule