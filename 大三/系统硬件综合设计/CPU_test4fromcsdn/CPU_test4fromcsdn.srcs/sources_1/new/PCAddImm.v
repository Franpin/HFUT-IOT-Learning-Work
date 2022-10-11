// PC 加立即数
// @param now_pc  当前pc值
// @param o_pc 输出pc值
// @param imm 立即数
module PCAddImm(now_pc, imm, o_pc);
  input [31:0] now_pc, imm;
  output [31:0] o_pc;
  // 内存单元是以字节为单位的，32位地址大小为4个字节，所以pc=pc+imm*4
  assign o_pc = now_pc + (imm << 2);
endmodule
