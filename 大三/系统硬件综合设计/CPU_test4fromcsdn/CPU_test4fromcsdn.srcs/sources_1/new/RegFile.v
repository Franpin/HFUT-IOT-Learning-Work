// �Ĵ������ʵ��
// @param rs ��������Դ1���ڵļĴ�����
// @param rt ��������Դ2���ڵļĴ�����
// @param rd ����洢�ļĴ�����
// @param i_data ���������
// @param RegWre ����Ĵ�����Ŀ����ź�
// @param clk ʱ���ź�
// @param o_data_1 �������1
// @param o_data_2 �������2
module RegFile (rs, rt, rd, i_data, RegWre, clk, o_data_1, o_data_2);
  input [4:0] rs, rt, rd;
  input [31:0] i_data;
  input RegWre, clk;
  output [31:0] o_data_1, o_data_2;
  reg [31:0] register [0:31];
  initial begin
   // ֻ��Ҫȷ����żĴ�����ֵ�ͺã�$0�����0
    register[0] = 0;
  end
  assign o_data_1 = register[rs];
  assign o_data_2 = register[rt];
  always @(i_data or rd) begin
   // rd != 0 ��ȷ����żĴ�������ı������
    if ((rd != 0) && (RegWre == 1)) begin
      register[rd] = i_data;
    end
  end
endmodule