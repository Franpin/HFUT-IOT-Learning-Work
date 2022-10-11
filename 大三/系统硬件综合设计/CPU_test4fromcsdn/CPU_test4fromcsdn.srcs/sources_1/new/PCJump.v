// pc跳转调用子程序
// @param pc 执行该指令时pc的值
// @param i_addr 输入的地址
// @param o_addr 输出的地址

module PCJump(pc, i_addr, o_addr);
  input [31:0] pc;
  input [25:0] i_addr;
  output reg[31:0] o_addr;
  reg [27:0] mid; // 用于存放中间值
  // 输出地址的前四位来自pc[31:28]，中间26位来自i_addr[27:2], 后两位是0
  always @(i_addr) begin
     mid = i_addr << 2;
     o_addr <= {pc[31:28], mid[27:0]};
  end
endmodule