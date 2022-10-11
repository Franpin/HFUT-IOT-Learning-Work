// 实现PC递增
// @param i_pc 输入的pc值
// @param o_pc 输出的pc值
module PCAddFour(i_pc, o_pc);
  input wire [31:0] i_pc;
  output wire [31:0] o_pc;
  assign o_pc[31:0] = i_pc[31:0] + 4;
endmodule