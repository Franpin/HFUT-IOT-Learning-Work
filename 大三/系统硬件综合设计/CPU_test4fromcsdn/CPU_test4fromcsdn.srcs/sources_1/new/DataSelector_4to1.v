// 四选一数据选择器的实现
// @param A 输入1
// @param B 输入2
// @param C 输入3
// @param D 输入4
// @param Control 数据选择器的控制信号
// @param Result 选择的结果
module DataSelector_4to1(A, B, C, D, Control, Result);
  input [31:0] A, B, C, D;
  input [1:0]Control;
  output reg[31:0] Result;
  always @(Control or A or B or C or D) begin
    case(Control)
        2'b00: Result = A;
        2'b01: Result = B;
        2'b10: Result = C;
        2'b11: Result = D;
        default: Result = 0;
     endcase
  end
endmodule