// PC ��������
// @param now_pc  ��ǰpcֵ
// @param o_pc ���pcֵ
// @param imm ������
module PCAddImm(now_pc, imm, o_pc);
  input [31:0] now_pc, imm;
  output [31:0] o_pc;
  // �ڴ浥Ԫ�����ֽ�Ϊ��λ�ģ�32λ��ַ��СΪ4���ֽڣ�����pc=pc+imm*4
  assign o_pc = now_pc + (imm << 2);
endmodule
