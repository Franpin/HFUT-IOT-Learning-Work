// pc��ת�����ӳ���
// @param pc ִ�и�ָ��ʱpc��ֵ
// @param i_addr ����ĵ�ַ
// @param o_addr ����ĵ�ַ

module PCJump(pc, i_addr, o_addr);
  input [31:0] pc;
  input [25:0] i_addr;
  output reg[31:0] o_addr;
  reg [27:0] mid; // ���ڴ���м�ֵ
  // �����ַ��ǰ��λ����pc[31:28]���м�26λ����i_addr[27:2], ����λ��0
  always @(i_addr) begin
     mid = i_addr << 2;
     o_addr <= {pc[31:28], mid[27:0]};
  end
endmodule