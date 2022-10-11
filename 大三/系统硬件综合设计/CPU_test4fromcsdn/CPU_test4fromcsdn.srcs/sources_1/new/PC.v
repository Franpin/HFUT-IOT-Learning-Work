// PCģ���ʵ��
// @param clk ʱ���ź�
// @param pcWre�ź�
// @param reset�ź�
// @param i_pc �����pcֵ
// @param o_pc �����pcֵ
// @param outside_pc ???
module PC(clk, i_pc, pcWre, reset, outside_pc, o_pc);
  input wire clk, pcWre, reset;
  input wire [31:0] i_pc, outside_pc;
  output reg [31:0] o_pc;
  always @(pcWre or reset) begin // ����͵����ڲ�̫һ���������ӳٵ����⣬ֻ�е�pcWre�ı��ʱ�����reset�ı��ʱ���ټ��
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
