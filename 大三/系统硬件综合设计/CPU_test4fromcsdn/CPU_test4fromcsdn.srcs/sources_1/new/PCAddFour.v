// ʵ��PC����
// @param i_pc �����pcֵ
// @param o_pc �����pcֵ
module PCAddFour(i_pc, o_pc);
  input wire [31:0] i_pc;
  output wire [31:0] o_pc;
  assign o_pc[31:0] = i_pc[31:0] + 4;
endmodule