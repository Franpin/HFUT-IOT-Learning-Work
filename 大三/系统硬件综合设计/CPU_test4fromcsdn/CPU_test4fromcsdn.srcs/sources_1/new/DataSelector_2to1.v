// 二选一数据选择器实现
// @param A 输入1
// @param B 输入2
// @param Control 选择器的控制信号
// @param Result 结果
module DataSelector_2to1(A, B, Control, Result);
  input [31:0] A, B;
  input Control;
  output [31:0] Result;
  assign Result = (Control == 1'b0 ? A : B);
endmodule
