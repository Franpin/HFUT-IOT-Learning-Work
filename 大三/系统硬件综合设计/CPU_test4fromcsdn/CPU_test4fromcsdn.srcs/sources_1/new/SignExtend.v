// 符号扩展单元的实现
// @param i_num 输入的数据
// @param ExtSel 控制符号扩展单元的信号
// @param o_num 输出的数据
module SignExtend(i_num, ExtSel, o_num);
  input [15:0] i_num;
  input [1:0] ExtSel;
  output reg[31:0] o_num;
  initial begin
    o_num = 0;
  end
  always @(i_num or ExtSel) begin
     case(ExtSel)
        // ExtSel 为00时，sa位扩展
        2'b00: o_num <= {{27{0}}, i_num[10:6]};
        // ExtSel 为01时，无符号立即数扩展
        2'b01: o_num <= {{16{0}}, i_num[15:0]};
        // ExtSel 为10时，有符号立即数扩展
        2'b10: o_num <= {{16{i_num[15]}}, i_num[15:0]};
        // 其它情况默认有符号立即数扩展
        default: o_num <= {{16{i_num[15]}}, i_num[15:0]}; // 默认符号扩展
    endcase
  end
endmodule