// ������չ��Ԫ��ʵ��
// @param i_num ���������
// @param ExtSel ���Ʒ�����չ��Ԫ���ź�
// @param o_num ���������
module SignExtend(i_num, ExtSel, o_num);
  input [15:0] i_num;
  input [1:0] ExtSel;
  output reg[31:0] o_num;
  initial begin
    o_num = 0;
  end
  always @(i_num or ExtSel) begin
     case(ExtSel)
        // ExtSel Ϊ00ʱ��saλ��չ
        2'b00: o_num <= {{27{0}}, i_num[10:6]};
        // ExtSel Ϊ01ʱ���޷�����������չ
        2'b01: o_num <= {{16{0}}, i_num[15:0]};
        // ExtSel Ϊ10ʱ���з�����������չ
        2'b10: o_num <= {{16{i_num[15]}}, i_num[15:0]};
        // �������Ĭ���з�����������չ
        default: o_num <= {{16{i_num[15]}}, i_num[15:0]}; // Ĭ�Ϸ�����չ
    endcase
  end
endmodule