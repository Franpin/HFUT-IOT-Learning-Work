// ������ʱ�洢ָ��Ķ�������ʽ
// @param i_data ���������
// @param clk ʱ���ź�
// @param IRWre ����IR�Ŀ����ź�
// @param o_data ���������
module IR(i_data, clk, IRWre, o_data);
  input clk, IRWre;
  input [31:0] i_data;
  output reg[31:0] o_data;
  always @(negedge clk) begin // �����ӳٵ����⣬�������½��ش����������ݴ���û��ʲôӰ��
    if (IRWre) begin
        o_data = i_data;
     end
  end
endmodule
