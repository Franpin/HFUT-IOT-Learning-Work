// ALU A����˿�ǰ��ѡһѡ����ʵ��
// @param A ����1
// @param B ����2
// @param Control ѡ�����Ŀ����ź�
// @param Result ���
module DataSelector_2to1_sa(A, B, Control, Result);
  input [31:0] A;
  input [4:0] B;
  input Control;
  output [31:0] Result;
  assign Result = (Control == 1'b0 ? A : {{27{0}}, B[4:0]});
endmodule